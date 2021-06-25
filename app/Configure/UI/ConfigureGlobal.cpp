#include "ConfigureGlobal.h"
#include "Configure/Configure.h"

ConfigureGlobal::ConfigureGlobal(QWidget *parent) : QGroupBox("设备参数",parent)
{

    setConfigLayout();
    //连接信号和槽
    connect(buttonAdd, &QPushButton::clicked, this, &ConfigureGlobal::buttonAddClicked);
    connect(buttonDel, &QPushButton::clicked, this, &ConfigureGlobal::buttonDelClicked);
    connect(tableCamera, &QTableWidget::cellChanged, this, &ConfigureGlobal::tableCameraCellChanged);
    connect(editNetIp, &QLineEdit::textChanged, this, &ConfigureGlobal::editNetIpTextChanged);
    connect(editNativeIp, &QLineEdit::textChanged, this, &ConfigureGlobal::editNativeIpTextChanged);
    connect(editMaxCarrierId, &QLineEdit::textChanged, this, &ConfigureGlobal::editMaxCarrierIdTextChanged);
}

void ConfigureGlobal::setConfigLayout()
{
    layoutGroupDevice = new QHBoxLayout;
    setCheckable(true);
    setChecked(false );

    layoutTableLabel = new QVBoxLayout; //表格标签布局

    buttonAdd = new QPushButton("添加");
    buttonAdd->setObjectName("btnAdd");


    buttonDel = new QPushButton("删除");
    buttonDel->setObjectName("btnDel");
    layoutButton = new QHBoxLayout; //表格操作按钮布局
    layoutButton->addWidget(buttonAdd);
    layoutButton->addWidget(buttonDel);
    layoutTableLabel->addLayout(layoutButton);

    tableCamera = new QTableWidget(0, 1);
    tableCamera->horizontalHeader()->setStretchLastSection(true);
    tableCamera->setHorizontalHeaderLabels(QStringList() << "相机参数：名称|IP|端口|PLC|进港异常口|出港异常口|开始格口|结束格口");
    layoutTableLabel->addWidget(tableCamera);

    loadFileToTableCamera(); //加载数据到表格

    editNetIp = new QLineEdit(Configure::getInstance()->getConfigure("PLC/AmsNetId").toString());
    editNativeIp = new QLineEdit(Configure::getInstance()->nativeip());
    editMaxCarrierId = new QLineEdit(QString::number(Configure::getInstance()->carrierNum()));
    editMaxBoxId = new QLineEdit();
    editMaxBoxId = new QLineEdit(QString::number(Configure::getInstance()->maxBoxId()));
    layoutDeviceEdit = new QFormLayout;
    layoutDeviceEdit->setSpacing(20);
    layoutDeviceEdit->addRow("PLC NetIP:", editNetIp);
    layoutDeviceEdit->addRow("本地数据库IP:", editNativeIp);
    layoutDeviceEdit->addRow("最大小车编号:", editMaxCarrierId);
    layoutDeviceEdit->addRow("最大格口编号:", editMaxBoxId);

    layoutGroupDevice->addLayout(layoutTableLabel);
    layoutGroupDevice->addLayout(layoutDeviceEdit);
    setLayout(layoutGroupDevice);
}


void ConfigureGlobal::buttonAddClicked()
{
    int row = tableCamera->rowCount();
    tableCamera->insertRow(row);
    //加入一行
    cameraArgList.append("");
}

void ConfigureGlobal::buttonDelClicked()
{
    //获取选中项
    QList<QTableWidgetSelectionRange> select = tableCamera->QTableWidget::selectedRanges();
    //获取选中数据
    for (int i = select.size() - 1; i >= 0; --i) {
        //获取行和列
        int topRow = select[i].topRow();
        int bottomRow = select[i].bottomRow();
        //删除前先获取文本
        for(int row = bottomRow; row >= topRow; --row) {
            //获取文本
            QTableWidgetItem *item = tableCamera->item(row, 0);
            if (item) {
               QString text = item->text();
               QString text1 = cameraArgList.takeAt(row);
               if (text != text1) {
                   qDebug() << text << text1;
               }
               //写入文件
               QString cameraArgs = cameraArgList.join('-');
               Configure::getInstance()->setConfigure("CAMERA/cameraArg", cameraArgs);
               //删除本行
               tableCamera->removeRow(row);
            }
        }
    }
    //loadFileToTableCamera();
}

void ConfigureGlobal::tableCameraCellChanged(int row, int column)
{
    QTableWidgetItem *item = tableCamera->item(row, column);
    if (item) {
        //获取文本
        QString text = item->text();
        //加入列表
        cameraArgList[row] = text;
        //写入文件
        QString cameraArgs = cameraArgList.join('-');
        Configure::getInstance()->setConfigure("CAMERA/cameraArg", cameraArgs);
    }
}

void ConfigureGlobal::editNetIpTextChanged(QString text)
{
    Configure::getInstance()->setConfigure("PLC/AmsNetId", text);
}

void ConfigureGlobal::editNativeIpTextChanged(QString text)
{
    Configure::getInstance()->setConfigure("NATIVEDB/ip", text);
}

void ConfigureGlobal::editMaxCarrierIdTextChanged(QString text)
{
    Configure::getInstance()->setConfigure("Track/carrierNum", text);
}

void ConfigureGlobal::loadFileToTableCamera()
{
    //为了保持文件和表格数据的一致性，全部删除，全部加载
    int rows = tableCamera->rowCount(); //清空表格，连同行列
    for (int i = 0; i < rows; ++i) {
        tableCamera->removeRow(i);
    }
    //获取参数
    QString cameraArgs = Configure::getInstance()->getConfigure("CAMERA/cameraArg").toString();
    qDebug()<<cameraArgs;
    //分解参数
    cameraArgList.clear();
    cameraArgList = cameraArgs.split('-', QString::SkipEmptyParts);
    //加载到表格
    for (int i = 0; i < cameraArgList.size(); ++i) {
        QString text = cameraArgList[i];
        //插入项
        if (!text.isEmpty()) {
            int row = tableCamera->rowCount();
            tableCamera->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(text);
            tableCamera->setItem(row, 0, item);
        }
    }
}
