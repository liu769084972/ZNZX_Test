#ifndef CALCULATESORTDATAUI_H
#define CALCULATESORTDATAUI_H

#include <QWidget>
#include <QFrame>
#include "define.h"

class CalculateSortDataUI:public QFrame
{
    Q_OBJECT

public:
    CalculateSortDataUI(QWidget *parent = nullptr);
    //根据视觉数量设置标签数量
    void setcalculateLabel();
    //计算总量
    void calculate(int scanNum, int indexCompany);

public:
    //保存Label，以备后面调用
    QVector<QLabel *> labelVector;

    QLabel *labelTotalNum; //显示数量
    QHBoxLayout *mainLayout; //主布局器
    int total = 0;
    QBitArray baCompany;



};

#endif // CALCULATESORTDATAUI_H
