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

#include "file.h"
#include "ui_file.h"

File::File(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::File)
{
  ui->setupUi(this);
}

File::File(QWidget *parent, MifareTag tag, int iFileNumber) :
  QDialog(parent),
  ui(new Ui::File)
{
  ui->setupUi(this);

  mTag = tag;

  fileNumber = iFileNumber;

  mifare_desfire_get_file_settings(tag, iFileNumber, &fileInfo);

  ui->spinBox->findChildren<QLineEdit*>().at(0)->setReadOnly(true);

  uint8_t limitedCreditEnable = 0;


  QStringList sList;
  sList << "Plain" << "MACed" << "Enciphered";
  ui->comboBox->addItems(sList);

  mifare_desfire_get_key_settings(mTag, &settings, &max_keys);

  for (int i=0; i<max_keys; i++) {
      ui->comboBox_2->addItem(QString("Key ") + QChar(i+49));
      ui->comboBox_3->addItem(QString("Key ") + QChar(i+49));
      ui->comboBox_4->addItem(QString("Key ") + QChar(i+49));
      ui->comboBox_5->addItem(QString("Key ") + QChar(i+49));
    }

  ui->comboBox_2->addItem("Free Acces");
  ui->comboBox_2->addItem("No Acces");
  ui->comboBox_3->addItem("Free Acces");
  ui->comboBox_3->addItem("No Acces");
  ui->comboBox_4->addItem("Free Acces");
  ui->comboBox_4->addItem("No Acces");
  ui->comboBox_5->addItem("Free Acces");
  ui->comboBox_5->addItem("No Acces");

  mifare_desfire_free_mem(mTag, &freeMem);

  connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(OK()));

}

File::~File()
{
  /*
  printf("Deconstructor File\n");
  fflush(stdout);
  */
  delete ui;
}


void File::changeEvent(QEvent *e)
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


void File::QDialog::keyPressEvent( QKeyEvent * e) {}


int File::save(const char* text)
{
  QMessageBox::information(this,"test","File!",QMessageBox::Yes);
}



void File::OK () {

  long lRead;
  long lWrite;
  long lReadWrite;
  long lChange;
  QString tmp;



  fileNumber = ui->spinBox->value();



  crypt = ui->comboBox->currentIndex();


  if ( ui->comboBox_2->currentIndex() < max_keys )
    lRead = ui->comboBox_2->currentIndex();
  else
    lRead = 15 - (ui->comboBox_2->count() - (ui->comboBox_2->currentIndex() + 1));  // 15 = Max Key Number (No Access)

  if ( ui->comboBox_3->currentIndex() < max_keys )
    lWrite = ui->comboBox_3->currentIndex();
  else
    lWrite = 15 - (ui->comboBox_3->count() - (ui->comboBox_3->currentIndex() + 1));

  if ( ui->comboBox_4->currentIndex() < max_keys )
    lReadWrite = ui->comboBox_4->currentIndex();
  else
    lReadWrite = 15 - (ui->comboBox_4->count() - (ui->comboBox_4->currentIndex() + 1));

  if ( ui->comboBox_5->currentIndex() < max_keys )
    lChange = ui->comboBox_5->currentIndex();
  else
    lChange = 15 - (ui->comboBox_5->count() - (ui->comboBox_5->currentIndex() + 1));

  access_rights = (uint16_t)tmp.sprintf("%lx%lx%lx%lx", lRead, lWrite, lReadWrite, lChange).toLong(NULL,16);

  printf("access rights: %x",access_rights);
  fflush(stdout);


  ui->dockWidget->setWidget(NULL);

  this->accept();
}
