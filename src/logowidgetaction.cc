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

LogoWidgetAction::LogoWidgetAction(const QString &title, QObject *parent)
    : QWidgetAction(parent) {

  QWidget *pWidget = new QWidget(NULL);
  QHBoxLayout *pLayout = new QHBoxLayout();

  pLabel = new QLabel(title);
  pMenu = new QMenu();
  pMenu->addMenu("");
  pLogo = new QLabel();
  pLogo->setPixmap(
      QPixmap(":/onedata-logo.png").scaled(QSize(80, 80), Qt::KeepAspectRatio));
  pLogo->setScaledContents(false);
  pLayout->addWidget(pLogo);
  pWidget->setLayout(pLayout);
  setDefaultWidget(pWidget);
}
