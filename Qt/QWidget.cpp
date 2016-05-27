#include "phpqtng.h"
#define QtParentClass	QObject
#define QtClass		QWidget

#define ME		QNAME(QtClass)
#define PARENT		QNAME(QtParentClass)

void ME::__construct(Php::Parameters &params)
{   
	
	if ( params.size()==0 )
		q = new QWidget ();
	else if ( params.size()==1 )
		q = new QWidget ( PARAM_QTYPE(QWidget,params[0]) );
	else if ( params.size()==2 )
		q = new QWidget ( PARAM_QTYPE(QWidget,params[0]), Qt::WindowFlags((int)params[1]) );

    else
    	Php::error <<"Arguments not matching any constructor of 'QWidget'.";
    //q=new QWidget();

}
Php::Value ME::get(const Php::Value &name, QtClass *q)
{
    return PARENT::get(name,q);
}
void ME::set(const Php::Value &name, const Php::Value &value, QtClass *q)
{
    PARENT::set(name,value,q);
}
Php::Value ME::call(const string name, Php::Parameters &params, QtClass *q)
{
	if ( name=="acceptDrops" )
	{
		if ( params.size()==0 )
			return bool(q->acceptDrops ());
	}
	else if ( name=="accessibleDescription" )
	{
		if ( params.size()==0 )
			return string(q->accessibleDescription ());
	}
	else if ( name=="accessibleName" )
	{
		if ( params.size()==0 )
			return string(q->accessibleName ());
	}
	else if ( name=="actions" )
	{
		if ( params.size()==0 )
			return q->actions ();
	}
	else if ( name=="activateWindow" )
	{
		if ( params.size()==0 )
			q->activateWindow (), return nullptr;
	}
	else if ( name=="addAction" )
	{
		if ( params.size()==1 )
			q->addAction ( PARAM_QTYPE(QAction,params[0]) ), return nullptr;
	}
	else if ( name=="addActions" )
	{
		if ( params.size()==1 )
			q->addActions ( (QList<QAction *>)params[0] ), return nullptr;
	}
	else if ( name=="adjustSize" )
	{
		if ( params.size()==0 )
			q->adjustSize (), return nullptr;
	}
	else if ( name=="autoFillBackground" )
	{
		if ( params.size()==0 )
			return bool(q->autoFillBackground ());
	}
	else if ( name=="backgroundRole" )
	{
		if ( params.size()==0 )
			return q->backgroundRole ();
	}
	else if ( name=="baseSize" )
	{
		if ( params.size()==0 )
			return q->baseSize ();
	}
	else if ( name=="childAt" )
	{
		if ( params.size()==1 )
			return QNAME(QWidget)(q->childAt ( QPoint(params[0]) ));
		else if ( params.size()==2 )
			return QNAME(QWidget)(q->childAt ( (int)params[0], (int)params[1] ));
	}
	else if ( name=="childrenRect" )
	{
		if ( params.size()==0 )
			return q->childrenRect ();
	}
	else if ( name=="childrenRegion" )
	{
		if ( params.size()==0 )
			return q->childrenRegion ();
	}
	else if ( name=="clearFocus" )
	{
		if ( params.size()==0 )
			q->clearFocus (), return nullptr;
	}
	else if ( name=="clearMask" )
	{
		if ( params.size()==0 )
			q->clearMask (), return nullptr;
	}
	else if ( name=="contentsMargins" )
	{
		if ( params.size()==0 )
			return q->contentsMargins ();
	}
	else if ( name=="contentsRect" )
	{
		if ( params.size()==0 )
			return q->contentsRect ();
	}
	else if ( name=="contextMenuPolicy" )
	{
		if ( params.size()==0 )
			return Qt::ContextMenuPolicy(q->contextMenuPolicy ());
	}
	else if ( name=="cursor" )
	{
		if ( params.size()==0 )
			return q->cursor ();
	}
	else if ( name=="effectiveWinId" )
	{
		if ( params.size()==0 )
			return WId(q->effectiveWinId ());
	}
	else if ( name=="ensurePolished" )
	{
		if ( params.size()==0 )
			q->ensurePolished (), return nullptr;
	}
	else if ( name=="focusPolicy" )
	{
		if ( params.size()==0 )
			return Qt::FocusPolicy(q->focusPolicy ());
	}
	else if ( name=="focusProxy" )
	{
		if ( params.size()==0 )
			return QNAME(QWidget)(q->focusProxy ());
	}
	else if ( name=="focusWidget" )
	{
		if ( params.size()==0 )
			return QNAME(QWidget)(q->focusWidget ());
	}
	else if ( name=="font" )
	{
		if ( params.size()==0 )
			return q->font ();
	}
	else if ( name=="fontInfo" )
	{
		if ( params.size()==0 )
			return q->fontInfo ();
	}
	else if ( name=="fontMetrics" )
	{
		if ( params.size()==0 )
			return q->fontMetrics ();
	}
	else if ( name=="foregroundRole" )
	{
		if ( params.size()==0 )
			return q->foregroundRole ();
	}
	else if ( name=="frameGeometry" )
	{
		if ( params.size()==0 )
			return q->frameGeometry ();
	}
	else if ( name=="frameSize" )
	{
		if ( params.size()==0 )
			return q->frameSize ();
	}
	else if ( name=="geometry" )
	{
		if ( params.size()==0 )
			return q->geometry ();
	}
	else if ( name=="getContentsMargins" )
	{
		if ( params.size()==4 )
			q->getContentsMargins ( (int)params[0], (int)params[1], (int)params[2], (int)params[3] ), return nullptr;
	}
	else if ( name=="grabGesture" )
	{
		if ( params.size()==1 )
			q->grabGesture ( Qt::GestureType((int)params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->grabGesture ( Qt::GestureType((int)params[0]), Qt::GestureFlags((int)params[1]) ), return nullptr;
	}
	else if ( name=="grabKeyboard" )
	{
		if ( params.size()==0 )
			q->grabKeyboard (), return nullptr;
	}
	else if ( name=="grabMouse" )
	{
		if ( params.size()==0 )
			q->grabMouse (), return nullptr;
		else if ( params.size()==1 )
			q->grabMouse ( QCursor(params[0]) ), return nullptr;
	}
	else if ( name=="grabShortcut" )
	{
		if ( params.size()==1 )
			return int(q->grabShortcut ( QKeySequence(params[0]) ));
		else if ( params.size()==2 )
			return int(q->grabShortcut ( QKeySequence(params[0]), Qt::ShortcutContext((int)params[1]) ));
	}
	else if ( name=="graphicsEffect" )
	{
		if ( params.size()==0 )
			return QNAME(QGraphicsEffect)(q->graphicsEffect ());
	}
	else if ( name=="graphicsProxyWidget" )
	{
		if ( params.size()==0 )
			return QNAME(QGraphicsProxyWidget)(q->graphicsProxyWidget ());
	}
	else if ( name=="hasEditFocus" )
	{
		if ( params.size()==0 )
			return bool(q->hasEditFocus ());
	}
	else if ( name=="hasFocus" )
	{
		if ( params.size()==0 )
			return bool(q->hasFocus ());
	}
	else if ( name=="hasMouseTracking" )
	{
		if ( params.size()==0 )
			return bool(q->hasMouseTracking ());
	}
	else if ( name=="height" )
	{
		if ( params.size()==0 )
			return int(q->height ());
	}
	else if ( name=="heightForWidth" )
	{
		if ( params.size()==1 )
			return int(q->heightForWidth ( (int)params[0] ));
	}
	else if ( name=="inputContext" )
	{
		if ( params.size()==0 )
			return QNAME(QInputContext)(q->inputContext ());
	}
	else if ( name=="inputMethodHints" )
	{
		if ( params.size()==0 )
			return Qt::InputMethodHints(q->inputMethodHints ());
	}
	else if ( name=="inputMethodQuery" )
	{
		if ( params.size()==1 )
			return q->inputMethodQuery ( Qt::InputMethodQuery((int)params[0]) );
	}
	else if ( name=="insertAction" )
	{
		if ( params.size()==2 )
			q->insertAction ( PARAM_QTYPE(QAction,params[0]), PARAM_QTYPE(QAction,params[1]) ), return nullptr;
	}
	else if ( name=="insertActions" )
	{
		if ( params.size()==2 )
			q->insertActions ( PARAM_QTYPE(QAction,params[0]), (QList<QAction *>)params[1] ), return nullptr;
	}
	else if ( name=="isActiveWindow" )
	{
		if ( params.size()==0 )
			return bool(q->isActiveWindow ());
	}
	else if ( name=="isAncestorOf" )
	{
		if ( params.size()==1 )
			return bool(q->isAncestorOf ( PARAM_QTYPE(QWidget,params[0]) ));
	}
	else if ( name=="isEnabled" )
	{
		if ( params.size()==0 )
			return bool(q->isEnabled ());
	}
	else if ( name=="isEnabledTo" )
	{
		if ( params.size()==1 )
			return bool(q->isEnabledTo ( PARAM_QTYPE(QWidget,params[0]) ));
	}
	else if ( name=="isFullScreen" )
	{
		if ( params.size()==0 )
			return bool(q->isFullScreen ());
	}
	else if ( name=="isHidden" )
	{
		if ( params.size()==0 )
			return bool(q->isHidden ());
	}
	else if ( name=="isMaximized" )
	{
		if ( params.size()==0 )
			return bool(q->isMaximized ());
	}
	else if ( name=="isMinimized" )
	{
		if ( params.size()==0 )
			return bool(q->isMinimized ());
	}
	else if ( name=="isModal" )
	{
		if ( params.size()==0 )
			return bool(q->isModal ());
	}
	else if ( name=="isVisible" )
	{
		if ( params.size()==0 )
			return bool(q->isVisible ());
	}
	else if ( name=="isVisibleTo" )
	{
		if ( params.size()==1 )
			return bool(q->isVisibleTo ( PARAM_QTYPE(QWidget,params[0]) ));
	}
	else if ( name=="isWindow" )
	{
		if ( params.size()==0 )
			return bool(q->isWindow ());
	}
	else if ( name=="isWindowModified" )
	{
		if ( params.size()==0 )
			return bool(q->isWindowModified ());
	}
	else if ( name=="layout" )
	{
		if ( params.size()==0 )
			return QNAME(QLayout)(q->layout ());
	}
	else if ( name=="layoutDirection" )
	{
		if ( params.size()==0 )
			return Qt::LayoutDirection(q->layoutDirection ());
	}
	else if ( name=="locale" )
	{
		if ( params.size()==0 )
			return q->locale ();
	}
	else if ( name=="macCGHandle" )
	{
		if ( params.size()==0 )
			return Qt::HANDLE(q->macCGHandle ());
	}
	else if ( name=="macQDHandle" )
	{
		if ( params.size()==0 )
			return Qt::HANDLE(q->macQDHandle ());
	}
	else if ( name=="mapFrom" )
	{
		if ( params.size()==2 )
			return q->mapFrom ( PARAM_QTYPE(QWidget,params[0]), QPoint(params[1]) );
	}
	else if ( name=="mapFromGlobal" )
	{
		if ( params.size()==1 )
			return q->mapFromGlobal ( QPoint(params[0]) );
	}
	else if ( name=="mapFromParent" )
	{
		if ( params.size()==1 )
			return q->mapFromParent ( QPoint(params[0]) );
	}
	else if ( name=="mapTo" )
	{
		if ( params.size()==2 )
			return q->mapTo ( PARAM_QTYPE(QWidget,params[0]), QPoint(params[1]) );
	}
	else if ( name=="mapToGlobal" )
	{
		if ( params.size()==1 )
			return q->mapToGlobal ( QPoint(params[0]) );
	}
	else if ( name=="mapToParent" )
	{
		if ( params.size()==1 )
			return q->mapToParent ( QPoint(params[0]) );
	}
	else if ( name=="mask" )
	{
		if ( params.size()==0 )
			return q->mask ();
	}
	else if ( name=="maximumHeight" )
	{
		if ( params.size()==0 )
			return int(q->maximumHeight ());
	}
	else if ( name=="maximumSize" )
	{
		if ( params.size()==0 )
			return q->maximumSize ();
	}
	else if ( name=="maximumWidth" )
	{
		if ( params.size()==0 )
			return int(q->maximumWidth ());
	}
	else if ( name=="minimumHeight" )
	{
		if ( params.size()==0 )
			return int(q->minimumHeight ());
	}
	else if ( name=="minimumSize" )
	{
		if ( params.size()==0 )
			return q->minimumSize ();
	}
	else if ( name=="minimumSizeHint" )
	{
		if ( params.size()==0 )
			return q->minimumSizeHint ();
	}
	else if ( name=="minimumWidth" )
	{
		if ( params.size()==0 )
			return int(q->minimumWidth ());
	}
	else if ( name=="move" )
	{
		if ( params.size()==1 )
			q->move ( QPoint(params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->move ( (int)params[0], (int)params[1] ), return nullptr;
	}
	else if ( name=="nativeParentWidget" )
	{
		if ( params.size()==0 )
			return QNAME(QWidget)(q->nativeParentWidget ());
	}
	else if ( name=="nextInFocusChain" )
	{
		if ( params.size()==0 )
			return QNAME(QWidget)(q->nextInFocusChain ());
	}
	else if ( name=="normalGeometry" )
	{
		if ( params.size()==0 )
			return q->normalGeometry ();
	}
	else if ( name=="overrideWindowFlags" )
	{
		if ( params.size()==1 )
			q->overrideWindowFlags ( Qt::WindowFlags((int)params[0]) ), return nullptr;
	}
	else if ( name=="palette" )
	{
		if ( params.size()==0 )
			return q->palette ();
	}
	else if ( name=="parentWidget" )
	{
		if ( params.size()==0 )
			return QNAME(QWidget)(q->parentWidget ());
	}
	else if ( name=="platformWindow" )
	{
		if ( params.size()==0 )
			return QNAME(QPlatformWindow)(q->platformWindow ());
	}
	else if ( name=="platformWindowFormat" )
	{
		if ( params.size()==0 )
			return q->platformWindowFormat ();
	}
	else if ( name=="pos" )
	{
		if ( params.size()==0 )
			return q->pos ();
	}
	else if ( name=="previousInFocusChain" )
	{
		if ( params.size()==0 )
			return QNAME(QWidget)(q->previousInFocusChain ());
	}
	else if ( name=="rect" )
	{
		if ( params.size()==0 )
			return q->rect ();
	}
	else if ( name=="releaseKeyboard" )
	{
		if ( params.size()==0 )
			q->releaseKeyboard (), return nullptr;
	}
	else if ( name=="releaseMouse" )
	{
		if ( params.size()==0 )
			q->releaseMouse (), return nullptr;
	}
	else if ( name=="releaseShortcut" )
	{
		if ( params.size()==1 )
			q->releaseShortcut ( (int)params[0] ), return nullptr;
	}
	else if ( name=="removeAction" )
	{
		if ( params.size()==1 )
			q->removeAction ( PARAM_QTYPE(QAction,params[0]) ), return nullptr;
	}
	else if ( name=="render" )
	{
		if ( params.size()==1 ) //competition (2)
		{
			 if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QPaintDevice" )
				q->render ( PARAM_QTYPE(QPaintDevice,params[0]) ), return nullptr;
			 else if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QPainter" )
				q->render ( PARAM_QTYPE(QPainter,params[0]) ), return nullptr;
		}
		else if ( params.size()==2 ) //competition (2)
		{
			 if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QPaintDevice" and params[1].type()==Php::Type::Object and GET_CLASS(params[1])=="QPoint" )
				q->render ( PARAM_QTYPE(QPaintDevice,params[0]), QPoint(params[1]) ), return nullptr;
			 else if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QPainter" and params[1].type()==Php::Type::Object and GET_CLASS(params[1])=="QPoint" )
				q->render ( PARAM_QTYPE(QPainter,params[0]), QPoint(params[1]) ), return nullptr;
		}
	}
	else if ( name=="repaint" )
	{
		if ( params.size()==1 ) //competition (2)
		{
			 if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QRect" )
				q->repaint ( QRect(params[0]) ), return nullptr;
			 else if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QRegion" )
				q->repaint ( QRegion(params[0]) ), return nullptr;
		}
		else if ( params.size()==4 )
			q->repaint ( (int)params[0], (int)params[1], (int)params[2], (int)params[3] ), return nullptr;
	}
	else if ( name=="resize" )
	{
		if ( params.size()==1 )
			q->resize ( QSize(params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->resize ( (int)params[0], (int)params[1] ), return nullptr;
	}
	else if ( name=="restoreGeometry" )
	{
		if ( params.size()==1 )
			return bool(q->restoreGeometry ( QByteArray(params[0]) ));
	}
	else if ( name=="saveGeometry" )
	{
		if ( params.size()==0 )
			return q->saveGeometry ();
	}
	else if ( name=="scroll" )
	{
		if ( params.size()==2 )
			q->scroll ( (int)params[0], (int)params[1] ), return nullptr;
		else if ( params.size()==3 )
			q->scroll ( (int)params[0], (int)params[1], QRect(params[2]) ), return nullptr;
	}
	else if ( name=="setAcceptDrops" )
	{
		if ( params.size()==1 )
			q->setAcceptDrops ( (bool)params[0] ), return nullptr;
	}
	else if ( name=="setAccessibleDescription" )
	{
		if ( params.size()==1 )
			q->setAccessibleDescription ( QString(params[0]) ), return nullptr;
	}
	else if ( name=="setAccessibleName" )
	{
		if ( params.size()==1 )
			q->setAccessibleName ( QString(params[0]) ), return nullptr;
	}
	else if ( name=="setAttribute" )
	{
		if ( params.size()==1 )
			q->setAttribute ( Qt::WidgetAttribute((int)params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->setAttribute ( Qt::WidgetAttribute((int)params[0]), (bool)params[1] ), return nullptr;
	}
	else if ( name=="setAutoFillBackground" )
	{
		if ( params.size()==1 )
			q->setAutoFillBackground ( (bool)params[0] ), return nullptr;
	}
	else if ( name=="setBackgroundRole" )
	{
		if ( params.size()==1 )
			q->setBackgroundRole ( (QPalette::ColorRole)params[0] ), return nullptr;
	}
	else if ( name=="setBaseSize" )
	{
		if ( params.size()==1 )
			q->setBaseSize ( QSize(params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->setBaseSize ( (int)params[0], (int)params[1] ), return nullptr;
	}
	else if ( name=="setContentsMargins" )
	{
		if ( params.size()==1 )
			q->setContentsMargins ( QMargins(params[0]) ), return nullptr;
		else if ( params.size()==4 )
			q->setContentsMargins ( (int)params[0], (int)params[1], (int)params[2], (int)params[3] ), return nullptr;
	}
	else if ( name=="setContextMenuPolicy" )
	{
		if ( params.size()==1 )
			q->setContextMenuPolicy ( Qt::ContextMenuPolicy((int)params[0]) ), return nullptr;
	}
	else if ( name=="setCursor" )
	{
		if ( params.size()==1 )
			q->setCursor ( QCursor(params[0]) ), return nullptr;
	}
	else if ( name=="setEditFocus" )
	{
		if ( params.size()==1 )
			q->setEditFocus ( (bool)params[0] ), return nullptr;
	}
	else if ( name=="setFixedHeight" )
	{
		if ( params.size()==1 )
			q->setFixedHeight ( (int)params[0] ), return nullptr;
	}
	else if ( name=="setFixedSize" )
	{
		if ( params.size()==1 )
			q->setFixedSize ( QSize(params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->setFixedSize ( (int)params[0], (int)params[1] ), return nullptr;
	}
	else if ( name=="setFixedWidth" )
	{
		if ( params.size()==1 )
			q->setFixedWidth ( (int)params[0] ), return nullptr;
	}
	else if ( name=="setFocus" )
	{
		if ( params.size()==1 )
			q->setFocus ( Qt::FocusReason((int)params[0]) ), return nullptr;
	}
	else if ( name=="setFocusPolicy" )
	{
		if ( params.size()==1 )
			q->setFocusPolicy ( Qt::FocusPolicy((int)params[0]) ), return nullptr;
	}
	else if ( name=="setFocusProxy" )
	{
		if ( params.size()==1 )
			q->setFocusProxy ( PARAM_QTYPE(QWidget,params[0]) ), return nullptr;
	}
	else if ( name=="setFont" )
	{
		if ( params.size()==1 )
			q->setFont ( QFont(params[0]) ), return nullptr;
	}
	else if ( name=="setForegroundRole" )
	{
		if ( params.size()==1 )
			q->setForegroundRole ( (QPalette::ColorRole)params[0] ), return nullptr;
	}
	else if ( name=="setGeometry" )
	{
		if ( params.size()==1 )
			q->setGeometry ( QRect(params[0]) ), return nullptr;
		else if ( params.size()==4 )
			q->setGeometry ( (int)params[0], (int)params[1], (int)params[2], (int)params[3] ), return nullptr;
	}
	else if ( name=="setGraphicsEffect" )
	{
		if ( params.size()==1 )
			q->setGraphicsEffect ( PARAM_QTYPE(QGraphicsEffect,params[0]) ), return nullptr;
	}
	else if ( name=="setInputContext" )
	{
		if ( params.size()==1 )
			q->setInputContext ( PARAM_QTYPE(QInputContext,params[0]) ), return nullptr;
	}
	else if ( name=="setInputMethodHints" )
	{
		if ( params.size()==1 )
			q->setInputMethodHints ( Qt::InputMethodHints((int)params[0]) ), return nullptr;
	}
	else if ( name=="setLayout" )
	{
		if ( params.size()==1 )
			q->setLayout ( PARAM_QTYPE(QLayout,params[0]) ), return nullptr;
	}
	else if ( name=="setLayoutDirection" )
	{
		if ( params.size()==1 )
			q->setLayoutDirection ( Qt::LayoutDirection((int)params[0]) ), return nullptr;
	}
	else if ( name=="setLocale" )
	{
		if ( params.size()==1 )
			q->setLocale ( QLocale(params[0]) ), return nullptr;
	}
	else if ( name=="setMask" )
	{
		if ( params.size()==1 ) //competition (2)
		{
			 if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QBitmap" )
				q->setMask ( QBitmap(params[0]) ), return nullptr;
			 else if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QRegion" )
				q->setMask ( QRegion(params[0]) ), return nullptr;
		}
	}
	else if ( name=="setMaximumHeight" )
	{
		if ( params.size()==1 )
			q->setMaximumHeight ( (int)params[0] ), return nullptr;
	}
	else if ( name=="setMaximumSize" )
	{
		if ( params.size()==1 )
			q->setMaximumSize ( QSize(params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->setMaximumSize ( (int)params[0], (int)params[1] ), return nullptr;
	}
	else if ( name=="setMaximumWidth" )
	{
		if ( params.size()==1 )
			q->setMaximumWidth ( (int)params[0] ), return nullptr;
	}
	else if ( name=="setMinimumHeight" )
	{
		if ( params.size()==1 )
			q->setMinimumHeight ( (int)params[0] ), return nullptr;
	}
	else if ( name=="setMinimumSize" )
	{
		if ( params.size()==1 )
			q->setMinimumSize ( QSize(params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->setMinimumSize ( (int)params[0], (int)params[1] ), return nullptr;
	}
	else if ( name=="setMinimumWidth" )
	{
		if ( params.size()==1 )
			q->setMinimumWidth ( (int)params[0] ), return nullptr;
	}
	else if ( name=="setMouseTracking" )
	{
		if ( params.size()==1 )
			q->setMouseTracking ( (bool)params[0] ), return nullptr;
	}
	else if ( name=="setPalette" )
	{
		if ( params.size()==1 )
			q->setPalette ( QPalette(params[0]) ), return nullptr;
	}
	else if ( name=="setParent" )
	{
		if ( params.size()==1 )
			q->setParent ( PARAM_QTYPE(QWidget,params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->setParent ( PARAM_QTYPE(QWidget,params[0]), Qt::WindowFlags((int)params[1]) ), return nullptr;
	}
	else if ( name=="setPlatformWindow" )
	{
		if ( params.size()==1 )
			q->setPlatformWindow ( PARAM_QTYPE(QPlatformWindow,params[0]) ), return nullptr;
	}
	else if ( name=="setPlatformWindowFormat" )
	{
		if ( params.size()==1 )
			q->setPlatformWindowFormat ( QPlatformWindowFormat(params[0]) ), return nullptr;
	}
	else if ( name=="setShortcutAutoRepeat" )
	{
		if ( params.size()==1 )
			q->setShortcutAutoRepeat ( (int)params[0] ), return nullptr;
		else if ( params.size()==2 )
			q->setShortcutAutoRepeat ( (int)params[0], (bool)params[1] ), return nullptr;
	}
	else if ( name=="setShortcutEnabled" )
	{
		if ( params.size()==1 )
			q->setShortcutEnabled ( (int)params[0] ), return nullptr;
		else if ( params.size()==2 )
			q->setShortcutEnabled ( (int)params[0], (bool)params[1] ), return nullptr;
	}
	else if ( name=="setSizeIncrement" )
	{
		if ( params.size()==1 )
			q->setSizeIncrement ( QSize(params[0]) ), return nullptr;
		else if ( params.size()==2 )
			q->setSizeIncrement ( (int)params[0], (int)params[1] ), return nullptr;
	}
	else if ( name=="setSizePolicy" )
	{
		if ( params.size()==1 )
			q->setSizePolicy ( (QSizePolicy)params[0] ), return nullptr;
		else if ( params.size()==2 )
			q->setSizePolicy ( (QSizePolicy::Policy)params[0], (QSizePolicy::Policy)params[1] ), return nullptr;
	}
	else if ( name=="setStatusTip" )
	{
		if ( params.size()==1 )
			q->setStatusTip ( QString(params[0]) ), return nullptr;
	}
	else if ( name=="setStyle" )
	{
		if ( params.size()==1 )
			q->setStyle ( PARAM_QTYPE(QStyle,params[0]) ), return nullptr;
	}
	else if ( name=="setToolTip" )
	{
		if ( params.size()==1 )
			q->setToolTip ( QString(params[0]) ), return nullptr;
	}
	else if ( name=="setUpdatesEnabled" )
	{
		if ( params.size()==1 )
			q->setUpdatesEnabled ( (bool)params[0] ), return nullptr;
	}
	else if ( name=="setWhatsThis" )
	{
		if ( params.size()==1 )
			q->setWhatsThis ( QString(params[0]) ), return nullptr;
	}
	else if ( name=="setWindowFilePath" )
	{
		if ( params.size()==1 )
			q->setWindowFilePath ( QString(params[0]) ), return nullptr;
	}
	else if ( name=="setWindowFlags" )
	{
		if ( params.size()==1 )
			q->setWindowFlags ( Qt::WindowFlags((int)params[0]) ), return nullptr;
	}
	else if ( name=="setWindowIcon" )
	{
		if ( params.size()==1 )
			q->setWindowIcon ( QIcon(params[0]) ), return nullptr;
	}
	else if ( name=="setWindowIconText" )
	{
		if ( params.size()==1 )
			q->setWindowIconText ( QString(params[0]) ), return nullptr;
	}
	else if ( name=="setWindowModality" )
	{
		if ( params.size()==1 )
			q->setWindowModality ( Qt::WindowModality((int)params[0]) ), return nullptr;
	}
	else if ( name=="setWindowOpacity" )
	{
		if ( params.size()==1 )
			q->setWindowOpacity ( (qreal)params[0] ), return nullptr;
	}
	else if ( name=="setWindowRole" )
	{
		if ( params.size()==1 )
			q->setWindowRole ( QString(params[0]) ), return nullptr;
	}
	else if ( name=="setWindowState" )
	{
		if ( params.size()==1 )
			q->setWindowState ( Qt::WindowStates((int)params[0]) ), return nullptr;
	}
	else if ( name=="setupUi" )
	{
		if ( params.size()==1 )
			q->setupUi ( PARAM_QTYPE(QWidget,params[0]) ), return nullptr;
	}
	else if ( name=="size" )
	{
		if ( params.size()==0 )
			return q->size ();
	}
	else if ( name=="sizeHint" )
	{
		if ( params.size()==0 )
			return q->sizeHint ();
	}
	else if ( name=="sizeIncrement" )
	{
		if ( params.size()==0 )
			return q->sizeIncrement ();
	}
	else if ( name=="sizePolicy" )
	{
		if ( params.size()==0 )
			return q->sizePolicy ();
	}
	else if ( name=="stackUnder" )
	{
		if ( params.size()==1 )
			q->stackUnder ( PARAM_QTYPE(QWidget,params[0]) ), return nullptr;
	}
	else if ( name=="statusTip" )
	{
		if ( params.size()==0 )
			return string(q->statusTip ());
	}
	else if ( name=="style" )
	{
		if ( params.size()==0 )
			return QNAME(QStyle)(q->style ());
	}
	else if ( name=="styleSheet" )
	{
		if ( params.size()==0 )
			return string(q->styleSheet ());
	}
	else if ( name=="testAttribute" )
	{
		if ( params.size()==1 )
			return bool(q->testAttribute ( Qt::WidgetAttribute((int)params[0]) ));
	}
	else if ( name=="toolTip" )
	{
		if ( params.size()==0 )
			return string(q->toolTip ());
	}
	else if ( name=="underMouse" )
	{
		if ( params.size()==0 )
			return bool(q->underMouse ());
	}
	else if ( name=="ungrabGesture" )
	{
		if ( params.size()==1 )
			q->ungrabGesture ( Qt::GestureType((int)params[0]) ), return nullptr;
	}
	else if ( name=="unsetCursor" )
	{
		if ( params.size()==0 )
			q->unsetCursor (), return nullptr;
	}
	else if ( name=="unsetLayoutDirection" )
	{
		if ( params.size()==0 )
			q->unsetLayoutDirection (), return nullptr;
	}
	else if ( name=="unsetLocale" )
	{
		if ( params.size()==0 )
			q->unsetLocale (), return nullptr;
	}
	else if ( name=="update" )
	{
		if ( params.size()==1 ) //competition (2)
		{
			 if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QRect" )
				q->update ( QRect(params[0]) ), return nullptr;
			 else if ( params[0].type()==Php::Type::Object and GET_CLASS(params[0])=="QRegion" )
				q->update ( QRegion(params[0]) ), return nullptr;
		}
		else if ( params.size()==4 )
			q->update ( (int)params[0], (int)params[1], (int)params[2], (int)params[3] ), return nullptr;
	}
	else if ( name=="updateGeometry" )
	{
		if ( params.size()==0 )
			q->updateGeometry (), return nullptr;
	}
	else if ( name=="updatesEnabled" )
	{
		if ( params.size()==0 )
			return bool(q->updatesEnabled ());
	}
	else if ( name=="visibleRegion" )
	{
		if ( params.size()==0 )
			return q->visibleRegion ();
	}
	else if ( name=="whatsThis" )
	{
		if ( params.size()==0 )
			return string(q->whatsThis ());
	}
	else if ( name=="width" )
	{
		if ( params.size()==0 )
			return int(q->width ());
	}
	else if ( name=="winId" )
	{
		if ( params.size()==0 )
			return WId(q->winId ());
	}
	else if ( name=="window" )
	{
		if ( params.size()==0 )
			return QNAME(QWidget)(q->window ());
	}
	else if ( name=="windowFilePath" )
	{
		if ( params.size()==0 )
			return string(q->windowFilePath ());
	}
	else if ( name=="windowFlags" )
	{
		if ( params.size()==0 )
			return Qt::WindowFlags(q->windowFlags ());
	}
	else if ( name=="windowIcon" )
	{
		if ( params.size()==0 )
			return q->windowIcon ();
	}
	else if ( name=="windowIconText" )
	{
		if ( params.size()==0 )
			return string(q->windowIconText ());
	}
	else if ( name=="windowModality" )
	{
		if ( params.size()==0 )
			return Qt::WindowModality(q->windowModality ());
	}
	else if ( name=="windowOpacity" )
	{
		if ( params.size()==0 )
			return qreal(q->windowOpacity ());
	}
	else if ( name=="windowRole" )
	{
		if ( params.size()==0 )
			return string(q->windowRole ());
	}
	else if ( name=="windowState" )
	{
		if ( params.size()==0 )
			return Qt::WindowStates(q->windowState ());
	}
	else if ( name=="windowSurface" )
	{
		if ( params.size()==0 )
			return QNAME(QWindowSurface)(q->windowSurface ());
	}
	else if ( name=="windowTitle" )
	{
		if ( params.size()==0 )
			return string(q->windowTitle ());
	}
	else if ( name=="windowType" )
	{
		if ( params.size()==0 )
			return Qt::WindowType(q->windowType ());
	}
	else if ( name=="x" )
	{
		if ( params.size()==0 )
			return int(q->x ());
	}
	else if ( name=="x11Info" )
	{
		if ( params.size()==0 )
			return q->x11Info ();
	}
	else if ( name=="x11PictureHandle" )
	{
		if ( params.size()==0 )
			return Qt::HANDLE(q->x11PictureHandle ());
	}
	else if ( name=="y" )
	{
		if ( params.size()==0 )
			return int(q->y ());
	}

	return PARENT::call(name,params,q);
}
Php::Value ME::__callStatic(const char *_name, Php::Parameters &params)
{
    return nullptr;
}