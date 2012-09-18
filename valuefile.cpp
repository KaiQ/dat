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

#include "valuefile.h"

ValueFile::ValueFile(QWidget *parent, MifareTag tag, int iFileNumber) : File(parent,tag,iFileNumber)
{
  wid = new ValueWidget(this);
  wid->init(freeMem);

  /*
  printf("Constructor Value\n");
  fflush(stdout);*/
}

ValueFile::~ValueFile()
{/*
  printf("Destructor Value\n");
  fflush(stdout);*/
}

int ValueFile::createFile()
{
  return mifare_desfire_create_value_file (mTag, fileNumber, crypt, access_rights, wid->lowerLimit, wid->upperLimit, wid->value, wid->limitedCreditEnable);
}

/*
// Manipulate the value file
   res = mifare_desfire_credit (tag, 4, 100);
   cut_assert_success ("mifare_desfire_credit()");

   res = mifare_desfire_debit (tag, 4, 97);
   cut_assert_success ("mifare_desfire_debit()");

int32_t value;
   res = mifare_desfire_get_value (tag, 4, &value);
*/


int ValueFile::save(const char* text)
{

}

int ValueFile::setDockWidget()
{

}

char* ValueFile::read()
{
  /*
  printf("Read Value\n");
  fflush(stdout);
  */

  int32_t value;

  if (mifare_desfire_get_value (mTag, fileNumber, &value) < 0)
    return "Error get Value";

  QString buffer;

  buffer.sprintf("Value: %d",value);

  fileSize = buffer.length();

  return strdup(buffer.toAscii());

}


int ValueFile::increase()
{
  mifare_desfire_credit (mTag, fileNumber, 1);
  mifare_desfire_commit_transaction(mTag);
}


int ValueFile::decrease()
{
  mifare_desfire_debit (mTag, fileNumber, 1);
  mifare_desfire_commit_transaction(mTag);
}
