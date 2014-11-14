#include "item.h"


Item::Item(Item* parent)
{
  this->parentItem = parent;
  this->active = false;
}


Item::~Item()
{
  qDebug("Destructor Item");
}


Item* Item::child(int row)
{
  return this->children[row];
}


int Item::childCount()
{
  return this->children.count();
}


Item* Item::parent()
{
  return this->parentItem;
}


int Item::row() const
{
  if (this->parentItem)
  {
    return this->parentItem->children.indexOf(const_cast<Item*>(this));
  }

  return 0;
}


void Item::addChild(Item *child)
{
  child->setParent(this);
  this->children.append(child);
}


void Item::setParent(Item *parent)
{
  this->parentItem = parent;
}


int Item::select()
{
  qDebug("setting active");
  this->active = true;
  return 0;
}


void Item::deselect()
{
  qDebug("deselect Item ~.~");
  this->active = false;
}


bool Item::isActive()
{
  return this->active;
}


void Item::setActive(bool value)
{
  this->active = value;
}


Item* Item::getActiveChild()
{
  for (int i = 0; i < this->children.count(); i++)
  {
    if (children[i]->isActive())
      return children[i];
  }

  return NULL;
}



