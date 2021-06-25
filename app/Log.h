#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QThread>
#include "define.h"



class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);
    static Log* getInstance();
    void loadFile();


signals:
    void appendAlarmWindow(QString message);

public slots:
    void appendRunLog(QString mes); //运行日志
    void appendDetailLog(QString mes); //详细日志
    void appendDispatchLog(QString mes); //发件日志
    void appendArriveLog(QString mes); //到件日志
    void slot_timeOutPlcLog(QString mes); //发送超时
    void slot_rangeOutPlcLog(QString mes); //超过区间
public:
    QFile *runLog;
    QTextStream *runLogWrite;
    QFile *detailLog;
    QTextStream *detailLogWrite;
    QFile *arriveLog;
    QTextStream *arriveWrite;
    QFile *dispatchLog;
    QTextStream *dispatchWrite;
    QFile *timeOutPlcLog;
    QTextStream *timeOutPlcWrite;
    QFile *rangeOutPlcLog;
    QTextStream *rangeOutPlcWrite;



private:
    static Log *instance_;
    static QThread *thread;


};

#endif // LOG_H
