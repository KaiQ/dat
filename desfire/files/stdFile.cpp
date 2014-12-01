#include "stdFile.h"


StdFile::StdFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent) :
  DesfireFile(filenumber, settings, parent)
{
}


StdFile::~StdFile()
{
}


QVariant StdFile::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] Standardfile").arg(this->filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

