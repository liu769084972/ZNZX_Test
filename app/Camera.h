#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include "define.h"

typedef struct {
    int cameraId = -1; //视觉编号，-1表示不存在
    QString cameraName; //视觉名称
    CameraType type = HaiKang; //视觉类型 大华，海康
    QTcpSocket *tcpSocekt = nullptr;
    QString ip; //视觉IP地址
    quint16 port = 0; //端口
    int plcIndex = -1; //对应的PLC索引
    short exceptionBoxId = -1; //异常口
    int carrierNum; //小车数量
    QString pdaCode;
} StructCamera;
class MainWindow;

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(MainWindow *main,QObject *parent = nullptr);
    //相机初始化
    void initCamera();
    /*
     *  目的：根据camera地址找到cameraId
     */
    int cameraIdFromCamera(QTcpSocket *tcpSocket);
    //是否是字母或者数字
    inline bool isLetterOrNumberString(QString str);



signals:
    void appendDetailLog(QString);
    void appendAlarm(QString content, QString level, QString component);

public slots:
    //打开相机
    void openCamera(int cameraId, bool isOpen);
    //连接成功
    void cameraConnectSuccess();
    //相机连接报错
    void cameraError();
    //读取相机内容
    void readCamera();

public:

    //设备状态
    QVector<QString> deviceState; //0为plc，其他相机编号+1
    MainWindow *m;

};

#endif // CAMERA_H
