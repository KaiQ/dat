#ifndef DESFIRE_FILE_H
#define DESFIRE_FILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include "item.h"


class DesfireFile : public Item
{
  public:
    DesfireFile(uint8_t filenumber,
        mifare_desfire_file_settings settings,
        QWidget* widget = NULL,
        Item* parent = NULL);
    ~DesfireFile();
    int select();
    void deselect();

  protected:
    uint8_t filenumber;
    mifare_desfire_file_settings settings;
};

#endif // DESFIRE_FILE_H
