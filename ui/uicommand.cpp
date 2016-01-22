#include "uicommand.h"

UICommand::UICommand(QWidget *parent) : QWidget(parent)
{
    netWork = new NetworkInterface();
}

void UICommand::sendCommandToPlane(QByteArray data)
{
    netWork->writeData(data);
}



