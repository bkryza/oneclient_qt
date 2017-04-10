#ifndef PROVIDERSETTINGSEDITOR_H
#define PROVIDERSETTINGSEDITOR_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "providersettings.h"

class ProviderSettingsEditor : public QDialog
{
    Q_OBJECT

public:
    ProviderSettingsEditor();
    ProviderSettingsEditor(const ProviderSettings& settings);

protected:
    void closeEvent(QCloseEvent *event) override;


private:

    void createLayout();

    ProviderSettings providerSettings;

    QLabel* providerNameLabel;
    QLineEdit* providerNameEdit;

    QLabel* hostnameLabel;
    QLineEdit* hostnameEdit;

    QLabel* portLabel;
    QLineEdit* portEdit;

    QLabel* mountPathLabel;
    QLineEdit* mountPathEdit;
    QPushButton* mountPathDialog;

    QLabel* accessTokenLabel;
    QLineEdit* accessTokenEdit;

    QPushButton* saveButton;
    QPushButton* cancelButton;

};

#endif
