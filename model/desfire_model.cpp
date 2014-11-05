#include "desfire_model.h"


DesfireModel::DesfireModel(QObject *parent)
  :QAbstractItemModel(parent)
{
  rootItem = new Item();
}


DesfireModel::~DesfireModel()
{
  delete rootItem;
}


int DesfireModel::rowCount(const QModelIndex & parent) const
{
  Item* item;

  if (!parent.isValid())
    item = this->rootItem;
  else
    item = static_cast<Item*>(parent.internalPointer());

  return item->childCount();
}


int DesfireModel::columnCount(const QModelIndex & /*parent*/) const
{
  return 1;
}


QVariant DesfireModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  Item *item = static_cast<Item*>(index.internalPointer());

  return item->data(role);
}


int DesfireModel::addCard(Card *card)
{
  beginInsertRows(QModelIndex(),
      this->rootItem->childCount(),
      this->rootItem->childCount());
  this->rootItem->addChild(dynamic_cast<Item*>(card));
  endInsertRows();
  return this->rootItem->childCount();
}


QModelIndex DesfireModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  Item* item;

  if (!parent.isValid())
    item = this->rootItem;
  else
    item = static_cast<Item*>(parent.internalPointer());

  Item* child = item->child(row);

  if (child)
    return this->createIndex(row, column, child);

  return QModelIndex();
}


QModelIndex DesfireModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
    return QModelIndex();

  Item* child = static_cast<Item*>(index.internalPointer());
  Item* parent = child->parent();

  if (parent == this->rootItem)
    return QModelIndex();

  return createIndex(parent->row(), 0, parent);
}
