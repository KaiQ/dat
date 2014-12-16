#ifndef STDFILE_H
#define STDFILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include "widgets/stdfilewidget.h"
#include "desfire/desfireFile.h"


class StdFile : public DesfireFile
{
  public:
    StdFile(uint8_t filenumber, mifare_desfire_file_settings settings, Item* parent);
    ~StdFile();
    QVariant data(int role) const;

  private:
    QString name;
};

#endif // STDFILE_H
