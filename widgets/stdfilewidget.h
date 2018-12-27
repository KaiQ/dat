#ifndef STDFILEWIDGET_H
#define STDFILEWIDGET_H

#include <QWidget>
#include "../desfire/files/stdFile.h"

namespace Ui {
  class StdFileWidget;
}

class StdFileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit StdFileWidget(QWidget *parent = 0);
  ~StdFileWidget();

  void setup(StdFile &file);

private:
  Ui::StdFileWidget *ui;
};

#endif // STDFILEWIDGET_H
