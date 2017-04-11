#include "settingsmanager.h"

#include <QApplication>
#include <QSettings>

#include <iostream>

void SettingsManager::initialize() {
  QCoreApplication::setOrganizationName("Onedata");
  QCoreApplication::setOrganizationDomain("onedata.org");
  QCoreApplication::setApplicationName("Oneclient");
}

QList<QString> SettingsManager::getRegisteredProviders() {
  QList<QString> results;

  QSettings settings;
  QStringList groups = settings.childGroups();
  for (auto group : groups) {
    if (group.startsWith("StorageProvider::")) {
      settings.beginGroup(group);
      results.append(settings.value("name").toString());
      settings.endGroup();
    }
  }

  return results;
}

QSharedPointer<ProviderSettings>
SettingsManager::getProviderSettings(const QString &providerName) {
  QSharedPointer<ProviderSettings> result{nullptr};

  QSettings settings;
  QStringList groups = settings.childGroups();

  for (auto group : groups) {
    if (group.startsWith("StorageProvider::")) {
      settings.beginGroup(group);
      if (settings.value("name").toString().compare(providerName) == 0) {
        result.reset(new ProviderSettings);
        result->name = settings.value("name").toString();
        result->hostname = settings.value("hostname").toString();
        result->port = settings.value("port").toInt();
        result->mountPath = settings.value("mountPath").toString();
        result->accessToken = settings.value("accessToken").toString();
        settings.endGroup();
        return result;
      }
      settings.endGroup();
    }
  }

  return result;
}

bool SettingsManager::addProvider(const ProviderSettings &providerSettings) {
  if (SettingsManager::getRegisteredProviders().contains(
          providerSettings.name)) {
    return false;
  }

  QSettings settings;
  settings.beginGroup("StorageProvider::" + providerSettings.name);
  settings.setValue("name", providerSettings.name);
  settings.setValue("hostname", providerSettings.hostname);
  settings.setValue("port", providerSettings.port);
  settings.setValue("mountPath", providerSettings.mountPath);
  settings.setValue("accessToken", providerSettings.accessToken);
  settings.endGroup();
  settings.sync();

  return true;
}

bool SettingsManager::updateProvider(const ProviderSettings &providerSettings) {
  if (!SettingsManager::getRegisteredProviders().contains(
          providerSettings.name)) {
    return false;
  }

  QSettings settings;
  settings.beginGroup("StorageProvider::" + providerSettings.name);
  settings.setValue("name", providerSettings.name);
  settings.setValue("hostname", providerSettings.hostname);
  settings.setValue("port", providerSettings.port);
  settings.setValue("mountPath", providerSettings.mountPath);
  settings.setValue("accessToken", providerSettings.accessToken);
  settings.endGroup();
  settings.sync();

  return true;
}

bool SettingsManager::removeProvider(const QString &providerName) {
  if (!SettingsManager::getRegisteredProviders().contains(providerName)) {
    return false;
  }

  QSettings settings;
  settings.beginGroup("StorageProvider::" + providerName);
  settings.remove("");
  settings.endGroup();
  settings.sync();

  return false;
}
