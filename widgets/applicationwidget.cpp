#include "applicationwidget.h"
#include "ui_applicationwidget.h"

ApplicationWidget::ApplicationWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ApplicationWidget),
  keySettings()
{
  ui->setupUi(this);


}

ApplicationWidget::~ApplicationWidget()
{
  delete ui;
}

void ApplicationWidget::setup(Application &application)
{
  uint8_t settings;
  uint8_t max_keys;

  if ( mifare_desfire_get_key_settings (application.getTag(), &settings, &max_keys) < 0)
  {
    qDebug() << "Could not read key settings of application";
    return;
  }

  keySettings.setup(settings, max_keys);

  ui->key_settings->parentWidget()->layout()->replaceWidget(ui->key_settings, &this->keySettings);
}
