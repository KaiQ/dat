#ifndef ITEM_H
#define ITEM_H

#include <QVector>
#include <QVariant>


class Item
{
  public:
    Item(Item* parent = 0);
    ~Item();
    virtual QVariant data(int role) const = 0;
    virtual int select() = 0;
    virtual void deselect() = 0;
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
