#include "phpqtng.h"
#define QtParentClass QWidget
#define QtClass QPushButton
#define ME QNAME(QtClass)
#define PARENT QNAME(QtParentClass)
void ME::__construct(Php::Parameters &params)
{   

    if (params.size()==1 )
        if (params[0].type()==Php::Type::String)
            q=new QPushButton( QString(params[0]) );
        else
            q=new QPushButton( PARAM_QWIDGET(params[0]) );
    else if (params.size()==2)
        q=new QPushButton( QString(params[1]) , PARAM_QWIDGET(params[1]) );
    else
        q=new QPushButton();

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
    //TODO: DUP
    string name=_name;
    if (name=="connect" and params.size()==4 )
    {
        QObject *sender=PARAM_QOBJECT(params[0]);
        QObject *receiver=PARAM_QOBJECT(params[2]);
        string sender_signal=params[1];
        sender_signal="2"+sender_signal;
        string receiver_slot=params[3];
        receiver_slot="1"+receiver_slot;
        if (sender_signal.substr(sender_signal.size()-2,2)!="()")
            sender_signal+="()";
        if (receiver_slot.substr(receiver_slot.size()-2,2)!="()")
            receiver_slot+="()";
        return int(q->connect(sender,sender_signal.c_str(),receiver,receiver_slot.c_str()));
    }
    return PhpQtNgBase::__call(_name,params);
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

