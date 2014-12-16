#include "desfireFile.h"


DesfireFile::DesfireFile(uint8_t _filenumber, mifare_desfire_file_settings _settings, QWidget* widget, Item* parent) :
  Item(parent, widget),
  settings(_settings),
  filenumber(_filenumber)
{
}


DesfireFile::~DesfireFile()
{
  qDebug("destructor DesfireFile");
  //TODO
}


int DesfireFile::select()
{
  this->active = true;
  return 0;
}


void DesfireFile::deselect()
{
  this->active = false;
}
