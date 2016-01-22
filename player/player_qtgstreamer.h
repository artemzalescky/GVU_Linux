#ifndef PLAYERQTGSTREAMER_H
#define PLAYERQTGSTREAMER_H

#include <QTimer>
#include <QTime>
#include <QSettings>
#include <QtGStreamer/QGst/Pipeline>
#include <QtGStreamer/QGst/Ui/VideoWidget>
#include <QtGStreamer/QGst/ChildProxy>
#include <QtGStreamer/QGst/PropertyProbe>
#include <QtGStreamer/QGlib/Connect>
#include <QtGStreamer/QGlib/Error>
#include <QtGStreamer/QGst/ElementFactory>
#include <QtGStreamer/QGst/Bus>
#include <QtGStreamer/QGst/Caps>
#include <QtGStreamer/QGst/Message>
#include <QtGStreamer/QGst/Query>
#include <QtGStreamer/QGst/ClockTime>
#include <QtGStreamer/QGst/Event>
#include <QtGStreamer/QGst/StreamVolume>
#include <QtGStreamer/QGst/Init>

class PlayerQtGstreamer : public QGst::Ui::VideoWidget
{
    Q_OBJECT

public:
    static const QString Encoder_MJPEG;
    static const QString Encoder_MPEG2;
    static const QString Encoder_Theora;
    static const QString Encoder_VP8;
    static const QString Encoder_H264;
    static const QString Encoder_None;

    PlayerQtGstreamer(QWidget *parent = 0);
    ~PlayerQtGstreamer();

    QGst::State state() const;

    void setEncoder(const QString & encoderName);

    QList<QString> getAvailaibleDevices();
    void setDevice(const QString & device);

    void play();
    void record(const QString & filenamewithoutext);
    void pause();
    void stop();

    // h should be in range -1;1
    void setHue(double h);
    // s should be in range -1;1
    void setSaturation(double s);
    // c should be in range -1;1
    void setContrast(double c);
    // b should be in range -1;1
    void setBrightness(double b);

Q_SIGNALS:
    void positionChanged();
    void stateChanged();

private:
    static const QString defaultEncoder;
    static const QString defaultDevice;

    void setupTextOverlayParams();
    void createPlayingPipeline();
    void createRecordingPipeline(const QString & filename, bool autoAddExtension);
    void onBusMessage(const QGst::MessagePtr & message);
    void handlePipelineStateChange(const QGst::StateChangedMessagePtr & scm);

    bool useEncoder;
    QString encoderName;

    QString device;

    double last_H, last_S, last_C, last_B;

    QGst::ElementPtr m_videoBalance;
    QGst::ElementPtr m_textoverlay;
    QGst::PipelinePtr m_pipeline;

private slots:
    void onChangeInfo(QString newInfo);
};

#endif // PLAYERQTGSTREAMER_H
