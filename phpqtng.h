#ifndef PHPQTNG_H
#define PHPQTNG_H
#include <iostream>
using namespace std;

#include <phpcpp.h>
#include <QDebug>

class MethodNotFound: public exception {
    public:
    /**
     *  Constructor
     */
    MethodNotFound() : std::exception() {}
    
    /**
     *  Destructor
     */
    virtual ~MethodNotFound() throw() {}
};

#define CONCAT(x,y) x##y
#define QNAME(x) CONCAT(Qt_,x)
#define PHPQTNG_CONSTRUCT(QtClass) 	void QNAME(QtClass)::__construct(Php::Parameters &params)

#define PHPQTNG_GET_BEGIN(QtClass) 		void Php::Value QNAME(QtClass)::__get(const Php::Value &name) {
#define PHPQTNG_GET_END(QtClass)    return Php::Base::__get(name); }

// #define PHPQTNG_SET(QtClass) void QNAME(QtClass)::__construct(Php::Parameters &params)
// #define PHPQTNG_CALL(QtClass) void QNAME(QtClass)::__construct(Php::Parameters &params)
// #define PHPQTNG_STATIC_CALL(QtClass) void QNAME(QtClass)::__construct(Php::Parameters &params)

#define PARAM_QOBJECT(param)  (QObject *)(((QNAME(QObject) *)param.implementation())->q)
#define PARAM_QWIDGET(param)  (QWidget *)(((QNAME(QWidget) *)param.implementation())->q)
#define PARAM_QTYPE(type,param)  (type *)(((QNAME(type) *)param.implementation())->q)


#define PHPQTNG_CLASS_NODELETE(QtClass) \
class QNAME(QtClass):public PHPQtNgBase \
{ \
public: \
    QtClass * q; \
    QNAME(QtClass)():q(0){} \
    void __construct(Php::Parameters &params); \
	Php::Value __get(const Php::Value &name); \
	void __set(const Php::Value &name, const Php::Value &value); \
	Php::Value __call(const char *_name, Php::Parameters &params) { \
        string name=_name; \
        return QNAME(QtClass)::call(name,params,q); \
    } \
    static Php::Value __callStatic(const char *name, Php::Parameters &params); \
    static Php::Value call(const string name, Php::Parameters &params, QtClass *q);
    //     return QNAME(QtClass)::call(string(name),params,this); \
    // } \
    // static Php::Value call(const string name, Php::Parameters &params, QNAME(QtClass) *obj); \
    // Php::Value baseCall(const string name, Php::Parameters &params) { \
    //     return Php::Base::__call(name.c_str(),params); \
    // } \
    // 
    
#define PHPQTNG_CLASS_STUB_NODELETE(QtClass)  PHPQTNG_CLASS_NODELETE(QtClass) };

#define PHPQTNG_CLASS(QtClass) PHPQTNG_CLASS_NODELETE(QtClass) \
    virtual ~QNAME(QtClass)() { \
        if (q) \
            delete q,q=0; \
    } \
    void __destruct() { \
    	if (q) \
    		delete q,q=0; \
    } \

#define PHPQTNG_CLASS_STUB(QtClass)  PHPQTNG_CLASS(QtClass) };


class PHPQtNgBase:public Php::Base
{
	public:
    static Php::Value call(const string name, Php::Parameters &params, void *q=0)
    {
        // throw MethodNotFound();
        throw Php::Exception("Method '"+name+"()' not found.");
        // unreachable code
        return nullptr;
    }

};
typedef PHPQtNgBase PhpQtNgBase;

#include <QObject>
PHPQTNG_CLASS_STUB_NODELETE(QObject);

#include <QObject>
PHPQTNG_CLASS_STUB_NODELETE(QWidget);

#include <QApplication>
PHPQTNG_CLASS(QApplication)
	int argc;
};

#include <QLabel>
PHPQTNG_CLASS_STUB(QLabel);

#include <QPushButton>
PHPQTNG_CLASS_STUB(QPushButton);

#include <QVBoxLayout>
PHPQTNG_CLASS_STUB(QVBoxLayout);

#endif