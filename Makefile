## QT SPECIFIC
QTDEFS =      	-DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
QTINCLUDES =  	-I/usr/local/include/qt/ \
	-I/usr/local/include/qt/mkspecs/unsupported/macx-clang-libc++ \
	-I/usr/local/lib/qt/QtCore.framework/Versions/5/Headers \
	-I/usr/local/lib/qt/QtGui.framework/Versions/5/Headers \
	-I/usr/local/lib/qt/QtWidgets.framework/Versions/5/Headers \
	-I/usr/local/include/qt \
	-I.

QTLDFLAGS = -L/usr/local/lib/qt \
	-framework QtGui \
	-framework QtCore \
	-framework QtWidgets \
	-L/usr/local/opt/openssl/lib \
	-L/usr/local/lib/qt \
	-F/usr/local/lib/qt \
	-L.



NAME                =   php-qt-ng


INI_DIR     =   $(shell php --ini | grep php.ini | cut -d":" -f 2)

EXTENSION_DIR       =   $(shell php-config --extension-dir)

EXTENSION           =   ${NAME}.so
INI                 =   ${NAME}.ini

COMPILER            =   g++
LINKER              =   g++

COMPILER_FLAGS      =   -Wall -c -O2 -std=c++11 -fpic -o ${QTDEFS} ${QTINCLUDES}
LINKER_FLAGS        =   -shared
LINKER_DEPENDENCIES =   -lphpcpp $(QTLDFLAGS)

RM                  =   rm -f
CP                  =   cp -f
MKDIR               =   mkdir -p

SOURCES = $(shell find . -name '*.cpp' | sort -k 1nr | cut -f2-)

OBJECTS             =   $(SOURCES:%.cpp=%.o)

#   From here the build instructions start


all:	${OBJECTS} ${EXTENSION}

${EXTENSION}:	${OBJECTS} 
	${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:	
	${COMPILER} ${COMPILER_FLAGS} -o $@ ${@:%.o=%.cpp}

install:	
	${CP} ${EXTENSION} ${EXTENSION_DIR} 
	${CP} ${INI} ${INI_DIR}

clean:
	${RM} ${EXTENSION} ${OBJECTS}

