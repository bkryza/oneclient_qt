#pragma once

#include <QAction>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QWidgetAction>

#include "providersettings.h"

enum class ProviderMountState {
  Broken,
  Disconnected,
  Connected
};

class ActiveMountWidgetAction : public QWidgetAction {
  Q_OBJECT
public:
  ActiveMountWidgetAction(const ProviderSettings &settings, QObject *parent);

  ProviderSettings providerSettings;

  ProviderMountState mountState;

private:

  QPushButton *pUnmountButton;
  QPushButton *pEditButton;
  QPushButton *pRemoveButton;

  QLabel *pProviderName;
  QLabel *pStatusIcon;


public slots:
  void mouseEnter();
  void mouseLeave();
  void openMount();
};
