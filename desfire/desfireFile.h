#ifndef DESFIRE_FILE_H
#define DESFIRE_FILE_H

#include <freefare.h>

#include <QString>
#include <QWidget>

#include "item.h"

class FileWidget;

class DesfireFile : public Item
{
  public:
    DesfireFile(uint8_t filenumber,
        mifare_desfire_file_settings settings,
        Item* parent = NULL);
    ~DesfireFile();
    int select();
    void deselect();
    FreefareTag getTag();
    uint8_t getFilenumber();
    mifare_desfire_file_settings &getSettings();
    QVariant data(int column, int role) const;
    QString const MapFileTypeToString(mifare_desfire_file_types fileType) const;

  protected:
    uint8_t filenumber;

  private:
    mifare_desfire_file_settings settings;
};

#endif // DESFIRE_FILE_H
