#ifndef STDFILEWIDGET_H
#define STDFILEWIDGET_H

#include <QWidget>

namespace Ui {
  class ValueFileWidget;
}

class ValueFileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ValueFileWidget(QWidget *parent = 0);
  ~ValueFileWidget();

private:
  Ui::ValueFileWidget *ui;
};

#endif // STDFILEWIDGET_H
