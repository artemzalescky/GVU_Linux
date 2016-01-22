#include "reportprepare.h"
#include "ui_reportprepare.h"

/*

  TO DO:
  fix bug with undo after coords add

*/


ReportPrepare::ReportPrepare(QString workPath, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportPrepare)
{
    mousefreq = 5;
    workingPath = workPath;
    ui->setupUi(this);
    LoadAllIcons();

    ui->stackedWidget->setCurrentIndex(0);
    ConnectSlots();
    files = new QStringList();
    currentPictureIndex = -1;
    OpenFileDialog::GetStartFileList(workingPath,FILE_OPENER_PHOTOS_ONLY,files);
    UpdateFiles();
    UpdatePicture();

    ui->drawLabel->installEventFilter(this);
    ui->drawLabel->setMouseTracking(true);

    ui->rectBtn->setChecked(true);
    ui->blackBtn->setChecked(true);

    ui->redo->setEnabled(false);
    ui->undo->setEnabled(true);

    ui->step1Btn->setChecked(true);

    ui->unzoom->setVisible(false);
}

ReportPrepare::~ReportPrepare()
{
    delete ui;
}

void ReportPrepare::ConnectSlots()
{
    QObject::connect(ui->step1Btn, SIGNAL(toggled(bool)), this, SLOT(step1Btn_Clicked(bool)));
    QObject::connect(ui->step2Btn, SIGNAL(toggled(bool)), this, SLOT(step2Btn_Clicked(bool)));
    QObject::connect(ui->step3Btn, SIGNAL(toggled(bool)), this, SLOT(step3Btn_Clicked(bool)));

    QObject::connect(ui->redBtn, SIGNAL(toggled(bool)), this, SLOT(red_Clicked(bool)));
    QObject::connect(ui->blackBtn, SIGNAL(toggled(bool)), this, SLOT(black_Clicked(bool)));
    QObject::connect(ui->cyanBtn, SIGNAL(toggled(bool)), this, SLOT(cyan_Clicked(bool)));
    QObject::connect(ui->rectBtn, SIGNAL(toggled(bool)), this, SLOT(rect_Clicked(bool)));
    QObject::connect(ui->roundBtn, SIGNAL(toggled(bool)), this, SLOT(round_Clicked(bool)));
    QObject::connect(ui->freeBtn, SIGNAL(toggled(bool)), this, SLOT(free_Clicked(bool)));

    QObject::connect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(nextBtn_Clicked()));
    QObject::connect(ui->prevBtn, SIGNAL(clicked()), this, SLOT(prevBtn_Clicked()));
    QObject::connect(ui->openBtn, SIGNAL(clicked()), this, SLOT(openBtn_Clicked()));

    QObject::connect(ui->zoom, SIGNAL(clicked()), this, SLOT(zoom()));
    QObject::connect(ui->unzoom, SIGNAL(clicked()), this, SLOT(unzoom()));

    QObject::connect(ui->redo, SIGNAL(clicked()), this, SLOT(Redo()));
    QObject::connect(ui->undo, SIGNAL(clicked()), this, SLOT(Undo()));

    QObject::connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listDblClicked(QListWidgetItem*)));
}
void ReportPrepare::LoadAllIcons()
{
    ui->prevBtn->setIcon(QIcon(IconLoader::getIcon_PREVIOUS()));
    ui->prevBtn->setToolTip(QString::fromUtf8("Предыдущий"));

    ui->nextBtn->setIcon(QIcon(IconLoader::getIcon_NEXT()));
    ui->nextBtn->setToolTip(QString::fromUtf8("Следующий"));

    ui->openBtn->setIcon(QIcon(IconLoader::getIcon_OPEN()));
    ui->openBtn->setToolTip(QString::fromUtf8("Выбрать файлы"));

    ui->rectBtn->setIcon(QIcon(IconLoader::getIcon_RECT()));
    ui->rectBtn->setToolTip(QString::fromUtf8("Прямоугольное выделение"));

    ui->roundBtn->setIcon(QIcon(IconLoader::getIcon_ROUND()));
    ui->roundBtn->setToolTip(QString::fromUtf8("Овальное выделение"));

    ui->freeBtn->setIcon(QIcon(IconLoader::getIcon_FREE()));
    ui->freeBtn->setToolTip(QString::fromUtf8("Свободное выделение"));

    ui->undo->setIcon(QIcon(IconLoader::getIcon_UNDO()));
    ui->undo->setToolTip(QString::fromUtf8("Отменить последнее действие"));

    ui->redo->setIcon(QIcon(IconLoader::getIcon_REDO()));
    ui->redo->setToolTip(QString::fromUtf8("Повторить последнее действие"));

    ui->zoom->setIcon(QIcon(IconLoader::getIcon_ZOOM()));
    ui->zoom->setToolTip(QString::fromUtf8("Развернуть"));

    ui->unzoom->setIcon(QIcon(IconLoader::getIcon_UNZOOM()));
    ui->unzoom->setToolTip(QString::fromUtf8("Свернуть"));

    QPixmap p1(40,40);
    p1.fill(QColor(255,0,0));
    ui->redBtn->setIcon(QIcon(p1));
    ui->redBtn->setToolTip(QString::fromUtf8("Выделять красным"));

    QPixmap p2(40,40);
    p2.fill(QColor(0,255,255));
    ui->cyanBtn->setIcon(QIcon(p2));
    ui->cyanBtn->setToolTip(QString::fromUtf8("Выделять голубым"));

    QPixmap p3(40,40);
    p3.fill(QColor(0,0,0));
    ui->blackBtn->setIcon(QIcon(p3));
    ui->blackBtn->setToolTip(QString::fromUtf8("Выделять черным"));
}

