#include "player_qtgstreamer.h"

const QString PlayerQtGstreamer::Encoder_MJPEG = "jpegenc";
const QString PlayerQtGstreamer::Encoder_MPEG2 = "mpeg2enc";
const QString PlayerQtGstreamer::Encoder_Theora = "theoraenc";
const QString PlayerQtGstreamer::Encoder_VP8 = "vp8enc";
const QString PlayerQtGstreamer::Encoder_H264 = "x264enc";
const QString PlayerQtGstreamer::Encoder_None = "";

const QString PlayerQtGstreamer::defaultDevice = "/dev/video0";


PlayerQtGstreamer::PlayerQtGstreamer(QWidget *parent)
    : QGst::Ui::VideoWidget(parent)
{
    QGst::init();

    last_H = 0;
    last_S = 0;
    last_C = 0;
    last_B = 0;
    useEncoder = false;
    device = defaultDevice;
}

PlayerQtGstreamer::~PlayerQtGstreamer()
{
    if (m_pipeline)
    {
        m_pipeline->setState(QGst::StateNull);
        stopPipelineWatch();
        m_pipeline.clear();
        delete m_pipeline;
    }
}

void PlayerQtGstreamer::setEncoder(const QString & encoderName)
{
    if (encoderName == Encoder_None)
        useEncoder = false;
    else
    {
        useEncoder = true;
        this->encoderName = encoderName;
    }
}

void PlayerQtGstreamer::createPlayingPipeline()
{
    if (m_pipeline)
    {
        m_pipeline->setState(QGst::StateNull);
        stopPipelineWatch();
        m_pipeline.clear();
        delete m_pipeline;
    }

    m_pipeline = QGst::Pipeline::create();

    watchPipeline(m_pipeline);

    QGst::ElementPtr m_videoSource = QGst::ElementFactory::make("v4l2src");
    QSettings settings;
    m_videoSource->setProperty("device", settings.value("videoDevice", device).toString());

    m_videoBalance = QGst::ElementFactory::make("videobalance");

    m_textoverlay = QGst::ElementFactory::make("textoverlay");
    setupTextOverlayParams();

    QGst::ElementPtr screenSink = QGst::ElementFactory::make("autovideosink");

    m_pipeline->add(m_videoSource, m_videoBalance, m_textoverlay, screenSink);

   // QGst::CapsPtr caps = QGst::Caps::createSimple("video/x-raw-yuv");
    //caps->setValue("format", QGst::Fourcc('U','Y','V','Y'));
   // caps->setValue("width", 640);
   // caps->setValue("height", 480);
   // caps->setValue("bpp", 24);
   // caps->setValue("framerate", QGst::Fraction(30,1));

    //m_videoSource->link(m_textoverlay, caps);

    m_videoSource->link(m_videoBalance);
    m_videoBalance->link(m_textoverlay);
    m_textoverlay->link(screenSink);

    setHue(last_H);
    setSaturation(last_S);
    setBrightness(last_B);
    setContrast(last_C);

    //connect the bus
    m_pipeline->bus()->addSignalWatch();
    QGlib::connect(m_pipeline->bus(), "message", this, &PlayerQtGstreamer::onBusMessage);
}

int i = 0;
void PlayerQtGstreamer::createRecordingPipeline(const QString & filename, bool autoAddExtension = true)
{
    if (m_pipeline)
    {
        m_pipeline->setState(QGst::StateNull);
        stopPipelineWatch();
        m_pipeline.clear();
        //delete m_pipeline;
    }

    m_pipeline = QGst::Pipeline::create();

    watchPipeline(m_pipeline);

    QGst::ElementPtr m_videoSource = QGst::ElementFactory::make("v4l2src");
    QSettings settings;
    m_videoSource->setProperty("device", settings.value("videoDevice", device).toString());

    //QGst::ElementPtr ffmpeg = QGst::ElementFactory::make("ffmpegcolorspace");
    QGst::ElementPtr tee = QGst::ElementFactory::make("tee");
    m_textoverlay = QGst::ElementFactory::make("textoverlay");
    setupTextOverlayParams();

    QGst::ElementPtr screenQueue = QGst::ElementFactory::make("queue");
    m_videoBalance = QGst::ElementFactory::make("videobalance");

    QGst::ElementPtr screenSink = QGst::ElementFactory::make("autovideosink");

    QGst::ElementPtr videoQueue = QGst::ElementFactory::make("queue");
    QGst::ElementPtr encoder = QGst::ElementFactory::make(encoderName);
    QString filenamewithext = filename;

    QGst::ElementPtr mux;
    if (!useEncoder)
    {
        mux = QGst::ElementFactory::make("avimux");
        if (autoAddExtension)
            filenamewithext  = filename + ".avi";
    }
    else
    {
        if (encoderName == Encoder_MJPEG)
        {
            encoder->setProperty("bitrate",8000);
            encoder->setProperty("speed-level", 2);
            mux = QGst::ElementFactory::make("avimux");
            if (autoAddExtension)
                filenamewithext  = filename + ".avi";
        }
        else if (encoderName == Encoder_MPEG2)
        {
            encoder->setProperty("bitrate",10000);
            if (autoAddExtension)
                filenamewithext  = filename + ".avi";
        }
        else if (encoderName == Encoder_VP8)
        {
            encoder->setProperty("target-bitrate",20000000);
            if (autoAddExtension)
                filenamewithext  = filename + ".avi";
        }
        else if (encoderName == Encoder_H264)
        {
            encoder->setProperty("bitrate",20000);
            if (autoAddExtension)
                filenamewithext  = filename + ".avi";
        }
        else if (encoderName == Encoder_Theora)
        {
            encoder->setProperty("bitrate",20000);
            mux = QGst::ElementFactory::make("oggmux");
            if (autoAddExtension)
                filenamewithext  = filename + ".ogg";
        }
    }

    QGst::ElementPtr sink = QGst::ElementFactory::make("filesink");
    sink->setProperty("location", filenamewithext);

    if (useEncoder)
        m_pipeline->add(m_videoSource, m_textoverlay, tee, screenQueue, m_videoBalance, screenSink, videoQueue, encoder, mux, sink);
    else
        m_pipeline->add(m_videoSource, m_textoverlay, tee, screenQueue, m_videoBalance, screenSink, videoQueue, mux, sink);

    //if (encoderName == Encoder_Theora)
    //{
   // QGst::CapsPtr caps = QGst::Caps::createSimple("video/x-theora");
   // caps->setValue("format", QGst::Fourcc('U','Y','V','Y'));
    //caps->setValue("width", 640);
    //caps->setValue("height", 480);
    //caps->setValue("bpp", 24);
    //caps->setValue("framerate", QGst::Fraction(30,1));
    //m_videoSource->link(m_textoverlay, caps);
    //}
    //else


    m_videoSource->link(m_textoverlay);
    //ffmpeg->link(m_textoverlay);
    m_textoverlay->link(tee);

    tee->link(screenQueue);
    screenQueue->link(m_videoBalance);
    m_videoBalance->link(screenSink);

    tee->link(videoQueue);
    if (useEncoder)
    {
        videoQueue->link(encoder);
        encoder->link(mux);
    }
    else
    {
        videoQueue->link(mux);
    }
    mux->link(sink);

    setHue(last_H);
    setSaturation(last_S);
    setBrightness(last_B);
    setContrast(last_C);

    //connect the bus
    m_pipeline->bus()->addSignalWatch();
    QGlib::connect(m_pipeline->bus(), "message", this, &PlayerQtGstreamer::onBusMessage);
}

