QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    edge.cpp \
    graphicslineitem.cpp \
    graphicspixmapitem.cpp \
    graphicssceneitem.cpp \
    input_node.cpp \
    labels.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    operators.cpp \
    output_node.cpp

HEADERS += \
    edge.h \
    graphicslineitem.h \
    graphicspixmapitem.h \
    graphicssceneitem.h \
    input_node.h \
    labels.h \
    mainwindow.h \
    node.h \
    operators.h \
    output_node.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Diploma.qrc
