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

#ifndef LCRECORDWIDGET_H
#define LCRECORDWIDGET_H

#include <QWidget>

namespace Ui {
  class LCRecordWidget;
}

class LCRecordWidget : public QWidget
{
  Q_OBJECT

public:
  explicit LCRecordWidget(QWidget *parent = 0);
  ~LCRecordWidget();
  void init();
  int32_t record_size;
  int32_t max_number_of_records;

private slots:
  void setRecordSize(int i);
  void setMaxNumberOfRecords(int i);


private:
  Ui::LCRecordWidget *ui;
};

#endif // LCRECORDWIDGET_H
