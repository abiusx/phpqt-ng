#include "phpqtng.h"
#define QtParentClass QObject
#define QtClass QWidget

#define ME QNAME(QWidget)
#define PARENT QNAME(QtParentClass)

void ME::__construct(Php::Parameters &params)
{

    if (params.size()==1)
        q=new QWidget( PARAM_QWIDGET(params[0]) );
    else if (params.size()==2)
        q=new QWidget( PARAM_QWIDGET(params[0]) , Qt::WindowFlags(int(params[1])) );
    else
        q=new QWidget();

}
Php::Value ME::get(const Php::Value &name, QtClass *q)
{
    return PARENT::get(name,q);
}
void ME::set(const Php::Value &name, const Php::Value &value, QtClass *q)
{
    PARENT::set(name,value,q);
}
Php::Value ME::call(const string name, Php::Parameters &params, QtClass *q)
{
    if (name=="show")
        q->show();
    else if (name=="setLayout")
        q->setLayout(PARAM_QTYPE(QVBoxLayout,params[0]));
    else
        return PARENT::call(name,params,q);
    return nullptr;
}
Php::Value ME::__callStatic(const char *_name, Php::Parameters &params)
{
    // for (auto &param : params)
    // {
    //     // append parameter string value to return value
    //     retval += " " + param.stringValue();
    // }

    return nullptr;
}
