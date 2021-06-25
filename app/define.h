#ifndef DEFINE_H
#define DEFINE_H

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QTableWidget>
#include <QRadioButton>
#include <QTextEdit>
#include <QComboBox>
#include <QAction>
#include <QTextCodec>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QTextStream>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUuid>
#include <QNetworkReply>
#include <QTimer>
#include <QToolButton>
#include <QCoreApplication>
#include <QProcess>
#include <QSettings>
#include <QMutex>
#include <QBitArray>
#include <QDir>

#define FILE_GLOBAL_PATH "configure/global.ini"       //    //H:/ExpressSort/Configure/global.ini
#define FILE_CHECK_PACK "configure/checkPack.csv" //集包检测阈值

#define FILE_TEST "configure/test.txt" //保存测试文件的路径

//本地数据库


#define NATIVE_DB_STO_COME "express_inflow_st" //申通进港表


#define COMPANYNUM 7 //公司数量

enum CameraType{DaHua, HaiKang};
enum CompanyIndex{Sto, Zto, Yto, Best, Tt, Yunda, Youzheng, Exception, UnKnown};

enum TabTitleIndex{SortArrivedSendBagTabPage, ConfigureTabPage, QueryStatisticsTabPage, TestTabPage, AlarmTabPage};

//读plc报警
const int railWayNum = 2;
const int boxIdNum = 25;
const int plcExpressIdLen = 31;
typedef bool(*pbAlarmArray)[boxIdNum];
typedef char(*pExpressIDArray)[boxIdNum][plcExpressIdLen];

#endif // DEFINE_H
