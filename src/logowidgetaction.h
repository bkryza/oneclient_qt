#pragma once

#include <QAction>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QWidgetAction>
#include <QMouseEvent>
#include <QEvent>

class LogoWidgetAction : public QWidgetAction {
public:
  LogoWidgetAction(const QString &title, QObject *parent);

  virtual bool event(QEvent *event) override;

private:
  QMenu *pMenu;
  QPushButton *pPushButton;
  QLabel *pLabel;
  QLabel *pLogo;
};
