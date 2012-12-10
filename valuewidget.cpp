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

#include "valuewidget.h"
#include "ui_valuewidget.h"

ValueWidget::ValueWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ValueWidget)
{
  ui->setupUi(this);
  connect(ui->ValUpLim,SIGNAL(valueChanged(int)),this,SLOT(setValULimit(int)));
  connect(ui->ValLowLim,SIGNAL(valueChanged(int)),this,SLOT(setValLLimit(int)));
  connect(ui->ValVal,SIGNAL(valueChanged(int)),this,SLOT(setValVal(int)));
  connect(ui->ValLimitCredit,SIGNAL(clicked(bool)),this,SLOT(setlimitedCreditEnable(bool)));
  upperLimit = ui->ValUpLim->value();
  lowerLimit = ui->ValLowLim->value();
  value = ui->ValVal->value();
  limitedCreditEnable = ui->ValLimitCredit->isChecked();
  ui->ValLowLim->setMaximum(upperLimit);
  ui->ValUpLim->setMinimum(lowerLimit);
  ui->ValVal->setMaximum(upperLimit);
  ui->ValVal->setMinimum(lowerLimit);
}

ValueWidget::~ValueWidget()
{
  delete ui;
}

void ValueWidget::setValULimit(int i) {
  ui->ValVal->setMaximum(i);
  ui->ValLowLim->setMaximum(i);
  upperLimit = i;
}

void ValueWidget::setValLLimit(int i) {
  ui->ValVal->setMinimum(i);
  ui->ValUpLim->setMinimum(i);
  lowerLimit = i;
}

void ValueWidget::init(int freeMem) {
  //ui->ValUpLim->setMaximum(freeMem);
}

void ValueWidget::setValVal(int i)
{
  value = i;
}

void ValueWidget::setlimitedCreditEnable(bool i)
{
  limitedCreditEnable = i;
}
