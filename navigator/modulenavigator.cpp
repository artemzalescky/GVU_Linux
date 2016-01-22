#include "modulenavigator.h"
#include "ui_modulenavigator.h"

ModuleNavigator::ModuleNavigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleNavigator)
{
    ui->setupUi(this);
    DefineModuleButtons();
}

ModuleNavigator::~ModuleNavigator()
{
    delete ui;
}

void ModuleNavigator::DefineModuleButtons()
{

}

void ModuleNavigator::mousePressEvent(QMouseEvent *event)
{

}
void ModuleNavigator::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        return;
    if (event->button() == Qt::LeftButton)
        return;
    else
    {
        for (int i = 0; i < 6; i++)
        {
            moduleButtons[i].moduleFrame->setLineWidth(1);
        }
        for (int i = 0; i < 6; i++)
        {
            if (moduleButtons[i].contains(event->pos().x(), event->pos().y()))
            {
                moduleButtons[i].moduleFrame->setLineWidth(3);
                return;
            }
        }
    }
}
void ModuleNavigator::mouseReleaseEvent(QMouseEvent *event)
{

}
