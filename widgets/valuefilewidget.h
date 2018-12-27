#ifndef STDFILEWIDGET_H
#define STDFILEWIDGET_H

#include <QWidget>
#include "../desfire/files/valueFile.h"

namespace Ui {
  class ValueFileWidget;
}

class ValueFileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ValueFileWidget(QWidget *parent = 0);
  ~ValueFileWidget();
  void setup(ValueFile &file);

private:
  Ui::ValueFileWidget *ui;
};

#endif // STDFILEWIDGET_H
