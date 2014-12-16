#include "backupfilewidget.h"
#include "ui_backupfilewidget.h"

BackupFileWidget::BackupFileWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::BackupFileWidget)
{
  ui->setupUi(this);
}

BackupFileWidget::~BackupFileWidget()
{
  delete ui;
}
