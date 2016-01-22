#-------------------------------------------------
#
# Project created by QtCreator 2012-07-29T12:17:46
#
#
# prerequisites:
# sudo apt-get install libphonon-dev
# sudo apt-get install libqtgstreamer-dev
# sudo apt-get install qtmobility-dev
#
# sudo apt-get install gstreamer0.1*
#
#
#--------------------------------------------------------------------------------------------------

QT       += core gui \ phonon \
        mobility \ multimediakit \ network

# produce nice compilation output
CONFIG += silent
QMAKE_CXXFLAGS += -std=c++11

# Tell qmake to use pkg-config to find QtGStreamer.
CONFIG += link_pkgconfig

# Now tell qmake to link to QtGStreamer and also use its include path and Cflags.
contains(QT_VERSION, ^4\\..*) {
  PKGCONFIG += QtGStreamer-0.10 QtGStreamerUi-0.10
}


#CONFIG += mobility
#MOBILITY += multimedia
#INCLUDEPATH += /usr/include/QtMobility /usr/include/QtGStreamer
#INCLUDEPATH += /usr/include/QtMultimediaKit
#INCLUDEPATH += /usr/include/QtGStreamer/

TARGET = VideoARM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    reportprepare.cpp \
    player/player_phonon.cpp \
    player/player_qtgstreamer.cpp \
    player/streamplayer.cpp \
    player/streamplayersmall.cpp \
    player/videoplayer.cpp \
    player/videoplayersmall.cpp \
    navigator/filesnavigator.cpp \
    navigator/modulenavigator.cpp \
    settings/addcomswidgetvideo.cpp \
    settings/allsettngs.cpp \
    focusCamera/cameraangleviewer.cpp \
    camMode/cammode.cpp \
    dialog/openfiledialog.cpp \
    informer/informer.cpp \
    netWork/networkinterface.cpp \
    netWork/protocol.cpp \
    data/datafromcamera.cpp \
    camMode/cammodedesc.cpp \
    joystick/joystick.cpp \
    joystick/sdljoystick.cpp \
    joystick/joystickcontrol.cpp \
    camera/cameracontrol.cpp \
    camera/fntk.cpp \
    camera/icamera.cpp \
    camera/musvir.cpp \
    camera/musvphoto.cpp \
    camera/musvtv.cpp \
    ui/mode/uiMode.cpp \
    ui/encodecontrol.cpp \
    ui/uicommand.cpp \
    ui/uiinitialposition.cpp \
    ui/uilandingposition.cpp \
    ui/uirecordvideo.cpp \
    ui/uirollandpitch.cpp \
    ui/uitakephoto.cpp \
    ui/uitakeseriesphoto.cpp \
    ui/uiverticalposition.cpp \
    ui/uiworkingposition.cpp \
    ui/uizoom.cpp

HEADERS  += mainwindow.h \
    reportprepare.h \       
    player/player_phonon.h \
    player/player_qtgstreamer.h \
    player/streamplayer.h \
    player/streamplayersmall.h \
    player/videoplayer.h \
    player/videoplayersmall.h \
    navigator/filesnavigator.h \
    navigator/modulenavigator.h \
    settings/addcomswidgetvideo.h \
    settings/allsettngs.h \
    resources/iconloader.h \
    resources/interface.h \
    focusCamera/cameraangleviewer.h \
    camMode/cammode.h \
    dialog/openfiledialog.h \
    informer/informer.h \
    netWork/networkinterface.h \
    netWork/protocol.h \
    data/datafromcamera.h \
    camMode/cammodedesc.h \
    joystick/joystick.h \
    joystick/sdljoystick.h \
    joystick/joystickcontrol.h \
    camera/cameracontrol.h \
    camera/fntk.h \
    camera/icamera.h \
    camera/musvir.h \
    camera/musvphoto.h \
    camera/musvtv.h \
    ui/mode/uiMode.h \
    ui/encodecontrol.h \
    ui/uicommand.h \
    ui/uiinitialposition.h \
    ui/uilandingposition.h \
    ui/uirecordvideo.h \
    ui/uirollandpitch.h \
    ui/uitakephoto.h \
    ui/uitakeseriesphoto.h \
    ui/uiverticalposition.h \
    ui/uiworkingposition.h \
    ui/uizoom.h

FORMS    += mainwindow.ui \    
    reportprepare.ui \
    cameraangleviewer.ui \
    cammode.ui \
    allsettngs.ui \
    videocammodedesc.ui \
    openfiledialog.ui \
    filesnavigator.ui \    
    addcomswidgetvideo.ui \    
    modulenavigator.ui \
    videoplayersmall.ui \
    videoplayer.ui \
    streamplayersmall.ui \
    streamplayer.ui \
    icamera.ui \
    videoplayer.ui \
    streamplayer.ui \
    streamplayersmall.ui \
    videoplayersmall.ui \
    cameracontrol.ui \
    cammodedesc.ui



#LIBS += -lvlc
LIBS        += -lSDL2

DISTFILES += \
    .gitlab-ci.yml \
    README

RESOURCES += \
    icons.qrc
