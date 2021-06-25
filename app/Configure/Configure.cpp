#include "Configure.h"


Configure* Configure::instance_ = NULL;

Configure* Configure::getInstance()
{
    if (instance_ == NULL) {
        instance_ = new Configure();
   }
    return  instance_;
}

Configure::Configure(QObject *parent) : QObject(parent)
{
    global_ = new QSettings(FILE_GLOBAL_PATH, QSettings::IniFormat);

    global_->setIniCodec(QTextCodec::codecForName("UTF-8")); //防止中文乱码

    loadINI();

}

void Configure::loadINI()
{
    //分拣机相关
    QString app_dir= QCoreApplication::applicationDirPath();
    _carrierNum = global_->value("Track/carrierNum").toInt();
    qDebug()<<_carrierNum;
    _maxBoxId = global_->value("Track/boxNum").toInt();

    //公司相关
    QString sto = global_->value("COMPANY/sto").toString();
    QStringList stoList = sto.split("|");
    QString zto = global_->value("COMPANY/zto").toString();
    QStringList ztoList = zto.split("|");
    QString yto = global_->value("COMPANY/yto").toString();
    QStringList ytoList = yto.split("|");
    QString best = global_->value("COMPANY/best").toString();
    QStringList bestList = best.split("|");
    QString tt = global_->value("COMPANY/tt").toString();
    QStringList ttList = tt.split("|");
    QString yunda = global_->value("COMPANY/yunda").toString();
    QStringList yundaList = yunda.split("|");
    QString youzheng = global_->value("COMPANY/youzheng").toString();
    QStringList youzhengList = youzheng.split("|");
    _companySwitchCome.clear();
    _companySwitchCome.resize(COMPANYNUM);
    _companySwitchCome[Sto] = stoList.value(0).toInt();
    _companySwitchCome[Zto] = ztoList.value(0).toInt();
    _companySwitchCome[Yto] = ytoList.value(0).toInt();
    _companySwitchCome[Best] = bestList.value(0).toInt();
    _companySwitchCome[Tt] = ttList.value(0).toInt();
    _companySwitchCome[Yunda] = yundaList.value(0).toInt();
    _companySwitchCome[Youzheng] = youzhengList.value(0).toInt();
    _companySwitchGo.clear();
    _companySwitchGo.resize(COMPANYNUM);
    _companySwitchGo[Sto] = stoList.value(1).toInt();
    _companySwitchGo[Zto] = ztoList.value(1).toInt();
    _companySwitchGo[Yto] = ytoList.value(1).toInt();
    _companySwitchGo[Best] = bestList.value(1).toInt();
    _companySwitchGo[Tt] = ttList.value(1).toInt();
    _companySwitchGo[Yunda] = yundaList.value(1).toInt();
    _companySwitchGo[Youzheng] = youzhengList.value(1).toInt();


    //PLC
    QStringList netIdList = global_->value("PLC/AmsNetId").toString().split('.');
    for(int i = 0; i < netIdList.size(); ++i) {
        _netId[i] = static_cast<unsigned char>(netIdList[i].toUShort());
    }

    //本地数据库相关NATIVEDB
    _nativeip = global_->value("NATIVEDB/ip").toString();

    //厂家接口最大报警时限，超过，将报警
    _interfaceMaxDelay = global_->value("ALARM/interfaceMaxDelay").toLongLong();

    //所有相机
    _cameraType = global_->value("CAMERA/cameraType").toInt();

    _camerasVector.clear();
    QString sCameras = global_->value("CAMERA/cameraArg").toString(); //相机参数
    QStringList camerasList = sCameras.split("-", QString::SkipEmptyParts);
    for(int i = 0; i < camerasList.size(); ++i) {
        QStringList cameraPart = camerasList[i].split("|");
        StructCamera structCamera;
        structCamera.cameraId = i;
        structCamera.cameraName = cameraPart.value(0);
        if (cameraPart.value(1) == "大华") {
            structCamera.type = DaHua;
        } else if (cameraPart.value(1) == "海康") {
            structCamera.type = HaiKang;
        } else {
            structCamera.type = HaiKang; //默认
        }
        structCamera.ip = cameraPart.value(2);
        structCamera.port = cameraPart.value(3).toUShort();
        structCamera.plcIndex = cameraPart.value(4).toInt();
        structCamera.exceptionBoxId = cameraPart.value(5).toShort();
        structCamera.carrierNum = cameraPart.value(6).toInt();
        structCamera.pdaCode = cameraPart.value(7);
        _camerasVector.append(structCamera);
    }

    _detailLog = global_->value("LOG/detail").toBool();

    //GUI
    _arrivedRow = global_->value("GUI/arrivedRow").toInt();
    _sendOrBagRow = global_->value("GUI/sendOrBagRow").toInt();
    _appName = global_->value("GUI/appName").toString();

    if (_companySwitchGo[Sto] || _companySwitchCome[Sto]) {
        //configureSTO_ = new ConfigureSTO;
    }

    if (_companySwitchGo[Yto] || _companySwitchCome[Yto]) {
        //configureYTO_ = new ConfigureYTO;

    }

    _intervalCheckPack = getConfigure("CFG/intervalCheckPack").toInt();
    _emptyPackWarnThreshold = getConfigure("CFG/emptyPackWarnThreshold").toInt();
    _isCheckPack = getConfigure("CFG/isCheckPack").toBool();
    _isCheckEmptyPack = getConfigure("CFG/isCheckEmptyPack").toBool();

}

void Configure::setConfigure(const QString key, const QVariant value)
{
    QMutexLocker locker(&mutex_);
    global_->setValue(key, value);
}

QVariant Configure::getConfigure(const QString key)
{
    return global_->value(key);
}

void Configure::readPackCheckThreshold()
{
    QFile file(FILE_CHECK_PACK);
    if (!file.open(QIODevice::Text | QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, FILE_CHECK_PACK, file.errorString());
        return;
    }

    _packCheckThresholdVector.clear();
    _packCheckThresholdVector.resize(400);
    while (!file.atEnd()) {
        QString line = file.readLine();
        int boxNum = line.section(',', 0, 0).toInt();
        int num = line.section(',', 1, 1).toInt();
        if (boxNum < 400)
            _packCheckThresholdVector[boxNum] = num;
    }

}

QBitArray Configure::companySwitch()
{
    QBitArray ba;
    ba.resize(COMPANYNUM);
    for (int i = 0; i < COMPANYNUM; ++i) {
        ba[i] = _companySwitchGo[i] | _companySwitchCome[i];
    }

    return ba;
}
