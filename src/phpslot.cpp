#include "phpqtng.h"

#include <QHash>
#include <QList>
#include <QMetaObject>
#include <QObject>
using namespace std;
string normalizeSignalOrSlot(string signal_or_slot)
{
    if (signal_or_slot.length()<2 or signal_or_slot.substr(signal_or_slot.size()-2,2)!="()")
        signal_or_slot+="()";
    return signal_or_slot;
}
class PHPSlot 
{
public:
    Php::Value callback;
    Php::Array args;
    PHPSlot(Php::Value c):callback(c){}
    PHPSlot(Php::Value c, Php::Array a):callback(c),args(a){}
    virtual void call(QObject *sender, void **arguments) 
    {  
        // Php::Array params=(Php::Array)arguments[1];
        Php::Array params=args;

        // Php::Value return_value=callback(std::forward<Params>(params)...);
        Php::Value return_value=callback(params);
        arguments[0]=&return_value;
        
    }
    virtual ~PHPSlot()
    {

    }
};

class DynamicQObject: public QObject
{
public:
    DynamicQObject(QObject *parent = 0) : QObject(parent) { }

    virtual int qt_metacall(QMetaObject::Call c, int id, void **arguments)
    {
        id = QObject::qt_metacall(c, id, arguments);
        if (id < 0 || c != QMetaObject::InvokeMetaMethod) 
            return id;
        Q_ASSERT(id < slotList.size());
        
        slotList[id]->call(sender(), arguments);
        return -1;
    }

    bool emitDynamicSignal(char *signal, void **arguments)
    {
        QByteArray theSignal = QMetaObject::normalizedSignature(signal);
        int signalId = signalIndices.value(theSignal, -1);
        if (signalId >= 0) {
            QMetaObject::activate(this, metaObject(), signalId + metaObject()->methodCount(), 
                arguments);
            return true;
        } else {
            return false;
        }        
    }
    bool connectDynamicSlot(QObject *obj, const char *signal, Php::Value slot, Php::Value args)
    {
        static int id=0;

        QByteArray theSignal = QMetaObject::normalizedSignature(signal);
        // QByteArray theSlot = QMetaObject::normalizedSignature(slot);
        // if (!QMetaObject::checkConnectArgs(theSignal, theSlot))
            // return false;

        int signalId = obj->metaObject()->indexOfSignal(theSignal);
        // printf("%d---\n",signalId);
        if (signalId < 0) 
            return false;
        slotList.append(new PHPSlot(slot,args));
        int slotId = id++;//slotIndices.value(theSlot, -1);
        return QMetaObject::connect(obj, signalId, this, slotId + metaObject()->methodCount());
    }
    // bool connectDynamicSignal(char *signal, QObject *obj, char *slot)
    // {
    //     QByteArray theSignal = QMetaObject::normalizedSignature(signal);
    //     QByteArray theSlot = QMetaObject::normalizedSignature(slot);
    //     if (!QMetaObject::checkConnectArgs(theSignal, theSlot))
    //         return false;

    //     int slotId = obj->metaObject()->indexOfSlot(theSlot);
    //     if (slotId < 0) 
    //         return false;    

    //     int signalId = signalIndices.value(theSignal, -1);
    //     if (signalId < 0) {
    //         signalId = signalIndices.size();
    //         signalIndices[theSignal] = signalId;
    //     }

    //     return QMetaObject::connect(this, signalId + metaObject()->methodCount(), obj, slotId);        
    // }
    
    ~DynamicQObject()
    {
        for (int i=0;i<slotList.size();++i)
            delete slotList[i];
    }


private:
    // QHash<QByteArray, int> slotIndices;
    QList<PHPSlot *> slotList;
    QHash<QByteArray, int> signalIndices;
};


Php::Value dynamicConnect(Php::Parameters &params)
{
    static DynamicQObject dqo;
    Php::Array args;
    if (params.size()<3)
    {
        throw Php::Exception("Connect(): needs at least 3 arguments.");
        return false;
    }

    if (params.size()==4)
    {
        if (params[3].type()!=Php::Type::Array)   
        {
            throw Php::Exception("Connect(): Argument 4 should be a PHP array.");
            return false;

        }
        args=params[3];
    }
    string signal=normalizeSignalOrSlot(params[1]);
    return dqo.connectDynamicSlot(PARAM_QOBJECT(params[0]),signal.c_str(),params[2],args);
}

