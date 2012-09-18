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

#ifndef STDBACKUPWIDGET_H
#define STDBACKUPWIDGET_H

#include <QWidget>
#include <QMessageBox>


namespace Ui {
  class StdBackupWidget;
}

class StdBackupWidget : public QWidget
{
  Q_OBJECT

public:
  typedef int ret;
  void init(int freeMem);
  explicit StdBackupWidget(QWidget *parent = 0);
  ~StdBackupWidget();
  int getSize() { return fileSize; };


private:
  Ui::StdBackupWidget *ui;

private slots:
  void change(int);

protected:
  int fileSize;


};



#endif // STDBACKUPWIDGET_H
