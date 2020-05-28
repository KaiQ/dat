#include "desfireFile.h"
#include "card.h"
#include "widgets/filewidget.h"


DesfireFile::DesfireFile(uint8_t filenumber,
                         mifare_desfire_file_settings settings,
                         Item *parent) :
  Item(parent, new FileWidget(nullptr)),
  filenumber(filenumber),
  settings(settings)
{
}

DesfireFile::~DesfireFile()
{
}

int DesfireFile::select()
{
  if (mifare_desfire_get_file_settings(this->getTag(), filenumber, &settings) >= 0)
  {
    FileWidget* widget = reinterpret_cast<FileWidget*>(this->getWidget());
    if (widget)
    {
      widget->setupWidget(this);
    }
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

QVariant DesfireFile::data(int /* unused */, int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%1] " + MapFileTypeToString(static_cast<mifare_desfire_file_types>(this->settings.file_type)))
        .arg(this->filenumber, 2, 16, QChar('0'));
  }

  return QVariant();
}

QString const DesfireFile::MapFileTypeToString(mifare_desfire_file_types fileType) const
{
  switch (fileType)
  {
    case MDFT_STANDARD_DATA_FILE:
      return "Standard File";
    case MDFT_BACKUP_DATA_FILE:
      return "Backup File";
    case MDFT_VALUE_FILE_WITH_BACKUP:
      return "Value File";
    case MDFT_LINEAR_RECORD_FILE_WITH_BACKUP:
      return "Linear Record File";
    case MDFT_CYCLIC_RECORD_FILE_WITH_BACKUP:
      return "Cyclic Record File";
    default:
      return "Unknown Filetype";
  }
}
