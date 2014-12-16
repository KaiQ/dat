#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QAbstractTableModel>
#include <nfc/nfc.h>
#include <freefare.h>
#include <model/desfire_model.h>
#include "desfire/card.h"
#include "desfire/application.h"
#include "desfire/desfireFile.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  nfc_context *context;
  DesfireModel* model;

private slots:
  void deviceSelect();
  void deviceScan();
  void updateSelection(const QModelIndex & index);
};

#endif // MAINWINDOW_H
