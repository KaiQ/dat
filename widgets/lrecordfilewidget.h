#ifndef LRECORDFILEWIDGET_H
#define LRECORDFILEWIDGET_H

#include <QWidget>
#include <interface/fileinterface.h>

namespace Ui {
  class LRecordFileWidget;
}

class LRecordFileWidget : public FileInterface
{
  Q_OBJECT

public:
  LRecordFileWidget(DesfireFile &file);
  ~LRecordFileWidget();

  void setupWidget();

private:
  Ui::LRecordFileWidget *ui;

  void readRecord(int number);

private slots:
  void readRecord(QString number);
};

#endif // LRECORDFILEWIDGET_H