void ReportPrepare::UpdateFiles()
{
    fileNames.clear();
    fileSources.clear();

    ui->listWidget->clear();

    int n = files->count();
    for (int i = 0; i < n; i+=2)
    {
       fileSources.push_front((*files)[i]);
       fileNames.push_front((*files)[i+1]);
       ui->listWidget->insertItem(0,(*files)[i+1]);
    }
    if (n > 0)
    {
        currentPictureIndex = 0;
        ui->step2Btn->setEnabled(true);
        ui->step3Btn->setEnabled(true);

        ui->prevBtn->setEnabled(true);
        ui->nextBtn->setEnabled(true);

        if (currentPictureIndex == 0)
            ui->prevBtn->setEnabled(false);
        if (currentPictureIndex == fileSources.size() - 1)
            ui->nextBtn->setEnabled(false);
    }
    else
    {
        currentPictureIndex = -1;
        ui->prevBtn->setEnabled(false);
        ui->nextBtn->setEnabled(false);
        ui->step2Btn->setEnabled(false);
        ui->step3Btn->setEnabled(false);
    }
}

void ReportPrepare::UpdatePicture()
{
    if (currentPictureIndex < 0 || currentPictureIndex >= fileSources.size())
        return;

    ui->listWidget->setCurrentRow(currentPictureIndex);
    changingBMP = new QPixmap(fileSources[currentPictureIndex]);
    changedBMP = new QPixmap(fileSources[currentPictureIndex]);
    backupBMP = new QPixmap(fileSources[currentPictureIndex]);
    ui->previewLabel->setPixmap(*changingBMP);
    ui->drawLabel->setPixmap(*changingBMP);
    ui->finalLabel->setPixmap(*changingBMP);
}

bool ReportPrepare::SaveChanges()
{
    return true;
}


void ReportPrepare::nextBtn_Clicked()
{
    ui->prevBtn->setEnabled(true);
    if (++currentPictureIndex >= fileSources.size() - 1)
          ui->nextBtn->setEnabled(false);
    UpdatePicture();
}
void ReportPrepare::prevBtn_Clicked()
{
    ui->nextBtn->setEnabled(true);
    if (--currentPictureIndex <= 0)
        ui->prevBtn->setEnabled(false);
    UpdatePicture();
}
void ReportPrepare::openBtn_Clicked()
{
    files->clear();
    QLocale russian(QLocale::Russian, QLocale::RussianFederation);
    QLocale::setDefault(russian);
    OpenFileDialog ofd(workingPath,FILE_OPENER_PHOTOS_ONLY, files, this);
    ofd.setLocale(russian);
    if (ofd.exec() == QDialog::Accepted)
    {
        UpdateFiles();
        UpdatePicture();
    }
}

void ReportPrepare::listDblClicked(QListWidgetItem*)
{
    currentPictureIndex = ui->listWidget->currentRow();

    ui->prevBtn->setEnabled(true);
    ui->nextBtn->setEnabled(true);

    if (currentPictureIndex == 0)
        ui->prevBtn->setEnabled(false);
    if (currentPictureIndex == fileSources.size() - 1)
        ui->nextBtn->setEnabled(false);

    UpdatePicture();
}

