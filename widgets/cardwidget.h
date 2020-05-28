#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include "desfire/card.h"
#include "GUI/createapplication.h"

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

private slots:
  void OnClicked();

private:
  Ui::CardWidget *ui;
  CreateApplication createApplicationWidget;
};

#endif // CARDWIDGET_H
