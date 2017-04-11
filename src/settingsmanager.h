#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSharedPointer>
#include <QString>

#include "providersettings.h"

class SettingsManager {

public:
  static void initialize();

  static QList<QString> getRegisteredProviders();

  static QSharedPointer<ProviderSettings>
  getProviderSettings(const QString &providerName);

  static bool addProvider(const ProviderSettings &providerSettings);

  static bool updateProvider(const ProviderSettings &providerSettings);

  static bool removeProvider(const QString &providerName);
};

#endif /* SETTINGSMANAGER_H */
