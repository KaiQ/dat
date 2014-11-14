#ifndef VALUEFILE_H
#define VALUEFILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "desfire/file.h"


class ValueFile : public File
{
  public:
    ValueFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent);
    ~ValueFile();
    QVariant data(int role) const;

  private:
    QString name;
};

#endif // VALUEFILE_H
