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
  explicit CardWidget(QWidget *parent = 0);
  ~CardWidget();

  void setup(Card &card);

private:
  Ui::CardWidget *ui;
};

#endif // CARDWIDGET_H
