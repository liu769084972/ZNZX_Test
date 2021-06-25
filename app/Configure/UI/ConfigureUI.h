#ifndef CONFIGUREUI_H
#define CONFIGUREUI_H

#include <QWidget>
#include "define.h"

class ConfigureGlobal;
class ConfigureUI : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigureUI(QWidget *parent = nullptr);

    void setGlobalUi();


signals:

public slots:

public:
    QVBoxLayout *layoutMain;

    //设备参数布局
    ConfigureGlobal *configureGlobal;
};

#endif // CONFIGUREUI_H
