#include "ToolUI.h"

ToolUI::ToolUI(QGroupBox *parent) : QGroupBox(parent)
{
    layoutMain_ = new QHBoxLayout;
    QSize size(25,25);

    buttonTcpIpHelper_ = new QToolButton();
//    buttonTcpIpHelper_->setObjectName("btnTcpIpHelper");
    buttonTcpIpHelper_->setText("网络助手");
    buttonTcpIpHelper_->setIcon(QIcon(":/image/intel.png"));
    buttonTcpIpHelper_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    buttonTcpIpHelper_->setIconSize(size);



    buttonMySqlCommand_ = new QToolButton();
    buttonMySqlCommand_->setObjectName("btnMySqlCommand");
    buttonMySqlCommand_->setText("数据库");
    buttonMySqlCommand_->setIcon(QIcon(":/image/mysql.png"));
    buttonMySqlCommand_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    buttonMySqlCommand_->setIconSize(size);

    buttonCMD_ = new QToolButton();
    buttonCMD_->setObjectName("btnCMD");
    buttonCMD_->setText("CMD");
    buttonCMD_->setIcon(QIcon(":/image/cmd.png"));
    buttonCMD_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    buttonCMD_->setIconSize(size);

    buttonRemoteDesktop_ = new QToolButton();
    buttonRemoteDesktop_->setObjectName("btnRemoteDesktop");
    buttonRemoteDesktop_->setText("远程桌面");
    buttonRemoteDesktop_->setIcon(QIcon(":/image/local.png"));
    buttonRemoteDesktop_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    buttonRemoteDesktop_->setIconSize(size);

    connect(buttonTcpIpHelper_, &QToolButton::clicked, this, [=]()
    {
        QString appDirPath = QCoreApplication::applicationDirPath();
        QString fileName = QString("%1\\tools\\NetAssist.exe").arg(appDirPath);
        QProcess::execute("explorer " + fileName.replace('/', '\\'));
    });
    connect(buttonMySqlCommand_, &QToolButton::clicked, this, [=]()
    {
        QString program("C:\\Program Files\\MySQL\\MySQL Server 5.5\\bin\\mysql.exe");
        QStringList arguments;
        arguments << "-hlocalhost" << "-uroot" << "-p";
        QProcess *myProcess = new QProcess(this);
        myProcess->execute(program, arguments);
//        QString str = "C:\\Windows\\System32\\cmd.exe " + program.replace('/', "\\") + " -hlocalhost" + " -uroot" + " -p";
//        QProcess::execute(str);
    });
    connect(buttonCMD_, &QToolButton::clicked, this, [=]()
    {
        QString program("C:\\Windows\\System32\\cmd.exe");
        QString appDirPath = QCoreApplication::applicationDirPath();
        QString fileName = QString("%1\\tools\\NetAssist.exe").arg(appDirPath);
        QProcess::execute("explorer " + program.replace('/', '\\'));
    });

    connect(buttonRemoteDesktop_, &QToolButton::clicked, this, [=]()
    {
        QString program("C:\\Windows\\System32\\mstsc.exe");
        QString appDirPath = QCoreApplication::applicationDirPath();
        QString fileName = QString("%1\\tools\\NetAssist.exe").arg(appDirPath);
        QProcess::execute("explorer " + program.replace('/', '\\'));
    });

    layoutMain_->addWidget(buttonTcpIpHelper_);
    layoutMain_->addWidget(buttonMySqlCommand_);
    layoutMain_->addWidget(buttonCMD_);
    layoutMain_->addWidget(buttonRemoteDesktop_);

    setLayout(layoutMain_);
}
