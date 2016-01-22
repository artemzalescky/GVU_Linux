#include "videoplayer.h"
#include "ui_videoplayer.h"

QString DEFAULT_LCDNUMBER_VALUE = "00:00:00";

VideoPlayer::VideoPlayer(QString wordDir, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);

    CreatePhononObjects();
    ConnectSlots();

    filesToPlay = new QStringList();
    currentPlayIndex = -1;
    workingDirectory = wordDir;
    filesToPlay = new QStringList();
    OpenFileDialog::GetStartFileList(workingDirectory,FILE_OPENER_VIDEO_ONLY,filesToPlay);
    UpdateFiles();
    UpdateButtonsState();
    TogglePictureSettings(false);

    isplaying = false;
    ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PLAY()));
    ui->playBtn->setToolTip(QString::fromUtf8("Показ"));

    ui->stopBtn->setIcon(QIcon(IconLoader::getIcon_STOP()));
    ui->stopBtn->setToolTip(QString::fromUtf8("Стоп"));

    ui->prevBtn->setIcon(QIcon(IconLoader::getIcon_PREVIOUS()));
    ui->prevBtn->setToolTip(QString::fromUtf8("Предыдущий"));
    ui->prevBtn->setVisible(false);
    ui->nextBtn->setIcon(QIcon(IconLoader::getIcon_NEXT()));
    ui->nextBtn->setToolTip(QString::fromUtf8("Следующий"));
    ui->nextBtn->setVisible(false);

    ui->snapBtn->setIcon(QIcon(IconLoader::getIcon_SNAP()));
    ui->snapBtn->setToolTip(QString::fromUtf8("Захват кадра"));

    ui->setBtn->setIcon(QIcon(IconLoader::getIcon_COLORSETTINGS()));
    ui->setBtn->setToolTip(QString::fromUtf8("Настройки изображения"));

    ui->openBtn->setIcon(QIcon(IconLoader::getIcon_OPEN()));
    ui->openBtn->setToolTip(QString::fromUtf8("Выбрать файлы"));
}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::ConnectSlots()
{
    QObject::connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(playBtn_Clicked()));
    QObject::connect(ui->stopBtn, SIGNAL(clicked()), this, SLOT(stopBtn_Clicked()));
    QObject::connect(ui->prevBtn, SIGNAL(clicked()), this, SLOT(prevBtn_Clicked()));
    QObject::connect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(nextBtn_Clicked()));
    QObject::connect(ui->snapBtn, SIGNAL(clicked()), this, SLOT(snapBtn_Clicked()));
    QObject::connect(ui->openBtn, SIGNAL(clicked()), this, SLOT(openBtn_Clicked()));
    QObject::connect(ui->setBtn, SIGNAL(toggled(bool)), this, SLOT(setBtn_Clicked(bool)));

    QObject::connect(ui->bright, SIGNAL(valueChanged(int)), this, SLOT(changeBrightness(int)));
    QObject::connect(ui->contrast, SIGNAL(valueChanged(int)), this, SLOT(changeContrast(int)));
    QObject::connect(ui->hue, SIGNAL(valueChanged(int)), this, SLOT(changeHue(int)));
    QObject::connect(ui->sat, SIGNAL(valueChanged(int)), this, SLOT(changeSat(int)));

    QObject::connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(tableWidget_itemDoubleClicked(QListWidgetItem*)));
    QObject::connect(this->videoPlayer_->mediaObject(), SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(videoPlayer_stateChanged(Phonon::State,Phonon::State)));
    QObject::connect(this->videoPlayer_->mediaObject(), SIGNAL(tick(qint64)), this, SLOT(videoPlayer_tick(qint64)));
    QObject::connect(this->videoPlayer_->mediaObject(), SIGNAL(totalTimeChanged(qint64)), this, SLOT(videoPlayer_totalTimeChanged(qint64)));
    QObject::connect(this->videoPlayer_, SIGNAL(finished()), this, SLOT(videoPlayer_finished()));
}
void VideoPlayer::CreatePhononObjects()
{
    videoPlayer_ = new Phonon::VideoPlayer(Phonon::VideoCategory, ui->videowidget);
    videoPlayer_->videoWidget()->setVisible(true);
    videoPlayer_->mediaObject()->setTickInterval(1000);
    videoPlayer_->setGeometry(QRect(0,0,720,576));

    videoPlayer_->show();

    seekSlider_ = new Phonon::SeekSlider(ui->scroolWidget);
    seekSlider_->setMediaObject(videoPlayer_->mediaObject());
    seekSlider_->setVisible(true);
    seekSlider_->setGeometry(QRect(0,0,720,20));
}

