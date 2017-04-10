#pragma once

#include <QAction>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QWidgetAction>

class ActiveMountWidgetAction : public QWidgetAction {
  Q_OBJECT
public:
  ActiveMountWidgetAction(const QString &provider, QObject *parent);

  // virtual void focusOutEvent(QFocusEvent* event) Q_DECL_OVERRIDE;

private:
  QString providerName;

  QPushButton *pUnmountButton;
  QLabel *pProviderName;
  QLabel *pStatusIcon;

public slots:
  void mouseEnter();
  void mouseLeave();
};
