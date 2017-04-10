#include "logowidgetaction.h"

#include <QAction>
#include <QCheckBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QCoreApplication>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>

#include <iostream>

LogoWidgetAction::LogoWidgetAction(const QString &title, QObject *parent)
    : QWidgetAction(parent) {

  QWidget *pWidget = new QWidget(nullptr);
  QHBoxLayout *pLayout = new QHBoxLayout();
  pWidget->setAttribute(Qt::WA_Hover, true);

  pLabel = new QLabel(title);
  pMenu = new QMenu();
  pMenu->addMenu("");
  pLogo = new QLabel();
  // pLogo->setIcon(QIcon(QPixmap(iconName)))
  pLogo->setPixmap(
      QPixmap(":/onedata-logo.png").scaled(QSize(80, 80), Qt::KeepAspectRatio));
  pLogo->setScaledContents(false);
  pLayout->addWidget(pLogo);
  pWidget->setLayout(pLayout);
  setDefaultWidget(pWidget);
}

bool LogoWidgetAction::event(QEvent *event) {
  std::cout << "LogoWidgetAction Event called" << std::endl;
  if (event->type() == QEvent::MouseButtonPress) {
    std::cout << "Left mouse button pressed" << std::endl;
  }

  return QWidgetAction::event(event);
}
