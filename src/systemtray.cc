#include "systemtray.h"

#include "activemountwidgetaction.h"
#include "guimessage.h"
#include "hash.h"
#include "logowidgetaction.h"
#include "providersettings.h"
#include "providersettingseditor.h"
#include "settingsmanager.h"

#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QSettings>
#include <QSharedPointer>
#include <QSpinBox>
#include <QStorageInfo>
#include <QTextEdit>
#include <QVBoxLayout>
#include <boost/archive/text_iarchive.hpp>

#include <boost/interprocess/ipc/message_queue.hpp>

#include <iostream>
#include <memory>

SystemTray::SystemTray(QObject *parent) : QObject(parent) {
  createActions();
  createTrayIcon();
}

void SystemTray::show() { trayIcon->show(); }

void SystemTray::hide() { trayIcon->hide(); }

void SystemTray::createActions() {

  onedataLogoAction = new LogoWidgetAction(QString(tr("Oneclient")), this);

  manageProviders = new QAction(tr("Add &provider..."), this);
  QPixmap addProviderPixmap(":add.png");
  QIcon addProviderIcon(addProviderPixmap.scaled(
      QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation));
  manageProviders->setIcon(addProviderIcon);

  connect(manageProviders, &QAction::triggered, []() {
    ProviderSettingsEditor pse;
    if (pse.exec()) {
      ProviderSettings providerSettings = pse.getSettings();
      SettingsManager::addProvider(providerSettings);
    }
  });

  aboutAction = new QAction(tr("&About..."), this);
  connect(aboutAction, &QAction::triggered, this, &SystemTray::showAbout);

  logsAction = new QAction(tr("&Logs..."), this);
  // connect(aboutAction, &QAction::triggered, this, &SystemTray::showAbout);

  quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void SystemTray::updateTrayIconMenu() {

  trayIconMenu->clear();
  trayIconMenu->addAction(onedataLogoAction);
  trayIconMenu->addSeparator();

  auto registeredProviders = SettingsManager::getRegisteredProviders();
  for (auto providerName : registeredProviders) {
    auto ps = SettingsManager::getProviderSettings(providerName);
    if (!ps.isNull()) {
      ActiveMountWidgetAction *providerMenuItem =
          new ActiveMountWidgetAction(*ps);
      trayIconMenu->addAction(providerMenuItem);
      connect(providerMenuItem, &ActiveMountWidgetAction::removeProvider, this,
              &SystemTray::removeProvider);
      connect(providerMenuItem, &ActiveMountWidgetAction::editProvider, this,
              &SystemTray::editProvider);
      connect(providerMenuItem, &ActiveMountWidgetAction::mountUnmountProvider,
              this, &SystemTray::mountUnmountProvider);
    }
  }

  trayIconMenu->addSeparator();
  trayIconMenu->addAction(manageProviders);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(aboutAction);
  trayIconMenu->addAction(logsAction);
  trayIconMenu->addAction(quitAction);
}

void SystemTray::createTrayIcon() {

  trayIconMenu = new QMenu(nullptr);

  trayIcon = new QSystemTrayIcon(nullptr);
  trayIcon->setContextMenu(trayIconMenu);
  trayIcon->setIcon(QIcon(":/onedata-icon.png"));

  connect(trayIcon, &QSystemTrayIcon::activated, this,
          &SystemTray::updateTrayIconMenu);
}

void SystemTray::showAbout() {

  trayIcon->showMessage("ASDASDASD", "asdadsasdasdasdasdas  asd");
  return;

  auto pWindow = new QWidget(nullptr /*qobject_cast<QWidget>(trayIcon)*/);
  pWindow->resize(640, 400);
  pWindow->setStyleSheet("background-color: #BBBBBB");
  pWindow->setWindowModality(Qt::ApplicationModal);

  auto pLayout = new QHBoxLayout(pWindow);
  auto pLogoLabel = new QLabel(pWindow);
  pLogoLabel->setPixmap(QPixmap(":onedata-logo.png")
                            .scaledToWidth(180, Qt::SmoothTransformation));
  pLogoLabel->setScaledContents(false);
  pLayout->addWidget(pLogoLabel);

  auto pAboutLabel = new QLabel(pWindow);

  pAboutLabel->setText(tr(
      "<br>"
      "Oneclient &copy; 2014-2017<br><br>"
      "Oneclient is a command line Onedata client. It provides a POSIX "
      "interface to user's files in onedata system.<br><br>"
      "<a href='https://onedata.org'><span style='text-decoration: underline; "
      "color:#0000ff;'>onedata.org</span></a>"));
  pAboutLabel->setWordWrap(true);
  pAboutLabel->setTextFormat(Qt::RichText);
  pLayout->addWidget(pAboutLabel);

  pWindow->setLayout(pLayout);

  pWindow->show();
  pWindow->setWindowTitle(
      QApplication::translate("oneclient", "About Oneclient..."));
}

void SystemTray::removeProvider(QString providerName) {

  if (SettingsManager::removeProvider(providerName)) {
    std::cout << "Removed provider: " << providerName.toStdString()
              << std::endl;
    updateTrayIconMenu();
    hide();
    show();
  }
}

void SystemTray::mountUnmountProvider(QString providerName) {
  std::cout << "SystemTray::mountUnmountProvider: "
            << providerName.toStdString() << std::endl;

  auto ps = SettingsManager::getProviderSettings(providerName);
  QProcess process;

  foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
    if (storage.isValid() && storage.isReady()) {
      if (storage.rootPath() == ps->mountPath) {
        // Oneclient already mounted at this path
        // unmount
        process.startDetached("/usr/local/bin/oneclient",
                              QStringList() << "-u" << ps->mountPath);
        std::cout << "Oneclient successfully unmounted from "
                  << ps->mountPath.toStdString() << std::endl;
        boost::interprocess::message_queue::remove(
            Hash::hash(ps->mountPath.toStdString()).c_str());
        return;
      }
    }
  }

  std::cout << "Mounting oneclient at " << ps->mountPath.toStdString()
            << "using:\n"
            << ps->buildOneclientCommandLine().join(" ").toStdString()
            << std::endl;

  if (!ps.isNull()) {
    // Create interprocess communication queue for the new oneclient
    // process and pass it to the command line
    std::cout << "Creating interprocess message queue: "
              << Hash::hash(ps->mountPath.toStdString()) << std::endl;

    boost::interprocess::message_queue::remove(
        Hash::hash(ps->mountPath.toStdString()).c_str());
    boost::interprocess::message_queue(
        boost::interprocess::create_only,
        Hash::hash(ps->mountPath.toStdString()).c_str(), 20, 1024);
    auto cql = QSharedPointer<OneclientMessageListener>(
        new OneclientMessageListener(ps->mountPath));

    connect(cql.data(), &OneclientMessageListener::receivedNotification, this,
            &SystemTray::showNotification);
    connect(this, &SystemTray::showMessage, trayIcon,
            &QSystemTrayIcon::showMessage);

    clientMessageQueueListeners.insert(ps->mountPath, cql);
    cql->start();

    process.startDetached("/usr/local/bin/oneclient",
                          ps->buildOneclientCommandLine());
  }
}

void SystemTray::showNotification(int code, QString message) {
  std::cout << "Received oneclient notification: " << message.toStdString()
            << std::endl;
  // trayIcon->showMessage("Oneclient event", message);
  emit showMessage("Oneclient", message, QSystemTrayIcon::Information, 10000);
}

void SystemTray::editProvider(QString providerName) {

  auto oldSettings = SettingsManager::getProviderSettings(providerName);
  if (oldSettings.isNull())
    return;

  ProviderSettingsEditor pse{*oldSettings};
  if (pse.exec()) {
    ProviderSettings providerSettings = pse.getSettings();
    SettingsManager::updateProvider(providerSettings);
  }
}
