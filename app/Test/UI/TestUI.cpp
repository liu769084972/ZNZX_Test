#include "TestUI.h"
#include "ToolUI.h"
#include "Test/TestDrop.h"

TestUI::TestUI(QWidget *parent) : QWidget(parent)
{


    layoutMain_ = new QVBoxLayout;
    toolUI = new ToolUI;
    testDrop = new TestDrop(this, this);

    layoutMain_->addWidget(toolUI);
    setLayout(layoutMain_);

    layoutSettings();
    //创建信号和槽连接
    createSlotSignal();

}

void TestUI::layoutSettings()
{
    layoutGroupTestDrop_ = new QHBoxLayout; //群组框布局-水平布局

    groupTestDrop_ = new QGroupBox;

    editExpressId_ = new QLineEdit;
    editCarrierId_ = new QLineEdit;
    editBoxId_ = new QLineEdit;
    labelShowStatus_ = new QLabel;
    editCamera_ = new QLineEdit;
    editExpressId_->setReadOnly(true);
    editCarrierId_->setReadOnly(true);
    editBoxId_->setReadOnly(true);
    editCamera_->setReadOnly(true);

    buttonConnect_ = new QPushButton("连接");
    buttonConnect_->setObjectName("btnConnect");

    buttonClsoe_ = new QPushButton("关闭");
    buttonClsoe_ ->setObjectName("btnClsoe");

    layoutExpressId_ = new QFormLayout;
    layoutExpressId_->addRow("快递编号：", editExpressId_);

    layoutCarrierId_ = new QFormLayout;
    layoutCarrierId_->addRow("小车编号：", editCarrierId_);

    layoutBoxId_ = new QFormLayout;
    layoutBoxId_->addRow("格口编号：", editBoxId_);

    layoutCamera_ = new QFormLayout;
    layoutCamera_->addRow("相机名称：", editCamera_);

    layoutButton_ = new QHBoxLayout;
    layoutButton_->addWidget(buttonConnect_);
    layoutButton_->addWidget(buttonClsoe_);
    layoutButton_->addStretch();

    layoutShowData_ = new QVBoxLayout; //展示数据区的布局
    layoutShowData_->addLayout(layoutExpressId_);
    layoutShowData_->addLayout(layoutCarrierId_);
    layoutShowData_->addLayout(layoutBoxId_);
    layoutShowData_->addLayout(layoutCamera_);
    layoutShowData_->addStretch();
    layoutShowData_->addWidget(labelShowStatus_);
    layoutShowData_->addLayout(layoutButton_);

    buttonAddExpressIdBoxId_ = new QPushButton("添加"); //添加TestDrop::expressIdBoxIdHash添加格口和快递号
    buttonEditExpressIdBoxId_ = new QPushButton("编辑"); //编辑TestDrop::expressIdBoxIdHash添加格口和快递号
    buttonDelExpressIdBoxId_ = new QPushButton("删除"); //删除TestDrop::expressIdBoxIdHash格口和快递号
    buttonClearExpressIdBoxId_ = new QPushButton("清空"); //清空
    buttonLoad_ = new QPushButton("加载");
    buttonSave_ = new QPushButton("保存");

    //按钮加入到布局
    layoutButtonExpressBoxId_ = new QVBoxLayout;
    buttonAddExpressIdBoxId_->setObjectName("btnAddExpressIdBoxId");
    buttonEditExpressIdBoxId_->setObjectName("btnEditExpressIdBoxId");
    buttonDelExpressIdBoxId_->setObjectName("btnDelExpressIdBoxId");
    buttonClearExpressIdBoxId_->setObjectName("btnClearExpressIdBoxId");
    buttonSave_->setObjectName("btnSave");
    buttonLoad_->setObjectName("btnLoad");

    layoutButtonExpressBoxId_->setSpacing(10);
    layoutButtonExpressBoxId_->addWidget(buttonAddExpressIdBoxId_);
    layoutButtonExpressBoxId_->addWidget(buttonEditExpressIdBoxId_);
    layoutButtonExpressBoxId_->addWidget(buttonDelExpressIdBoxId_);
    layoutButtonExpressBoxId_->addWidget(buttonClearExpressIdBoxId_);
    layoutButtonExpressBoxId_->addWidget(buttonSave_);
    layoutButtonExpressBoxId_->addWidget(buttonLoad_);
    layoutButtonExpressBoxId_->addStretch();

    tableShowExpressBoxId_ = new QTableWidget(0, 2); //显示已添加的快递和格口表格
    tableShowExpressBoxId_->setHorizontalHeaderLabels(QStringList() << "快递编号" << "格口编号");
    tableShowExpressBoxId_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableShowExpressBoxId_->setAlternatingRowColors(true);
   // tableShowExpressBoxId_->setStyleSheet("border 0px; color: #6b6d7b; alternate-background-color: red; background: white; ");
    layoutTableShowExpressBoxId_ = new QHBoxLayout;
    layoutTableShowExpressBoxId_->addWidget(tableShowExpressBoxId_);
    layoutTableShowExpressBoxId_->addSpacing(30);
    layoutTableShowExpressBoxId_->addLayout(layoutButtonExpressBoxId_);

    //加入到群组框布局
    layoutGroupTestDrop_->addLayout(layoutShowData_);
    //增加水平宽度
    layoutGroupTestDrop_->addSpacing(30);
    layoutGroupTestDrop_->addLayout(layoutTableShowExpressBoxId_);

    layoutGroupTestDrop_->addStretch();
    //设置为群组框布局
    groupTestDrop_->setLayout(layoutGroupTestDrop_);
    //将群组框加入到界面主布局器
    layoutMain_->addWidget(groupTestDrop_);
}

