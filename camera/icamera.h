#ifndef ICAMERA_H
#define ICAMERA_H

#include <QWidget>
#include <map>
#include <QMultiMap>
#include <list>
#include <vector>
#include <QMap>

#include "resources/interface.h"
#include "ui/encodecontrol.h"


//-------------- Управление камерами -------------
static const std::list<Control_Camera> FNTKCommands = {
    make_photo,
    make_series_photo,
    record_video
};
static const std::list<Control_Camera> MUSVPHOTOCommands = {
    zoom,
    make_photo,
    make_series_photo,
    record_video,
    rollAndPitch,
    initial_position,
    landing_position
};
static const std::list<Control_Camera> MUSVTVCommands = {
    zoom,
    make_photo,
    make_series_photo,
    record_video,
    rollAndPitch,
    initial_position,
    vertical_position,
    working_position,
    landing_position
};
static const std::list<Control_Camera> MUSVIRCommands = {
    zoom,
    make_photo,
    make_series_photo,
    record_video,
    rollAndPitch,
    initial_position,
    vertical_position,
    working_position,
    landing_position
};

static std::map<Payload_Type, std::list<Control_Camera> > ControlPayloadMap = {
    std::pair<Payload_Type, std::list<Control_Camera>>( CAMERA_FNTK, FNTKCommands ),
    std::pair<Payload_Type, std::list<Control_Camera>>( CAMERA_MUSVPHOTO, MUSVPHOTOCommands ),
    std::pair<Payload_Type, std::list<Control_Camera>>( CAMERA_MUSVTV, MUSVTVCommands ),
    std::pair<Payload_Type, std::list<Control_Camera>>( CAMERA_MUSVIR, MUSVIRCommands )
};

//----------- РЕЖИМЫ КАМЕР ------------------------
static const std::list<iCamera_Mode> FNTKModes = {
    photoMode,
    videoMode,
};
static const std::list<iCamera_Mode> MUSVPHOTOModes = {
    photoMode,
    videoMode,
};
static const std::list<iCamera_Mode> MUSVTVModes = {
    videoMode,
};
static const std::list<iCamera_Mode> MUSVIRModes = {
    videoMode,
    irMode
};

static std::map<Payload_Type, std::list<iCamera_Mode> > ModePayloadMap = {
    std::pair<Payload_Type, std::list<iCamera_Mode>>( CAMERA_FNTK, FNTKModes ),
    std::pair<Payload_Type, std::list<iCamera_Mode>>( CAMERA_MUSVPHOTO, MUSVPHOTOModes ),
    std::pair<Payload_Type, std::list<iCamera_Mode>>( CAMERA_MUSVTV, MUSVTVModes ),
    std::pair<Payload_Type, std::list<iCamera_Mode>>( CAMERA_MUSVIR, MUSVIRModes )
};
//-----------------------------------------------------------------------------------

namespace Ui
{
    class ICamera;
}

class ICamera : public QWidget
{
    Q_OBJECT

public:
    explicit ICamera( QWidget* parent = 0 );
    ~ICamera();

private:
    Ui::ICamera* ui;
    Payload_Type type;

    FNTKSetting fntk;
    MUSVPHOTOSetting musvPhoto;
    MUSVTVSetting musvTV;
    MUSVIRSetting musvIR;

private:
    //std::multimap< iCamera_Mode, Command*> ModeCommandMap;       // управление камерой
   // Command* changeModeCommand;

public:
    void initCommands(Payload_Type type);
    void initModes(Payload_Type type);

    void setPayloadType( Payload_Type pType ) {
        type = pType;
    };
    Payload_Type getPayloadType() {
        return type;
    }

    iCamera_Mode getDefaultMode( Payload_Type pType );

 //   std::vector<QWidget*> getWidgetsControl( iCamera_Mode mode );
 //   QWidget* getWidgetChangeMode();


signals:
    void newCamMode( iCamera_Mode m );
};

#endif // ICAMERA_H
