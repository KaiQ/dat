#ifndef ITEM_H
#define ITEM_H

#include <QVector>
#include <QVariant>


class Item
{
  public:
    Item(Item* parent = 0);
    ~Item();
    virtual QVariant data(int role) const;
    int childCount();
    Item* parent();
    Item* child(int row);
    int row() const;
    void addChild(Item *child);
    void setParent(Item *parent);

  private:
    QVector<Item*> children;
    Item *parentItem;
};


#endif // ITEM_H
