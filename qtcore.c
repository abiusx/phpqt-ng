#include "qtcore.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	printf("MainWindow constructor...");
	fflush(stdout);
    ui->setupUi(this);
	printf(" done.\n");
	fflush(stdout);
}
//FIXME: something is messing with the first few bytes of QApplication_internal
MainWindow::~MainWindow()
{
	printf("MainWindow destructor...");
	fflush(stdout);
    delete ui;
	printf(" done.\n");
	fflush(stdout);
}
zend_class_entry 	*PQT(QApplication);
zend_object_handlers PQT(QApplication_handlers);

static zend_function_entry QApplication_methods[] = {
  PHP_ME(QApplication, exec, NULL, ZEND_ACC_PUBLIC)
  PHP_ME(QApplication, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  {NULL, NULL, NULL}
};
zend_object* QApplication_object_create(zend_class_entry *class_type TSRMLS_DC)
{
  	QApplication_internal *intern;
 
  // allocate the struct we're going to use
  	intern = (QApplication_internal*)ecalloc(1, sizeof(QApplication_internal) + zend_object_properties_size(class_type));
  	memset(intern, 0, sizeof(QApplication_internal));
 
  	zend_object_std_init(&intern->std, class_type TSRMLS_CC);
  	object_properties_init(&intern->std, class_type);
  	intern->std.handlers = &PQT(QApplication_handlers);
  	printf("QApplication instance created\n");
	printf("ME: %p , %p , %p\n",intern,intern->window,intern->app);
	printf("Sizeof %d %d %d\n",sizeof(QApplication_internal),sizeof(zend_object),zend_object_properties_size(class_type));
 	return &intern->std;
}
void QApplication_object_free(zend_object *object TSRMLS_DC)
{
	QApplication_internal *intern = Z_CUSTOM_OBJ_P(object,QApplication_internal); //PHP7
  	if (intern->app)
    	efree(intern->app);
	if (intern->window)
		efree(intern->window);
	printf("QApplication freed.\n");
  	// efree(intern); //PHP5
  	zend_object_std_dtor(object); //PHP7
}

void QApplication_minit(TSRMLS_D) {
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, "QApplication", QApplication_methods);
  // ce.create_object = QApplication_instance_init; //PHP5
  PQT(QApplication) = zend_register_internal_class(&ce TSRMLS_CC);
  PQT(QApplication)->create_object = QApplication_object_create;
  // handlers
  memcpy(&PQT(QApplication_handlers), zend_get_std_object_handlers(), sizeof(PQT(QApplication_handlers)));

	PQT(QApplication_handlers).free_obj = QApplication_object_free; /* This is the free handler */
    // PQT(QApplication_handlers).dtor_obj = my_destroy_object; /* This is the dtor handler */
    /* PQT(QApplication_handlers).clone_obj is also available though we won't use it here */
    PQT(QApplication_handlers).offset   = XtOffsetOf(QApplication_internal, std); /* Here, we declare the offset to the engine */

 
  /* fields */
  zend_declare_property_bool(PQT(QApplication), "alive", strlen("alive"), 1, ZEND_ACC_PUBLIC TSRMLS_CC);
}
PHP_METHOD(QApplication,__construct ) {
 	int _argc;
 	zval *_argv;
	char **__argv;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"la",&_argc,&_argv)==FAILURE)
        return;
    // zval*obj=getThis();
	QApplication_internal *intern = Z_CUSTOM_OBJ_P(getThis(),QApplication_internal); //PHP7
	printf("These last two should be zero: %p , %p , %p\n",intern,intern->window,intern->app);
	/**TODO: get from PHP land **/
	__argv=new char*[5];
	__argv[0]=new char[100];
	__argv[1]=new char[100];
	__argv[2]=new char[100];
	strcpy(__argv[0],"hello");
	strcpy(__argv[1],"there");
	strcpy(__argv[2],"how do you do");
	/***/
	intern->app=new QApplication(_argc,__argv);
	intern->window=new MainWindow();
		printf("YE:%d\n",intern->window->isAnimated());
    printf("This: %p\n",getThis());
	printf("%p , %p , %p\n",intern,intern->window,intern->app);
	printf("QApplication constructed.\n");
	// RETURN_LONG(intern->app->exec());
}
PHP_METHOD(QApplication,exec ) {
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"")==FAILURE)
        return;	
    printf("This: %p\n",getThis());
    printf("QApplication::exec called.\n");
	QApplication_internal *intern = Z_CUSTOM_OBJ_P(getThis(),QApplication_internal); //PHP7
	printf("%p , %p , %p \n",intern,intern->window,intern->app);
	fflush(stdout);
	printf("YE:%d\n ",intern->window->isAnimated());
	intern->window->show();
	intern->window->activateWindow();
	intern->window->raise();
	RETURN_LONG(intern->app->exec());
	RETURN_LONG(0);
}