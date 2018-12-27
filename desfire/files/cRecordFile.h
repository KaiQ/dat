#ifndef CRECORDFILE_H
#define CRECORDFILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "desfire/desfireFile.h"


class CRecordFile : public DesfireFile
{
  public:
    CRecordFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent);
    ~CRecordFile();
    QVariant data(int column, int role) const;
    void setupWidget();

  private:
    QString name;
};

#endif // CRECORDFILE_H
