#include "lRecordFile.h"


LRecordFile::LRecordFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent) :
  DesfireFile(filenumber, settings, parent)
{
}


LRecordFile::~LRecordFile()
{
}


QVariant LRecordFile::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] lRecordFile").arg(this->filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