void VideoPlayer::UpdateFiles()
{
    filesToPlaySource.clear();
    filesToPlayNames.clear();
    videoSources.clear();
    ui->tableWidget->clear();


    int n = filesToPlay->count();
    for (int i = 0; i < n; i+=2)
    {
       Phonon::MediaSource src((*filesToPlay)[i]);
       videoSources.push_front(src);
       filesToPlaySource.push_front((*filesToPlay)[i]);
       filesToPlayNames.push_front((*filesToPlay)[i+1]);
       ui->tableWidget->insertItem(0,(*filesToPlay)[i + 1]);
    }
    if (n > 0)
    {
        currentPlayIndex = 0;
        ui->tableWidget->setCurrentRow(currentPlayIndex);
    }
    else
        currentPlayIndex = -1;
}
void VideoPlayer::UpdateButtonsState()
{
    if (filesToPlay->count() == 0)
    {
        ui->nextBtn->setEnabled(false);
        ui->prevBtn->setEnabled(false);
        ui->playBtn->setEnabled(false);
        ui->stopBtn->setEnabled(false);
        ui->snapBtn->setEnabled(false);
    }
    else
    {
        ui->nextBtn->setEnabled(true);
        ui->prevBtn->setEnabled(true);
        ui->playBtn->setEnabled(true);
        ui->stopBtn->setEnabled(true);
        ui->snapBtn->setEnabled(true);
    }
}
void VideoPlayer::UpdatePlaying()
{
    if (currentPlayIndex >= 0 && currentPlayIndex < videoSources.count())
    {
        ui->tableWidget->setCurrentRow(currentPlayIndex);
        stopBtn_Clicked();
        playBtn_Clicked();
    }
}

void VideoPlayer::ShowCenter(bool show)
{
    if (show)
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

       ui->vLh->setVisible(true);
       ui->vLv->setVisible(true);

       ui->vLh->raise();
       ui->vLv->raise();
    }
    else
    {
        ui->vLh->setVisible(false);
        ui->vLv->setVisible(false);
    }
}
void VideoPlayer::ShowInfo(bool show)
{
    if (show)
    {
        QString s1 = QString::fromUtf8("Широта ");
        s1 += "112.3";
        ui->sh->setText(s1);

        QString s2 = QString::fromUtf8("Долгота ");
        s2 += "52.3";
        ui->dolg->setText(s2);

        ui->h->setVisible(true);
        ui->sh->setVisible(true);
        ui->dolg->setVisible(true);

        ui->h->raise();
        ui->sh->raise();
        ui->dolg->raise();
    }
    else
    {
        ui->h->setVisible(false);
        ui->sh->setVisible(false);
        ui->dolg->setVisible(false);
    }
}

void VideoPlayer::TogglePictureSettings(bool toggle)
{
    ui->sat->setVisible(toggle);
    ui->bright->setVisible(toggle);
    ui->contrast->setVisible(toggle);
    ui->hue->setVisible(toggle);
    ui->label->setVisible(toggle);
    ui->label_2->setVisible(toggle);
    ui->label_3->setVisible(toggle);
    ui->label_4->setVisible(toggle);

    ui->tableWidget->setVisible(!toggle);
    //ui->nextBtn->setVisible(!toggle);
    //ui->prevBtn->setVisible(!toggle);
    ui->stopBtn->setVisible(!toggle);
    ui->playBtn->setVisible(!toggle);
    ui->openBtn->setVisible(!toggle);
}

void VideoPlayer::Play()
{
    if (currentPlayIndex < 0)
    {
        QMessageBox::information(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("Нечего воспроизводить"));
        return;
    }
    if (!videoPlayer_->isPaused())
        videoPlayer_->play(videoSources[currentPlayIndex]);
    else
        videoPlayer_->play();
}
void VideoPlayer::Pause()
{
    videoPlayer_->pause();
}
void VideoPlayer::Stop()
{
    videoPlayer_->stop();
}
void VideoPlayer::Next()
{
    //TO DO : CORRECT (not more than src num)
    currentPlayIndex++;
    UpdatePlaying();
}
void VideoPlayer::Prev()
{
    //TO DO : CORRECT
    currentPlayIndex--;
    UpdatePlaying();
}
void VideoPlayer::MakeSnap()
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

