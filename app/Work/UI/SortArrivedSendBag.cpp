#include "SortArrivedSendBag.h"
#include "ArrivedSendBagUI.h"
#include "SortUI.h"

SortArrivedSendBag::SortArrivedSendBag(QWidget *parent) : QWidget(parent)
{
    sort = new SortUI;
    arrSndBag = new ArrivedSendBagUI;

    layoutMain = new QHBoxLayout;
    layoutMain->addWidget(sort);
    layoutMain->addWidget(arrSndBag);
    //layoutMain->addWidget(devStatus);

    setLayout(layoutMain);
}
