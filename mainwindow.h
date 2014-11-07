#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QAbstractTableModel>
#include <nfc/nfc.h>
#include <freefare.h>
#include <model/desfire_model.h>

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
};

#endif // MAINWINDOW_H
