#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H

#include <QWidget>
#include <desfire/desfireFile.h>

class FileInterface : public QWidget
{
  Q_OBJECT

public:
  FileInterface(DesfireFile &file) :
    QWidget(),
    file(file)
  {}

  virtual void setupWidget() = 0;

protected:
  DesfireFile &file;
};

#endif // FILEINTERFACE_H
