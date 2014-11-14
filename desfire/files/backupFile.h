#ifndef BACKUPFILE_H
#define BACKUPFILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "desfire/file.h"


class BackupFile : public File
{
  public:
    BackupFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent);
    ~BackupFile();
    QVariant data(int role) const;

  private:
    QString name;
};

#endif // BACKUPFILE_H
