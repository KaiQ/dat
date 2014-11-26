#include "file.h"


File::File(uint8_t _filenumber, mifare_desfire_file_settings _settings, Item* parent) :
  Item(parent),
  settings(_settings),
  filenumber(_filenumber)
{
}


File::~File()
{
  qDebug("destructor File");
  //TODO
}


int File::select()
{
  this->active = true;
  return 0;
}


void File::deselect()
{
  this->active = false;
}
