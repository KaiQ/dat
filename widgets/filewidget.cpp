#include "filewidget.h"
#include "ui_filewidget.h"
#include "widgets/stdfilewidget.h"
#include "widgets/lrecordfilewidget.h"
#include "widgets/valuefilewidget.h"
#include <freefare.h>

FileWidget::FileWidget(QWidget *parent) :
  QWidget(parent),
  file(nullptr),
  subWidget(nullptr),
  ui(new Ui::FileWidget)
{
  ui->setupUi(this);
}

FileWidget::~FileWidget()
{
  if (this->subWidget != nullptr)
  {
    delete this->subWidget;
  }
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

void FileWidget::setupWidget(DesfireFile *file)
{
  this->file = file;

  ui->communicationSettings->setText(QString("%1")
                                     .arg(MapCommunicationSettingToString(file->getSettings().communication_settings)
                                          , 16,
                                          '0'));
  ui->access_read->setText(QString("%1").arg(MDAR_READ(file->getSettings().access_rights)));
  ui->access_write->setText(QString("%1").arg(MDAR_WRITE(file->getSettings().access_rights)));
  ui->access_read_write->setText(QString("%1").arg(MDAR_READ_WRITE(file->getSettings().access_rights)));
  ui->access_change_rights->setText(QString("%1").arg(MDAR_CHANGE_AR(file->getSettings().access_rights)));

  if (this->subWidget == nullptr)
  {
    this->subWidget = createSubWidget();
    ui->fileWidget->parentWidget()->layout()->replaceWidget(ui->fileWidget, this->subWidget);
  }

  this->subWidget->setupWidget();
}

FileInterface* FileWidget::createSubWidget()
{
  switch (this->file->getSettings().file_type)
  {
    case MDFT_STANDARD_DATA_FILE:
      return new StdFileWidget(*file);
    case MDFT_BACKUP_DATA_FILE:
      return new StdFileWidget(*file);
    case MDFT_VALUE_FILE_WITH_BACKUP:
      return new ValueFileWidget(*file);
    case MDFT_LINEAR_RECORD_FILE_WITH_BACKUP:
      return new LRecordFileWidget(*file);
    case MDFT_CYCLIC_RECORD_FILE_WITH_BACKUP:
      return new LRecordFileWidget(*file);
    default:
      return nullptr;
  }
}
