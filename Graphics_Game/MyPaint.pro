QT +=core gui
greaterThan(QT_MAJOR_VERSION,4):QT+=widgets
CONFIG += c++17
SOURCES += \
    main.cpp \
    mypaint.cpp \
    configwindow.cpp

HEADERS += \
    Arc.h \
    Brush.h \
    Circle.h \
    Fill.h \
    Line.h \
    TransMatrix.h \
    mypaint.h \
    configwindow.h \
    Polygon.h \
    point.h

RESOURCES += \
    images.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    configwindow.ui \
