#ifndef COMMON_H
#define COMMON_H

#include <QObject>

//plc连接状态
enum PLCSTATUS
{
    PLC_OFF = 0,
    PLC_ON = 1
};

//相机状态
enum CAMERASTATUS
{
    CAMERA_OFF = 0,
    CAMERA_ON = 1

};

class Common : public QObject
{
    Q_OBJECT
public:
    explicit Common(QObject *parent = nullptr);
    static Common *getInstance();

signals:

public slots:

public:
    PLCSTATUS plc_status_ ;
    CAMERASTATUS camera_status_;
    bool comeOrGo_  = true;  //true进港 false出港


private:
    static Common *instance_;

};

#endif // COMMON_H
