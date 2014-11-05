#include "card.h"


Card::Card(QString _type, QString _uid) :
  Item(),
  type(_type),
  uid(_uid)
{
}


QVariant Card::data(int role) const
{
  printf("card data %d\n", role);
  fflush(stdout);
  if ( role == Qt::DisplayRole )
  {
    printf("card data DisplayRole\n");
    fflush(stdout);
    return QString("%1 [%2]")
      .arg(this->type)
      .arg(this->uid);
  }

  return QVariant();
}


bool Card::select()
{
  printf("activated\n");
  fflush(stdout);
  return true;
}
