#ifndef CARD_H
#define CARD_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include <QVector>
#include "application.h"
#include "item.h"


class Card : public Item
{
public:
  Card(QString, QString);
  QVariant data(int role) const;
  bool select();

private:
  QString uid;
  QString type;
};

#endif // CARD_H
