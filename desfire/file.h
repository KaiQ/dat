#ifndef File_H
#define File_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "item.h"


class File : public Item
{
  public:
    File(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent = 0);
    ~File();
    virtual int select();
    void deselect();

  protected:
    uint8_t filenumber;
    mifare_desfire_file_settings settings;
};

#endif // File_H
