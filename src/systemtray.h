#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include "oneclientmessagelistener.h"

#include <QAction>
#include <QCheckBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QCoreApplication>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QVBoxLayout>

#include <map>
#include <thread>

class SystemTray : public QObject {
  Q_OBJECT
public:
  SystemTray(QObject *parent = nullptr);

  void show();
  void hide();

signals:
  void showMessage(
      const QString &title, const QString &message,
      QSystemTrayIcon::MessageIcon icon,
      int millisecondsTimeoutHint);

public slots:
  void showAbout();
  void updateTrayIconMenu();

  void showNotification(int code, QString message);

  void removeProvider(QString providerName);
  void mountUnmountProvider(QString providerName);
  void editProvider(QString providerName);

private:
  void createActions();
  void createTrayIcon();

private:
  QLabel *iconLabel;

  QAction *onedataLogoAction;
  QAction *provider1Action;
  QAction *provider2Action;
  QAction *provider3Action;

  QAction *manageProviders;

  QAction *aboutAction;
  QAction *logsAction;
  QAction *quitAction;

  QSystemTrayIcon *trayIcon;
  QMenu *trayIconMenu;

  QMap<QString, QSharedPointer<OneclientMessageListener>>
      clientMessageQueueListeners;
  // QMap<QString, std::shared_ptr<boost::interprocess::message_queue>>
  // messageQueues;
};

#endif /* SYSTEMTRAY_H */
