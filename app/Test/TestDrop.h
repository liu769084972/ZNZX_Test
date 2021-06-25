#ifndef TESTDROP_H
#define TESTDROP_H

#include <QObject>
#include "define.h"
#include "Camera.h"

class TestUI;
class Camera;
class PLC;
class TestDrop : public QObject
{
    Q_OBJECT
public:
    explicit TestDrop(TestUI *testUi, QObject *parent = nullptr);
    //添加一个条形码，小车号
    void addOneExpressIdBoxId(QString expressId, short boxId);
    //清除数据
    void clearExpressIdBoxIdHash();
    //删除当前的条形码
    void deleteOneExpressIdBoxId(QString expressId);
    //创建文件
    QString mkMultiDir(const QString path);
    //判断字符串是否只包含数字和字母
    inline bool isLetterOrNumberString(QString str);

signals:

public slots:
    //初始化相机内容
    void initCamera();
    //打开相机
    void openCamera();
    //关闭相机
    void closeCamera();
    //读取相机内容
    void readCamera();

private:
    QHash<QString, short> expressIdBoxIdHash; //存放测试用的快递单号和格口

    //视觉
    QVector<StructCamera> cameras;

    //界面类
    TestUI *testUI;

    PLC *plc;

    //设备状态
    QVector<QString> deviceState; //0为plc，其他相机编号+1

    short carrierId[8] = {0};


};

#endif // TESTDROP_H
