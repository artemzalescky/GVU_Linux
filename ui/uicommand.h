#ifndef UICOMMAND_H
#define UICOMMAND_H

#include <QWidget>
#include "netWork/protocol.h"
#include "netWork/networkinterface.h"

class UICommand : public QWidget
{
    Q_OBJECT
public:
    explicit UICommand(QWidget *parent = 0);

private:
    NetworkInterface *netWork;

public:
    void sendCommandToPlane(QByteArray data);
};


#endif // UICOMMAND_H
