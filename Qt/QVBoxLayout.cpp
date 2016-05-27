#include "phpqtng.h"
#define QtParentClass QObject
#define QtClass QVBoxLayout

#define ME QNAME(QtClass)
#define PARENT QNAME(QtParentClass)
void ME::__construct(Php::Parameters &params)
{   

    if (params.size()==1)
        q=new QVBoxLayout( PARAM_QWIDGET(params[0]) );
    else
        q=new QVBoxLayout();

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
    if (name=="addWidget")
        q->addWidget(PARAM_QWIDGET(params[0]));
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

