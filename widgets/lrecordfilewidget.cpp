#include "lrecordfilewidget.h"
#include "ui_lrecordfilewidget.h"

LRecordFileWidget::LRecordFileWidget(DesfireFile &file) :
  FileInterface(file),
  ui(new Ui::LRecordFileWidget)
{
  ui->setupUi(this);

  connect(this->ui->comboBox,
          SIGNAL(currentIndexChanged(QString)),
          this,
          SLOT(readRecord(QString)));
}

LRecordFileWidget::~LRecordFileWidget()
{
  delete ui;
}

void LRecordFileWidget::setupWidget()
{
  ui->comboBox->clear();
  for (int i = 0; i < file.getSettings().settings.linear_record_file.current_number_of_records; i++)
  {
    ui->comboBox->addItem(QString("%1").arg(i));
  }

  ui->record_size->setText(QString("%1 Bytes").arg(file.getSettings().settings.linear_record_file.record_size));
  ui->curr_number_of_records->setText(QString("%1").arg(file.getSettings().settings.linear_record_file.current_number_of_records));
  ui->max_number_of_records->setText(QString("%1").arg(file.getSettings().settings.linear_record_file.max_number_of_records));

  readRecord(0);
}

void LRecordFileWidget::readRecord(int number)
{
  char *buffer;
  auto fileSize = file.getSettings().settings.linear_record_file.record_size+1;

    buffer = (char *)calloc(fileSize * file.getSettings().settings.linear_record_file.current_number_of_records, sizeof(char));

    if(!buffer)
    {
      qDebug() << "Error reading linear record file";
      return;
    }

    auto bytes = mifare_desfire_read_records(file.getTag(), file.getFilenumber(), number, 1, buffer);

    if(bytes < 0)
    {
      qDebug() << "Error linear cyclic record file";
      ui->textEdit->setText(QString("<ERROR> could not read record"));
      return;
    }

    ui->textEdit->setText(QByteArray(buffer, bytes).toHex());
}

void LRecordFileWidget::readRecord(QString number)
{
  readRecord(number.toInt());
}
