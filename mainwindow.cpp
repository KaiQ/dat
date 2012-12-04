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

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->cardList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(fillApplicationList(QListWidgetItem*)));
  connect(ui->applicationList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(fillFileList(QListWidgetItem*)));
  connect(ui->fileList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(fillAfterFileList(QListWidgetItem*)));
  connect(ui->fileList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(setLabelTxt(QListWidgetItem*)));
  connect(ui->actionCard_Info,SIGNAL(triggered()),this,SLOT(keySettingsInfo()));
  connect(ui->actionKey_Settings_info,SIGNAL(triggered()),this,SLOT(cardInfo()));
  connect(ui->actionScan,SIGNAL(triggered()),this,SLOT(deviceScan()));
  connect(ui->actionDevice,SIGNAL(triggered()),this,SLOT(deviceSelect()));
  connect(ui->actionFree_Memory,SIGNAL(triggered()),this,SLOT(freeMemory()));
  connect(ui->actionFormat_PICC,SIGNAL(triggered()),this,SLOT(formatPicc()));
  connect(ui->actionConfiguration,SIGNAL(triggered()),this,SLOT(setConfiguration()));
  connect(ui->actionSet_Default_Key,SIGNAL(triggered()),this,SLOT(setDefaultKey()));
  connect(ui->actionAuthenticate,SIGNAL(triggered()),this,SLOT(applicationAuthentificate()));
  connect(ui->actionCreate_Application,SIGNAL(triggered()),this,SLOT(applicationCreate()));
  connect(ui->actionDelete_Application,SIGNAL(triggered()),this,SLOT(applicationDelete()));
  connect(ui->actionStandard_File,SIGNAL(triggered()),this,SLOT(createStdFile()));
  connect(ui->actionBackup_File,SIGNAL(triggered()),this,SLOT(createBackupFile()));
  connect(ui->actionValue_File,SIGNAL(triggered()),this,SLOT(createValueFile()));
  connect(ui->actionLinear_Record_File,SIGNAL(triggered()),this,SLOT(createLRecordFile()));
  connect(ui->actionCyclic_Record_File,SIGNAL(triggered()),this,SLOT(createCRecordFile()));
  connect(ui->actionDelete_File,SIGNAL(triggered()),this,SLOT(deleteFile()));
  connect(ui->buttonSave,SIGNAL(clicked()),this,SLOT(saveFile()));
  connect(ui->buttonDelete,SIGNAL(clicked()),this,SLOT(deleteFile()));
  connect(ui->buttonIncrease,SIGNAL(clicked()),this,SLOT(valueFileIncrease()));
  connect(ui->buttonDecrease,SIGNAL(clicked()),this,SLOT(valueFileDecrease()));
  connect(ui->buttonPrintxD,SIGNAL(clicked()),this,SLOT(filePrint()));

  uint8_t key_data_null[8] = { 0,0,0,0,0,0,0,0};
  defaultKey = mifare_desfire_des_key_new_with_version (key_data_null);
  defaultKeyNumber = 0;

  device = NULL;
  tag = NULL;
  aids = NULL;
  lSelTag = -1;
  lSelAid = -1;
  lSelFile = -1;

}

