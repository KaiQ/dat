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
  nfc_connstring m_devices[8];
  nfc_context *m_context;
  nfc_device *m_device;
  DesfireModel* model;

private slots:
  void deviceSelect();
  void deviceScan();
  void cardSelect(const QModelIndex & index);
};

#endif // MAINWINDOW_H
