#ifndef APPLICATION_H
#define APPLICATION_H

#include "defaultFile.h"
#include "key.h"

class Application
{
public:
  Application();

private:
  DefaultFile files[32];
  Key keys[14];

};

#endif // APPLICATION_H
