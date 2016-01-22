#ifndef REPORTPREPARE_H
#define REPORTPREPARE_H

#include <QWidget>
#include <QBitmap>
#include <qmath.h>
#include <QListWidget>
#include <QMouseEvent>
#include <QPainter>
#include "resources/iconloader.h"
#include "dialog/openfiledialog.h"

namespace Ui {
    class ReportPrepare;
}

enum DRAW_MODE
{
    DRAW_RECTANGLE,
    DRAW_ROUND,
    DRAW_FREE
};

class ReportPrepare : public QWidget
{
    Q_OBJECT

private:
    Ui::ReportPrepare *ui;
    QString workingPath;
    QPixmap * backupBMP;
    QPixmap * changedBMP;
    QPixmap * changingBMP;
    QPainter * painter;
    QColor curColor;
    DRAW_MODE curMode;

    QString curCoord;

    QPoint start, end, prevEnd;
    QStringList * files;
    QStringList fileNames;
    QStringList fileSources;
    int currentPictureIndex;

    int mousemoves;
    int mousefreq;

public:
    explicit ReportPrepare(QString workPath, QWidget *parent = 0);
    ~ReportPrepare();

private:
    void ConnectSlots();
    void LoadAllIcons();
    void UpdateFiles();
    void UpdatePicture();
    bool SaveChanges();

    QString GetCoordsText(int x, int y);
    void AutoFillLegend();

    bool eventFilter(QObject *obj, QEvent *ev);
    void mouseMoveEvent_(QMouseEvent* event);
    void mouseButtonReleasedEvent_(QMouseEvent* event);
    void mouseButtonPressedEvent_(QMouseEvent* event);
    void mouseButtonDblClickEvent_(QMouseEvent* event);

private slots:
    void step1Btn_Clicked(bool );
    void step2Btn_Clicked(bool );
    void step3Btn_Clicked(bool );

    void rect_Clicked(bool );
    void round_Clicked(bool );
    void free_Clicked(bool );
    void red_Clicked(bool );
    void black_Clicked(bool );
    void cyan_Clicked(bool );

    void zoom();
    void unzoom();

    void nextBtn_Clicked();
    void prevBtn_Clicked();
    void listDblClicked(QListWidgetItem*);
    void openBtn_Clicked();

    void Undo();
    void Redo();
};

#endif // REPORTPREPARE_H
