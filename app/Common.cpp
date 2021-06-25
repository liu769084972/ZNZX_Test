#include "Common.h"

Common* Common::instance_ = NULL;


Common* Common::getInstance()
{
    if(instance_ == NULL)
    {
        instance_ = new Common();
    }
    return  instance_;
}

Common::Common(QObject *parent) : QObject(parent)
{

}
