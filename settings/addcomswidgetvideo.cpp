#include "addcomswidgetvideo.h"
#include "ui_addcomswidgetvideo.h"
#include "QPushButton"

AddComsWidgetVideo::AddComsWidgetVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddComsWidgetVideo)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    prevSelectedPageIndex = 0;
    ConnectSlots();

    //TODO : REMOVE, LOAD SETTINGS FROM CONSTRUCTOR PARAMETER
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //loadSettings(PARAM);
    toDefaultSettings();
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

AddComsWidgetVideo::~AddComsWidgetVideo()
{
    delete ui;
}

void AddComsWidgetVideo::ConnectSlots()
{
    QObject::connect(ui->vset_page0, SIGNAL(toggled(bool)), this, SLOT(toPage0(bool)));
    QObject::connect(ui->vset_page1, SIGNAL(toggled(bool)), this, SLOT(toPage1(bool)));
    QObject::connect(ui->vset_page2, SIGNAL(toggled(bool)), this, SLOT(toPage2(bool)));
    QObject::connect(ui->vset_page3, SIGNAL(toggled(bool)), this, SLOT(toPage3(bool)));
    QObject::connect(ui->vset_page4, SIGNAL(toggled(bool)), this, SLOT(toPage4(bool)));

    QObject::connect(ui->vs_drives, SIGNAL(toggled(bool)), this, SLOT(drivesToggled(bool)));
    QObject::connect(ui->vs_videocam, SIGNAL(toggled(bool)), this, SLOT(camToggled(bool)));

    QObject::connect(ui->vs_hd, SIGNAL(toggled(bool)), this, SLOT(hdToggled(bool)));
    QObject::connect(ui->vs_night, SIGNAL(toggled(bool)), this, SLOT(nightToggled(bool)));
    QObject::connect(ui->vs_still, SIGNAL(toggled(bool)), this, SLOT(stillToggled(bool)));
    QObject::connect(ui->vs_bkgrndLight, SIGNAL(toggled(bool)), this, SLOT(bkgrndToggled(bool)));
    QObject::connect(ui->vs_bw, SIGNAL(toggled(bool)), this, SLOT(bwToggled(bool)));
    QObject::connect(ui->vs_negative, SIGNAL(toggled(bool)), this, SLOT(negativeToggled(bool)));
    QObject::connect(ui->vs_effectsOFF, SIGNAL(clicked()), this, SLOT(effectsOffClicked()));

    QObject::connect(ui->autoExpBtn, SIGNAL(toggled(bool)), this, SLOT(autoExpToggled(bool)));
    QObject::connect(ui->sens_low_Btn, SIGNAL(toggled(bool)), this, SLOT(sensLowToggled(bool)));
    QObject::connect(ui->sens_norm_Btn, SIGNAL(toggled(bool)), this, SLOT(sensNormToggled(bool)));

    QObject::connect(ui->wb_atw_btn, SIGNAL(toggled(bool)), this, SLOT(wbATWToggled(bool)));
    QObject::connect(ui->wb_auto_btn, SIGNAL(toggled(bool)), this, SLOT(wbAutoToggled(bool)));
    QObject::connect(ui->wb_manual_btn, SIGNAL(toggled(bool)), this, SLOT(wbManualToggled(bool)));
    QObject::connect(ui->wb_nn_btn, SIGNAL(toggled(bool)), this, SLOT(wbNNToggled(bool)));
    QObject::connect(ui->wb_n_btn, SIGNAL(toggled(bool)), this, SLOT(wbNToggled(bool)));
    QObject::connect(ui->wb_opt_btn, SIGNAL(toggled(bool)), this, SLOT(wbOPTToggled(bool)));
}

