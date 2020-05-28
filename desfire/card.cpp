#include "card.h"
#include "widgets/cardwidget.h"


Card::Card(FreefareTag _tag, Item* parent) :
  Item(parent),
  tag(_tag)
{
  this->type = freefare_get_tag_friendly_name(_tag);
  this->uid = freefare_get_tag_uid(_tag);
  this->setWidget(new CardWidget());
}


Card::~Card()
{
  qDebug() << "Destructor Card";

  if (this->isActive())
  {
    qDebug() << "found active";
    this->deselect();
  }
}


QVariant Card::data(int /* unused */, int role) const
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
  qDebug() << "select Card";
  size_t aid_count = 0;

  mifare_desfire_connect(this->tag);

  mifare_desfire_get_application_ids (this->tag, &this->aids, &aid_count);

  qDebug() << QString("found %1 aids").arg(aid_count);

  for (unsigned int i = 0; i < aid_count; i++ )
  {
    this->addChild(new Application(this->aids[i], this));
  }

  CardWidget* widget = reinterpret_cast<CardWidget*>(this->getWidget());
  if (widget)
  {
    widget->setup(*this);
  }

  return 0;
}


void Card::deselect()
{
  if (this->tag)
  {
    mifare_desfire_disconnect(this->tag);
  }
}


FreefareTag Card::getTag()
{
  return this->tag;
}

