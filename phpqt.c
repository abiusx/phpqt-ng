#include "phpqt.h"
//ZEND_BEGIN_ARG_INFO(phpqt_byref, pass_rest_by_reference)
ZEND_BEGIN_ARG_INFO_EX(phpqt_byref_arginfo, 
    1 /*pass_rest_by_reference*/, 
    0/*return_reference*/,
    1/*required_num_args*/)
ZEND_ARG_PASS_INFO(1/*by_ref*/)
ZEND_END_ARG_INFO();

PHP_FUNCTION(zval_id)
{
    //BUG: produces same ids for some values
    //computes the address of first zval sent to us, 
    //and the rest receive id relative to that.
    zval *z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"z",&z)==FAILURE)
        return;
    zend_bool is_ref = Z_ISREF_P(z);
    // if (is_ref)
    //     z=Z_REFVAL_P(z);
    long id=*(( long*)(&z->value)); //return_value will become the address
    // long id=(zend_uintptr_t) Z_COUNTED_P(z);; //same as above
    // printf("===%u\n",id);
    static long base=0;
    if (base==0) base=id-1; 
    id=(id^base)>>3; //zval is at least 16 bytes
    RETURN_LONG(id);
}
PHP_FUNCTION(is_ref)
{
    zval *z;
    int res;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"z",&z)==FAILURE)
        return;
    RETURN_BOOL(Z_REFCOUNT_P(z) > 2); 
    //1 is the reference sent to this function, the other is the actual var. 
    //if more, reference!
}
PHP_MSHUTDOWN_FUNCTION(phpqt)
{
        return SUCCESS;

}
#include "qtcore.h" 

PHP_MINIT_FUNCTION(phpqt)
{
    QApplication_minit(TSRMLS_C);
    return SUCCESS;
}
PHP_RINIT_FUNCTION(phpqt)
{
    return SUCCESS;
}
PHP_RSHUTDOWN_FUNCTION(phpqt)
{
    return SUCCESS;
}
static zend_function_entry phpqt_functions[] = {
    // PHP_FE(is_ref,              phpqt_byref_arginfo)
    // PHP_FE(zval_id,              phpqt_byref_arginfo)

    { NULL,NULL,NULL}
};


zend_module_entry phpqt_module_entry = {
     STANDARD_MODULE_HEADER,
    PHPQT_EXTNAME, //name
    phpqt_functions, // Functions 
    // NULL,NULL,NULL,NULL,
    PHP_MINIT(phpqt), // MINIT 
    PHP_MSHUTDOWN(phpqt), // MSHUTDOWN 
    PHP_RINIT(phpqt), // RINIT 
    PHP_RSHUTDOWN(phpqt), // RSHUTDOWN 
    NULL, // MINFO 
    PHPQT_EXTVER,
    STANDARD_MODULE_PROPERTIES
    ///OR
    // NO_MODULE_GLOBALS,
    // NULL,//ZEND_MODULE_POST_ZEND_DEACTIVATE_N(phpqt),

    // STANDARD_MODULE_PROPERTIES_EX
};
// #ifdef COMPILE_DL_MYLIB
ZEND_GET_MODULE(phpqt)
// #endif
