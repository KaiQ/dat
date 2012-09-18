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

#ifndef CRECORDFILE_H
#define CRECORDFILE_H

#include "file.h"
#include "lcrecordwidget.h"

class CRecordFile : public File
{
public:
  CRecordFile(QWidget *parent, MifareTag tag = 0, int iFileNumber = -1);
  ~CRecordFile();
  int createFile();
  void init ();
  int save(const char* text);
  char* read();

private slots:
  void OK();

private:
  LCRecordWidget *wid;
  char *buffer;
protected:
  int setDockWidget();

};

#endif // CRECORDFILE_H