void PlayerQtGstreamer::setupTextOverlayParams()
{
    if (m_textoverlay)
    {
        m_textoverlay->setProperty("xpad", 5);
        m_textoverlay->setProperty("ypad", 5);
        m_textoverlay->setProperty("font-desc", "Sans 12");
        m_textoverlay->setProperty("shaded-background", true);
    }
}

QGst::State PlayerQtGstreamer::state() const
{
    return m_pipeline ? m_pipeline->currentState() : QGst::StateNull;
}

void PlayerQtGstreamer::play()
{
    createPlayingPipeline();
    createRecordingPipeline("/dev/null",false);
    if (m_pipeline)
    {
        m_pipeline->setState(QGst::StatePlaying);
    }
}

void PlayerQtGstreamer::pause()
{
    if (m_pipeline) {
        m_pipeline->setState(QGst::StatePaused);
    }
}

void PlayerQtGstreamer::record(const QString & filenamewithoutext)
{
    createRecordingPipeline(filenamewithoutext);
    if (m_pipeline)
    {
        m_pipeline->setState(QGst::StatePlaying);
    }
}

void PlayerQtGstreamer::stop()
{
    if (m_pipeline)
    {
        m_pipeline->setState(QGst::StateNull);
    //once the pipeline stops, the bus is flushed so we will
    //not receive any StateChangedMessage about this.
    //so, to inform the ui, we have to emit this signal manually
              Q_EMIT stateChanged();
        //play();
    }
}

void PlayerQtGstreamer::setHue(double h)
{
    last_H = qMax(qMin(1.0,h),-1.0);
    if (m_videoBalance)
    {
        m_videoBalance->setProperty("hue",last_H);
    }
}

void PlayerQtGstreamer::setSaturation(double s)
{
    last_S = s + 1;
    last_S = qMax(qMin(1.0,last_S),-1.0);
    if (m_videoBalance)
    {
        m_videoBalance->setProperty("saturation",last_S);
    }
}

void PlayerQtGstreamer::setContrast(double c)
{
    last_C = c + 1;
    last_C = qMax(qMin(1.0,last_C),-1.0);
    if (m_videoBalance)
    {
        m_videoBalance->setProperty("contrast",last_C);
    }
}

void PlayerQtGstreamer::setBrightness(double b)
{
    last_B = qMax(qMin(1.0,b),-1.0);
    if (m_videoBalance)
    {
        m_videoBalance->setProperty("brightness",last_B);
    }
}

void PlayerQtGstreamer::onBusMessage(const QGst::MessagePtr & message)
{
    switch (message->type()) {
    case QGst::MessageEos: //End of stream. We reached the end of the file.
        stop();
        break;
    case QGst::MessageError: //Some error occurred.
        qCritical() << message.staticCast<QGst::ErrorMessage>()->error();
        stop();
        break;
    case QGst::MessageStateChanged: //The element in message->source() has changed state
        if (message->source() == m_pipeline) {
            handlePipelineStateChange(message.staticCast<QGst::StateChangedMessage>());
        }
        break;
    default:
        break;
    }
}

void PlayerQtGstreamer::handlePipelineStateChange(const QGst::StateChangedMessagePtr & scm)
{
    switch (scm->newState()) {
    case QGst::StatePlaying:
        //start the timer when the pipeline starts playing
        //m_positionTimer.start(100);
        break;
    case QGst::StatePaused:
        //stop the timer when the pipeline pauses
        if(scm->oldState() == QGst::StatePlaying) {
            //m_positionTimer.stop();
        }
        break;
    default:
        //stop the timer when the pipeline pauses
        if(scm->oldState() == QGst::StatePlaying) {
            //m_positionTimer.stop();
        }
        break;
    }

    Q_EMIT stateChanged();
}

void PlayerQtGstreamer::onChangeInfo(QString newInfo)
{
    if (m_textoverlay)
    {
        m_textoverlay->setProperty("text", newInfo);
    }
}
