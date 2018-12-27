#ifndef BACKUPFILE_H
#define BACKUPFILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "desfire/desfireFile.h"


class BackupFile : public DesfireFile
{
  public:
    BackupFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent);
    ~BackupFile();
    QVariant data(int column, int role) const;
    void setupWidget();

  private:
    QString name;
};

#endif // BACKUPFILE_H
