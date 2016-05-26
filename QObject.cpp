#include "phpqtng.h"
using namespace std;
#define ME QNAME(QObject)
void ME::__construct(Php::Parameters &params)
{   
    if (params.size()==1 and params[0].type()==Php::Type::Object)
        q=new QObject(PARAM_QOBJECT(params[0]));
    else
        q=new QObject();

}
Php::Value ME::__get(const Php::Value &name)
{

    return Php::Base::__get(name);
}
void ME::__set(const Php::Value &name, const Php::Value &value)
{
    
    Php::Base::__set(name,value);
}
Php::Value ME::__call(const char *_name, Php::Parameters &params)
{
    string name(_name);
    // if (name=="show")
    //     q->show();
    // else
        return Php::Base::__call(_name,params);
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

