#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include "desfire/card.h"

namespace Ui {
  class CardWidget;
}

class CardWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CardWidget(Card *card, QWidget *parent = 0);
  ~CardWidget();

private:
  Ui::CardWidget *ui;
  Card* card;
};

#endif // CARDWIDGET_H
