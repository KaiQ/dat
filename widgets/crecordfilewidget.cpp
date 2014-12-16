#include "crecordfilewidget.h"
#include "ui_crecordfilewidget.h"

CRecordFileWidget::CRecordFileWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CRecordFileWidget)
{
  ui->setupUi(this);
}

CRecordFileWidget::~CRecordFileWidget()
{
  delete ui;
}
