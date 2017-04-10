#include "activemountwidgetaction.h"

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

#include "focusdetectingwidget.h"

ActiveMountWidgetAction::ActiveMountWidgetAction(const QString &provider,
                                                 QObject *parent)
    : QWidgetAction(parent) {

  providerName = provider;

  auto pWidget =
      new FocusDetectingWidget(nullptr /*qobject_cast<QWidget *>(this)*/);
  pWidget->setStyleSheet(":hover{}");
  pWidget->setAttribute(Qt::WA_Hover, true);

  connect(pWidget, &FocusDetectingWidget::mouseEnter, this,
          &ActiveMountWidgetAction::mouseEnter);
  connect(pWidget, &FocusDetectingWidget::mouseLeave, this,
          &ActiveMountWidgetAction::mouseLeave);

  auto pLayout = new QHBoxLayout();

  // Setup mount point status icon
  QPixmap pix{":/disconnected.png"};
  pStatusIcon = new QLabel();
  pStatusIcon->setPixmap(pix.scaled(QSize(15, 15), Qt::KeepAspectRatio));
  pLayout->addWidget(pStatusIcon);

  // Setup provider name
  pProviderName = new QLabel(providerName);
  pLayout->addWidget(pProviderName);

  // Setup unmount button
  pUnmountButton = new QPushButton("Mount");
  pLayout->addWidget(pUnmountButton);

  // connect(this, &QAction::hovered, this, &ActiveMountWidgetAction::onHover);

  // Register widget layout
  pWidget->setLayout(pLayout);
  setDefaultWidget(pWidget);
}

void ActiveMountWidgetAction::mouseEnter() {

  // QPixmap pix{":/error.png"};
  // pStatusIcon->setPixmap(pix.scaled(QSize(15, 15), Qt::KeepAspectRatio));

  // std::cout << "Hovered over provider " << providerName.toUtf8().constData()
  //           << std::endl;
}

void ActiveMountWidgetAction::mouseLeave() {

  // QPixmap pix{":/connected.png"};
  // pStatusIcon->setPixmap(pix.scaled(QSize(15, 15), Qt::KeepAspectRatio));

  // std::cout << "Hover left over provider " <<
  // providerName.toUtf8().constData()
  //           << std::endl;
}
