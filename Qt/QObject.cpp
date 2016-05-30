#include "phpqtng.h"
// #define QtParentClass QWidget
#define QtClass QObject

#define ME QNAME(QtClass)

void ME::__construct(Php::Parameters &params)
{   
    if (params.size()==1 and params[0].type()==Php::Type::Object)
        q=new QObject(PARAM_QOBJECT(params[0]));
    else
        q=new QObject();

}
Php::Value ME::get(const Php::Value &name, QtClass *q)
{
    return nullptr;
}
void ME::set(const Php::Value &name, const Php::Value &value, QtClass *q)
{
    
}
Php::Value ME::call(const string name, Php::Parameters &params, QtClass *q)
{
    if (name=="connect" and params.size()==4 )
    {
        QObject *sender=PARAM_QOBJECT(params[0]);
        QObject *receiver=PARAM_QOBJECT(params[2]);
        string sender_signal=params[1];
        sender_signal=SIGNAL_PREFIX+sender_signal;
        string receiver_slot=params[3];
        receiver_slot=SLOT_PREFIX+receiver_slot;
        sender_signal=normalizeSignalOrSlot(sender_signal);
        receiver_slot=normalizeSignalOrSlot(receiver_slot);
        return (bool)(q->connect(sender,sender_signal.c_str(),receiver,receiver_slot.c_str()));
    }
    //todo: with 3 params, consider (q) the first
    else
        return PhpQtNgBase::call(name,params);
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

