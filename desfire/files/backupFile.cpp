#include "backupFile.h"


BackupFile::BackupFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent) :
  File(filenumber, settings, parent)
{
}


BackupFile::~BackupFile()
{
}


QVariant BackupFile::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] BackupFile").arg(this->filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

