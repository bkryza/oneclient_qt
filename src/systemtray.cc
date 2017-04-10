#include "systemtray.h"

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
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QSettings>

#include <iostream>

#include "activemountwidgetaction.h"
#include "logowidgetaction.h"
#include "providersettings.h"
#include "providersettingseditor.h"

SystemTray::SystemTray(QObject *parent) : QObject(parent) {
  createActions();
  createTrayIcon();
}

void SystemTray::show() { trayIcon->show(); }

void SystemTray::hide() { trayIcon->hide(); }

void SystemTray::createActions() {
  onedataLogoAction = new LogoWidgetAction(QString(tr("Oneclient")), this);
  // connect(onedataLogoAction, &QAction::triggered, this, &QWidget::hide);

  // provider1Action =
  //     new ActiveMountWidgetAction(QString(tr("EGI DataHub")), this);
  // connect(provider1Action, &ActiveMountWidgetAction::triggered, this,
  //         &SystemTray::openMount);

  // provider2Action = new ActiveMountWidgetAction(QString(tr("Cyfronet")), this);
  // connect(provider2Action, &ActiveMountWidgetAction::triggered, this,
  //         &SystemTray::openMount);

  // provider3Action = new ActiveMountWidgetAction(QString(tr("INFN")), this);
  // connect(provider3Action, &ActiveMountWidgetAction::triggered, this,
  //         &SystemTray::openMount);

  manageProviders = new QAction(tr("Add &provider..."), this);
  manageProviders->setIcon(QIcon(":add.png"));
  connect(manageProviders, &QAction::triggered, []() {
    ProviderSettingsEditor pse;
    if(pse.exec()) {
      ProviderSettings providerSettings = pse.getSettings();

      QSettings settings;
      settings.beginGroup("StorageProvider::"+providerSettings.name);
      settings.setValue("name", providerSettings.name);
      settings.setValue("hostname", providerSettings.hostname);
      settings.setValue("port", providerSettings.port);
      settings.setValue("mountPath", providerSettings.mountPath);
      settings.setValue("accessToken", providerSettings.accessToken);

      settings.endGroup();
      settings.sync();

    }
  });

  aboutAction = new QAction(tr("&About..."), this);
  connect(aboutAction, &QAction::triggered, this, &SystemTray::showAbout);

  quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void SystemTray::updateTrayIconMenu() {

  trayIconMenu->clear();

  trayIconMenu->addAction(onedataLogoAction);

  trayIconMenu->addSeparator();

  QSettings settings;
  QStringList groups = settings.childGroups();
  for(auto group : groups) {
    if(group.startsWith("StorageProvider::")) {
      ProviderSettings ps;
      settings.beginGroup(group);
      ps.name = settings.value("name").toString();
      ps.hostname = settings.value("hostname").toString();
      ps.port = settings.value("port").toInt();
      ps.mountPath = settings.value("mountPath").toString();
      ps.accessToken = settings.value("accessToken").toString();
      settings.endGroup();
      trayIconMenu->addAction(new ActiveMountWidgetAction(ps));
    }
  }


  trayIconMenu->addAction(manageProviders);

  trayIconMenu->addSeparator();

  trayIconMenu->addAction(aboutAction);
  trayIconMenu->addAction(quitAction);

}
void SystemTray::createTrayIcon() {
  trayIconMenu = new QMenu(nullptr);

  trayIcon = new QSystemTrayIcon(nullptr);
  trayIcon->setContextMenu(trayIconMenu);
  trayIcon->setIcon(QIcon(":/onedata-icon.png"));

  connect(trayIcon, &QSystemTrayIcon::activated, this, &SystemTray::updateTrayIconMenu);
}

void SystemTray::showAbout() {
  auto pWindow = new QWidget(nullptr /*qobject_cast<QWidget>(trayIcon)*/);
  pWindow->resize(640, 400);
  pWindow->setStyleSheet("background-color: #BBBBBB");
  pWindow->setWindowModality(Qt::ApplicationModal);

  auto pLayout = new QHBoxLayout(pWindow);
  auto pLogoLabel = new QLabel(pWindow);
  pLogoLabel->setPixmap(QPixmap(":onedata-logo.png").scaledToWidth(180));
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
