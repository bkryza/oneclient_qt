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

constexpr auto logoWidth = 120;
constexpr auto logoHeight = 40;

LogoWidgetAction::LogoWidgetAction(const QString &title, QObject *parent)
    : QWidgetAction(parent) {

  QWidget *pWidget = new QWidget(nullptr);
  pWidget->setAttribute(Qt::WA_Hover, true);

  QHBoxLayout *pLayout = new QHBoxLayout();
  pLayout->setAlignment(Qt::AlignLeft);

  pLogo = new QLabel(pWidget);
  pLogo->setEnabled(true);
  pLogo->setStyleSheet("padding: 0px;");
  pLogo->setMinimumWidth(logoWidth);
  pLogo->setMaximumWidth(logoWidth);
  pLogo->setPixmap(QPixmap(":/onedata-logo.png")
                       .scaled(QSize(logoWidth, logoHeight),
                               Qt::KeepAspectRatio, Qt::SmoothTransformation));

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
