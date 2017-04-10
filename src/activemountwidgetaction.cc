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
#include <QDesktopServices>

#include <iostream>

#include "focusdetectingwidget.h"

ActiveMountWidgetAction::ActiveMountWidgetAction(const ProviderSettings &settings,
                                                 QObject *parent)
    : QWidgetAction(parent) {

  providerSettings = settings;

  auto pWidget =
      new FocusDetectingWidget(nullptr /*qobject_cast<QWidget *>(this)*/);
  pWidget->setStyleSheet(":hover{}");
  pWidget->setAttribute(Qt::WA_Hover, true);

  connect(pWidget, &FocusDetectingWidget::mouseEnter, this,
          &ActiveMountWidgetAction::mouseEnter);
  connect(pWidget, &FocusDetectingWidget::mouseLeave, this,
          &ActiveMountWidgetAction::mouseLeave);
  connect(pWidget, &FocusDetectingWidget::mousePressed, this,
          &ActiveMountWidgetAction::openMount);

  auto pLayout = new QHBoxLayout();

  // Setup mount point status icon
  QPixmap pix{":/disconnected.png"};
  pStatusIcon = new QLabel();
  pStatusIcon->setPixmap(pix.scaled(QSize(15, 15), Qt::KeepAspectRatio));
  pLayout->addWidget(pStatusIcon);

  // Setup provider name
  pProviderName = new QLabel(providerSettings.name);
  pLayout->addWidget(pProviderName);

  auto createActionButton = [](const QString& iconName) {
    auto button = new QPushButton();
    button->setFlat(true);
    button->setMinimumWidth(30);
    button->setMaximumWidth(30);
    button->setMinimumHeight(30);
    button->setMaximumHeight(30);
    button->setIcon(QIcon(QPixmap(iconName)));
    return button;
  };

  pUnmountButton = createActionButton(":mount.png");
  pLayout->addWidget(pUnmountButton);
  pEditButton = createActionButton(":edit.png");
  pLayout->addWidget(pEditButton);
  pRemoveButton = createActionButton(":remove.png");
  pLayout->addWidget(pRemoveButton);

  // Register widget layout
  pWidget->setLayout(pLayout);
  setDefaultWidget(pWidget);
}

void ActiveMountWidgetAction::openMount() {
  std::cout << "Pressed provider mount" << std::endl;
  QDesktopServices::openUrl(QUrl::fromLocalFile("~/Desktop"));
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
