#include "ConfigureUI.h"
#include "Configure/Configure.h"
#include "ConfigureGlobal.h"
ConfigureUI::ConfigureUI(QWidget *parent) : QWidget(parent)
{
    layoutMain = new QVBoxLayout;
    //以进港为主，决定UI（因为进港一般可以多个，而出港只有一个
    setGlobalUi();
    QBitArray ba = Configure::getInstance()->companySwitchCome();
    qDebug()<<ba[Sto]<<ba[Yto];
    if(ba[Sto])
    {
//    setStoUi();
    }
    else if(ba[Yto])
    {
//        setYtoUi();
    }
    setLayout(layoutMain);

}

void ConfigureUI::setGlobalUi()
{
    configureGlobal = new ConfigureGlobal;
    layoutMain->addWidget(configureGlobal);
}
