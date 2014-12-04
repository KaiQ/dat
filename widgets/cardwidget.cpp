#include "cardwidget.h"
#include "ui_cardwidget.h"

CardWidget::CardWidget(Card* _card, QWidget *parent) :
  QWidget(parent),
  card(_card),
  ui(new Ui::CardWidget)
{
  ui->setupUi(this);
}

CardWidget::~CardWidget()
{
  delete ui;
}
