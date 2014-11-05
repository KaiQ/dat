#include "item.h"


Item::Item(Item* parent)
{
  this->parentItem = parent;
}


Item::~Item()
{
  qDeleteAll(this->children);
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


QVariant Item::data(int role) const
{
  return "ROOT";
}


void Item::setParent(Item *parent)
{
  this->parentItem = parent;
}
