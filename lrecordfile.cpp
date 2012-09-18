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

#include "lrecordfile.h"

LRecordFile::LRecordFile(QWidget *parent, MifareTag tag, int iFileNumber) : File(parent,tag,iFileNumber)
{
  wid = new LCRecordWidget(this);
  wid->init();
  buffer = NULL;

  /*
  printf("Constructor Linear\n");
  fflush(stdout);
  */
}

LRecordFile::~LRecordFile()
{
  /*
  printf("Destructor Linear\n");
  fflush(stdout);
  */

  if(buffer)
    free(buffer);
}

int LRecordFile::createFile()
{
  return mifare_desfire_create_linear_record_file ( mTag, fileNumber, crypt, access_rights, wid->record_size, wid->max_number_of_records);

}


int LRecordFile::save(const char* text)
{
  int min = fileSize<strlen(text)?fileSize:strlen(text);
  mifare_desfire_write_data(mTag,fileNumber,0,min,(uint8_t *)text);
  mifare_desfire_commit_transaction(mTag);
}

int LRecordFile::setDockWidget()
{

}

char* LRecordFile::read()
{
  /*
  printf("Read Linear\n");
  fflush(stdout);
  */

  fileSize = fileInfo.settings.linear_record_file.record_size+1;

  buffer = (char *)malloc(sizeof(char) * fileSize);

  if(!buffer)
    return "Error reading linear record file";

  memset(buffer,0,fileSize);

  mifare_desfire_read_records (mTag, fileNumber, fileInfo.settings.linear_record_file.current_number_of_records, fileSize-1, buffer);

  if(!buffer)
    return "Error linear cyclic record file";
  else
    return buffer;
}
