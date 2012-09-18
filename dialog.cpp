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

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  format=0;
  random=0;

  connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(toggleFormat(int)));
  connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(toggleRandom(int)));

}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::changeEvent(QEvent *e)
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

int Dialog::getConfigData() {
  return format | random;
}

void Dialog::toggleFormat(int i) {
  format = i;
}

void Dialog::toggleRandom(int i) {
  random = i;
}
