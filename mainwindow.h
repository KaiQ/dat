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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QInputDialog>
#include <nfc/nfc.h>
#include <freefare.h>
#include <math.h>
#include "dialog.h"
#include "key.h"
#include "application.h"
#include "standartfile.h"
#include "backupfile.h"
#include "crecordfile.h"
#include "lrecordfile.h"
#include "valuefile.h"



#define FORMATABLE  2
#define RANDOMUID   1


namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  static QString QprintLastPiccError(MifareTag tag);


protected:
  void changeEvent(QEvent *e);

private slots:
  void setLabelTxt(QListWidgetItem* Item);
  void fillAfterFileList(QListWidgetItem* Item);
  void fillApplicationList(QListWidgetItem* Item);
  void fillFileList(QListWidgetItem* Item);
  void cardInfo();
  void keySettingsInfo();
  void deviceSelect();
  void deviceScan();
  void freeMemory();
  void formatPicc();
  void setConfiguration();
  void setDefaultKey();
  void applicationAuthentificate();
  void applicationCreate();
  void applicationDelete();
  void createStdFile();
  void createBackupFile();
  void createValueFile();
  void createLRecordFile();
  void createCRecordFile();
  void deleteFile();
  void saveFile();
  void valueFileIncrease();
  void valueFileDecrease();
  void filePrint();

private:
  Ui::MainWindow *ui;
  nfc_device_desc_t devices[8];
  nfc_device_t *device;
  MifareTag *tag;
  MifareDESFireAID *aids;
  uint8_t *files;
  File *selectedFile;

  long lSelTag;
  long lSelAid;
  long lSelFile;
  MifareDESFireKey defaultKey;
  int defaultKeyNumber;
  QString QprintLastPiccError();


};


#endif // MAINWINDOW_H
