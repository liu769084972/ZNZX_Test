#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QObject>
#include "define.h"
#include "Camera.h"

class Configure : public QObject
{
    Q_OBJECT
public:
    explicit Configure(QObject *parent = nullptr);
    static Configure* getInstance();

    QBitArray &companySwitchCome(){ return _companySwitchCome; }
    QBitArray &companySwitchGo(){ return _companySwitchGo; }
    unsigned char* netId() { return _netId; }
    QString &nativeip() { return _nativeip; } //本地数据库IP
    int cameraType() { return _cameraType; } //相机类型
    int carrierNum() { return _carrierNum; } //小车数量
    int maxBoxId() { return _maxBoxId; } //最大格口编号
    qint64 interfaceMaxDelay() { return _interfaceMaxDelay; }
    QVector<StructCamera> &camerasVector() { return _camerasVector; } //返回所有视觉信息
    bool detailLog() { return _detailLog; }
    //GUI
    int arrivedRow() { return _arrivedRow; }
    int sendOrBagRow() { return _sendOrBagRow; }
    QString appName() { return _appName; }

    int intervalCheckPack() { return _intervalCheckPack; }
    QVector<int>& packCheckThresholdVector() { return _packCheckThresholdVector; }
    int emptyPackWarnThreshold() { return _emptyPackWarnThreshold; }
    bool isCheckPack() { return _isCheckPack; }
    bool isCheckEmptyPack() { return _isCheckEmptyPack; }

    //获取配置参数
    void loadINI();
    //写下文件参数
    void setConfigure(const QString key, const QVariant value);
    //读取文件参数
    QVariant getConfigure(const QString key);
    ///公司选择
    QBitArray companySwitch();
    //判断未集包的阈值
    void readPackCheckThreshold();

signals:

public slots:


public:
    QSettings *global_;
    QMutex mutex_;

    QBitArray _companySwitchCome; //设备使用快递公司-进港
    QBitArray _companySwitchGo; //设备使用快递公司-进港

    unsigned char _netId[6]; //PLC NetId

    int _cameraType; //相机类型
    int _carrierNum; //小车数量
    int _maxBoxId; //最大格口编号

    QString _nativeip; //本地数据库

    //[ALARM]
    //接口最大延迟，超过，会产生一条报警，单位毫秒
    qint64 _interfaceMaxDelay = 200;

    QVector<StructCamera> _camerasVector;

    //界面设置
    //[GUI]
    //到件显示列表的行数
    int _arrivedRow;
    //派件或集包显示列表的行数
    int _sendOrBagRow;
    QString _appName;
    int _intervalCheckPack;
    int _emptyPackWarnThreshold;

    bool _isCheckPack;
    bool _isCheckEmptyPack;
    bool _detailLog;
    //判断可能未集包的阈值
    QVector<int> _packCheckThresholdVector;



private:
    static Configure *instance_;

};

#endif // CONFIGURE_H