void AddComsWidgetVideo::loadSettings(VideocamSettings newSettings)
{
    ui->vs_drives->setChecked(newSettings.drive_power);
    ui->vs_videocam->setChecked(newSettings.videocam_power);

    ui->vs_hd->setChecked(newSettings.hd);
    ui->vs_night->setChecked(newSettings.night_vision);
    ui->vs_still->setChecked(newSettings.still_image);
    ui->vs_bkgrndLight->setChecked(newSettings.bkrgdLight);

    curSettings.videoeffectsOFF = newSettings.videoeffectsOFF;
    if (newSettings.videoeffectsOFF)
    {
        ui->vs_bw->setChecked(false);
        ui->vs_negative->setChecked(false);
    }
    else
    {
        ui->vs_bw->setChecked(newSettings.bw);
        ui->vs_negative->setChecked(newSettings.negative);
    }

    ui->autoExpBtn->setChecked(newSettings.autoexposition);
    ui->sens_low_Btn->setChecked(!newSettings.sensitivity);
    ui->sens_norm_Btn->setChecked(newSettings.sensitivity);

    switch(newSettings.wb)
    {
    case WHITE_BALANCE_AUTO:
        ui->wb_auto_btn->setChecked(true);
        break;
    case WHITE_BALANCE_ATW:
        ui->wb_atw_btn->setChecked(true);
        break;
    case WHITE_BALANCE_NOT_NATURAL_LIGHT:
        ui->wb_nn_btn->setChecked(true);
        break;
    case WHITE_BALANCE_NATURAL_LIGHT:
        ui->wb_n_btn->setChecked(true);
        break;
    case WHITE_BALANCE_MANUAL:
        ui->wb_manual_btn->setChecked(true);
        break;
    case WHITE_BALANCE_OPT:
        ui->wb_opt_btn->setChecked(true);
        break;
    }

}

void AddComsWidgetVideo::saveSettings()
{

}

void AddComsWidgetVideo::toDefaultSettings()
{
    curSettings.SetDefault();
    loadSettings(curSettings);
}

