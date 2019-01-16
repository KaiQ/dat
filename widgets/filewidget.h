#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <desfire/desfireFile.h>
#include <interface/fileinterface.h>

namespace Ui {
  class FileWidget;
}

class FileWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FileWidget(QWidget *parent);
  ~FileWidget();
  virtual void setupWidget(DesfireFile *file);

protected:
  FileWidget();
  DesfireFile *file;

private:
  FileInterface *createSubWidget();
  mifare_desfire_file_types fileType;
  FileInterface *subWidget;
  Ui::FileWidget *ui;
};

#endif // FILEWIDGET_H