void TestUI::createSlotSignal()
{
    connect(buttonAddExpressIdBoxId_, &QPushButton::clicked,
            this, &TestUI::buttonAddExpressIdBoxIdClicked);
    connect(tableShowExpressBoxId_, &QTableWidget::cellChanged,
            this, &TestUI::tableShowExpressBoxIdCellChanged);
    //删除选中行
    connect(buttonDelExpressIdBoxId_, &QPushButton::clicked,
            this, &TestUI::buttonDelExpressIdBoxIdClicked);

    connect(buttonLoad_, &QPushButton::clicked, this, &TestUI::loadFileToTable);
    connect(buttonSave_, &QPushButton::clicked, this, &TestUI::saveDataToFile);

    connect(buttonConnect_, &QPushButton::clicked, testDrop, &TestDrop::openCamera);
    connect(buttonClsoe_, &QPushButton::clicked, testDrop, &TestDrop::closeCamera);
}

void TestUI::buttonAddExpressIdBoxIdClicked()
{
//    //插入一行
    int row = tableShowExpressBoxId_->rowCount();
    tableShowExpressBoxId_->insertRow(row);
//    plc->writeBoxId("1111", 1, 2, 3);

}

void TestUI::buttonDelExpressIdBoxIdClicked()
{
    //从expressIdBoxIdHash删除选中的行
    QList<QTableWidgetSelectionRange> selectedItem = tableShowExpressBoxId_->selectedRanges();

    for (int i = 0; i < selectedItem.length(); ++i) {
        int topRow = selectedItem[i].topRow();
        int bottomRow = selectedItem[i].bottomRow();
        for (int row = bottomRow; row >= topRow; --row) {
            QTableWidgetItem *item0 = tableShowExpressBoxId_->item(row, 0);
            if (item0) {
                testDrop->deleteOneExpressIdBoxId(item0->text());
            }
            tableShowExpressBoxId_->removeRow(row);
        }
    }
}

void TestUI::tableShowExpressBoxIdCellChanged(int row, int /*column*/)
{
    //获取对应行的快递号和格口号
    QTableWidgetItem *item0 = tableShowExpressBoxId_->item(row, 0);
    QTableWidgetItem *item1 = tableShowExpressBoxId_->item(row, 1);
    if (item0 && item1) {
        if (!isComoCarrierIdSelected) {
            QString expressId = item0->text();
            QString boxId = item1->text();
            if (!expressId.isEmpty() && !boxId.isEmpty()) {
                testDrop->addOneExpressIdBoxId(expressId, boxId.toShort());
            }
        }
    }
}

void TestUI::showData(QString expressId, QString carrierId, QString boxId, QString camera)
{
    editExpressId_->setText(expressId);
    editCarrierId_->setText(carrierId);
    editBoxId_->setText(boxId);
    editCamera_->setText(camera);
}

void TestUI::saveDataToFile()
{
    QFile file(FILE_TEST);
    file.close(); //先清空

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "警告", "文件打开失败");
        return;
    }
    QTextStream write(&file);
    int rows = tableShowExpressBoxId_->rowCount();
    for (int row = 0; row < rows; ++row) {
        QTableWidgetItem *item0 = tableShowExpressBoxId_->item(row, 0);
        QTableWidgetItem *item1 = tableShowExpressBoxId_->item(row, 1);

        if (item0 && item1) {
            QString expressId = item0->text().trimmed();
            QString boxId = item1->text().trimmed();

            write << QString("%1,%2").arg(expressId, boxId) << "\r\n";
        }
    }
}

void TestUI::loadFileToTable()
{
    QFile file(FILE_TEST);

    if (!file.open(QIODevice::ReadOnly)) {
        emit appendDetailLog("测试文件打开失败");
        return;
    }

    while (!file.atEnd()) {
        int rows = tableShowExpressBoxId_->rowCount();
        tableShowExpressBoxId_->insertRow(rows);
        QString line = file.readLine();
        QString expressId = line.section(',', 0, 0).trimmed();
        QString boxId = line.section(',', 1, 1).trimmed();
        QTableWidgetItem *item0 = new QTableWidgetItem(expressId);
        QTableWidgetItem *item1 = new QTableWidgetItem(boxId);
        tableShowExpressBoxId_->setItem( rows, 0,item0);
        tableShowExpressBoxId_->setItem( rows, 1,item1);

        testDrop->addOneExpressIdBoxId(expressId, boxId.toShort());
    }
}


