#include "valuefilewidget.h"
#include "ui_valuefilewidget.h"

ValueFileWidget::ValueFileWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ValueFileWidget)
{
  ui->setupUi(this);
}

ValueFileWidget::~ValueFileWidget()
{
  delete ui;
}

void ValueFileWidget::setup(ValueFile &file)
{
  int32_t value;
  if (mifare_desfire_get_value (file.getTag(), file.getFilenumber(), &value) < 0)
  {
    qDebug() << "Error get Value";
    return;
  }
  ui->lineEdit->setText(QString("%1").arg(value));
}
