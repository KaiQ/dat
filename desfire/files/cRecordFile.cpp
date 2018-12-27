#include "cRecordFile.h"
#include "widgets/crecordfilewidget.h"


CRecordFile::CRecordFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent) :
  DesfireFile(filenumber, settings,new CRecordFileWidget(),  parent)
{
}


CRecordFile::~CRecordFile()
{
}


QVariant CRecordFile::data(int column, int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] CRecordFile").arg(this->filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

void CRecordFile::setupWidget()
{
  //reinterpret_cast<CRecordFileWidget*>(this->getWidget())->setup(*this);
}
