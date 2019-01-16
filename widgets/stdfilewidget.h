#ifndef STDFILEWIDGET_H
#define STDFILEWIDGET_H

#include <QWidget>
#include <interface/fileinterface.h>

namespace Ui {
  class StdFileWidget;
}

class StdFileWidget : public FileInterface
{
  Q_OBJECT

public:
  StdFileWidget(DesfireFile &file);
  ~StdFileWidget();

  void setupWidget();

private:
  Ui::StdFileWidget *ui;
};

#endif // STDFILEWIDGET_H
