#include "desfireFile.h"
#include "card.h"
#include "widgets/filewidget.h"


DesfireFile::DesfireFile(uint8_t _filenumber, mifare_desfire_file_settings _settings, QWidget* widget, Item* parent) :
  Item(parent, new FileWidget(widget)),
  filenumber(_filenumber),
  settings(_settings)
{
}

DesfireFile::~DesfireFile()
{
}

int DesfireFile::select()
{
  if (mifare_desfire_get_file_settings(this->getTag(), filenumber, &settings) >= 0)
  {
    reinterpret_cast<FileWidget*>(this->getWidget())->setupRootWidget(this);
    this->setupWidget();
  }
  return 0;
}

void DesfireFile::deselect()
{
}

mifare_desfire_file_settings &DesfireFile::getSettings()
{
  return this->settings;
}

FreefareTag DesfireFile::getTag()
{
  Card *card = reinterpret_cast<Card *>(this->parent()->parent());
  return card->getTag();
}

uint8_t DesfireFile::getFilenumber()
{
  return filenumber;
}

void DesfireFile::setupRootWidget()
{
}

QWidget* DesfireFile::getSubWidget()
{
  return reinterpret_cast<FileWidget*>(this->getWidget())->getSubWidget();
}
