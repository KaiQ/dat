#ifndef STDFILE_H
#define STDFILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "desfire/desfireFile.h"


class StdFile : public DesfireFile
{
  public:
    StdFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent);
    ~StdFile();
    QVariant data(int column, int role) const;
    void setupWidget();

  private:
    QString name;
};

#endif // STDFILE_H
