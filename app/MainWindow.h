#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include "define.h"

namespace Ui {
class MainWindow;
}


//测试还是运行版本
enum VERSIONSTATUS
{
  RELEASE,
  TEST,
};

class TestUI;
class ConfigureUI;
class SortArrivedSendBag;
class Camera;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
   static MainWindow* getInstance();
    //状态栏初始化，下位机视觉连接状态
    void initStatusBar();
    //工具栏设置初始化
    void initToolBar();
    //设置tabWidget
    void setTabWidget();
    //信号与槽
    void connectSignalSlot();
    //提示相机连接状态
    void setCameraStatus(int indexCamera, QString status);




    ~MainWindow();
signals:
    void arrivedSignal(bool);

public slots:
    //状态栏改变
    void slotChangeStatusBar();
    //添加报警信息
    void appendAlarm(QString content, QString level, QString component);
public:
    SortArrivedSendBag *sortArrivedSendBag;
    TestUI *testUI_;
    ConfigureUI *configureUI;
    Camera *camera;


    QLabel *m_status1;
    QLabel *m_status2;
    QLabel *m_status3;
    QLabel *m_status4;
    QLabel *pTimeLabel;

    VERSIONSTATUS verson_status_;


    QTimer* status_timer_; //状态定时器
    //工具栏
    QAction *actionConnectAllCamera_;
    QAction *actionCloseAllCamera_;


private:
    Ui::MainWindow *ui;
    static MainWindow* instance_;
};

#endif // MAINWINDOW_H
