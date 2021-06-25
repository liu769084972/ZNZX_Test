#include "Log.h"

Log *Log::instance_ = nullptr;
QThread *Log::thread = nullptr;

Log *Log::getInstance()
{

    if (!instance_) {
        instance_ = new Log;
    }

    if (!thread) {
        thread = new QThread;
        thread->start();
    }

    if (thread !=  instance_->thread) {
        instance_->moveToThread(thread);
        thread->start();
    }

    return instance_;
}

Log::Log(QObject *parent) : QObject(parent)
{

}

void Log::loadFile()
{
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString fileName = QString("%1/logs/runLog%2.log").arg(appDirPath)
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    runLog = new QFile(fileName);
    if (!runLog->open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit appendAlarmWindow(QString("分拣运行日志打开失败：%1").arg(runLog->errorString()));
    }
    runLogWrite = new QTextStream(runLog);

    QString fileName1 = QString("%1/logs/detailLog%2.log").arg(appDirPath)
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    detailLog = new QFile(fileName1);
    if (!detailLog->open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit appendAlarmWindow(QString("详细日志打开失败：%1").arg(runLog->errorString()));
    }
    detailLogWrite = new QTextStream(detailLog);

    QString fileName2 = QString("%1/logs/arriveLog%2.log").arg(appDirPath)
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    arriveLog = new QFile(fileName2);
    if (!arriveLog->open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit appendAlarmWindow(QString("详细日志打开失败：%1").arg(arriveLog->errorString()));
    }
    arriveWrite = new QTextStream(arriveLog);

    QString fileName3 = QString("%1/logs/dispatchLog%2.log").arg(appDirPath)
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    dispatchLog = new QFile(fileName3);
    if (!dispatchLog->open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit appendAlarmWindow(QString("详细日志打开失败：%1").arg(dispatchLog->errorString()));
    }
    dispatchWrite = new QTextStream(dispatchLog);

    QString fileName4 = QString("%1/logs/timeOutPlcLog%2.log").arg(appDirPath)
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    timeOutPlcLog = new QFile(fileName4);
    if (!timeOutPlcLog->open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit appendAlarmWindow(QString("快递号请求超时报警日志文件打开失败：%1").arg(timeOutPlcLog->errorString()));
    }
    timeOutPlcWrite = new QTextStream(timeOutPlcLog);

    QString fileName5 = QString("%1/logs/rangeOutPlcLog%2.log").arg(appDirPath)
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    rangeOutPlcLog = new QFile(fileName5);
    if (!rangeOutPlcLog->open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit appendAlarmWindow(QString("快递号超过区间报警日志文件打开失败：%1").arg(rangeOutPlcLog->errorString()));
    }
    rangeOutPlcWrite = new QTextStream(rangeOutPlcLog);

    QString flag = QString("----------------日志开始(%1)----------------")
            .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss.zzz"));
    appendDetailLog(flag);
    appendDispatchLog(flag);
    slot_timeOutPlcLog(flag);
    slot_rangeOutPlcLog(flag);
}

void Log::appendRunLog(QString mes)
{
    *runLogWrite << mes << "\r\n";
    runLogWrite->flush();
}

void Log::appendDetailLog(QString mes)
{
    *detailLogWrite << mes << "\r\n";
    detailLogWrite->flush();
}

void Log::appendDispatchLog(QString mes)
{
    *dispatchWrite << mes << "\r\n";
    dispatchWrite->flush();
}

void Log::appendArriveLog(QString mes)
{
    *arriveWrite << mes << "\r\n";
    arriveWrite->flush();
}

void Log::slot_timeOutPlcLog(QString mes)
{
    *timeOutPlcWrite << mes << "\r\n";
    timeOutPlcWrite->flush();
}

void Log::slot_rangeOutPlcLog(QString mes)
{
    *rangeOutPlcWrite << mes << "\r\n";
    rangeOutPlcWrite->flush();
}









