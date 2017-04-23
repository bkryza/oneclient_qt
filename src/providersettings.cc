#include "providersettings.h"

#include <QStringList>

QStringList ProviderSettings::buildOneclientCommandLine() const {
  QStringList result;

  result << "-H" << hostname;
  result << "-t" << accessToken;
  result << "-P" << QString::number(port);
  result << "-i";
  result << "-o"
         << "allow_other,noapplexattr,noappledouble,defer_permissions,fsname="
            "oneclient,volname=" +
                name;

  result << mountPath;

  return result;
}