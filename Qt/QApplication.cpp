#include "phpqtng.h"
#define QtParentClass QObject
#define QtClass QApplication

#define ME QNAME(QtClass)
#define PARENT QNAME(QtParentClass)
void ME::__construct(Php::Parameters &params)
{   
    argc=params[0];
    vector<string> strings=params[1];
    char** cstrings = new char*[strings.size()];

    for(size_t i = 0; i < strings.size(); ++i)
    {
        cstrings[i] = new char[strings[i].size() + 1];
        std::strcpy(cstrings[i], strings[i].c_str());
    }


    q=new QApplication(argc,cstrings);
    //dont delete here, QApplication modifies them
    return;


    for(size_t i = 0; i < strings.size(); ++i)
        delete[] cstrings[i];

    delete[] cstrings;

    vector<string> argv=params[1];
    vector<char*>cstring;//=new char*[argv.size()];
    for (size_t i=0;i<argv.size();++i)
        cstring.push_back(const_cast<char*>(argv[i].c_str()));
    q=new QApplication(argc,&cstring[0]);

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
    if (name=="exec")
        return q->exec();
    else
        return PARENT::call(name,params,q);
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

