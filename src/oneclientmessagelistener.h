#pragma once

#include <QString>
#include <QThread>

class OneclientMessageListener: public QThread
{
    Q_OBJECT
public:
    OneclientMessageListener(const QString& mountPoint);

signals:
    void receivedNotification(int code, QString message);

protected:
    void run();

private:
    QString m_mountpoint;
};