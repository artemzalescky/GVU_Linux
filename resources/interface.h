#ifndef INTERFACE_H
#define INTERFACE_H

#include <QString>

#include <map>
using std::map;
using std::pair;

enum VIDEOCAM_MODES {
    VIDEOCAM_MODE_WATCH,        // слежение
    VIDEOCAM_MODE_SCAN,         // сканирование
    VIDEOCAM_MODE_TARGETING,    // наведение
    VIDEOCAM_MODE_TOSTARTPOINT  // в исходную точку
};

enum PHOTOCAM_MODES {
    PHOTOCAM_MODE_HANDSHOT,
    PHOTOCAM_MODE_AUTOSHOT
};

enum FILE_OPENER_MODE {
    FILE_OPENER_PHOTOS_ONLY,
    FILE_OPENER_VIDEO_ONLY,
    FILE_OPENER_PHOTOS_AND_VIDEO,
    FILE_OPENER_FOLDERS_ONLY
};
enum WHITE_BALANCE {
    WHITE_BALANCE_AUTO,
    WHITE_BALANCE_NOT_NATURAL_LIGHT,
    WHITE_BALANCE_NATURAL_LIGHT,
    WHITE_BALANCE_ATW,
    WHITE_BALANCE_MANUAL,
    WHITE_BALANCE_OPT
};

enum IR_PICTURE_ORIENTATION {
    IR_PICTURE_ORIENTATION_NORMAL,
    IR_PICTURE_ORIENTATION_INVERSE,
    IR_PICTURE_ORIENTATION_REVERSE,
    IR_PICTURE_ORIENTATION_INVERSE_REVERSE
};


//--------------------------------
//------  N E W ------------------

// тип целевой нагрузки
enum Payload_Type : uint8_t {
    CAMERA_FNTK,
    CAMERA_MUSVPHOTO,
    CAMERA_MUSVTV,
    CAMERA_MUSVIR
};

enum iCamera_Mode : uint8_t {
    photoMode = 1,
    videoMode = 2,
    irMode = 4,
    SomeNewMode = 8
};

struct ComKey {
    QString name;
    Payload_Type type;

    bool operator < ( const ComKey& com ) const {
        return ( name == com.name ) ? ( type < com.type ) : ( name < com.name );
    }
};

enum Control_Camera : uint32_t {
    zoom = 1,
    make_photo = 2,
    make_series_photo = 4,
    record_video = 8,
    rollAndPitch = 16,
    initial_position = 32, // начальное положение
    vertical_position = 64, // вертикальное положение
    working_position = 128, // рабочее положение
    landing_position = 256,  // посадочное положение
    color_mode = 512
};

// соответствие камеры -> управления и режима
// НЕОБХОДИМО ВЫНЕСТИ В ОТДЕЛЬНЫЙ ФАЙЛ
const map<Control_Camera, uint8_t> fntkControl = {
    pair<Control_Camera, uint8_t>( make_photo, photoMode ),
    pair<Control_Camera, uint8_t>( make_series_photo, photoMode ),
    pair<Control_Camera, uint8_t>( record_video, videoMode )
};
const map<Control_Camera, uint8_t> musvPhotoControl = {
    pair<Control_Camera, uint8_t>( zoom, photoMode ),
    pair<Control_Camera, uint8_t>( make_photo, photoMode ),
    pair<Control_Camera, uint8_t>( make_series_photo, photoMode ),
    pair<Control_Camera, uint8_t>( record_video, videoMode ),
    pair<Control_Camera, uint8_t>( rollAndPitch, photoMode | videoMode ),
    pair<Control_Camera, uint8_t>( initial_position, photoMode | videoMode ),
    pair<Control_Camera, uint8_t>( landing_position, photoMode | videoMode )
};

