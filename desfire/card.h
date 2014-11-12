#ifndef CARD_H
#define CARD_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "item.h"
#include "device.h"
#include "application.h"


class Card : public Item
{
public:
  Card(MifareTag tag, Item* parent = 0);
  ~Card();
  QVariant data(int role) const;
  int select();
  void deselect();
  MifareTag getTag();

private:
  QString uid;
  QString type;
  MifareTag tag;
  MifareDESFireAID *aids;
};

#endif // CARD_H
