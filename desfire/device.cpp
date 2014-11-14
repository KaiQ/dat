#include "device.h"


Device::Device(nfc_device *_device, Item* parent) :
  Item(parent),
  device(_device)
{
  this->setActive(true);
}


Device::~Device()
{
  qDebug("Destructor Device");
  qDeleteAll(this->children);
  if (this->isActive())
  {
    qDebug("found active");
    this->deselect();
  }
}


QVariant Device::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return "Device Name";
    //TODO?
  }

  return QVariant();
}


int Device::select()
{
  MifareTag *tags = freefare_get_tags(this->device);

  if (!tags)
    return -1; //TODO ERROR MESSAGE CODE

  for (int i = 0; tags[i]; i++)
  {
    Card *newCard = new Card(tags[i], this);
    this->addChild(newCard);
  }

  this->active = true;
  return this->childCount();
}


void Device::deselect()
{
  qDebug("deselect Device :-)");
  if (this->device)
  {
    qDebug("close Device");
    nfc_close(this->device);
  }
}



nfc_device* Device::getDevice()
{
  return this->device;
}

