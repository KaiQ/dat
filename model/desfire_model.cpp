#include "desfire_model.h"


DesfireModel::DesfireModel(QObject *parent)
  :QAbstractItemModel(parent)
{
  rootItem = new Device();
}


DesfireModel::~DesfireModel()
{
  delete this->rootItem;
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


void DesfireModel::select(const QModelIndex & index)
{
  if (!index.isValid())
  {
    printf("hier");
    fflush(stdout);
    return;
  }

  Item *item = static_cast<Item*>(index.internalPointer());
  if (item->select() < 0)
  {
    //TODO ERROR MESSAGE CODE
    return;
  }
}


bool DesfireModel::setDevice(nfc_device *device)
{
  delete this->rootItem;

  this->rootItem = new Device(device);
}


void DesfireModel::scanDevice()
{
  beginInsertRows(QModelIndex(),
      this->rootItem->childCount(),
      this->rootItem->childCount());
  this->rootItem->select();
  endInsertRows();
  printf("-> %d\n", this->rootItem->childCount());
  fflush(stdout);
}
