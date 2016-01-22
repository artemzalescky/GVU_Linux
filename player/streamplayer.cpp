#include "streamplayer.h"
#include "ui_streamplayer.h"

StreamPlayer::StreamPlayer(QString wDir, iCamera_Mode cameraType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StreamPlayer)
{
    workingDirectory = wDir;
    camType = cameraType;

    ui->setupUi(this);
    ui->widget_3->setVisible(false);

    player = new PlayerQtGstreamer(ui->videowidget);
    player->resize(ui->videowidget->width(), ui->videowidget->height());
    player->setEncoder(PlayerQtGstreamer::Encoder_None);

    di = new Informer();
    QObject::connect((QObject*)di,SIGNAL(newInfo(QString)),player,SLOT(onChangeInfo(QString)));

    TogglePictureSettings(false);
    ui->advComWidget->setVisible(false);

    addCommandsWidget_video = new AddComsWidgetVideo(ui->advComWidget);

    ConnectSlots();

    isplaying = false;
    ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PLAY()));
    ui->playBtn->setToolTip(QString::fromUtf8("Показ"));

    isrecording = false;
    ui->recBtn->setIcon(QIcon(IconLoader::getIcon_REC()));
    ui->recBtn->setToolTip(QString::fromUtf8("Начать запись"));

    ui->snapBtn->setIcon(QIcon(IconLoader::getIcon_SNAP()));
    ui->snapBtn->setToolTip(QString::fromUtf8("Захват кадра"));

    ui->setBtn->setIcon(QIcon(IconLoader::getIcon_COLORSETTINGS()));
    ui->setBtn->setToolTip(QString::fromUtf8("Настройки изображения"));





}
StreamPlayer::~StreamPlayer()
{
    player->stop();
    delete player;
    delete ui;
}

void StreamPlayer::ConnectSlots()
{
    QObject::connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(playBtn_Clicked()));
    QObject::connect(ui->recBtn, SIGNAL(clicked()), this, SLOT(recBtn_Clicked()));
    QObject::connect(ui->snapBtn, SIGNAL(clicked()), this, SLOT(snapBtn_Clicked()));
    QObject::connect(ui->setBtn, SIGNAL(toggled(bool)), this, SLOT(setBtn_Clicked(bool)));

    QObject::connect(ui->setmodeadv, SIGNAL(toggled(bool)), this, SLOT(showAddCommands(bool)));



    QObject::connect(ui->bright, SIGNAL(valueChanged(int)), this, SLOT(changeBrightness(int)));
    QObject::connect(ui->contrast, SIGNAL(valueChanged(int)), this, SLOT(changeContrast(int)));
    QObject::connect(ui->hue, SIGNAL(valueChanged(int)), this, SLOT(changeHue(int)));
    QObject::connect(ui->sat, SIGNAL(valueChanged(int)), this, SLOT(changeSat(int)));
}

void StreamPlayer::TogglePictureSettings(bool toggle)
{
    ui->widget_2->setVisible(toggle);
}

void StreamPlayer::ToggleCameraManage(bool toggle)
{
    ui->widget->setVisible(toggle);
    ui->setmodeadv->setVisible(toggle);
    ui->setmodeadv->raise();
}

void StreamPlayer::ShowCenter()
{
    int s1 = 30, s2 = 2;
    int cX = ui->videowidget->pos().x() + ui->videowidget->size().width()/2;
    int cY = ui->videowidget->pos().y() + ui->videowidget->size().height()/2;

    ui->vLh->move(cX - s1/2, cY - s2/2);
    ui->vLh->setText("");
    ui->vLh->resize(s1,s2);
    QPixmap p1(s1,s2);
    QPainter qp1(&p1);
    qp1.fillRect(0,0,s1,s2,QBrush(QColor(0,255,255)));
    ui->vLh->setPixmap(p1);

    ui->vLv->move(cX - s2/2, cY - s1/2);
    ui->vLv->setText("");
    ui->vLv->resize(s2,s1);
    QPixmap p2(s2,s1);
    QPainter qp2(&p2);
    qp2.fillRect(0,0,s2,s1,QBrush(QColor(0,255,255)));
    ui->vLv->setPixmap(p2);

    ui->vLh->raise();
    ui->vLv->raise();
}
void StreamPlayer::ShowInfo()
{
    QString s1 = QString::fromUtf8("Широта ");
    s1 += "112.3";
    ui->sh->setText(s1);

    QString s2 = QString::fromUtf8("Долгота ");
    s2 += "52.3";
    ui->dolg->setText(s2);


    //ui->infow->raise();

    ui->h->raise();
    ui->sh->raise();
    ui->dolg->raise();
}
bool StreamPlayer::Play()
{
    player->play();
    ShowCenter();
    ShowInfo();
    if (false)
    {
        QMessageBox::information(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("Не удалось начать показ видео"));
        return false;
    }

    isplaying = true;
    ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PAUSE()));
    ui->playBtn->setToolTip(QString::fromUtf8("Пауза"));

    return true;
}
bool StreamPlayer::Pause()
{
    player->pause();

    isplaying = false;
    ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PLAY()));
    ui->playBtn->setToolTip(QString::fromUtf8("Показ"));

    return true;
}

