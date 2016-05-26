#include "phpqtng.h"
#define QtParentClass QWidget
#define QtClass QLabel

#define ME QNAME(QtClass)
#define PARENT QNAME(QtParentClass)
void ME::__construct(Php::Parameters &params)
{   

    if (params.size()==1 and params[0].type()==Php::Type::String)
        q=new QLabel( QString(params[0]) );
    else if (params.size()==1 and params[0].type()==Php::Type::Object)
        q=new QLabel( PARAM_QWIDGET(params[0]) );
    else if (params.size()==2 and params[0].type()==Php::Type::Object)
        q=new QLabel( PARAM_QWIDGET(params[0]) , Qt::WindowFlags((int)params[1]) );
    else if (params.size()==2 and params[0].type()==Php::Type::String)
        q=new QLabel( QString(params[0]) , PARAM_QWIDGET(params[1]) );
    else if (params.size()==3)
        q=new QLabel( QString(params[0]) , PARAM_QWIDGET(params[1]) , Qt::WindowFlags((int)params[2]) );
    else
        Php::error << "No such constructor."<<endl;

}
Php::Value ME::__get(const Php::Value &name)
{

    return Php::Base::__get(name);
}
void ME::__set(const Php::Value &name, const Php::Value &value)
{
    
    Php::Base::__set(name,value);
}
Php::Value ME::call(const string name, Php::Parameters &params,QtClass *q)
{
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

