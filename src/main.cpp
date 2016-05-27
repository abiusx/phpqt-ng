#include "phpqtng.h"

#define AddClass(QtClass) \
do { \
    Php::Class<QNAME(QtClass)> qo(#QtClass); \
    qo.method("__construct", &QNAME(QtClass)::__construct); \
    PHPQtNg.add(std::move(qo)); \
} while(0) \
/**
 *  Switch to C context to ensure that the get_module() function
 *  is callable by C programs (which the Zend engine is)
 */
extern "C" {
    /**
     *  Startup function that is called by the Zend engine 
     *  to retrieve all information about the extension
     *  @return void*
     */
    PHPCPP_EXPORT void *get_module() {
        // create static instance of the extension object
        static Php::Extension PHPQtNg("PHPQtNg", "1.0");

        // description of the class so that PHP knows which methods are accessible
        AddClass(QObject);
        AddClass(QWidget);
        AddClass(QLabel);
        AddClass(QPushButton);
        AddClass(QLayout);
        AddClass(QVBoxLayout);
        AddClass(QApplication);
        // Php::Class<QNAME(QObject)> qobject("QObject");
        // qobject.method("__construct", &QNAME(QObject)::__construct);
        
        // Php::Class<QNAME(QWidget)> qwidget("QWidget");
        // qwidget.method("__construct", &QNAME(QWidget)::__construct);
        
        // Php::Class<QNAME(QApplication)> qapplication("QApplication");
        // qapplication.method("__construct", &QNAME(QApplication)::__construct,{
        //     Php::ByRef("argc",Php::Type::Numeric),
        //     Php::ByVal("argv",Php::Type::Array)
        // });
        
        // Php::Class<QNAME(QLabel)> qlabel("QLabel");
        // qlabel.method("__construct", &QNAME(QLabel)::__construct);
        
        

        // add the class to the extension
        // PHPQtNg.add(std::move(qobject));
        // PHPQtNg.add(std::move(qwidget));
        // PHPQtNg.add(std::move(qapplication));
        // PHPQtNg.add(std::move(qlabel));

        // return the extension
        return PHPQtNg;
    }
}