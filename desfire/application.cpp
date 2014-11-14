#include "application.h"


Application::Application(MifareDESFireAID _aid, Item* parent) :
  Item(parent),
  aid(_aid)
{
  this->name.sprintf("%06X", mifare_desfire_aid_get_aid(_aid));
}


Application::~Application()
{
  qDebug("Destructor Application");
  qDeleteAll(this->children);
  if (this->isActive())
  {
    qDebug("found active");
    this->deselect();
  }
}


QVariant Application::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return this->name;
  }

  return QVariant();
}



int Application::select()
{
  qDebug("select Application");
  uint8_t *files;
  size_t file_count = 0;
  size_t aid_count = 0;

  Card *card = dynamic_cast<Card *>(this->parent());

  mifare_desfire_select_application (card->getTag(), this->aid);

  mifare_desfire_get_file_ids(card->getTag(), &files, &file_count);

  /*
     if ( mifare_desfire_last_picc_error(tag[lSelTag]) == AUTHENTICATION_ERROR) {
     printf("AUTHENTICATION_ERROR\n");
     fflush(stdout);
     if ( mifare_desfire_authenticate(tag[lSelTag], defaultKeyNumber, defaultKey) < 0 ) {
     Key k(NULL,tag[lSelTag]);
     k.show();
     k.exec();
     k.Auth();
     }
     mifare_desfire_get_file_ids(tag[lSelTag], &files, &file_count);
     }
     */

  struct mifare_desfire_file_settings set;
  memset(&set,0,sizeof(mifare_desfire_file_settings));

  for(int i=0; i<file_count; i++)
  {
    mifare_desfire_get_file_settings(card->getTag(), files[i], &set);
    if(set.file_type == MDFT_STANDARD_DATA_FILE)
    {
      StdFile *file = new StdFile(i, set, this);
      this->addChild(file);
    } else if(set.file_type == MDFT_BACKUP_DATA_FILE)
    {
      BackupFile *file = new BackupFile(i, set, this);
      this->addChild(file);
    } else if(set.file_type == MDFT_VALUE_FILE_WITH_BACKUP)
    {
      ValueFile *file = new ValueFile(i, set, this);
      this->addChild(file);
    } else if(set.file_type == MDFT_LINEAR_RECORD_FILE_WITH_BACKUP)
    {
      LRecordFile *file = new LRecordFile(i, set, this);
      this->addChild(file);
    } else if(set.file_type == MDFT_CYCLIC_RECORD_FILE_WITH_BACKUP)
    {
      CRecordFile *file = new CRecordFile(i, set, this);
      this->addChild(file);
    } else
    {
      printf("Error get settings");
    }
  }

  this->active = true;
  return 0;
}


void Application::deselect()
{
  qDebug("deselect Application");
  //qDeleteAll(this->children);
  this->children.clear();
}
