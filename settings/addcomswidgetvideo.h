#ifndef ADDCOMSWIDGETVIDEO_H
#define ADDCOMSWIDGETVIDEO_H

#include <QWidget>
#include "resources/interface.h"

namespace Ui {
class AddComsWidgetVideo;
}

class AddComsWidgetVideo : public QWidget
{
    Q_OBJECT
    
public:
    explicit AddComsWidgetVideo(QWidget *parent = 0);
    ~AddComsWidgetVideo();
    
private:
    Ui::AddComsWidgetVideo *ui;
    int prevSelectedPageIndex;
    WHITE_BALANCE prevWB;
    VideocamSettings curSettings;

private:
    void ConnectSlots();
    void preventFromAllPagesOff();
    void loadSettings(VideocamSettings newSettings);
    void saveSettings();
    void toDefaultSettings();

    //управление питанием
    void turnONdrives();   // включить питание приводов
    void turnOFFdrives();  // выключить питание приводов
    void turnONcam();      // включить питание камеры
    void turnOFFcam();     // выключить питание камеры

    //управление режимами ЦН
    void turnONhd(); //включить высокое разрешение
    void turnOFFhd(); //выключить высокое разрешение
    void turnONnight(); //включить режим ночного видения
    void turnOFFnight(); //выключить режим ночного видения
    void turnONstill(); //включить режим замороженного изображения
    void turnOFFstill(); //выключить режим замороженного изображения
    void turnONbkgrndLight(); //включить фоновую подсветку
    void turnOFFbkgrndLight(); //выключить фоновую подсветку
    void turnONnegative();  //включить негатив
    void turnOFFnegative();//выключить негатив
    void turnONbw(); //включить черно белый
    void turnOFFbw(); //выключить черно белый
    void turnOFFeffects(); //выключить видеоэффекты

    void turnOnAutoExp();//включить автоэкспозицию
    void turnOFFAutoExp();//выключить автоэкспозицию
    void turnOnNormSens();//включить режим нормальной чувствительности
    void turnOnLowSens();//включить режим низкой чувствительности
    void turnOnWB_NN();//переключить баланс белого на искусственное освещение
    void turnOnWB_N();//переключить баланс белого на естесственное освещение
    void turnOnWB_Auto();//переключить баланс белого на авто
    void turnOnWB_Manual();//переключить баланс белого на ручной
    void turnOnWB_OPT();//переключить баланс белого на ОРТ
    void turnOnWB_ATW();//переключить баланс белого на АТW


private slots:
    void toPage0(bool toggled);
    void toPage1(bool toggled);
    void toPage2(bool toggled);
    void toPage3(bool toggled);
    void toPage4(bool toggled);

    void drivesToggled(bool toggled);
    void camToggled(bool toggled);

    void nightToggled(bool toggled);
    void bkgrndToggled(bool toggled);
    void hdToggled(bool toggled);
    void stillToggled(bool toggled);
    void bwToggled(bool toggled);
    void negativeToggled(bool toggled);
    void effectsOffClicked();

    void autoExpToggled(bool toggled);
    void sensNormToggled(bool toggled);
    void sensLowToggled(bool toggled);

    void wbNNToggled(bool toggled);
    void wbNToggled(bool toggled);
    void wbAutoToggled(bool toggled);
    void wbManualToggled(bool toggled);
    void wbOPTToggled(bool toggled);
    void wbATWToggled(bool toggled);
    void preventFromAllWBOff();          // гарантирует что хотя бы один баланс белого выбран

};

#endif // ADDCOMSWIDGETVIDEO_H
