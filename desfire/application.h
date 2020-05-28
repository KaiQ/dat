#ifndef APPLICATION_H
#define APPLICATION_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "item.h"
#include "card.h"

class Application : public Item
{
  public:
    Application(MifareDESFireAID aid, Item* parent = 0);
    virtual ~Application();
    QVariant data(int column, int role) const;
    int select();
    void deselect();
    FreefareTag getTag();

  private:
    MifareDESFireAID aid;
    QString name;
};

#endif // APPLICATION_H
