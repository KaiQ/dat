#include "cardwidget.h"
#include "ui_cardwidget.h"
#include <cmath>
#include <QMessageBox>
#include <GUI/createapplication.h>

CardWidget::CardWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CardWidget),
  createApplicationWidget(parent)
{
  ui->setupUi(this);
  connect(ui->buttonCreateApplication, SIGNAL(clicked(bool)),
          this, SLOT(OnClicked()));
  ui->buttonCreateApplication->setEnabled(false);
}

CardWidget::~CardWidget()
{
  delete ui;
}

void CardWidget::setup(Card &card)
{
  struct mifare_desfire_version_info info;
  uint8_t settings;
  uint8_t max_keys;
  if (mifare_desfire_get_version(card.getTag(), &info) < 0)
  {
    return;
  }

  if ( mifare_desfire_get_key_settings (card.getTag(), &settings, &max_keys) < 0)
  {
    return;
  }

  this->ui->uid->setText(card.uid);

  this->ui->batchnumber->setText(QString("0x%1%2%3%4%5")
                                 .arg(info.batch_number[0], 2, 16, QChar('0'))
                                 .arg(info.batch_number[1], 2, 16, QChar('0'))
                                 .arg(info.batch_number[2], 2, 16, QChar('0'))
                                 .arg(info.batch_number[3], 2, 16, QChar('0'))
                                 .arg(info.batch_number[4], 2, 16, QChar('0')));
  this->ui->production_date->setText(QString("week %1, 20%2")
                                     .arg(info.production_week, 2, 16, QChar('0'))
                                     .arg(info.production_year, 2, 16, QChar('0')));
  this->ui->hardware_vendor_id->setText(QString("0x%1")
                                        .arg(info.hardware.vendor_id, 2, 16, QChar('0')));
  this->ui->hardware_type->setText(QString("0x%1")
                                   .arg(info.hardware.type, 2, 16, QChar('0')));
  this->ui->hardware_subtype->setText(QString("0x%1")
                                      .arg(info.hardware.subtype, 2, 16, QChar('0')));
  this->ui->hardware_version->setText(QString("%1.%2")
                                      .arg(info.hardware.version_major)
                                      .arg(info.hardware.version_minor));
  this->ui->hardware_storage_size->setText(QString("0x%1 (%2%3 bytes)")
                                           .arg(info.hardware.storage_size, 2, 16, QChar('0'))
                                           .arg((info.hardware.storage_size & 1) ? ">" : "=")
                                           .arg((int)pow(2, info.hardware.storage_size >> 1)));
  this->ui->hardware_protocol->setText(QString("0x%1")
                                       .arg(info.hardware.protocol, 2, 16, QChar('0')));

  this->ui->software_vendor_id->setText(QString("0x%1")
                                        .arg(info.software.vendor_id, 2, 16, QChar('0')));
  this->ui->software_type->setText(QString("0x%1")
                                   .arg(info.software.type, 2, 16, QChar('0')));
  this->ui->software_subtype->setText(QString("0x%1")
                                      .arg(info.software.subtype, 2, 16, QChar('0')));
  this->ui->software_version->setText(QString("%1.%2")
                                      .arg(info.software.version_major)
                                      .arg(info.software.version_minor));
  this->ui->software_storage_size->setText(QString("0x%1 (%2%3 bytes)")
                                           .arg(info.software.storage_size, 2, 16, QChar('0'))
                                           .arg((info.software.storage_size & 1) ? ">" : "=")
                                           .arg((int)pow(2, info.software.storage_size >> 1)));
  this->ui->software_protocol->setText(QString("0x%1")
                                       .arg(info.software.protocol, 2, 16, QChar('0')));


  this->ui->master_key->setText(QString("0x%1")
                                .arg(settings, 2, 16, QChar('0')));
  this->ui->config_changeable->setText(QString("0x%1")
                                       .arg(settings & 0x08, 2, 16, QChar('0')));
  this->ui->master_key_not_req->setText(QString("0x%1")
                                        .arg(settings & 0x04, 2, 16, QChar('0')));
  this->ui->free_directory_list_access->setText(QString("0x%1")
                                                .arg(settings & 0x02, 2, 16, QChar('0')));
  this->ui->allow_change_master_key->setText(QString("0x%1")
                                             .arg(settings & 0x01, 2, 16, QChar('0')));

  ui->buttonCreateApplication->setEnabled(true);

  createApplicationWidget.setTag(card.getTag());
}

void CardWidget::OnClicked()
{
  createApplicationWidget.exec();
}
