#include "std.h"


QVariant Std::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return QString("[%02X] Standardfile").arg(this->filenumber);
  }

  return QVariant();
}

