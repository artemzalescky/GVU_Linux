#ifndef CHOOSECAMERA_H
#define CHOOSECAMERA_H

#include <QWidget>
#include <QRadioButton>

#include "camera/icamera.h"
#include "camera/fntk.h"
#include "camera/musvphoto.h"
#include "camera/musvtv.h"
#include "camera/musvir.h"


#include "ui/uizoom.h"
#include "ui/uitakephoto.h"
#include "ui/uitakeseriesphoto.h"
#include "ui/uirecordvideo.h"
#include "ui/uirollandpitch.h"
#include "ui/uiinitialposition.h"
#include "ui/uilandingposition.h"
#include "ui/uiverticalposition.h"
#include "ui/uiworkingposition.h"

#include <QLayoutItem>

namespace Ui
{
    class ChooseCamera;
}
/**
 * @brief The CameraControl class - класс управления камерой
 */
class CameraControl : public QWidget
{
    Q_OBJECT

public:
    explicit CameraControl( QWidget* parent = 0 );
    ~CameraControl();

private:
    Ui::ChooseCamera* ui;
    ICamera* cam = nullptr;

    std::vector<QWidget*> MyWidgetsUI;

private:
    ICamera* createCam( Payload_Type type );

    // object ui
    UIZoom *zoom;
    UITakePhoto *takePhoto;
    UITakeSeriesPhoto *takeSeriesPhoto;
    UIRecordVideo *recordVideo;
    UIRollAndPitch *rollAndPitch;

    UIInitialPosition *initialPosition;
    UILandingPosition *landingPosition;
    UIVerticalPosition *verticalPosition;
    UIWorkingPosition *workingPosition;


private:
    void createWidgets();
    void updateEncodeFunction(Payload_Type pType);

signals:
    void chooseCamera(Payload_Type type);
    void chooseMode(iCamera_Mode mode);

private slots:
    void changePayloadComboBox( int index );

};

#endif // CHOOSECAMERA_H
