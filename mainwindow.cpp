#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  nfc_init(&this->context);

  this->model = new DesfireModel(this);
  this->ui->treeView->setModel(this->model);

  connect(this->ui->actionDevice,
      SIGNAL(triggered()),
      this,
      SLOT(deviceSelect()));
  connect(this->ui->treeView,
      SIGNAL(doubleClicked(const QModelIndex&)),
      this->model,
      SLOT(select(const QModelIndex&)));
  connect(this->ui->treeView,
      SIGNAL(clicked(const QModelIndex&)),
      this,
      SLOT(updateSelection(const QModelIndex&)));
}


MainWindow::~MainWindow()
{
  delete ui;
  delete this->model;
}


void MainWindow::deviceSelect()
{
  bool temp;
  size_t device_count;
  QStringList deviceList;
  nfc_device *device;
  nfc_connstring devices[8];

  device_count = nfc_list_devices (this->context,devices, 8);

  for (unsigned int d = 0; d < device_count; d++)
  {
    device = nfc_open (this->context,devices[d]);
    deviceList << nfc_device_get_name(device);
    nfc_close(device);
    device = NULL;
  }

  QString choose = QInputDialog::getItem(this,tr("select Device"),tr("Devices:"),deviceList,0,false,&temp);

  if (!temp)
  {
    return;
  }
  // TODO close und modell aktualisieren

  nfc_device *selectedDevice = nfc_open (this->context, devices[deviceList.indexOf(choose)]);
  if (!selectedDevice)
  {
    ui->statusBar->showMessage(" Connecting to nfc device failed",5000);
    return;
  }

  this->model->setDevice(selectedDevice);

  deviceScan();
}


void MainWindow::deviceScan()
{
  this->model->scanDevice();
}


// Change Widget after New Item was clicked
void MainWindow::updateSelection(const QModelIndex & index)
{
  // first remove old... so it's not be deleted
  this->ui->scrollArea->takeWidget();
  this->ui->scrollArea->setWidget(this->model->getWidget(index));
}







