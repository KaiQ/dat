#include "filewidget.h"
#include "ui_filewidget.h"
#include <freefare.h>

FileWidget::FileWidget(QWidget *subWidget, QWidget *parent) :
  QWidget(parent),
  subWidget(subWidget),
  ui(new Ui::FileWidget)
{
  ui->setupUi(this);
}

FileWidget::~FileWidget()
{
  delete ui;
}

QString const MapCommunicationSettingToString(uint8_t communication_setting)
{
  switch (communication_setting) {
    case MDCM_PLAIN:
      return QString("Plain");
    case MDCM_MACED:
      return QString("MACED");
    case MDCM_ENCIPHERED:
      return QString("ENCIPHERED");
    default:
      return QString("Unknown");
  }
}

void FileWidget::setupRootWidget(DesfireFile *file)
{
  ui->communicationSettings->setText(QString("%1")
                                     .arg(MapCommunicationSettingToString(file->getSettings().communication_settings)
                                          , 16,
                                          '0'));
  ui->access_read->setText(QString("%1").arg(MDAR_READ(file->getSettings().access_rights)));
  ui->access_write->setText(QString("%1").arg(MDAR_WRITE(file->getSettings().access_rights)));
  ui->access_read_write->setText(QString("%1").arg(MDAR_READ_WRITE(file->getSettings().access_rights)));
  ui->access_change_rights->setText(QString("%1").arg(MDAR_CHANGE_AR(file->getSettings().access_rights)));
  ui->fileWidget->parentWidget()->layout()->replaceWidget(ui->fileWidget, this->subWidget);
}

QWidget* FileWidget::getSubWidget()
{
  return this->subWidget;
}
