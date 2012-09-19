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

#include "crecordfile.h"

CRecordFile::CRecordFile(QWidget *parent, MifareTag tag, int iFileNumber) : File(parent,tag,iFileNumber)
{
  wid = new LCRecordWidget(this);
  wid->init();
  buffer = NULL;

  /*
  printf("Constructor Cyclic\n");
  fflush(stdout);*/
}

CRecordFile::~CRecordFile()
{
  /*
  printf("Destructor Cyclic\n");
  fflush(stdout);
  */

  if(buffer)
    free(buffer);
}

int CRecordFile::createFile() {
  return mifare_desfire_create_cyclic_record_file ( mTag, fileNumber, crypt, access_rights, wid->record_size, wid->max_number_of_records);
}


int CRecordFile::save(const char* text)
{
  int min = (fileSize-1)<strlen(text)?fileSize:strlen(text);
  mifare_desfire_write_record(mTag, fileNumber, 0, min, (uint8_t *)text);
  mifare_desfire_commit_transaction(mTag);
}

/*
 *   // Write to the cyclic record file
   res =
   cut_assert_success ("mifare_desfire_write_record()");

   // Overwrite the cyclic record file
   res = mifare_desfire_write_record (tag, 0, 0, 2, (char *)"r.");
   cut_assert_success("mifare_desfire_write_record()");

   res = mifare_desfire_read_records (tag, 0, 0, 1, buffer)
*/

char* CRecordFile::read()
{
  /*
  printf("Read Cyclic\n");
  fflush(stdout);
  */

  fileSize = fileInfo.settings.linear_record_file.record_size+1;

  buffer = (char *)malloc(sizeof(char) * fileSize);

  if(!buffer)
    return "Error malloc cyclic";

  memset(buffer,0,fileSize);

  mifare_desfire_read_records (mTag, fileNumber, 0, fileSize-1, buffer);

  fflush(stdout);

  if(!buffer)
    return "Error reading cyclic record file";
  else
    return buffer;
}



int CRecordFile::setDockWidget()
{

}
