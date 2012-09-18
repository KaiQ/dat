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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QDialog>
#include <QMessageBox>
#include "mainwindow.h"

namespace Ui {
  class Application;
}

class Application : public QDialog {
  Q_OBJECT
public:
  Application(QWidget *parent = 0);
  Application(QWidget *parent = 0, MifareTag tag = 0);
  ~Application();
  void createApplication();

protected:
  void changeEvent(QEvent *e);

private slots:
  void OK();

private:
  Ui::Application *ui;
  int keyNumbers;
  int comMode;
  MifareDESFireAID aid;
  MifareTag mTag;
};

#endif // APPLICATION_H