const map<Control_Camera, uint8_t> musvTVControl = {
    pair<Control_Camera, uint8_t>( zoom, videoMode ),
    pair<Control_Camera, uint8_t>( record_video, videoMode ),
    pair<Control_Camera, uint8_t>( rollAndPitch,  videoMode ),
    pair<Control_Camera, uint8_t>( initial_position,  videoMode ),
    pair<Control_Camera, uint8_t>( vertical_position,  videoMode ),
    pair<Control_Camera, uint8_t>( working_position,  videoMode ),
    pair<Control_Camera, uint8_t>( landing_position,  videoMode )
};
const map<Control_Camera, uint8_t> musvIRControl = {
    pair<Control_Camera, uint8_t>( zoom, irMode ),
    pair<Control_Camera, uint8_t>( rollAndPitch, irMode | videoMode ),
    pair<Control_Camera, uint8_t>( initial_position, irMode | videoMode ),
    pair<Control_Camera, uint8_t>( vertical_position, irMode | videoMode ),
    pair<Control_Camera, uint8_t>( working_position, irMode | videoMode ),
    pair<Control_Camera, uint8_t>( landing_position, irMode | videoMode )
};

const map<Payload_Type, map<Control_Camera, uint8_t> > Camera_Mode_Control  = {
    pair<Payload_Type, map<Control_Camera, uint8_t> > ( CAMERA_FNTK, fntkControl ),
    pair<Payload_Type, map<Control_Camera, uint8_t> > ( CAMERA_MUSVPHOTO, musvPhotoControl ),
    pair<Payload_Type, map<Control_Camera, uint8_t> > ( CAMERA_MUSVTV, musvTVControl ),
    pair<Payload_Type, map<Control_Camera, uint8_t> > ( CAMERA_MUSVIR, musvIRControl )

};

/* НАХОДИТСЯ В процессе реализации */

struct FNTKSetting {
    float roll = 0;
    float pitch = 0;
    iCamera_Mode mode = videoMode;
};

struct MUSVPHOTOSetting {
    float roll = 0;
    float pitch = 0;
    iCamera_Mode mode = videoMode;
};

struct MUSVTVSetting {
    float roll = 0;
    float pitch = 0;
    iCamera_Mode mode = videoMode;
};

struct MUSVIRSetting {
    float roll = 0;
    float pitch = 0;
    iCamera_Mode mode = irMode;
};

/* Работа с джостиком */
enum Joy_Key_Button {
    StartView = 1,
    OnRecord = 3,
    ParkingOn = 4,
    ParkingOff = 5,
    VerticalPosition = 6,
    ColorModInc = 7,
    ColorModDec = 8,
    PreShoot = 9,
    BurstMode = 10,
    Shoot = 12,
    ZoomInc = 13,
    ZoomDec = 14,
/*
    ZeroPos = 2,
    TimerInc = 12,
    TimerDec = 13,
    Gimbal = 14,
    Photo = 15,
    Curs = 16,
    ChangeFocus = 17,
    MakeTvSnap = 18,
    TVEnbl1 = 19,
    IREnbl1 = 20,
*/
};

//--------------------------------

struct VideocamSettings {
    //управление питанием
    bool drive_power; //питание приводов
    bool videocam_power; //питание камеры

    //управление режимами
    bool hd; //режим высокого разрешения
    bool night_vision; //режим ночного видения
    bool still_image; //режим замороженного изображения
    bool videoeffectsOFF; //видеоэффекты выключены
    bool negative; // негатив
    bool bw; //черно белый
    bool bkrgdLight; //фоновая подсветка

    //управление параметрами ЦН
    bool autoexposition; //автоматическая автоэкспозиция
    bool sensitivity; //чувсвтительность автофокуса true - норм, false - низкая
    WHITE_BALANCE wb; //баланс белого

    //управление зумом
    float currentZoom; //текущий зум
    bool digitalZoom; //цифровой зум

    //управление настройками
    bool cross; // отображение перекрестия
    bool grid; //отображение сетки
    bool showSettings; //отображение настроек

    void SetDefault() {
        drive_power = true;
        videocam_power = true;
        hd = true;
        night_vision = false;
        still_image = false;
        videoeffectsOFF = true;
        negative = false;
        bw = false;
        bkrgdLight = false;
        autoexposition = true;
        sensitivity = true;
        wb = WHITE_BALANCE_AUTO;
        currentZoom = 1;
        digitalZoom = true;
        cross = true;
        grid = false;
        showSettings = true;
    }
};



#endif // INTERFACE_H

