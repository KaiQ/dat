#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>

namespace Ui {
  class FileWidget;
}

class FileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FileWidget(QWidget *parent = 0);
  ~FileWidget();

private:
  Ui::FileWidget *ui;
};

#endif // FILEWIDGET_H
