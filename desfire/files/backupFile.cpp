#include "backupFile.h"
#include "widgets/backupfilewidget.h"


BackupFile::BackupFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent) :
  DesfireFile(filenumber, settings, new BackupFileWidget(), parent)
{
}


BackupFile::~BackupFile()
{
}


QVariant BackupFile::data(int column, int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] BackupFile").arg(this->filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

void BackupFile::setupWidget()
{
  //reinterpret_cast<BackupFileWidget*>(this->getWidget())->setup(*this);
}

