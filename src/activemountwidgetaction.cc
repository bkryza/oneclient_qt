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
  pLayout->setAlignment(Qt::AlignLeft);

  pLayout->setAlignment(Qt::AlignLeft);

  // Setup mount point status icon
  pStatusIcon = new QLabel();
  // QPixmap disabled_icon( "disabled.png" );
  // QIcon icon( enabled_icon );
  // icon.addPixmap( disabled_icon, QIcon::Disabled );
  // QAction action( icon, "&Menu action..." );

  QPixmap pix{":/disconnected.png"};
  pStatusIcon->setPixmap(pix.scaled(QSize(20, 20), Qt::KeepAspectRatio, Qt::SmoothTransformation));
  pLayout->addWidget(pStatusIcon);

  // Setup provider name and host name
  QVBoxLayout* providerIdentificationLayout = new QVBoxLayout();
  providerIdentificationLayout->setSpacing(0);
  pProviderName = new QLabel(providerSettings.name);
  pProviderName->setMaximumWidth(200);
  pProviderName->setMinimumWidth(200);
  pProviderName->setFont(QFont("Lucida Grande", 14, QFont::Bold));
  providerIdentificationLayout->addWidget(pProviderName);
  pProviderHostname = new QLabel(providerSettings.hostname);
  pProviderHostname->setFont(QFont("Lucida Grande", 11, QFont::Normal));
  providerIdentificationLayout->addWidget(pProviderHostname);
  pLayout->addLayout(providerIdentificationLayout);

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

  QHBoxLayout *mountActionsLayout = new QHBoxLayout();
  mountActionsLayout->setSpacing(0);

  pUnmountButton = createActionButton(":mount.png");
  pUnmountButton->setStyleSheet("border: 1px; margin: 0px; padding: 0px;");
  connect(pUnmountButton, &QPushButton::pressed, [&]() {
    emit mountUnmountProvider(providerSettings.name);
  });
  mountActionsLayout->addWidget(pUnmountButton);

  pEditButton = createActionButton(":edit.png");
  pEditButton->setStyleSheet("border: none; margin: 0px; padding: 0px;");
  connect(pEditButton, &QPushButton::pressed, [&]() {
    emit editProvider(providerSettings.name);
  });
  mountActionsLayout->addWidget(pEditButton);

  pRemoveButton = createActionButton(":remove.png");
  pRemoveButton->setStyleSheet("border: none; margin: 0px; padding: 0px;");
  mountActionsLayout->addWidget(pRemoveButton);
  connect(pRemoveButton, &QPushButton::pressed, [&]() {
    emit removeProvider(providerSettings.name);
  });
  pLayout->addLayout(mountActionsLayout);

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