void VideoPlayer::videoPlayer_totalTimeChanged(qint64 time)
{
    displayTimeTotal_.setHMS(time / (60000*60), (time / 60000) % 60, (time / 1000) % 60);
    ui->totalLCD->display(displayTimeTotal_.toString("hh:mm:ss"));
}
void VideoPlayer::videoPlayer_finished()
{
    stopBtn_Clicked();
    playNext();
}
void VideoPlayer::playNext()
{
    currentPlayIndex++;
    UpdatePlaying();
}
void VideoPlayer::videoPlayer_tick(qint64 time)
{
    QTime displayTime(time / (60000*60), (time / 60000) % 60, (time / 1000) % 60);
    ui->timeLCD->display(displayTime.toString("hh:mm:ss")); // + QString("  ") + displayTimeTotal_.toString("hh:mm:ss"));
}
void VideoPlayer::videoPlayer_stateChanged(Phonon::State newState, Phonon::State oldState)
{
    switch (newState)
    {
        case Phonon::ErrorState:
            if (videoPlayer_->mediaObject()->errorType() == Phonon::FatalError)
            {
                 QMessageBox::information(this,QString::fromUtf8("Фатальная ошибка"),QString::fromUtf8("Воспроизведение невозможно."));
                 stopBtn_Clicked();
            }
            else
            {
                QMessageBox::information(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("Внутренняя ошибка. Возможны проблемы при воспроизведении."));
            }
            break;

        case Phonon::PlayingState:
            break;

        case Phonon::StoppedState:
            ui->timeLCD->display(DEFAULT_LCDNUMBER_VALUE);

            break;

        case Phonon::PausedState:
            break;

        case Phonon::BufferingState:
            break;

        default:
            break;
    }

}

void VideoPlayer::playBtn_Clicked()
{
    if (!isplaying)
    {
        Play();
        ShowCenter(true);
        ShowInfo(true);
        isplaying = true;
        ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PAUSE()));
        ui->playBtn->setToolTip(QString::fromUtf8("Пауза"));
    }
    else
    {
        Pause();
        isplaying = false;
        ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PLAY()));
        ui->playBtn->setToolTip(QString::fromUtf8("Показ"));
    }
}
void VideoPlayer::stopBtn_Clicked()
{
    isplaying = false;
    ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PLAY()));
    ui->playBtn->setToolTip(QString::fromUtf8("Показ"));
    Stop();
}
void VideoPlayer::prevBtn_Clicked()
{
    Prev();
}
void VideoPlayer::nextBtn_Clicked()
{
    Next();
}
void VideoPlayer::snapBtn_Clicked()
{
    MakeSnap();
}
void VideoPlayer::setBtn_Clicked(bool toggle)
{
    TogglePictureSettings(toggle);
}

void VideoPlayer::changeHue(int h_)
{
    qreal h = (h_ - 50)/50.0;
    Phonon::VideoWidget * vW = videoPlayer_->videoWidget();
    vW->setHue(h);
}
void VideoPlayer::changeSat(int br_)
{
    qreal br = (br_ - 50)/50.0;
    Phonon::VideoWidget * vW = videoPlayer_->videoWidget();
    vW->setSaturation(br);
}
void VideoPlayer::changeBrightness(int br_)
{
    qreal br = (br_ - 50)/50.0;
    Phonon::VideoWidget * vW = videoPlayer_->videoWidget();
    vW->setBrightness(br);
}
void VideoPlayer::changeContrast(int c_)
{
    qreal c = (c_ - 50)/50.0;
    Phonon::VideoWidget * vW = videoPlayer_->videoWidget();
    vW->setContrast(c);
}

void VideoPlayer::tableWidget_itemDoubleClicked(QListWidgetItem* item)
{
    currentPlayIndex = ui->tableWidget->currentRow();
    UpdatePlaying();
}

void VideoPlayer::openBtn_Clicked()
{
    filesToPlay->clear();
    QLocale russian(QLocale::Russian, QLocale::RussianFederation);
    QLocale::setDefault(russian);
    OpenFileDialog ofd(workingDirectory,FILE_OPENER_VIDEO_ONLY, filesToPlay, this);
    ofd.setLocale(russian);
    if (ofd.exec() == QDialog::Accepted)
    {
        UpdateFiles();
        UpdateButtonsState();
    }
}