bool StreamPlayer::Record()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString name = QString(workingDirectory);
    name += "video/";
    QString dateDir = date.toString("yyyy-MM-dd");
    QDir videoDir(name);
    if (!videoDir.exists(dateDir))
        videoDir.mkdir(dateDir);
    name += dateDir;
    name += "/";
    name += dateDir;
    name += " ";
    name += time.toString("hh-mm-ss");

    player->record(name);

    isplaying = false;
    isrecording = true;
    ui->recBtn->setIcon(QIcon(IconLoader::getIcon_STOPREC()));
    ui->recBtn->setToolTip(QString::fromUtf8("Остановить запись"));

    ui->playBtn->setEnabled(false);
    ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PLAY()));
    ui->playBtn->setToolTip(QString::fromUtf8("Показ"));

    return true;
}

bool StreamPlayer::StopRecord()
{
    player->stop();

    ui->playBtn->setEnabled(true);
    isrecording = false;
    ui->recBtn->setIcon(QIcon(IconLoader::getIcon_REC()));
    ui->recBtn->setToolTip(QString::fromUtf8("Начать запись"));

    return true;
}

void StreamPlayer::MakeSnap()
{
    QPixmap shot = QPixmap::grabWindow(this->winId());
    QPixmap croped = shot.copy(ui->videowidget->pos().x(),ui->videowidget->pos().y(),ui->videowidget->size().width(),ui->videowidget->size().height());
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString name = QString(workingDirectory);
    name += "photo/";
    QString dateDir = date.toString("yyyy-MM-dd");
    QDir photoDir(name);
    if (!photoDir.exists(dateDir))
        photoDir.mkdir(dateDir);
    name += dateDir;
    name += "/";
    name += dateDir;
    name += " ";
    name += time.toString("hh-mm-ss");
    name += ".png";

    int i = 2;
    QFile * posFile = new QFile(name);
    while (posFile->exists())
    {
        name = QString(workingDirectory);
        name += "photo/";
        name += dateDir;
        name += "/";
        name += dateDir;
        name += " ";
        name += time.toString("hh-mm-ss");
        name += QString(" (%1)").arg(i++);
        name += ".png";
        posFile = new QFile(name);
    }

    croped.save(name);
}

void StreamPlayer::fmScan()
{
    QMessageBox::information(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("scan"));
}
void StreamPlayer::fmToStartPos()
{
    QMessageBox::information(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("to start"));
}

void StreamPlayer::fmLookAfter()
{
    QMessageBox::information(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("look after"));
}
void StreamPlayer::fmShot()
{
    QMessageBox::information(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("shot"));
}

void StreamPlayer::fmAutoShot()
{
    QMessageBox::information(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("autoshot"));
}

void StreamPlayer::playBtn_Clicked()
{
    if (!isplaying)
    {
        Play();
    }
    else
    {
        Pause();
     }
    ui->setmodeadv->raise();
}

void StreamPlayer::recBtn_Clicked()
{
    if (!isrecording)
    {
        Record();
    }
    else
    {
        StopRecord();
        Play();
    }
    ui->setmodeadv->raise();
}

void StreamPlayer::snapBtn_Clicked()
{
    MakeSnap();
    ui->setmodeadv->raise();
}

void StreamPlayer::setBtn_Clicked(bool toggle)
{
    TogglePictureSettings(toggle);
    ToggleCameraManage(!toggle);
}


void StreamPlayer::showAddCommands(bool toggle)
{
    ui->advComWidget->raise();
    ui->advComWidget->setVisible(toggle);

    ui->setmodeadv->raise();
    if(toggle)
        ui->setmodeadv->setText(QString::fromUtf8("Свернуть"));
    else
        ui->setmodeadv->setText(QString::fromUtf8("Настройки ЦН"));

    ui->widget->setVisible(!toggle);
    ui->playBtn->setVisible(!toggle);
    ui->snapBtn->setVisible(!toggle);
    ui->recBtn->setVisible(!toggle);
    ui->setBtn->setVisible(!toggle);
}



void StreamPlayer::changeHue(int h_)
{
    qreal h = (h_ - 50)/50.0;
    player->setHue(h);
}

void StreamPlayer::changeSat(int st_)
{
    qreal st = (st_ - 50)/50.0;
    player->setSaturation(st);
}

void StreamPlayer::changeBrightness(int br_)
{
    qreal br = (br_ - 50)/50.0;
    player->setBrightness(br);
}

void StreamPlayer::changeContrast(int c_)
{
    qreal c = (c_ - 50)/50.0;
    player->setContrast(c);
}

void StreamPlayer::changeCamYaw(int y)
{
    camYaw = y;
    QMessageBox::information(this,"error", "yaw");
}

void StreamPlayer::changeCamPitch(int p)
{
    camPitch = p;
    QMessageBox::information(this,"error", "pitch");
}

void StreamPlayer::changeZoom(int z)
{
    camZoom = z;
    QMessageBox::information(this,"error", "zoom");
}
