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

  if ( role == Qt::BackgroundRole )
    if ( item->isActive() )
    {
      qDebug("return green");
      return QColor(Qt::green);
    }

  return item->data(role);
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
    qDebug("selected an invalid index? o.0");
    return;
  }

  Item *item = static_cast<Item*>(index.internalPointer());
  Item *parent = item->parent();
  Item *active = parent->getActiveChild();

  if (active == item)
  {
    qDebug("activating an active Item");
    return;
  }

  if (active)
  {
    qDebug("deselecting active Item first");
    int to = item->childCount();
    active->deselect();
    qDebug("deselecting active Item done");
    /* // brings bugs xD
    beginRemoveRows(index,
        0,
        to);
    endInsertRows();
    */
    QModelIndex oldActiveIndex = this->index(active->row(), index.column(), index.parent());
    this->dataChanged(oldActiveIndex, oldActiveIndex);
  }

  qDebug("selecting next active item");
  int from = item->childCount();
  if (item->select() >= 0)
  {
    qDebug("selecting next active item done");
    //TODO necessary?
    beginInsertRows(index,
        from,
        item->childCount());
    endInsertRows();
    this->dataChanged(index, index);
    qDebug("events about rows inserted");
    //TODO ERROR MESSAGE CODE
    return;
  }
}


void DesfireModel::setDevice(nfc_device *device)
{
  //TODO signal about remove
  delete this->rootItem;

  this->rootItem = new Device(device);
}


void DesfireModel::scanDevice()
{
  int from = this->rootItem->childCount();
  this->rootItem->select();
  beginInsertRows(QModelIndex(),
      from,
      this->rootItem->childCount());
  endInsertRows();
  fflush(stdout);
}
