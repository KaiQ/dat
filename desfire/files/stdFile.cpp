#include "stdFile.h"
#include "widgets/stdfilewidget.h"
#include "../application.h"
#include "../card.h"


StdFile::StdFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent) :
  DesfireFile(filenumber, settings, new StdFileWidget(), parent)
{
}


StdFile::~StdFile()
{
}


QVariant StdFile::data(int column, int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] Standardfile").arg(filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

void StdFile::setupWidget()
{
  reinterpret_cast<StdFileWidget*>(this->getSubWidget())->setup(*this);
}
