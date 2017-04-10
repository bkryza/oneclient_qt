#pragma once


#include <QAction>
#include <QObject>
#include <QString>
#include <QWidgetAction>
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QIcon>

class LogoWidgetAction : public QWidgetAction {
public:
  LogoWidgetAction(const QString &title, QObject *parent);


private:
  QMenu *pMenu;
  QPushButton *pPushButton;
  QLabel *pLabel;
  QLabel *pLogo;
};
