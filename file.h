/*
 *This file is part of "Desfire Access Tool".
 *
 *"Desfire Access Tool" is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *"Desfire Access Tool" is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with "Desfire Access Tool".  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FILE_H
#define FILE_H

#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <nfc/nfc.h>
#include <freefare.h>



namespace Ui {
  class File;
}

class File : public QDialog {
  Q_OBJECT
public:

  File(QWidget *parent = 0);
  File(QWidget *parent, MifareTag tag = 0, int iFileNumber = -1);
  ~File();
  virtual int createFile() = 0;
  virtual int save(const char* text) = 0;
  virtual char* read() = 0;
  int fileSize;


public slots:
  void OK();



protected:
  Ui::File *ui;
  uint8_t settings;
  uint8_t max_keys;
  uint16_t access_rights;
  uint32_t freeMem;
  int32_t fileNumber;
  MifareTag mTag;
  uint8_t crypt;
  struct mifare_desfire_file_settings fileInfo;
  void changeEvent(QEvent *e);
  virtual int setDockWidget() = 0;


};

#endif // FILE_H
