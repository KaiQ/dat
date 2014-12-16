#ifndef STDFILEWIDGET_H
#define STDFILEWIDGET_H

#include <QWidget>

namespace Ui {
  class CRecordFileWidget;
}

class CRecordFileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CRecordFileWidget(QWidget *parent = 0);
  ~CRecordFileWidget();

private:
  Ui::CRecordFileWidget *ui;
};

#endif // STDFILEWIDGET_H
