#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QStatusBar>
#include <QDebug>
#include <QDateTime>
#include "Test/UI/TestUI.h"
#include "Configure/UI/ConfigureUI.h"
#include "Work/UI/SortArrivedSendBag.h"
#include "Work/UI/SortUI.h"
#include "Work/UI/ArrivedSendBagUI.h"
#include "Work/UI/SortDataShowUI.h"
#include "Camera.h"
#include "Common.h"


MainWindow* MainWindow::instance_ = NULL;


MainWindow* MainWindow::getInstance()
{
    if(instance_ == NULL)
    {
        instance_ = new MainWindow();
    }
    return  instance_;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sortArrivedSendBag = new SortArrivedSendBag();
    testUI_ = new TestUI;
    configureUI = new ConfigureUI;
    camera = new Camera(this, this);

    Common::getInstance()->plc_status_ = PLC_OFF;
    Common::getInstance()->camera_status_ = CAMERA_OFF;
    connectSignalSlot();
    initToolBar();
    initStatusBar();
    setTabWidget();
    status_timer_ = new QTimer;
    QObject::connect(status_timer_,SIGNAL(timeout()),this,SLOT(slotChangeStatusBar()));
    status_timer_->start(1000);
}

void MainWindow::initStatusBar()
{
    QStatusBar *pStatusBar = statusBar();

    m_status1 = new QLabel(QStringLiteral("  PLC连接状态:  "));
    m_status2 = new QLabel;
    m_status3 = new QLabel(QStringLiteral("  视觉连接状态:  "));
    m_status4 = new QLabel;
    pTimeLabel = new QLabel;
    pStatusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角

    pStatusBar->addWidget(m_status1);
    pStatusBar->addWidget(m_status2);
    pStatusBar->addWidget(m_status3);
    pStatusBar->addWidget(m_status4);
    pStatusBar->addPermanentWidget(pTimeLabel);
}

void MainWindow::initToolBar()
{

    //一键连接
    actionConnectAllCamera_ = new QAction("一键连接",this);
    actionConnectAllCamera_->setIcon(QIcon(":/image/open.png"));
    actionConnectAllCamera_->setChecked(true);

    //actionConnectAllCamera->setShortcut();
    actionConnectAllCamera_->setStatusTip("连接所有的相机");
    connect(actionConnectAllCamera_, &QAction::triggered, this, [=]()
    {
        auto vector = sortArrivedSendBag->sort->sortData->sortDataWidgetVector;
        foreach(auto i, vector) {
            i->buttonConnect->click();
        }
    });

    //一键关闭
    actionCloseAllCamera_ = new QAction("一键关闭", this);
    actionCloseAllCamera_->setIcon(QIcon(":/image/close.png"));
    //actionCloseAllCamera->setShortcut();
    actionCloseAllCamera_->setStatusTip("关闭所有的相机");
    actionCloseAllCamera_->setChecked(true);

    connect(actionCloseAllCamera_, &QAction::triggered, this, [=]()
    {
        auto vector = sortArrivedSendBag->sort->sortData->sortDataWidgetVector;
        foreach(auto i, vector) {
            i->buttonClose->click();
        }
    });
     ui->mainToolBar->setMovable(false);
     ui->mainToolBar->addAction(actionConnectAllCamera_);
     ui->mainToolBar->addAction(actionCloseAllCamera_);
     ui->mainToolBar->setIconSize(QSize(25,25));
     ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


}

void MainWindow::setTabWidget()
{
    ui->tabWidget->setTabPosition(QTabWidget::South);

    ui->tabWidget->insertTab(SortArrivedSendBagTabPage, sortArrivedSendBag, "分拣-到件-派件-集包");
    ui->tabWidget->insertTab(TestTabPage, configureUI, "配置");
//    ui->tabWidget->insertTab(QueryStatisticsTabPage, queryStatistics, "查询统计");
    ui->tabWidget->insertTab(TestTabPage, testUI_, "测试");
//    ui->tabWidget->insertTab(AlarmTabPage, alarmUI, "报警");
    QTabBar * bars = ui->tabWidget->tabBar();
    bars->setFont(QFont("", 25));

}

void MainWindow::connectSignalSlot()
{
    connect(sortArrivedSendBag->sort->sortData, &SortDataShowUI::buttonCameraClicked,
            camera, &Camera::openCamera);
    connect(sortArrivedSendBag->arrSndBag, &ArrivedSendBagUI::isArrived,
            this, &MainWindow::arrivedSignal);
}

void MainWindow::setCameraStatus(int indexCamera, QString status)
{
    sortArrivedSendBag->sort->sortData->sortDataWidgetVector[indexCamera]->status->setText(status);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotChangeStatusBar()
{
    const QString m_red_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:0px solid black;background:#ff4d4d";
    const QString m_green_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:0px solid black;background:#47d147";
    if(Common::getInstance()->plc_status_ == PLC_ON)
    {
        m_status2->setStyleSheet(m_green_SheetStyle);//改成 绿色圆形
    }else{
        m_status2->setStyleSheet(m_red_SheetStyle);//改成 红色圆形
    }
    if(Common::getInstance()->camera_status_ == CAMERA_ON)
    {
        m_status4->setStyleSheet(m_green_SheetStyle);//改成 绿色圆形
    }else{
        m_status4->setStyleSheet(m_red_SheetStyle);//改成 红色圆形
    }
    //更新时间的槽函数中的代码
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeStr = currentTime.toString(QStringLiteral("yyyy年MM月dd日 hh:mm:ss") + "   ");
    pTimeLabel->setText(timeStr);

}

void MainWindow::appendAlarm(QString content, QString level, QString component)
{
 //   alarmUI->appendMessage(content, level, component);
}
