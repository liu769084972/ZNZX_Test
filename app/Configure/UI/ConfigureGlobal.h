#ifndef CONFIGUREGLOBAL_H
#define CONFIGUREGLOBAL_H

#include <QWidget>
#include "define.h"

class ConfigureGlobal : public QGroupBox
{
    Q_OBJECT
public:
    explicit ConfigureGlobal(QWidget *parent = nullptr);
    //参数布局设置
    void setConfigLayout();

    //从文件加载数据到表格-保持一致性
    void loadFileToTableCamera();
    //表格增删
    void buttonAddClicked();
    void buttonDelClicked();



signals:

public slots:
    //文本发送改变，同步到文件
    void tableCameraCellChanged(int row, int column);
    void editNetIpTextChanged(QString text);
    void editNativeIpTextChanged(QString text);
    void editMaxCarrierIdTextChanged(QString text);

public:
    QLabel *labelTableTip; //提示表格内容格式
    QTableWidget *tableCamera;
    QPushButton *buttonAdd;
    QPushButton *buttonEdit;
    QPushButton *buttonDel;
    QVBoxLayout *layoutTableLabel;
    QHBoxLayout *layoutTableButton;
    QHBoxLayout *layoutButton;
    QHBoxLayout *layoutGroupDevice;
    QStringList cameraArgList; //代表表格每行的数据，如果对应的项不存在，或者文本为空，则指为""

    QLineEdit *editNetIp;
    QLineEdit *editNativeIp;
    QLineEdit *editMaxCarrierId;
    QLineEdit *editMaxBoxId;
    QFormLayout *layoutDeviceEdit;


};

#endif // CONFIGUREGLOBAL_H
