#include "allsettngs.h"
#include "ui_allsettngs.h"

AllSettngs::AllSettngs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllSettngs)
{
    ui->setupUi(this);
}

AllSettngs::~AllSettngs()
{
    delete ui;
}
