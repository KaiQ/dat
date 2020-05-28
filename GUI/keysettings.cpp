#include "keysettings.h"
#include "ui_keysettings.h"

KeySettings::KeySettings(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::KeySettings)
{
  ui->setupUi(this);
}

KeySettings::~KeySettings()
{
  delete ui;
}

void KeySettings::setup(uint8_t key_settings, uint8_t max_key_no)
{
  this->ui->key_change_rights->setText(QString("0x%1")
                                       .arg(key_settings >> 4, 2, 16, QChar('0')));
  this->ui->settings_change_rights->setText(QString("0x%1")
                                            .arg((key_settings >> 3) & 0x1, 2, 16, QChar('0')));
  this->ui->file_alter_rights->setText(QString("0x%1")
                                       .arg((key_settings >> 2) & 0x1, 2, 16, QChar('0')));
  this->ui->directory_access_rights->setText(QString("0x%1")
                                             .arg((key_settings >> 1) & 0x1, 2, 16, QChar('0')));
  this->ui->master_key_rights->setText(QString("0x%1")
                                       .arg(key_settings & 0x01, 2, 16, QChar('0')));
}
