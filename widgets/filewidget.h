#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include "desfire/desfireFile.h"

namespace Ui {
  class FileWidget;
}

class FileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FileWidget(QWidget *subWidget, QWidget *parent = nullptr);
  ~FileWidget();

  void setupRootWidget(DesfireFile *file);
  QWidget* getSubWidget();

private:
  QWidget *subWidget;
  Ui::FileWidget *ui;
};

#endif // FILEWIDGET_H
