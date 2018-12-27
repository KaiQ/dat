#ifndef LRECORDFILE_H
#define LRECORDFILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "desfire/desfireFile.h"


class LRecordFile : public DesfireFile
{
  public:
    LRecordFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent);
    ~LRecordFile();
    QVariant data(int column, int role) const;
    void setupWidget();

  private:
    QString name;
};

#endif // LRECORDFILE_H
