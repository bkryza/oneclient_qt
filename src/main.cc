#include <QApplication>

// #ifndef QT_NO_SYSTEMTRAYICON
#include <QMessageBox>
#include <QSettings>
#include "systemtray.h"
#include "settingsmanager.h"

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

    QApplication::setQuitOnLastWindowClosed(false);

    SystemTray systemtray;
    systemtray.show();
    return app.exec();
}
//
// #else
//
// #include <QLabel>
// #include <QDebug>
//
// int main(int argc, char *argv[])
// {
//     QApplication app{argc, argv};
//     constexpr QString text{"QSystemTrayIcon is not supported on this platform"};
//     QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
//
//     auto label = new QLabel(text);
//     label->setWordWrap(true);
//
//     label->show();
//     qDebug() << text;
//
//     SystemTray systemtray;
//     systemtray.show();
//     return app.exec();
// }
//
// #endif
