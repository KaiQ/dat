#ifndef STD_H
#define STD_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "desfire/file.h"

class Std : public File
{
public:
  QVariant data(int role) const;

private:
  QString name;
};

#endif // STD_H
