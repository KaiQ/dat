#ifndef DESFIRE_FILE_H
#define DESFIRE_FILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include "item.h"
#include "widgets/stdfilewidget.h"


class DesfireFile : public Item
{
  public:
    DesfireFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent = 0);
    ~DesfireFile();
    int select();
    void deselect();

  protected:
    uint8_t filenumber;
    mifare_desfire_file_settings settings;
};

#endif // DESFIRE_FILE_H
