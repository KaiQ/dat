#ifndef CREATEAPPLICATION_H
#define CREATEAPPLICATION_H

#include <QDialog>
#include <freefare.h>

namespace Ui {
  class CreateApplication;
}

class CreateApplication : public QDialog
{
  Q_OBJECT

public:
  explicit CreateApplication(QWidget *parent = nullptr);
  ~CreateApplication();

  void setTag(FreefareTag tag);

private:
  Ui::CreateApplication *ui;
  FreefareTag tag;

  bool isValidAid(QString aid);

private slots:
  void createApplication();
};

#endif // CREATEAPPLICATION_H
