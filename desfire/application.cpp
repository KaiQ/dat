#include "application.h"


Application::Application(MifareDESFireAID _aid, Item* parent) :
  Item(parent),
  aid(_aid)
{
  this->name.sprintf("%06X", mifare_desfire_aid_get_aid(_aid));
}


Application::~Application()
{
  //TODO
}


QVariant Application::data(int role) const
{
  if ( role == Qt::DisplayRole )
  {
    return this->name;
  }

  return QVariant();
}



int Application::select()
{
}


void Application::deselect()
{
}
