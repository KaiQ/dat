#ifndef STDFILEWIDGET_H
#define STDFILEWIDGET_H

#include <QWidget>
#include "../desfire/files/lRecordFile.h"

namespace Ui {
  class LRecordFileWidget;
}

class LRecordFileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit LRecordFileWidget(QWidget *parent = 0);
  ~LRecordFileWidget();

  void setup(LRecordFile &file);

private:
  LRecordFile *file;
  Ui::LRecordFileWidget *ui;

  void readRecord(int number);

private slots:
  void readRecord(QString number);
};

#endif // STDFILEWIDGET_H
