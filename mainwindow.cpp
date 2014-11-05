#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  nfc_init(&this->m_context);
  connect(ui->actionDevice, SIGNAL(triggered()), this, SLOT(deviceSelect()));
  connect(ui->cardList, SIGNAL(doubleClicked()), this, SLOT(cardSelect()));

  this->model = new DesfireModel(this);
  this->ui->cardList->setModel(this->model);

  this->m_device = NULL;
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::deviceSelect()
{
  bool temp;
  size_t device_count;
  QStringList deviceList;
  nfc_device *device;
  nfc_connstring devices[8];

  device_count = nfc_list_devices (m_context,devices, 8);

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

  for (unsigned int d = 0; d < device_count; d++)
  {
    device = nfc_open (m_context,devices[d]);
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

  this->m_device = nfc_open (m_context, devices[deviceList.indexOf(choose)]);
  if (!this->m_device) {
    ui->statusBar->showMessage(" Connecting to nfc device failed",5000);
    return;
  }

  deviceScan();
}


void MainWindow::deviceScan()
{
  if (!this->m_device)
  {
    ui->statusBar->showMessage("No Device Selected",5000);
    return;
  }

  MifareTag *tag = freefare_get_tags(this->m_device);
  if (!tag)
  {
    ui->statusBar->showMessage("Error listing tags",5000);
    return;
  }

  for (int i = 0; tag[i]; i++)
  {
    Card *newCard = new Card(freefare_get_tag_friendly_name(tag[i]),
         freefare_get_tag_uid(tag[i]));
    this->model->addCard(newCard);
  }
}


void MainWindow::cardSelect(const QModelIndex & index)
{
  printf("hier");
  fflush(stdout);
}
