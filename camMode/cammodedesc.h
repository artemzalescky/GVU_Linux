#ifndef CAMMODEDESC_H
#define CAMMODEDESC_H

#include <QWidget>
#include "resources/interface.h"
#include "resources/iconloader.h"

namespace Ui {
    class PhotocamModeDesc;
}

/**
 * @brief The CamModeDesc class Класс РЕЖИМ ЦН  в котором показывается (тип, статус, режим)
 *
 * РАЗОБРАТЬСЯ С СТАТУСОМ КАМЕРЫ (Предусмотреть индентификатор включения камеры(данные будут идти по udp с камеры!!!!!!!!!!!!!!)
 */

class CamModeDesc : public QWidget
{
    Q_OBJECT

public:
    explicit CamModeDesc(Payload_Type pType, iCamera_Mode mode, QWidget *parent = 0);
    ~CamModeDesc();

private:
    Ui::PhotocamModeDesc *ui;

    void setON();
    void setOFF();
    void setRegime(iCamera_Mode mode);

    void setType(Payload_Type type);
};

#endif // CAMMODEDESC_H
