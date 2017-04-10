#ifndef PROVIDERSETTINGS_H
#define PROVIDERSETTINGS_H

#include <QDir>
#include <QString>

class ProviderSettings {

public:
  ProviderSettings() = default;

  QString name;
  QString hostname;
  unsigned int port = 5555;
  QString mountPath;
  QString accessToken;

};

#endif /*PROVIDERSETTINGS_H*/
