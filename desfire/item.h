#ifndef ITEM_H
#define ITEM_H

#include <QVector>
#include <QVariant>
#include <QWidget>


class Item
{
  public:
    Item(Item* parent = 0, QWidget* widget = 0);
    virtual ~Item() = 0;
    virtual QVariant data(int role) const = 0;
    virtual int select() = 0;
    virtual void deselect() = 0;
    int childCount();
    Item* parent();
    Item* child(int row);
    int row() const;
    void addChild(Item *child);
    void setParent(Item *parent);
    bool isActive();
    void setActive(bool value = false);
    Item* getActiveChild();
    virtual QWidget* getWidget();

  protected:
    void setWidget(QWidget*);
    QVector<Item*> children;
    bool active;

  private:
    Item *parentItem;
    QWidget* widget;
};


#endif // ITEM_H
