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
  return 2;
}


QVariant DesfireModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  Item *item = static_cast<Item*>(index.internalPointer());

  if ( role == Qt::BackgroundRole )
  {
    if ( item->isActive() )
    {
      return QColor(23, 192, 6, 50);
    }
  }

  if (index.column() == 1)
  {
    return QString();
  }

  return item->data(index.column(), role);
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
    qDebug() << "selected an invalid index? o.0";
    return;
  }

  Item *item = static_cast<Item*>(index.internalPointer());

  if (item->isActive())
  {
    qDebug() << "activating an active Item";
    return;
  }

  // Get the highest active parent
  Item *activeParent = item;
  while (!activeParent->isActive())
  {
    activeParent = activeParent->parent();
  }

  // find the lowest activated item from the active parent
  Item *lowestActive = activeParent;
  while (lowestActive->getActiveChild())
  {
    lowestActive = lowestActive->getActiveChild();
  }

  // deselect lowest activated item until highest active parent is reached
  while (lowestActive != activeParent)
  {
    lowestActive->deselect();
    lowestActive->setActive(false);
    this->dataChanged(this->createIndex(lowestActive->row(), 0, lowestActive),
                      this->createIndex(lowestActive->row(), columnCount(), lowestActive));
    lowestActive = lowestActive->parent();
  }

  while (activeParent != item->parent())
  {
    Item *nextActiveParent = item;
    while (nextActiveParent->parent() != activeParent)
    {
      nextActiveParent = nextActiveParent->parent();
    }

    if (nextActiveParent->select() < 0)
    {
      qDebug() << "could not activate parent";
      return;
    };
    nextActiveParent->setActive(true);
    activeParent = nextActiveParent;
  }

  int from = item->childCount();
  if (item->select() >= 0)
  {
    item->setActive(true);
    qDebug() << "selecting next active item done";
    beginInsertRows(index,
        from,
        item->childCount());
    endInsertRows();
    this->dataChanged(index, index);
    qDebug() << "events about rows inserted";
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


Card* DesfireModel::getActiveCard()
{
  if (this->rootItem)
    return dynamic_cast<Card*>(this->rootItem->getActiveChild());

  return NULL;
}



Application* DesfireModel::getActiveApplication()
{
  Card* c = getActiveCard();

  if (c)
    return dynamic_cast<Application*>(c->getActiveChild());

  return NULL;
}


DesfireFile* DesfireModel::getActiveFile()
{
  Application* a = getActiveApplication();

  if (a)
    return dynamic_cast<DesfireFile*>(a->getActiveChild());

  return NULL;
}


QWidget* DesfireModel::getWidget(const QModelIndex &index)
{
  if (!index.isValid())
  {
    qDebug() << "selected an index not in list...";
    return new QWidget();
  }

  Item *item = static_cast<Item*>(index.internalPointer());
  return item->getWidget();
}
