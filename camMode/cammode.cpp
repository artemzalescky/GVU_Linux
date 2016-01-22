#include "cammode.h"
#include "ui_cammode.h"

CamMode::CamMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CamMode)
{
    ui->setupUi(this);
}

void CamMode::SetDescription(QWidget * desc)
{
    cameraDescription = desc;
    cameraDescription->move(40,40);
    ui->regim = cameraDescription;
}

CamMode::~CamMode()
{
    delete ui;
}


