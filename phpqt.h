#ifndef PHPQT_H
/* Prevent double inclusion */
#define PHPQT_H

/* Define Extension Properties */
#define PHPQT_EXTVER    "1.2"
#define PHPQT_EXTNAME    "PHP-QT"

 	
#define Z_CUSTOM_OBJ_P(obj,type)	(type *)((char *)obj - XtOffsetOf(type, std))
#define PQT(x)		phpqt_##x
#define PQTNAME 	PQT
#define PHPQTNAME 	PQT
#define PHPQT_NAME 	PQT
#define PQT_NAME 	PQT
/* Import configure options
   when building outside of
   the PHP source tree */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Include PHP Standard Header */
#include "php.h"

/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry phpqt_module_entry;
#define phpext_phpqt_ptr &phpqt_module_entry





#endif 
