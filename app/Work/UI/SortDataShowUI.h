#ifndef SORTDATASHOWUI_H
#define SORTDATASHOWUI_H

#include <QWidget>
#include "define.h"

//一个相机的框架
typedef struct {
    QLineEdit *editExpressId = nullptr;
    QLineEdit *editCarrierId  = nullptr;
    QLineEdit *editBoxId  = nullptr;

    QLabel *status  = nullptr;
    QPushButton *buttonConnect = nullptr;
    QPushButton *buttonClose = nullptr;

} SortDataWidget;

class SortDataShowUI : public QWidget
{
    Q_OBJECT
public:
    explicit SortDataShowUI(QWidget *parent = nullptr);
    //设置相机界面
    void setUI();
    //显示数据信息到界面上
    void showData(int cameraId, QString expressId, QString carrierId, QString boxId); //显示分拣数据


signals:
    void buttonCameraClicked(int indexCamera, bool isOpen);

public slots:

public:
    QVector<SortDataWidget *> sortDataWidgetVector; //容器


};

#endif // SORTDATASHOWUI_H