MainWindow::~MainWindow()
{
  if (aids)
    mifare_desfire_free_application_ids(aids);
  if (tag)
    freefare_free_tags(tag);
  if (device)
    nfc_close(device);
  delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void MainWindow::setLabelTxt(QListWidgetItem* item)
{

  if (lSelFile == ui->fileList->currentRow())
    return;

  struct mifare_desfire_file_settings set;
  QString info;
  QString temp;

  lSelFile = ui->fileList->currentRow();

  memset(&set,0,sizeof(mifare_desfire_file_settings));


  mifare_desfire_get_file_settings(tag[lSelTag], ui->fileList->currentItem()->text().toInt(NULL,16), &set);

  File *selectedFile;

  if(set.file_type == MDFT_STANDARD_DATA_FILE){
    selectedFile = new standartFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
    info.append("STANDARD DATA FILE\n");
  }else if(set.file_type == MDFT_BACKUP_DATA_FILE){
    selectedFile = new BackupFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
    info.append("BACKUP FILE\n");
  }else if(set.file_type == MDFT_VALUE_FILE_WITH_BACKUP){
    selectedFile = new ValueFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
    info.append("VALUE FILE\n");
  }else if(set.file_type == MDFT_LINEAR_RECORD_FILE_WITH_BACKUP){
    selectedFile = new LRecordFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
    info.append("LINEAR RECORD FILE\n");
  }else if(set.file_type == MDFT_CYCLIC_RECORD_FILE_WITH_BACKUP){
    selectedFile = new CRecordFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
    info.append("CYCLIC RECORD FILE\n");
  }else
  {
    printf("Error get settings");
    fflush(stdout);
    return;
  }

  info.append(temp.sprintf("\ncommunication_settings\n0x%02X",set.communication_settings));
  info.append(temp.sprintf("\naccess_rights\n0x%02X\n", set.access_rights));

  /*
  printf("access rights: %04X\n",set.access_rights);
  fflush(stdout);
  */

  switch(set.file_type)
  {
    case MDFT_STANDARD_DATA_FILE:
    case MDFT_BACKUP_DATA_FILE:
      info.append(temp.sprintf("\n\nFile size: %d Byte", set.settings.standard_file.file_size));
      break;
    case MDFT_VALUE_FILE_WITH_BACKUP:
      info.append(temp.sprintf("\nlower_limit %d", set.settings.value_file.lower_limit));
      info.append(temp.sprintf("\nupper_limit %d", set.settings.value_file.upper_limit));
      info.append(temp.sprintf("\nlimited_credit_value %d", set.settings.value_file.limited_credit_value));
      info.append(temp.sprintf("\nlimited_credit_enabled %s", set.settings.value_file.limited_credit_enabled?"Yes":"No"));
      break;
    case MDFT_LINEAR_RECORD_FILE_WITH_BACKUP:
    case MDFT_CYCLIC_RECORD_FILE_WITH_BACKUP:
      info.append(temp.sprintf("\nrecord_size %d\nmax_number_of_records %d\ncurrent_number_of_records %d",
                               set.settings.linear_record_file.record_size,
                               set.settings.linear_record_file.max_number_of_records,
                               set.settings.linear_record_file.current_number_of_records));
      break;
  }

  // readFile();
  char* buffer = NULL;

  mifare_desfire_authenticate(tag[lSelTag], defaultKeyNumber, defaultKey);
  buffer = selectedFile->read();


  if (buffer)
  {
    /*
    for(int i=0;i< selectedFile->fileSize-1;i++)
    {
      printf("%2X ",buffer[i]);
    }
    printf("\n");  // DEBUG
    fflush(stdout);
    */

    ui->textEdit->setText(buffer);
  }
  else
    ui->textEdit->setText("Error File reading (NULL)");

  ui->fileInfo->setText(info);

  delete(selectedFile);

}


void MainWindow::fillApplicationList(QListWidgetItem* Item)
{

  if (tag) {
    freefare_free_tags(tag);
    tag = NULL;
  }

  if (aids) {
    mifare_desfire_free_application_ids(aids);
    aids = NULL;
  }

  tag = freefare_get_tags(device);
  if (!tag)
    ui->textEdit->setPlainText("Error listing tags");

  size_t aid_count = 0;
  lSelTag = ui->cardList->currentRow();

  mifare_desfire_connect (tag[lSelTag]);

  if ( mifare_desfire_select_application (tag[lSelTag], NULL) == PERMISSION_ERROR ) 
  {
    if ( mifare_desfire_authenticate(tag[lSelTag], defaultKeyNumber, defaultKey) < 0 ) {
      Key key(this,tag[lSelTag]);
      key.exec();
      if ( key.result() == QDialog::Rejected )
        return;
      key.Auth();
    }
  }


  mifare_desfire_get_application_ids (tag[lSelTag], &aids, &aid_count);

  QString temp;

  for (int i = 0; i < aid_count; i++ )
  {
    ui->applicationList->addItem(temp.sprintf("%06X",mifare_desfire_aid_get_aid(aids[i])));
  }

  // ui->applicationList->sortItems(Qt::AscendingOrder);

  uint8_t key_version;
  mifare_desfire_get_key_version(tag[lSelTag],0, &key_version);
  /*
  printf("Key Version: %02X\n",key_version);
  fflush(stdout);
  */

  //mifare_desfire_select_application (tag[lSelTag], NULL);

  ui->menuApplication->setEnabled(false);
  ui->menuCard->setEnabled(true);
  ui->menuFile->setEnabled(false);

  lSelFile = -1;

}



void MainWindow::fillFileList(QListWidgetItem* Item)
{

  size_t file_count = 0;
  size_t aid_count = 0;

  lSelAid = ui->applicationList->currentRow();

  mifare_desfire_select_application (tag[lSelTag], aids[lSelAid]);

  mifare_desfire_get_file_ids(tag[lSelTag], &files, &file_count);

  if ( mifare_desfire_last_picc_error(tag[lSelTag]) == AUTHENTICATION_ERROR) {
     printf("AUTHENTICATION_ERROR\n");
     fflush(stdout);
    if ( mifare_desfire_authenticate(tag[lSelTag], defaultKeyNumber, defaultKey) < 0 ) {
      Key k(NULL,tag[lSelTag]);
      k.show();
      k.exec();
      k.Auth();
    }
    mifare_desfire_get_file_ids(tag[lSelTag], &files, &file_count);
  }

  if (!files) {
    ui->statusBar->showMessage(QprintLastPiccError(),5000);

    return;
  }

  QString temp;

  //printf("%06X\n",mifare_desfire_aid_get_aid(aids[lSelAid]));
  for(int i=0; i<file_count; i++)
  {
    ui->fileList->addItem(temp.sprintf("%02x",files[i]));
    //printf("  %02X\n",files[i]);
  }

  // ui->fileList->sortItems(Qt::AscendingOrder);
  ui->menuApplication->setEnabled(true);
  ui->menuFile->setEnabled(false);

  lSelFile = -1;
}

void MainWindow::fillAfterFileList(QListWidgetItem* Item)
{
  ui->menuFile->setEnabled(true);
}



void MainWindow::cardInfo() {

  QString infos("UID:\t") ;
  infos.append(freefare_get_tag_uid (tag[lSelTag]));
  infos.append("\nATQA:\t");
  infos.append("TODO");
  infos.append("\nSAK:\t");
  infos.append("TODO");
  QMessageBox::information(this,"Card Info",infos,QMessageBox::Yes);
}

void MainWindow::keySettingsInfo() {

  struct mifare_desfire_version_info info;
  uint8_t settings;
  uint8_t max_keys;

  if (mifare_desfire_get_version(tag[lSelTag], &info) < 0)
    ui->statusBar->showMessage(" Getting version failed",5000);

  if ( mifare_desfire_get_key_settings (tag[lSelTag], &settings, &max_keys) < 0)
    ui->statusBar->showMessage("mifare_desfire_get_key_settings",5000);


  QString infos;
  infos.sprintf("Batch number:\t\t0x%02x%02x%02x%02x%02x"
                "\nProduction date:\t\tweek %x, 20%02x"
                "\n\nHardware Information:"
                "\n\tVendor ID:\t\t0x%02x"
                "\n\tType:\t\t0x%02x"
                "\n\tSubtype:\t\t0x%02x"
                "\n\tVersion:\t\t%d.%d"
                "\n\tStorage size:\t0x%02x (%s%d bytes)"
                "\n\tProtocol:\t\t0x%02x"
                "\nSoftware Information:"
                "\n\tVendor ID:\t\t0x%02x"
                "\n\tType:\t\t0x%02x"
                "\n\tSubtype:\t\t0x%02x"
                "\n\tVersion:\t\t%d.%d"
                "\n\tStorage size:\t0x%02x (%s%d bytes)"
                "\n\tProtocol:\t\t0x%02x"
                "\n\nMaster Key settings:\t\t0x%02x"
                "\nconfiguration changeable:\t0x%02x"
                "\nPICC Master Key not\nrequired for create / delete:\t0x%02x"
                "\nFree directory list\naccess without PICC Master Key:\t0x%02x"
                "\nAllow changing the Master Key:\t0x%02x",
                info.batch_number[0], info.batch_number[1], info.batch_number[2], info.batch_number[3], info.batch_number[4],
      info.production_week, info.production_year,
      info.hardware.vendor_id,
      info.hardware.type,
      info.hardware.subtype,
      info.hardware.version_major,info.hardware.version_minor,
      info.hardware.storage_size, (info.hardware.storage_size & 1) ? ">" : "=", (int)pow (2, info.hardware.storage_size >> 1),
      info.hardware.protocol,
      info.software.vendor_id,
      info.software.type,
      info.software.subtype,
      info.software.version_major, info.software.version_minor,
      info.software.storage_size, (info.software.storage_size & 1) ? ">" : "=", (int)pow (2, info.software.storage_size >> 1),
      info.software.protocol,
      settings,
      settings & 0x08,
      settings & 0x04,
      settings & 0x02,
      settings & 0x01);


  QMessageBox::information(this,"Key Settings Info",infos,QMessageBox::Yes);
}


void MainWindow::deviceScan() {

  if (!device) {
    ui->statusBar->showMessage("No Device Selected",5000);
    return;
  }

  if (aids) {
    mifare_desfire_free_application_ids(aids);
    aids = NULL;
  }

  if (tag) {
    freefare_free_tags(tag);
    tag = NULL;
  }

  tag = freefare_get_tags(device);
  if (!tag) {
    ui->statusBar->showMessage("Error listing tags",5000);
    return;
  }

  for (int i = 0; tag[i]; i++) {
    ui->cardList->addItem(freefare_get_tag_friendly_name(tag[i]));

  }

  ui->menuCard->setEnabled(false);
  ui->menuApplication->setEnabled(false);
}

void MainWindow::deviceSelect() {
  bool temp;
  size_t device_count;

  device_count = nfc_list_devices (NULL,devices, 8);

  QStringList deviceList;

  if (device) {
    nfc_close(device);
    device = NULL;
  }

  if (!device_count) {
    deviceList << "No Device Found";
  }

  for (unsigned int d = 0; d < device_count; d++) {
    device = nfc_open (NULL,devices[d]);
    deviceList << nfc_device_get_name(device);
    nfc_close(device);
  }

  QString choose = QInputDialog::getItem(this,"select Device","Devices:",deviceList,0,false,&temp);

  if (!temp || choose == "No Device Found")
    return;

  device = NULL;

  device = nfc_open (NULL, devices[deviceList.indexOf(choose)]);
  if (!device) {
    ui->statusBar->showMessage(" Connecting to nfc device failed",5000);
    return;
  }

  deviceScan();

}



QString MainWindow::QprintLastPiccError(){


  switch(mifare_desfire_last_picc_error(tag[lSelTag])){
    case OPERATION_OK:
      return "OPERATION_OK";
      break;
    case NO_CHANGES:
      return "NO_CHANGES";
      break;
    case OUT_OF_EEPROM_ERROR:
      return "OUT_OF_EEPROM_ERROR";
      break;
    case ILLEGAL_COMMAND_CODE:
      return "ILLEGAL_COMMAND_CODE";
      break;
    case INTEGRITY_ERROR:
      return "INTEGRITY_ERROR";
      break;
    case NO_SUCH_KEY:
      return "NO_SUCH_KEY";
      break;
    case LENGTH_ERROR:
      return "LENGTH_ERROR";
      break;
    case PERMISSION_ERROR:
      return "PERMISSION_ERROR";
      break;
    case PARAMETER_ERROR:
      return "PARAMETER_ERROR";
      break;
    case APPLICATION_NOT_FOUND:
      return "APPLICATION_NOT_FOUND";
      break;
    case APPL_INTEGRITY_ERROR:
      return "APPL_INTEGRITY_ERROR";
      break;
    case AUTHENTICATION_ERROR:
      return "AUTHENTICATION_ERROR";
      break;
    case ADDITIONAL_FRAME:
      return "ADDITIONAL_FRAME";
      break;
    case BOUNDARY_ERROR:
      return "BOUNDARY_ERROR";
      break;
    case PICC_INTEGRITY_ERROR:
      return "PICC_INTEGRITY_ERROR";
      break;
    case COMMAND_ABORTED:
      return "COMMAND_ABORTED";
      break;
    case PICC_DISABLED_ERROR:
      return "PICC_DISABLED_ERROR";
      break;
    case COUNT_ERROR:
      return "COUNT_ERROR";
      break;
    case DUPLICATE_ERROR:
      return "DUPLICATE_ERROR";
      break;
    case EEPROM_ERROR:
      return "EEPROM_ERROR";
      break;
    case FILE_NOT_FOUND:
      return "FILE_NOT_FOUND";
      break;
    case FILE_INTEGRITY_ERROR:
      return "FILE_INTEGRITY_ERROR";
      break;
    default:
      return "Unknown error";
  }
}


void MainWindow::freeMemory() {
  //TODO: These options can only be applied to a ev1 Tag

  uint32_t size = 0;

  if( mifare_desfire_free_mem(tag[lSelTag], &size) < 0)
    ui->statusBar->showMessage("Getting free memory failed",5000);
  else
    ui->statusBar->showMessage(tr("Free memory: %1 Byte").arg(size));
}


void MainWindow::formatPicc() {

  if ( mifare_desfire_format_picc(tag[lSelTag]) < 0 )
  {
    mifare_desfire_authenticate(tag[lSelTag], defaultKeyNumber, defaultKey);
    if ( mifare_desfire_format_picc(tag[lSelTag]) < 0 )
    {
      ui->statusBar->showMessage("Format failure",5000);
      return;
    }    
  }
  ui->statusBar->showMessage("Card sucessfully deleted",5000);

}

void MainWindow::setConfiguration() {

  Dialog dialog;
  dialog.exec();
  int tmp = dialog.getConfigData();

  if ( mifare_desfire_set_configuration(tag[lSelTag], tmp & FORMATABLE, tmp & RANDOMUID) < 0 ) {
    if ( mifare_desfire_last_picc_error(tag[lSelTag]) == AUTHENTICATION_ERROR) {
      if ( mifare_desfire_authenticate(tag[lSelTag], defaultKeyNumber, defaultKey) < 0 ) {
        Key key(NULL,tag[lSelTag]);
        key.exec();
        if ( key.result() == QDialog::Rejected )
          return;
        key.Auth();
      }
      mifare_desfire_set_configuration(tag[lSelTag], tmp & FORMATABLE, tmp & RANDOMUID);
    }
    else ui->statusBar->showMessage(QprintLastPiccError(),5000);
  }
  else ui->statusBar->showMessage("NO EV1",5000);

}


void MainWindow::setDefaultKey() {
  Key key(this,tag[lSelTag]);
  key.exec();
  if ( key.result() == QDialog::Rejected )
    return;

  mifare_desfire_set_default_key(tag[lSelTag], key.getKey());
  if (defaultKey)
    free(defaultKey);
  defaultKey = key.getKey();
  defaultKeyNumber = key.getKeyNumber();

}


void MainWindow::applicationAuthentificate() {
  uint8_t *files = NULL;
  size_t file_count = 0;

  Key key(this,tag[lSelTag]);
  key.exec();

  if ( key.result() == QDialog::Rejected )
    return;

  key.Auth();

  mifare_desfire_get_file_ids(tag[lSelTag], &files, &file_count);

  if (!files) {
    ui->statusBar->showMessage(QprintLastPiccError(),5000);
    return;
  }

  QString temp;

  for(int i=0; i<file_count; i++)
    ui->fileList->addItem(temp.sprintf("%02x",files[i]));
  ui->menuApplication->setEnabled(true);
}


void MainWindow::applicationCreate() {
  Application app(this,tag[lSelTag]);
  app.exec();
  if ( app.result() == QDialog::Rejected )
    return;
  app.createApplication();
  ui->applicationList->clear();
  ui->fileList->clear();
  ui->menuApplication->setEnabled(false);
  ui->menuCard->setEnabled(false);
}

void MainWindow::applicationDelete() {
  mifare_desfire_delete_application(tag[lSelTag], aids[lSelAid]);
  // printf("aid: %X\n",lSelAid);
  ui->applicationList->clear();
  ui->fileList->clear();
  ui->menuApplication->setEnabled(false);
  ui->menuCard->setEnabled(false);
}


void MainWindow::createStdFile() {
  standartFile file(NULL,tag[lSelTag]);
  file.exec();
  if (file.result() == QDialog::Rejected)
    return;

  if ( file.createFile() < 0 )
    ui->statusBar->showMessage(QprintLastPiccError(),5000);
}

void MainWindow::createBackupFile()
{
  BackupFile file(NULL,tag[lSelTag]);
  file.exec();
  if (file.result() == QDialog::Rejected)
    return;

  if ( file.createFile() < 0 )
    ui->statusBar->showMessage(QprintLastPiccError(),5000);
}

void MainWindow::createValueFile() {
  ValueFile file(NULL,tag[lSelTag]);
  file.exec();
  if (file.result() == QDialog::Rejected)
    return;

  if ( file.createFile() < 0 )
    ui->statusBar->showMessage(QprintLastPiccError(),5000);
}

void MainWindow::createLRecordFile() {
  LRecordFile file(NULL,tag[lSelTag]);
  file.exec();
  if (file.result() == QDialog::Rejected)
    return;

  if ( file.createFile() < 0 )
    ui->statusBar->showMessage(QprintLastPiccError(),5000);
}

void MainWindow::createCRecordFile() {
  CRecordFile file(NULL,tag[lSelTag]);
  file.exec();
  if (file.result() == QDialog::Rejected)
    return;

  if ( file.createFile() < 0 )
    ui->statusBar->showMessage(QprintLastPiccError(),5000);
}

void MainWindow::deleteFile()
{
  if ( ! ui->fileList->currentItem() )
  {
    ui->statusBar->showMessage("Please select a file",5000);
    return;
  }

  mifare_desfire_delete_file(tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
}


void MainWindow::saveFile()
{
  if ( ! ui->fileList->currentItem() )
  {
    ui->statusBar->showMessage("Please select a file",5000);
    return;
  }

  struct mifare_desfire_file_settings set;
  mifare_desfire_get_file_settings(tag[lSelTag], ui->fileList->currentItem()->text().toInt(NULL,16), &set);

  File *selectedFile;

  if(set.file_type == MDFT_STANDARD_DATA_FILE){
    selectedFile = new standartFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
  }
  else if(set.file_type == MDFT_BACKUP_DATA_FILE){
    selectedFile = new BackupFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
  }else if(set.file_type == MDFT_VALUE_FILE_WITH_BACKUP){
    selectedFile = new ValueFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
  }else if(set.file_type == MDFT_LINEAR_RECORD_FILE_WITH_BACKUP){
    selectedFile = new LRecordFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
  }else if(set.file_type == MDFT_CYCLIC_RECORD_FILE_WITH_BACKUP){
    selectedFile = new CRecordFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));
  }else
    return;

  selectedFile->save(ui->textEdit->toPlainText().toAscii());

  delete(selectedFile);

}


void MainWindow::valueFileIncrease()
{
  struct mifare_desfire_file_settings set;
  mifare_desfire_get_file_settings(tag[lSelTag], ui->fileList->currentItem()->text().toInt(NULL,16), &set);

  if(set.file_type != MDFT_VALUE_FILE_WITH_BACKUP)
    return;

  ValueFile selectedFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));

  selectedFile.increase();
}


void MainWindow::valueFileDecrease()
{
  struct mifare_desfire_file_settings set;
  mifare_desfire_get_file_settings(tag[lSelTag], ui->fileList->currentItem()->text().toInt(NULL,16), &set);

  if(set.file_type != MDFT_VALUE_FILE_WITH_BACKUP)
    return;

  ValueFile selectedFile(NULL,tag[lSelTag],ui->fileList->currentItem()->text().toInt(NULL,16));

  selectedFile.decrease();
}


void MainWindow::filePrint()
{
  // current testing function
  // no real printing function planned :-)


}
