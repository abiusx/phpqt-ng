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
Php::Value ME::__get(const Php::Value &name)
{

    return Php::Base::__get(name);
}
void ME::__set(const Php::Value &name, const Php::Value &value)
{
    
    Php::Base::__set(name,value);
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

