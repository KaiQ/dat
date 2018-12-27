#include "valueFile.h"
#include "widgets/valuefilewidget.h"


ValueFile::ValueFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent) :
  DesfireFile(filenumber, settings,new ValueFileWidget(),  parent)
{
}


ValueFile::~ValueFile()
{
}


QVariant ValueFile::data(int column, int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] ValueFile").arg(this->filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

void ValueFile::setupWidget()
{
  reinterpret_cast<ValueFileWidget*>(this->getSubWidget())->setup(*this);
}
