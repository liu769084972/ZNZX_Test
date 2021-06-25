#ifndef TOOLUI_H
#define TOOLUI_H
#include "define.h"

#include <QWidget>

class ToolUI : public QGroupBox
{
    Q_OBJECT
public:
    explicit ToolUI(QGroupBox *parent = nullptr);
    QHBoxLayout *layoutMain_;

    QToolButton *buttonTcpIpHelper_;
    QToolButton *buttonMySqlCommand_;
    QToolButton *buttonCMD_;
    QToolButton *buttonRemoteDesktop_;


signals:

public slots:
};

#endif // TOOLUI_H