void ReportPrepare::step1Btn_Clicked(bool toggle)
{
    if (toggle == false)
    {
        ui->step1Btn->setChecked(false);
        return;
    }
    else
        ui->step1Btn->setChecked(true);

    ui->step2Btn->setChecked(false);
    ui->step3Btn->setChecked(false);

    ui->stackedWidget->setCurrentIndex(0);
}
void ReportPrepare::step2Btn_Clicked(bool toggle)
{
    if (toggle == false)
    {
        ui->step2Btn->setChecked(false);
        return;
    }
    else
        ui->step2Btn->setChecked(true);

    ui->step1Btn->setChecked(false);
    ui->step3Btn->setChecked(false);

    ui->stackedWidget->setCurrentIndex(1);
}
void ReportPrepare::step3Btn_Clicked(bool toggle)
{
    if (toggle == false)
    {
        ui->step3Btn->setChecked(false);
        return;
    }
    else
        ui->step3Btn->setChecked(true);

    ui->step2Btn->setChecked(false);
    ui->step1Btn->setChecked(false);

    ui->stackedWidget->setCurrentIndex(2);

    AutoFillLegend();
}

void ReportPrepare::AutoFillLegend()
{
    if (curCoord != NULL)
        ui->leg_coord->setText(curCoord);
    if (currentPictureIndex >= 0 && fileNames.count() > currentPictureIndex)
    {
        QString time = fileNames[currentPictureIndex];
        if (time.contains('('))
            time.truncate(fileNames[currentPictureIndex].lastIndexOf('(') - 1);
        else
            time.truncate(fileNames[currentPictureIndex].lastIndexOf('.'));

        ui->leg_time->setText(time);
    }

}

void ReportPrepare::rect_Clicked(bool toggle)
{
    if (toggle == false)
        return;
    ui->roundBtn->setChecked(false);
    ui->freeBtn->setChecked(false);
    curMode = DRAW_RECTANGLE;
}
void ReportPrepare::round_Clicked(bool toggle)
{
    if (toggle == false)
        return;
    ui->rectBtn->setChecked(false);
    ui->freeBtn->setChecked(false);
    curMode = DRAW_ROUND;
}
void ReportPrepare::free_Clicked(bool toggle)
{
    if (toggle == false)
        return;
    ui->roundBtn->setChecked(false);
    ui->rectBtn->setChecked(false);
    curMode = DRAW_FREE;
}
void ReportPrepare::red_Clicked(bool toggle)
{
    if (toggle == false)
        return;
    ui->blackBtn->setChecked(false);
    ui->cyanBtn->setChecked(false);
    curColor = QColor::fromRgb(255,0,0);
}
void ReportPrepare::black_Clicked(bool toggle)
{
    if (toggle == false)
        return;
    ui->redBtn->setChecked(false);
    ui->cyanBtn->setChecked(false);
    curColor = QColor::fromRgb(0,0,0);
}
void ReportPrepare::cyan_Clicked(bool toggle)
{
    if (toggle == false)
        return;
    ui->blackBtn->setChecked(false);
    ui->redBtn->setChecked(false);
    curColor = QColor::fromRgb(0,255,255);
}

void ReportPrepare::zoom()
{
    ui->zoom->setVisible(false);
    ui->unzoom->setVisible(true);
    ui->frame->resize(QSize(720,576));
    ui->previewLabel->resize(QSize(720,576));
    ui->frame->move(0,20);
    ui->openBtn->setVisible(false);
    ui->nextBtn->setVisible(false);
    ui->prevBtn->setVisible(false);
}

void ReportPrepare::unzoom()
{
    ui->zoom->setVisible(true);
    ui->unzoom->setVisible(false);
    ui->frame->resize(QSize(360,288));
    ui->previewLabel->resize(QSize(360,288));
    ui->frame->move(340,30);
    ui->openBtn->setVisible(true);
    ui->nextBtn->setVisible(true);
    ui->prevBtn->setVisible(true);
}

bool ReportPrepare::eventFilter(QObject *obj, QEvent *event_)
 {
    if (ui->stackedWidget->currentIndex() != 1)
        return true;

    if (obj == ui->drawLabel)
    {
         if (event_->type() == QEvent::MouseMove)
         {
             mouseMoveEvent_(static_cast<QMouseEvent*>(event_));
             return true;
         }
         else if (event_->type() == QEvent::MouseButtonDblClick)
         {
             mouseButtonDblClickEvent_(static_cast<QMouseEvent*>(event_));
             return true;
         }
         else if (event_->type() == QEvent::MouseButtonPress)
         {
             mouseButtonPressedEvent_(static_cast<QMouseEvent*>(event_));
             return true;
         }
         else if (event_->type() == QEvent::MouseButtonRelease)
         {
             mouseButtonReleasedEvent_(static_cast<QMouseEvent*>(event_));
             return true;
         }
         else
             return false;
     }
     else
        return false;
 }

