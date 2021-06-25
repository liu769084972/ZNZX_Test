#include "Camera.h"
#include "MainWindow.h"
#include "Configure/Configure.h"
#include "Test/UI/TestUI.h"
#include "Log.h"
#include "common.h"

Camera::Camera(MainWindow *main,QObject *parent )
    : m(main),QObject(parent)
{
    connect(this, &Camera::appendDetailLog, Log::getInstance(), &Log::appendDetailLog);

    connect(this, &Camera::appendAlarm, m, &MainWindow::appendAlarm);
    initCamera();

}

void Camera::initCamera()
{
    QVector<StructCamera>& cameras  = Configure::getInstance()->camerasVector();
    int length = cameras.size();
    for (int i = 0; i < length; ++i) {
        cameras[i].tcpSocekt = new QTcpSocket(this);
        connect(cameras[i].tcpSocekt, &QAbstractSocket::connected, this, &Camera::cameraConnectSuccess);
        connect(cameras[i].tcpSocekt, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Camera::cameraError);
        connect(cameras[i].tcpSocekt, SIGNAL(readyRead()), this, SLOT(readCamera()));
        //cameras[i].tcpSocekt->connectToHost(cameras[i].ip, cameras[i].port);
    }
}

int Camera::cameraIdFromCamera(QTcpSocket *tcpSocket)
{
    QVector<StructCamera>& cameras = Configure::getInstance()->camerasVector();
    for (int i = 0; i < cameras.size(); ++i) {
        if (tcpSocket == cameras[i].tcpSocekt) {
            return i;
        }
    }
    return -1;
}

void Camera::openCamera(int cameraId, bool isOpen)
{
    QVector<StructCamera>& cameras = Configure::getInstance()->camerasVector();

    if (!cameras[cameraId].tcpSocekt) {
        cameras[cameraId].tcpSocekt = new QTcpSocket(this);
        connect(cameras[cameraId].tcpSocekt, SIGNAL(readyRead()), this, SLOT(readViewer()));
        connect(cameras[cameraId].tcpSocekt, SIGNAL(connected()), this, SLOT(success()));
        connect(cameras[cameraId].tcpSocekt, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(error()));
    }

    if (cameras[cameraId].tcpSocekt->state() == QAbstractSocket::UnconnectedState && isOpen) { //如果状态是关，则连接
        m->setCameraStatus(cameraId, "<font style='color:blue'>正在连接视觉...</font>");
        cameras[cameraId].tcpSocekt->connectToHost(cameras[cameraId].ip,
                                                   cameras[cameraId].port);
    }

    if (!isOpen && cameras[cameraId].tcpSocekt->state() == QAbstractSocket::ConnectedState) {
        cameras[cameraId].tcpSocekt->close();
        Common::getInstance()->camera_status_ = CAMERA_OFF;
        m->setCameraStatus(cameraId, "<font style='color:blue'>关闭</font>");
    }
}

void Camera::cameraConnectSuccess()
{
    QTcpSocket *tcpSocket = qobject_cast<QTcpSocket *>(sender());
    int cameraId = cameraIdFromCamera(tcpSocket);
    if (cameraId >= 0) {
        Common::getInstance()->camera_status_ = CAMERA_ON;
        m->setCameraStatus(cameraId, "<font color=green>连接成功!</font>");
    }
}
void Camera::cameraError()
{
    QTcpSocket *tcpSocket = qobject_cast<QTcpSocket *>(sender());
    int cameraId = cameraIdFromCamera(tcpSocket);
    if (cameraId >= 0) {
        m->setCameraStatus(cameraId, QString("<font color=red>%1</font>")
                                                   .arg(tcpSocket->errorString()));
        QVector<StructCamera>& cameras = Configure::getInstance()->camerasVector();
        emit appendAlarm(QString("%1：%2").arg(cameras[cameraId].cameraName)
                         .arg(tcpSocket->errorString()), "严重", "相机");
    }
}

void Camera::readCamera()
{
    QTcpSocket *tcpSocket = qobject_cast<QTcpSocket *>(sender());

    //读取内容
    QString cameraData = tcpSocket->readAll();
    //找到相机位置
    QVector<StructCamera>& cameras = Configure::getInstance()->camerasVector();
    int cameraId = cameraIdFromCamera(tcpSocket);

    //发送给快递类
    if (cameraId >= 0) {
        int plcIndex = cameras[cameraId].plcIndex;
        short exceptionBoxId = cameras[cameraId].exceptionBoxId;
        CameraType type = cameras[cameraId].type;
        int carrierNum = cameras[cameraId].carrierNum;
        QString pdaCode = cameras[cameraId].pdaCode;
        QString cameraName = cameras[cameraId].cameraName;
        //获取快递号和小车号
        QString expressId;
        if (type == DaHua) { //大华
            expressId = cameraData.trimmed();
        }
        else if (type == HaiKang)
        { //海康
            //排除Noread和空车
            if (cameraData.contains("NoRead", Qt::CaseInsensitive) ||
                    cameraData.length() < 3 ||
                    !cameraData.startsWith('[')) {
                return;
            }

            //去掉]后面的连包（也可以做连包处理）
            cameraData = cameraData.section(']', 0, 0);
            cameraData.remove("[");
            expressId = cameraData.trimmed();
        }

        //        if (expressId.isEmpty() || !isLetterOrNumberString(expressId))
        //            return;
        //        express->saveExpressTocarrierExpressVector(expressId, pdaCode,
        //                plcIndex, exceptionBoxId, cameraId, carrierNum, cameraName);
    }
}
