#ifndef VALUEFILEWIDGET_H
#define VALUEFILEWIDGET_H

#include <QWidget>
#include <interface/fileinterface.h>

namespace Ui {
  class ValueFileWidget;
}

class ValueFileWidget : public FileInterface
{
  Q_OBJECT

public:
  ValueFileWidget(DesfireFile &file);
  ~ValueFileWidget();

  void setupWidget();

private:
  Ui::ValueFileWidget *ui;
};

#endif // VALUEFILEWIDGET_H
