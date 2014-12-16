#include "lrecordfilewidget.h"
#include "ui_lrecordfilewidget.h"

LRecordFileWidget::LRecordFileWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LRecordFileWidget)
{
  ui->setupUi(this);
}

LRecordFileWidget::~LRecordFileWidget()
{
  delete ui;
}
