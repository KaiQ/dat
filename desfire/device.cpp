#include "device.h"


Device::Device(nfc_device *_device, Item* parent) :
  Item(parent),
  device(_device)
{
}


Device::~Device()
{
  this->deselect();
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
}


void Device::deselect()
{
}



nfc_device* Device::getDevice()
{
  return this->device;
}

