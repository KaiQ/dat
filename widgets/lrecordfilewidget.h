#ifndef STDFILEWIDGET_H
#define STDFILEWIDGET_H

#include <QWidget>

namespace Ui {
  class LRecordFileWidget;
}

class LRecordFileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit LRecordFileWidget(QWidget *parent = 0);
  ~LRecordFileWidget();

private:
  Ui::LRecordFileWidget *ui;
};

#endif // STDFILEWIDGET_H
