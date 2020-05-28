#include "createapplication.h"
#include "ui_createapplication.h"

#include <freefare.h>

CreateApplication::CreateApplication(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CreateApplication)
{
  ui->setupUi(this);
  connect(ui->buttonBox, SIGNAL(accepted()),
          this, SLOT(createApplication()));
}

CreateApplication::~CreateApplication()
{
  delete ui;
}

void CreateApplication::setTag(FreefareTag tag)
{
  this->tag = tag;
}

bool CreateApplication::isValidAid(QString aid)
{
  bool error = false;
  int aidNumber = aid.toInt(&error, 16);
  return !error && aidNumber > 0;
}

void CreateApplication::createApplication()
{
  if (isValidAid(ui->aid->text()))
  {
    return;
  }

  uint8_t keyChangeRights = 0;
  if (ui->keyChangeRightsNeedKey->isChecked())
  {
    keyChangeRights = 0xE;
  }
  else if (ui->keyChangeRightsNeedsMaster->isChecked())
  {
    keyChangeRights = 0x0;
  }
  else if (ui->keyChangeRightsCanNotChange->isChecked())
  {
    keyChangeRights = 0xF;
  }
  else if (ui->keyChangeRightsNeedSpecific->isChecked())
  {
    keyChangeRights = ui->specificKey->value() & 0xFF;
  }
  keyChangeRights = keyChangeRights << 4 & 0xFF;

  uint8_t settingsChangeRights = ui->settingsRightsMasterChange->isChecked() << 3 & 0xFF;

  uint8_t fileAlterRights = ui->fileAlterRightsNoMaster->isChecked() << 2 & 0xFF;

  uint8_t directoryAlterRights = ui->directoryAccessRightsFreeListening->isChecked() << 1 & 0xFF;

  uint8_t masterKeyRights = ui->masterKeyRightsNeedMaster->isChecked();

  uint8_t settings = keyChangeRights |
                     settingsChangeRights |
                     fileAlterRights |
                     directoryAlterRights |
                     masterKeyRights;

  int ret = mifare_desfire_create_application(this->tag,
                                              mifare_desfire_aid_new(ui->aid->text().toUInt(nullptr, 16)),
                                              settings,
                                              ui->numKeys->value() & 0xFF);

  // TODO handle error
  if (ret == 0)
  {
    this->close();
  }
}
