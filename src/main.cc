#include <QApplication>

#include "systemtray.h"
#include "settingsmanager.h"

#include <QMessageBox>
#include <QSettings>
#include <QSystemTrayIcon>
#include <iostream>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    SettingsManager::initialize();

    QSettings settings;
    settings.sync();

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

    //
    // Setup an interpocess communication queue path
    //
    std::cout << "SUPPORTS MESSAGES: " << QSystemTrayIcon::supportsMessages() << std::endl;

    QApplication::setQuitOnLastWindowClosed(false);

    SystemTray systemtray;
    systemtray.show();

    return app.exec();
}
