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

#include "lcrecordwidget.h"
#include "ui_lcrecordwidget.h"

LCRecordWidget::LCRecordWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LCRecordWidget)
{
  ui->setupUi(this);
  connect(ui->RecMaxNbr,SIGNAL(valueChanged(int)),this,SLOT(setMaxNumberOfRecords(int)));
  connect(ui->RecSize,SIGNAL(valueChanged(int)),this,SLOT(setRecordSize(int)));
  max_number_of_records = ui->RecMaxNbr->value();
  record_size = ui->RecSize->value();
}

LCRecordWidget::~LCRecordWidget()
{
  delete ui;
}


void LCRecordWidget::init() {
  ui->LCRecordBox->setEnabled(true);
}


void LCRecordWidget::setRecordSize(int i)
{
  max_number_of_records = i;
}

void LCRecordWidget::setMaxNumberOfRecords(int i)
{
  record_size = i;
}
