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

#include "application.h"
#include "ui_application.h"


Application::Application(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Application)
{
  ui->setupUi(this);
}


Application::Application(QWidget *parent, MifareTag tag) :
  QDialog(parent),
  ui(new Ui::Application)
{
  ui->setupUi(this);

  QStringList sList;
  sList << "Plain" << "MACed" << "Enciphered";
  ui->comboBox->addItems(sList);

  connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(OK()));

  mTag = tag;
}


Application::~Application()
{
  delete ui;
}

void Application::changeEvent(QEvent *e)
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

void Application::createApplication()
{

  mifare_desfire_select_application (mTag, NULL);

  if ( mifare_desfire_create_application( mTag, aid, comMode, keyNumbers) < 0 )
    QMessageBox::warning(NULL,"Warning","could not create application",QMessageBox::Yes);
}

void Application::OK()
{
  keyNumbers = ui->spinBox->value();

  switch (ui->comboBox->currentIndex()) {
    case (0): comMode = MDCM_PLAIN;
      break;
    case (1): comMode = MDCM_MACED;
      break;
    case (2): comMode = MDCM_ENCIPHERED;
      break;
    }

  aid = mifare_desfire_aid_new(ui->lineEdit->text().toLongLong(NULL,16));

  accept();

}
