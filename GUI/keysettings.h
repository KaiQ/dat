#ifndef KEYSETTINGS_H
#define KEYSETTINGS_H

#include <QWidget>

namespace Ui {
  class KeySettings;
}

class KeySettings : public QWidget
{
  Q_OBJECT

public:
  explicit KeySettings(QWidget *parent = 0);
  ~KeySettings();

  void setup(uint8_t key_settings, uint8_t max_key_no);

private:
  Ui::KeySettings *ui;
};

#endif // KEYSETTINGS_H
