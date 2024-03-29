QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fivestones
TEMPLATE = app
MOC_DIR		= temp/moc
RCC_DIR		= temp/rcc
UI_DIR		= temp/ui
OBJECTS_DIR	= temp/obj
DESTDIR		= $$PWD/../bin

CONFIG += c++11

SOURCES += \    
    main.cpp \
    mainwindow.cpp \
	chessboard/chessboard.cpp \
	AImodel/AIModel.cpp

HEADERS += \    
    mainwindow.h \
	chessboard/chessboard.h \
	AImodel/AIModel.h

FORMS += \
    mainwindow.ui

RC_ICONS	= $$PWD/images/fivestones.ico
RESOURCES	+= main.qrc

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/chessboard
INCLUDEPATH += $$PWD/AImodel

DISTFILES += \
	images/fivestones.ico
