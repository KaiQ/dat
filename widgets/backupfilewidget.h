#ifndef STDFILEWIDGET_H
#define STDFILEWIDGET_H

#include <QWidget>

namespace Ui {
  class BackupFileWidget;
}

class BackupFileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit BackupFileWidget(QWidget *parent = 0);
  ~BackupFileWidget();

private:
  Ui::BackupFileWidget *ui;
};

#endif // STDFILEWIDGET_H
