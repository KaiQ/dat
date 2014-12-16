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
