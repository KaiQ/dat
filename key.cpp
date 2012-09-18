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

#include "key.h"
#include "ui_key.h"
#include "mainwindow.h"

Key::Key(QWidget *parent, MifareTag tag) :
  QDialog(parent),
  ui(new Ui::Key)
{
  ui->setupUi(this);

  mTag = tag;
  iKeyLen = 8;
  key_data = NULL;

  mifare_desfire_get_key_settings(mTag, NULL, &max_keys);

  for (int i=0; i<max_keys; i++) {
    ui->keys->addItem(QChar(i+49));
  }

  QStringList cryptList;
  cryptList << "DES" << "3DES" << "3K3DES" << "AES";
  ui->crypts->addItems(cryptList);

  connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(OK()));
}


Key::~Key()
{
  delete ui;
  if (key_data)
    free(key_data);
}

void Key::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void Key::setIKeyLen(int k) {
  iKeyLen = k;
}


void Key::OK()
{

  key_data = (uint8_t*)malloc(sizeof(uint8_t)*iKeyLen);
  cryptNumber = ui->crypts->currentIndex();
  keyNumber = ui->keys->currentIndex();

  memset(key_data,0,iKeyLen);

  for (int i = 0; i <= ui->lineEdit->text().length()>>1; i++)
  {
    key_data[i] =  (uint8_t)ui->lineEdit->text().mid(i*2,2).toInt(NULL,16);
  }


  switch(cryptNumber) {
    case(0):
      mKey = mifare_desfire_des_key_new (key_data);
      break;
    case(1):
      mKey = mifare_desfire_3des_key_new (key_data);
      break;
    case(2):
      mKey = mifare_desfire_3k3des_key_new (key_data);
      break;
    case(3):
      mKey = mifare_desfire_aes_key_new (key_data);
      break;
  }

  this->accept();
}


void Key::Auth() {

  if (mifare_desfire_authenticate(mTag,keyNumber , mKey) < 0 )
    QMessageBox::warning(NULL,"Warning","Authentification ERROR",QMessageBox::Yes);


}
