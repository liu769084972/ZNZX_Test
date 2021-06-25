#ifndef SORTUI_H
#define SORTUI_H

#include <QWidget>
#include "define.h"

class CalculateSortDataUI;
class SortDataShowUI;

class SortUI: public QFrame
{
public:
    SortUI(QWidget *parent = nullptr);

public:
    QVBoxLayout *layoutMain;
    CalculateSortDataUI *calSortData; //计数
    SortDataShowUI *sortData; //分拣数据
};

#endif // SORTUI_H
