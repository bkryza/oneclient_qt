#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

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
#include <QTextEdit>
#include <QVBoxLayout>

#include <QSystemTrayIcon>

class SystemTray : public QObject {
  Q_OBJECT
public:
  SystemTray(QObject *parent = nullptr);

  void show();
  void hide();

public slots:
  void showAbout();
  void updateTrayIconMenu();

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
};

#endif /* SYSTEMTRAY_H */
