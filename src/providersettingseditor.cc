#include "providersettingseditor.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>

ProviderSettingsEditor::ProviderSettingsEditor() { createLayout(); }

ProviderSettingsEditor::ProviderSettingsEditor(const ProviderSettings &settings)
    : providerSettings(settings) {

  createLayout();
}

void ProviderSettingsEditor::createLayout() {

  QVBoxLayout *mainLayout = new QVBoxLayout;
  // mainLayout->setAlignment(line, Qt::AlignHCenter);

  providerNameLabel = new QLabel(tr("Provider name"));
  hostnameLabel = new QLabel(tr("Provider host name"));
  portLabel = new QLabel(tr("Provider port"));
  mountPathLabel = new QLabel(tr("Mount point"));
  accessTokenLabel = new QLabel(tr("Access token"));

  providerNameEdit = new QLineEdit();
  providerNameEdit->setText(providerSettings.name);

  hostnameEdit = new QLineEdit();
  hostnameEdit->setText(providerSettings.hostname);

  portEdit = new QLineEdit();
  portEdit->setValidator( new QIntValidator(1, 99999, this) );
  portEdit->setText(QString::number(providerSettings.port));

  mountPathEdit = new QLineEdit();
  mountPathEdit->setText(providerSettings.mountPath);

  accessTokenEdit = new QLineEdit();
  accessTokenEdit->setText(providerSettings.accessToken);

  mountPathDialog = new QPushButton(tr("Open..."));
  connect(mountPathDialog, &QPushButton::clicked, [&](bool checked) {
    QString path = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "~",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!path.trimmed().isEmpty()) {
      providerSettings.mountPath = path;
      mountPathEdit->setText(providerSettings.mountPath);
    }
  });

  auto mountPointLayout = new QHBoxLayout(nullptr);

  mainLayout->addWidget(providerNameLabel);
  mainLayout->addWidget(providerNameEdit);

  mainLayout->addWidget(hostnameLabel);
  mainLayout->addWidget(hostnameEdit);

  mainLayout->addWidget(portLabel);
  mainLayout->addWidget(portEdit);

  mainLayout->addWidget(mountPathLabel);
  mountPointLayout->addWidget(mountPathEdit);
  mountPointLayout->addWidget(mountPathDialog);
  mainLayout->addLayout(mountPointLayout);

  mainLayout->addWidget(accessTokenLabel);
  mainLayout->addWidget(accessTokenEdit);

  auto modalButtonsLayout = new QHBoxLayout(nullptr);
  cancelButton = new QPushButton(tr("&Cancel"));
  saveButton = new QPushButton(tr("&Save"));
  modalButtonsLayout->addWidget(saveButton);
  modalButtonsLayout->addWidget(cancelButton);
  mainLayout->addLayout(modalButtonsLayout);

  setLayout(mainLayout);

  setWindowTitle(tr("Provider settings..."));
  resize(400, 300);
}

void ProviderSettingsEditor::closeEvent(QCloseEvent *event) {}
