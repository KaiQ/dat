#include "stdfilewidget.h"
#include "ui_stdfilewidget.h"

StdFileWidget::StdFileWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StdFileWidget)
{
  ui->setupUi(this);
}

StdFileWidget::~StdFileWidget()
{
  delete ui;
}
