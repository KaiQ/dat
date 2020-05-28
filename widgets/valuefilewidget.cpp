#include "valuefilewidget.h"
#include "ui_valuefilewidget.h"

ValueFileWidget::ValueFileWidget(DesfireFile &file) :
  FileInterface(file),
  ui(new Ui::ValueFileWidget)
{
  ui->setupUi(this);
  connect(ui->pushButton,
          SIGNAL(pressed()),
          this,
          SLOT(SaveValue()));
}

ValueFileWidget::~ValueFileWidget()
{
  delete ui;
}

void ValueFileWidget::setupWidget()
{
  int32_t value;
  if (mifare_desfire_get_value (file.getTag(), file.getFilenumber(), &value) < 0)
  {
    qDebug() << "Error get Value";
    return;
  }
  ui->lineEdit->setText(QString("%1").arg(value));
}

void ValueFileWidget::SaveValue()
{
}
