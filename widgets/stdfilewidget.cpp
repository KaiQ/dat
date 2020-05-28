#include "stdfilewidget.h"
#include "ui_stdfilewidget.h"
#include <QByteArray>

StdFileWidget::StdFileWidget(DesfireFile &dFile) :
  FileInterface(dFile),
  ui(new Ui::StdFileWidget)
{
  ui->setupUi(this);
}

StdFileWidget::~StdFileWidget()
{
  delete ui;
}

void StdFileWidget::setupWidget()
{
  auto fileSize = file.getSettings().settings.standard_file.file_size+1;
  char *buffer = static_cast<char*>(calloc(fileSize,sizeof(char)));

  if(!buffer)
  {
    ui->asciiText->setText("<ERROR> No free memory");
    ui->utf8Text->setText("<ERROR> No free memory");
    ui->hexText->setText("<ERROR> No free memory");
    return;
  }

  if (mifare_desfire_read_data (file.getTag(), file.getFilenumber(), 0, fileSize-1, buffer) < 0)
  {
    qDebug() << QString("Could not read file 0x%1 error=0x%2")
                .arg(file.getFilenumber(), 0, 16)
                .arg(mifare_desfire_last_picc_error(file.getTag()), 0, 16);
    free(buffer);
    ui->asciiText->setText("<ERROR> Could not read file");
    ui->utf8Text->setText("<ERROR> Could not read file");
    ui->hexText->setText("<ERROR> Could not read file");
    return;
  }

  QByteArray bytes = QByteArray(buffer);
  QByteArray ascii;
  for (auto i : bytes)
  {
    if (!QChar(i).isPrint())
    {
      // replace non-ascii and non-printable characters with dots
      ascii.append('.');
    }
    else
    {
      ascii.append(i);
    }
  }

  ui->asciiText->setText(ascii);
  ui->utf8Text->setText(QString(buffer).toUtf8());
  ui->hexText->setText(QByteArray(buffer).toHex(' '));

  free(buffer);
}
