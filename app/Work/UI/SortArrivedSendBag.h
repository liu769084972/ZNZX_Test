#ifndef SORTARRIVEDSENDBAG_H
#define SORTARRIVEDSENDBAG_H

#include <QWidget>
#include "define.h"

class SortUI;
class ArrivedSendBagUI;

class SortArrivedSendBag : public QWidget
{
    Q_OBJECT
public:
    explicit SortArrivedSendBag(QWidget *parent = nullptr);

signals:

public slots:

public:
    SortUI *sort; //分拣
    ArrivedSendBagUI *arrSndBag; //到派集包
    QHBoxLayout *layoutMain; //主布局器

};

#endif // SORTARRIVEDSENDBAG_H
