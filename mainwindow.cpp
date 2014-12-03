#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  nfc_init(&this->context);

  this->model = new DesfireModel(this);
  this->ui->cardList->setModel(this->model);
  this->ui->cardList->setRootIndex(QModelIndex());
  this->ui->applicationList->setModel(this->model);
  this->ui->fileList->setModel(this->model);
  this->ui->fileList->setRootIndex(QModelIndex());

  connect(this->ui->actionDevice,
      SIGNAL(triggered()),
      this,
      SLOT(deviceSelect()));
  connect(this->ui->cardList,
      SIGNAL(doubleClicked(const QModelIndex&)),
      this->model,
      SLOT(select(const QModelIndex&)));
  connect(this->ui->applicationList,
      SIGNAL(doubleClicked(const QModelIndex&)),
      this->model,
      SLOT(select(const QModelIndex&)));
  connect(this->ui->fileList,
      SIGNAL(doubleClicked(const QModelIndex&)),
      this->model,
      SLOT(select(const QModelIndex&)));
  connect(this->ui->cardList,
      SIGNAL(clicked(const QModelIndex&)),
      this,
      SLOT(updateSelection(const QModelIndex&)));
  connect(this->ui->applicationList,
      SIGNAL(clicked(const QModelIndex&)),
      this,
      SLOT(updateSelection(const QModelIndex&)));
  connect(this->ui->fileList,
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

  /*
  if (this->m_device)
  {
    if (QMessageBox::question(this, "Realy?", "Do You realy want to change the Device?",
          QMessageBox::Ok | QMessageBox::No, QMessageBox::No))
    {
      nfc_close(this->m_device);
      this->m_device = NULL;
    }
    else
      return;
  }
  */

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


void MainWindow::showCardInfo()
{
  if (!this->model)
    return;

  Card* c = this->model->getActiveCard();

  if (!c)
    return;
}


void MainWindow::updateSelection(const QModelIndex & index)
{
  this->ui->scrollArea->takeWidget();
  this->ui->scrollArea->setWidget(this->model->getWidget(index));
}







