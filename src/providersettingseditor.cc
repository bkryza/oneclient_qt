#include "providersettingseditor.h"

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QVBoxLayout>
#include <QMessageBox>

constexpr auto minPortRange = 1;
constexpr auto maxPortRange = 99999;

ProviderSettingsEditor::ProviderSettingsEditor() { createLayout(); }

ProviderSettingsEditor::ProviderSettingsEditor(const ProviderSettings &settings)
    : providerSettings(settings) {

  createLayout();
}

void ProviderSettingsEditor::createLayout() {

  QVBoxLayout *mainLayout = new QVBoxLayout;

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
  portEdit->setValidator(new QIntValidator(minPortRange, maxPortRange, this));
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
    if (!path.trimmed().isEmpty()) {
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

  auto modalButtonsBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  mainLayout->addWidget(modalButtonsBox);

  connect(modalButtonsBox, SIGNAL(accepted()), this, SLOT(verify()));
  connect(modalButtonsBox, SIGNAL(rejected()), this, SLOT(reject()));

  setLayout(mainLayout);

  setWindowTitle(tr("Provider settings..."));
  resize(400, 300);
}

void ProviderSettingsEditor::verify() {
  if (!providerNameEdit->text().isEmpty() &&
      !hostnameEdit->text().isEmpty() && !portEdit->text().isEmpty() &&
      !mountPathEdit->text().isEmpty() && !accessTokenEdit->text().isEmpty()) {

        providerSettings.name = providerNameEdit->text();
        providerSettings.hostname = hostnameEdit->text();
        providerSettings.port = portEdit->text().toInt();
        providerSettings.mountPath = mountPathEdit->text();
        providerSettings.accessToken = accessTokenEdit->text();

    accept();
    return;
  }

  QMessageBox::StandardButton answer;
  answer = QMessageBox::warning(
      this, tr("Incomplete Form"),
      tr("The form does not contain all the necessary information.\n"
         "Do you want to discard it?"),
      QMessageBox::Yes | QMessageBox::No);

  if (answer == QMessageBox::Yes)
    reject();
}

ProviderSettings ProviderSettingsEditor::getSettings() {
  return providerSettings;
}

void ProviderSettingsEditor::closeEvent(QCloseEvent *event) {}
