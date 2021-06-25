#ifndef TESTUI_H
#define TESTUI_H

#include <QWidget>
#include "define.h"

class ToolUI;
class TestDrop;
class TestUI : public QWidget
{
    Q_OBJECT
public:
    explicit TestUI(QWidget *parent = nullptr);
    //布局设置
    void layoutSettings();
    //创建信号与槽
    void createSlotSignal();

signals:
    void appendDetailLog(QString);

public slots:
    void buttonAddExpressIdBoxIdClicked(); //添加快递和格口编号
    void buttonDelExpressIdBoxIdClicked(); //删除快递和格口编号
    void tableShowExpressBoxIdCellChanged(int row, int); //项数据改变
    void showData(QString expressId, QString carrierId, QString boxId, QString camera);

    void saveDataToFile();
    void loadFileToTable();

public:
    //功能栏
    ToolUI *toolUI;

    //测试落格主体类
    TestDrop *testDrop;

    //指定小车和不指定小车
    bool isComoCarrierIdSelected = false;
    //布局
    QVBoxLayout *layoutMain_;
    QHBoxLayout *layoutGroupTestDrop_; //群组框布局-水平布局
    QVBoxLayout *layoutShowData_; //展示数据区的布局
    QFormLayout *layoutExpressId_;
    QFormLayout *layoutCarrierId_;
    QFormLayout *layoutBoxId_;
    QFormLayout *layoutCamera_;
    QHBoxLayout *layoutButton_;
    QHBoxLayout *layoutTableShowExpressBoxId_;
    QVBoxLayout *layoutButtonExpressBoxId_;

    QGroupBox *groupTestDrop_;
    QLineEdit *editExpressId_;      //快递编号，小车编号，格口编号，相机名称
    QLineEdit *editCarrierId_;
    QLineEdit *editBoxId_;
    QLineEdit *editCamera_;
    QLabel *labelShowStatus_;
    QPushButton *buttonConnect_; //连接视觉按钮
    QPushButton *buttonClsoe_; //关闭视觉按钮
    QPushButton *buttonAddExpressIdBoxId_; //添加TestDrop::expressIdBoxIdHash添加格口和快递号
    QPushButton *buttonEditExpressIdBoxId_; //编辑TestDrop::expressIdBoxIdHash添加格口和快递号
    QPushButton *buttonDelExpressIdBoxId_; //删除TestDrop::expressIdBoxIdHash格口和快递号
    QPushButton *buttonClearExpressIdBoxId_; //清空TestDrop::expressIdBoxIdHash格口和快递号
    QPushButton *buttonLoad_; //加载保存至文件的数据
    QPushButton *buttonSave_; //保存当前格口的数据
    QTableWidget *tableShowExpressBoxId_; //显示已添加的快递和格口


};

#endif // TESTUI_H
