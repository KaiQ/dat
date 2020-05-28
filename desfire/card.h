#ifndef CARD_H
#define CARD_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include <QPushButton>
#include "item.h"
#include "device.h"
#include "application.h"


class Card : public Item
{
  public:
    Card(FreefareTag tag, Item* parent = 0);
    virtual ~Card();
    QVariant data(int column, int role) const;
    int select();
    void deselect();
    FreefareTag getTag();
    QString uid;
    QString type;

  private:

    FreefareTag tag;
    MifareDESFireAID *aids;
};

#endif // CARD_H
