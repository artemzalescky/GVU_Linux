#ifndef UITAKEPHOTO_H
#define UITAKEPHOTO_H

#include "ui/uicommand.h"
#include "encodecontrol.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "QLabel"
#include <vector>

using EncodeControl::TakePhotoEncodeFunction;

class UITakePhoto : public UICommand
{
    Q_OBJECT
public:
    explicit UITakePhoto( QWidget* parent = 0 );

    QVBoxLayout* layout;
    QPushButton* btnTakePhoto;

    void setEFunction( const TakePhotoEncodeFunction& value );
    void updateEncodeFunction( Payload_Type t );

    bool getVisibility() const;
    void setVisibility( bool value );

private:
    bool visibility = false;

    TakePhotoEncodeFunction eFunction;

private slots:
    void photo();

};

#endif // UITAKEPHOTO_H
