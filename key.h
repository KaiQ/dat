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

#ifndef KEY_H
#define KEY_H

#include <QDialog>
#include <QMessageBox>
#include <nfc/nfc.h>
#include <freefare.h>

namespace Ui {
  class Key;
}

class Key : public QDialog {
  Q_OBJECT
public:
  Key(QWidget *parent = 0);
  Key(QWidget *parent = 0, MifareTag tag = 0);
  ~Key();
  void Auth();
  MifareDESFireKey getKey() {return mKey;}
  int getKeyNumber() {return keyNumber;}

protected:
  void changeEvent(QEvent *e);

private slots:
  void OK();
  void setIKeyLen(int k);

private:
  Ui::Key *ui;
  int iKeyLen;
  uint8_t *key_data;
  uint8_t max_keys;
  int cryptNumber;
  int keyNumber;
  MifareTag mTag;
  MifareDESFireKey mKey;

};


#endif // KEY_H
