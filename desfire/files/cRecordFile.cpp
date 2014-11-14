#include "cRecordFile.h"


CRecordFile::CRecordFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent) :
  File(filenumber, settings, parent)
{
}


CRecordFile::~CRecordFile()
{
}


QVariant CRecordFile::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] CRecordFile").arg(this->filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

