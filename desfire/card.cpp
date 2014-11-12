#include "card.h"


Card::Card(MifareTag _tag, Item* parent) :
  Item(parent),
  tag(_tag)
{
  this->type = freefare_get_tag_friendly_name(_tag);
  this->uid = freefare_get_tag_uid(_tag);
}


Card::~Card()
{
  qDebug("Destructor Card");
  qDeleteAll(this->children);

  if (this->isActive())
  {
    qDebug("found active");
    this->deselect();
  }
}


QVariant Card::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("%1 [%2]")
      .arg(this->type)
      .arg(this->uid);
  }

  return QVariant();
}


int Card::select()
{
  qDebug("select Card");
  size_t aid_count = 0;

  mifare_desfire_connect(this->tag);

  mifare_desfire_get_application_ids (this->tag, &this->aids, &aid_count);

  printf("found %ld aids\n", aid_count);
  fflush(stdout);

  for (unsigned int i = 0; i < aid_count; i++ )
  {
    Application *newApplication = new Application(this->aids[i], this);
    this->addChild(newApplication);
  }

  return 0;
}


void Card::deselect()
{
  qDebug("deselect Card");
  if (this->tag)
    mifare_desfire_disconnect(this->tag);
}


MifareTag Card::getTag()
{
  return this->tag;
}
