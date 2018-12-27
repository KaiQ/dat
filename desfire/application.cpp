#include "application.h"


Application::Application(MifareDESFireAID _aid, Item* parent) :
  Item(parent, new QPushButton("Application")),
  aid(_aid)
{
  this->name.sprintf("%06X", mifare_desfire_aid_get_aid(_aid));
}


Application::~Application()
{
  qDebug() << "Destructor Application";

  if (this->isActive())
  {
    qDebug() << "found active";
    this->deselect();
  }
}


QVariant Application::data(int column, int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("Application [%1]")
      .arg(this->name);
  }

  return QVariant();
}



int Application::select()
{
  qDebug() << "select Application";
  uint8_t *files;
  size_t file_count = 0;

  Card *card = reinterpret_cast<Card *>(this->parent());

  mifare_desfire_select_application (card->getTag(), this->aid);

  mifare_desfire_get_file_ids(card->getTag(), &files, &file_count);

  struct mifare_desfire_file_settings set;
  memset(&set,0,sizeof(mifare_desfire_file_settings));

  for(size_t i=0; i<file_count; i++)
  {
    mifare_desfire_get_file_settings(card->getTag(), files[i], &set);
    if(set.file_type == MDFT_STANDARD_DATA_FILE)
    {
      StdFile *file = new StdFile(files[i], set, this);
      this->addChild(file);
    } else if(set.file_type == MDFT_BACKUP_DATA_FILE)
    {
      StdFile *file = new StdFile(files[i], set, this);
      //BackupFile *file = new BackupFile(files[i], set, this);
      this->addChild(file);
    } else if(set.file_type == MDFT_VALUE_FILE_WITH_BACKUP)
    {
      ValueFile *file = new ValueFile(files[i], set, this);
      this->addChild(file);
    } else if(set.file_type == MDFT_LINEAR_RECORD_FILE_WITH_BACKUP)
    {
      LRecordFile *file = new LRecordFile(files[i], set, this);
      this->addChild(file);
    } else if(set.file_type == MDFT_CYCLIC_RECORD_FILE_WITH_BACKUP)
    {
      CRecordFile *file = new CRecordFile(files[i], set, this);
      this->addChild(file);
    } else
    {
      qDebug() << "Error get File settings";
    }
  }
  return 0;
}


void Application::deselect()
{
  qDebug() << "deselect Application";
}