void AddComsWidgetVideo::toPage0(bool toggled)
{
    if (!toggled)
    {
        preventFromAllPagesOff();
        return;
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->vset_page1->setChecked(false);
    ui->vset_page2->setChecked(false);
    ui->vset_page3->setChecked(false);
    ui->vset_page4->setChecked(false);
    prevSelectedPageIndex = 0;
}

void AddComsWidgetVideo::toPage1(bool toggled)
{
    if (!toggled)
    {
        preventFromAllPagesOff();
        return;
    }

    ui->stackedWidget->setCurrentIndex(1);
    ui->vset_page0->setChecked(false);
    ui->vset_page2->setChecked(false);
    ui->vset_page3->setChecked(false);
    ui->vset_page4->setChecked(false);
    prevSelectedPageIndex = 1;
}

void AddComsWidgetVideo::toPage2(bool toggled)
{
    if (!toggled)
    {
        preventFromAllPagesOff();
        return;
    }

    ui->stackedWidget->setCurrentIndex(2);
    ui->vset_page1->setChecked(false);
    ui->vset_page0->setChecked(false);
    ui->vset_page3->setChecked(false);
    ui->vset_page4->setChecked(false);
    prevSelectedPageIndex = 2;
}

void AddComsWidgetVideo::toPage3(bool toggled)
{
    if (!toggled)
    {
        preventFromAllPagesOff();
        return;
    }

    ui->stackedWidget->setCurrentIndex(3);
    ui->vset_page1->setChecked(false);
    ui->vset_page2->setChecked(false);
    ui->vset_page0->setChecked(false);
    ui->vset_page4->setChecked(false);
    prevSelectedPageIndex = 3;
}

void AddComsWidgetVideo::toPage4(bool toggled)
{
    if (!toggled)
    {
        preventFromAllPagesOff();
        return;
    }

    ui->stackedWidget->setCurrentIndex(4);
    ui->vset_page1->setChecked(false);
    ui->vset_page2->setChecked(false);
    ui->vset_page3->setChecked(false);
    ui->vset_page0->setChecked(false);
    prevSelectedPageIndex = 4;
}

void AddComsWidgetVideo::preventFromAllPagesOff()
{
    if (!ui->vset_page0->isChecked() && !ui->vset_page1->isChecked() && !ui->vset_page2->isChecked() && !ui->vset_page3->isChecked() && !ui->vset_page4->isChecked())
    {
        switch(prevSelectedPageIndex)
        {
        case 0:
            ui->vset_page0->setChecked(true); return;
        case 1:
            ui->vset_page1->setChecked(true); return;
        case 2:
            ui->vset_page2->setChecked(true); return;
        case 3:
            ui->vset_page3->setChecked(true); return;
        case 4:
            ui->vset_page4->setChecked(true); return;
        default:
            ui->vset_page0->setChecked(true); return;
        }
    }
}

//ОБРАБОТЧИКИ СОБЫТИЙ ИНТЕРФЕЙСА

void AddComsWidgetVideo::drivesToggled(bool toggled)
{
    if (toggled)
        turnONdrives();
    else
        turnOFFdrives();
}

void AddComsWidgetVideo::camToggled(bool toggled)
{
    if (toggled)
        turnONcam();
    else
        turnOFFcam();
}


void AddComsWidgetVideo::hdToggled(bool toggled)
{
    if (toggled)
        turnONhd();
    else
        turnOFFhd();
}

void AddComsWidgetVideo::nightToggled(bool toggled)
{
    if (toggled)
        turnONnight();
    else
        turnOFFnight();
}

void AddComsWidgetVideo::stillToggled(bool toggled)
{
    if (toggled)
        turnONstill();
    else
        turnOFFstill();
}

void AddComsWidgetVideo::bkgrndToggled(bool toggled)
{
    if (toggled)
        turnONbkgrndLight();
    else
        turnOFFbkgrndLight();
}

void AddComsWidgetVideo::bwToggled(bool toggled)
{
    if (toggled)
        turnONbw();
    else
        turnOFFbw();
}

void AddComsWidgetVideo::negativeToggled(bool toggled)
{
    if (toggled)
        turnONnegative();
    else
        turnOFFnegative();
}

void AddComsWidgetVideo::effectsOffClicked()
{
    ui->vs_negative->setChecked(false);
    ui->vs_bw->setChecked(false);

    turnOFFeffects();
}


void AddComsWidgetVideo::autoExpToggled(bool toggled)
{
    if (toggled)
        turnOnAutoExp();
    else
        turnOFFAutoExp();
}

void AddComsWidgetVideo::sensNormToggled(bool toggled)
{
    if (toggled)
    {
        turnOnNormSens();
        ui->sens_low_Btn->setChecked(false);
    }
}

void AddComsWidgetVideo::sensLowToggled(bool toggled)
{
    if (toggled)
    {
        turnOnLowSens();
         ui->sens_norm_Btn->setChecked(false);
    }
}

void AddComsWidgetVideo::wbNNToggled(bool toggled)
{
    if (toggled)
        turnOnWB_NN();
    else
        preventFromAllWBOff();
}

void AddComsWidgetVideo::wbNToggled(bool toggled)
{
    if (toggled)
        turnOnWB_N();
    else
        preventFromAllWBOff();
}

void AddComsWidgetVideo::wbAutoToggled(bool toggled)
{
    if (toggled)
        turnOnWB_Auto();
    else
        preventFromAllWBOff();
}

void AddComsWidgetVideo::wbManualToggled(bool toggled)
{
    if (toggled)
        turnOnWB_Manual();
    else
        preventFromAllWBOff();
}

void AddComsWidgetVideo::wbOPTToggled(bool toggled)
{
    if (toggled)
        turnOnWB_OPT();
    else
        preventFromAllWBOff();
}

void AddComsWidgetVideo::wbATWToggled(bool toggled)
{
    if (toggled)
        turnOnWB_ATW();
    else
        preventFromAllWBOff();
}

void AddComsWidgetVideo::preventFromAllWBOff()
{
    if (ui->wb_atw_btn->isChecked() == false &&
            ui->wb_auto_btn->isChecked() == false &&
            ui->wb_manual_btn->isChecked() == false &&
            ui->wb_nn_btn->isChecked() == false &&
            ui->wb_n_btn->isChecked() == false &&
            ui->wb_opt_btn->isChecked() == false)
    {
        switch (prevWB)
        {
        case WHITE_BALANCE_AUTO:
            ui->wb_auto_btn->setChecked(true);
            return;
        case WHITE_BALANCE_ATW:
            ui->wb_atw_btn->setChecked(true);
            return;
        case WHITE_BALANCE_MANUAL:
            ui->wb_manual_btn->setChecked(true);
            return;
        case WHITE_BALANCE_OPT:
            ui->wb_opt_btn->setChecked(true);
            return;
        case WHITE_BALANCE_NOT_NATURAL_LIGHT:
            ui->wb_nn_btn->setChecked(true);
            return;
        case WHITE_BALANCE_NATURAL_LIGHT:
            ui->wb_n_btn->setChecked(true);
            return;
        }
    }
}


//ОБРАБОТЧИКИ КОМАНД

void AddComsWidgetVideo::turnONdrives()
{
    curSettings.drive_power = true;
    ui->vs_drives->setText(QString::fromUtf8("Приводы ЦН - ВЫКЛ"));
}

void AddComsWidgetVideo::turnOFFdrives()
{
    curSettings.drive_power = false;
    ui->vs_drives->setText(QString::fromUtf8("Приводы ЦН - ВКЛ"));
}

void AddComsWidgetVideo::turnONcam()
{
    curSettings.videocam_power = true;
    ui->vs_videocam->setText(QString::fromUtf8("Видеокамера - ВЫКЛ"));
}

void AddComsWidgetVideo::turnOFFcam()
{
    curSettings.videocam_power = false;
    ui->vs_videocam->setText(QString::fromUtf8("Видеокамера - ВКЛ"));
}


void AddComsWidgetVideo::turnONhd()
{
    curSettings.hd = true;
    ui->vs_hd->setText(QString::fromUtf8("Высокое разрешение - ВЫКЛ"));
}

void AddComsWidgetVideo::turnOFFhd()
{
    curSettings.hd = false;
    ui->vs_hd->setText(QString::fromUtf8("Высокое разрешение - ВКЛ"));
}

void AddComsWidgetVideo::turnONnight()
{
    curSettings.night_vision = true;
    ui->vs_night->setText(QString::fromUtf8("Ночное видение - ВЫКЛ"));
}

void AddComsWidgetVideo::turnOFFnight()
{
    curSettings.night_vision = false;
    ui->vs_night->setText(QString::fromUtf8("Ночное видение - ВКЛ"));
}

void AddComsWidgetVideo::turnONstill()
{
    curSettings.still_image = true;
    ui->vs_still->setText(QString::fromUtf8("Заморозка изображения - ВЫКЛ"));
}

void AddComsWidgetVideo::turnOFFstill()
{
    curSettings.still_image = false;
    ui->vs_still->setText(QString::fromUtf8("Заморозка изображения - ВКЛ"));
}

void AddComsWidgetVideo::turnONbkgrndLight()
{
    curSettings.bkrgdLight = true;
    ui->vs_bkgrndLight->setText(QString::fromUtf8("Фоновая подсветка - ВЫКЛ"));
}

void AddComsWidgetVideo::turnOFFbkgrndLight()
{
    curSettings.bkrgdLight = false;
    ui->vs_bkgrndLight->setText(QString::fromUtf8("Фоновая подсветка - ВКЛ"));
}

void AddComsWidgetVideo::turnONnegative()
{
    curSettings.videoeffectsOFF = false;
    curSettings.negative = true;
    ui->vs_negative->setText(QString::fromUtf8("Негатив - ВЫКЛ"));
}

void AddComsWidgetVideo::turnOFFnegative()
{
    curSettings.videoeffectsOFF = curSettings.wb;
    curSettings.negative = false;
    ui->vs_negative->setText(QString::fromUtf8("Негатив - ВКЛ"));
}

void AddComsWidgetVideo::turnONbw()
{
    curSettings.videoeffectsOFF = false;
    curSettings.bw = true;
    ui->vs_bw->setText(QString::fromUtf8("Черно-белый - ВЫКЛ"));
}

void AddComsWidgetVideo::turnOFFbw()
{
    curSettings.videoeffectsOFF = curSettings.negative;
    curSettings.bw = false;
    ui->vs_bw->setText(QString::fromUtf8("Черно-белый - ВКЛ"));
}

void AddComsWidgetVideo::turnOFFeffects()
{
    curSettings.videoeffectsOFF = true;
}


void AddComsWidgetVideo::turnOnAutoExp()
{
    curSettings.autoexposition = true;
}

void AddComsWidgetVideo::turnOFFAutoExp()
{
    curSettings.autoexposition = false;
}

void AddComsWidgetVideo::turnOnNormSens()
{
    curSettings.sensitivity = true;
}

void AddComsWidgetVideo::turnOnLowSens()
{
    curSettings.sensitivity = false;
}

void AddComsWidgetVideo::turnOnWB_NN()
{
    curSettings.wb = WHITE_BALANCE_NOT_NATURAL_LIGHT;
    prevWB = WHITE_BALANCE_NOT_NATURAL_LIGHT;
}

void AddComsWidgetVideo::turnOnWB_N()
{
    curSettings.wb = WHITE_BALANCE_NATURAL_LIGHT;
    prevWB = WHITE_BALANCE_NATURAL_LIGHT;
}

void AddComsWidgetVideo::turnOnWB_Auto()
{
    curSettings.wb = WHITE_BALANCE_AUTO;
    prevWB = WHITE_BALANCE_AUTO;
}

void AddComsWidgetVideo::turnOnWB_Manual()
{
    curSettings.wb = WHITE_BALANCE_MANUAL;
    prevWB = WHITE_BALANCE_MANUAL;
}

void AddComsWidgetVideo::turnOnWB_OPT()
{
    curSettings.wb = WHITE_BALANCE_OPT;
    prevWB = WHITE_BALANCE_OPT;
}

void AddComsWidgetVideo::turnOnWB_ATW()
{
    curSettings.wb = WHITE_BALANCE_ATW;
    prevWB = WHITE_BALANCE_ATW;
}
