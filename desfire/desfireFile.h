#ifndef DESFIRE_FILE_H
#define DESFIRE_FILE_H

#include <nfc/nfc.h>
#include <freefare.h>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include "item.h"


class DesfireFile : public Item
{
  public:
    DesfireFile(uint8_t filenumber,
        mifare_desfire_file_settings settings,
        QWidget* widget = NULL,
        Item* parent = NULL);
    ~DesfireFile();
    int select();
    void deselect();
    FreefareTag getTag();
    uint8_t getFilenumber();

    mifare_desfire_file_settings &getSettings();
    virtual void setupWidget() = 0;
    QWidget* getSubWidget();

  protected:
    uint8_t filenumber;

  private:
    void setupRootWidget();

    mifare_desfire_file_settings settings;
};

#endif // DESFIRE_FILE_H