void ReportPrepare::mouseMoveEvent_(QMouseEvent* event)
{
    if (ui->stackedWidget->currentIndex() != 1)
        return;
    if (mousemoves++%mousefreq != 0)
        return;

    ui->lineEdit->setText(QString("%1").arg(event->x()));
    ui->lineEdit_2->setText(QString("%1").arg(event->y()));

    if (event->buttons() !=  Qt::NoButton)
    {
        end = event->pos();

        int x, y, w, h;
        x = qMin(end.x(),start.x());
        w = qMax(end.x(),start.x()) - x;
        y = qMin(end.y(),start.y());
        h = qMax(end.y(),start.y()) - y;

        if (curMode == DRAW_RECTANGLE)
        {
            QPainter * painterr = new QPainter(changingBMP);
            painterr->drawPixmap(0,0, changedBMP->width(),changedBMP->height() ,*changedBMP);
            QPen p(curColor);
            p.setWidth(2);
            painterr->setPen(p);
            painterr->drawRect(x,y,w,h);
            painterr->end();
            ui->drawLabel->setPixmap(*changingBMP);
        }
        else if (curMode == DRAW_ROUND)
        {
            QPainter * painterr = new QPainter(changingBMP);
            painterr->drawPixmap(0,0, changedBMP->width(),changedBMP->height() ,*changedBMP);
            QPen p(curColor);
            p.setWidth(2);
            painterr->setPen(p);
            painterr->drawEllipse(x,y,w,h);
            painterr->end();
            ui->drawLabel->setPixmap(*changingBMP);
        }
        else if (curMode == DRAW_FREE)
        {
            QPainter * painterr = new QPainter(changingBMP);
            QPen p(curColor);
            p.setWidth(2);
            painterr->setPen(p);
            painterr->drawLine(prevEnd,end);
            painterr->end();
            ui->drawLabel->setPixmap(*changingBMP);
        }
        prevEnd = end;
    }
}
void ReportPrepare::mouseButtonReleasedEvent_(QMouseEvent* event)
{
    if (ui->stackedWidget->currentIndex() != 1)
        return;

    changedBMP = new QPixmap(*changingBMP);
    ui->finalLabel->setPixmap(*changedBMP);
}

void ReportPrepare::mouseButtonPressedEvent_(QMouseEvent* event)
{
    if (ui->stackedWidget->currentIndex() != 1)
        return;

    mousemoves = 0;
    backupBMP = new QPixmap(*changedBMP);
    start = event->pos();
    prevEnd = start;

    ui->redo->setEnabled(false);
    ui->undo->setEnabled(true);
}
void ReportPrepare::mouseButtonDblClickEvent_(QMouseEvent* event)
{
    if (ui->stackedWidget->currentIndex() != 1)
        return;

    QPainter * painterr = new QPainter(changingBMP);
    QPen p(curColor);
    p.setWidth(2);
    painterr->setPen(p);
    int x = event->x();
    int y = event->y();
    int shift = 10;
    painterr->drawPixmap(0,0, changedBMP->width(),changedBMP->height() ,*changedBMP);
    painterr->drawLine(x, y, x + shift, y - shift);
    painterr->drawText(x + shift + 2, y - shift - 2, GetCoordsText(x,y));
    painterr->end();

    ui->drawLabel->setPixmap(*changingBMP);
    changedBMP = new QPixmap(*changingBMP);
    ui->finalLabel->setPixmap(*changedBMP);
}

QString ReportPrepare::GetCoordsText(int x, int y)
{
    curCoord = QString("%1 %2").arg(x).arg(y);
    return curCoord;
}

void ReportPrepare::Undo()
{
    changedBMP = new QPixmap(*backupBMP);
    ui->drawLabel->setPixmap(*changedBMP);
    ui->finalLabel->setPixmap(*changedBMP);

    ui->redo->setEnabled(true);
    ui->undo->setEnabled(false);
}
void ReportPrepare::Redo()
{
    changedBMP = new QPixmap(*changingBMP);
    ui->drawLabel->setPixmap(*changedBMP);
    ui->finalLabel->setPixmap(*changedBMP);

    ui->redo->setEnabled(false);
    ui->undo->setEnabled(true);
}

