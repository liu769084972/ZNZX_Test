#include "MainWindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //防止中文乱码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));//GBK

    int fontId = QFontDatabase::addApplicationFont(":/Font/iconfont.ttf");
    QString m_strFontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(m_strFontName);
    font.setPointSize(10);
    QApplication::setFont(font);

    MainWindow w;

    w.show();


    return a.exec();
}
