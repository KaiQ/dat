#ifndef APPLICATIONWIDGET_H
#define APPLICATIONWIDGET_H

#include <QWidget>
#include <desfire/application.h>
#include <GUI/keysettings.h>

namespace Ui {
  class ApplicationWidget;
}

class ApplicationWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ApplicationWidget(QWidget *parent = 0);
  ~ApplicationWidget();

  void setup(Application &application);

private:
  Ui::ApplicationWidget *ui;
  KeySettings keySettings;
};

#endif // APPLICATIONWIDGET_H
