#include "applicationwidget.h"
#include "ui_applicationwidget.h"

ApplicationWidget::ApplicationWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ApplicationWidget)
{
  ui->setupUi(this);
}

ApplicationWidget::~ApplicationWidget()
{
  delete ui;
}
