TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mygraphlib.cpp \
    geompack.cpp \
    mycolor.cpp \
    myutils.cpp \
    tspinstance.cpp \
    tspmodel.cpp \
    tspcallback.cpp \
    graphviewer.cpp

HEADERS += \
    main.h \
    mygraphlib.h \
    geompack.h \
    mycolor.h \
    myutils.h \
    tspinstance.h \
    tspmodel.h \
    tspcallback.h \
    graphviewer.h
