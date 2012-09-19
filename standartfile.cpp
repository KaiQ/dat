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

#include "standartfile.h"

standartFile::standartFile(QWidget *parent, MifareTag tag, int iFileNumber) : File(parent,tag,iFileNumber)
{
  wid = new StdBackupWidget(this);
  buffer = NULL;

  /*
  printf("Constructor Standart\n");
  fflush(stdout);*/
}

standartFile::~standartFile()
{/*
  printf("Destructor Standart\n");
  fflush(stdout);*/

  if (buffer)
    free(buffer);
}


int standartFile::createFile()
{
  return mifare_desfire_create_std_data_file(mTag, fileNumber, crypt, access_rights, wid->getSize());
}


int standartFile::save(const char* text)
{
  int min = fileSize-1<strlen(text)?fileSize:strlen(text);
  return mifare_desfire_write_data(mTag,fileNumber,0,min,(uint8_t *)text);
}

int standartFile::setDockWidget()
{


}

char* standartFile::read()
{
  /*
  printf("Read Standart\n");
  fflush(stdout);
  */

  fileSize = fileInfo.settings.standard_file.file_size+1;

  if(!buffer)
    buffer = (char *)malloc(sizeof(char) * (fileSize));

  if(!buffer)
    return "Error malloc";

  memset(buffer,0,fileSize);

  if (mifare_desfire_read_data (mTag, this->fileNumber,0,fileSize-1,buffer) < 0)
  {
    free(buffer);
    buffer = NULL;
    return "Error file reading";
  }
  else
    return buffer;
}
