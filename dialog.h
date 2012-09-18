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

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>


namespace Ui {
  class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT
public:
  Dialog(QWidget *parent = 0);
  ~Dialog();
  int getConfigData();


protected:
  void changeEvent(QEvent *e);
  int format;
  int random;

private slots:
  void toggleFormat(int i);
  void toggleRandom(int i);

private:
  Ui::Dialog *ui;


};

#endif // DIALOG_H
