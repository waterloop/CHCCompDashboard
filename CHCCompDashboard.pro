QT += quick

CONFIG += c++11
QMAKE_CXXFLAGS += /std:c++latest

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/livedatamodel/livedatamodel.cpp \
    src/livedatamodel/livedatanode.cpp \
    src/bmsmodel.cpp \
    src/guicontroller.cpp \
    src/logger.cpp \
    src/main.cpp \
    src/motorcontrolmodel.cpp \
    src/networkcontroller/relayudpcontroller.cpp \
    src/networkcontroller/networkcontroller.cpp \
    src/networkcontroller/relaytcpcontroller.cpp \
    src/podcontroller.cpp \
    src/torchicmodel.cpp

RESOURCES += qml.qrc \
    images.qrc

INCLUDEPATH += inc/

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    inc/bmsmodel.h \
    inc/common.h \
    inc/errorcontroller.h \
    inc/guicontroller.h \
    inc/livedatamodel/livedatamodelinput.h \
    inc/livedatamodel/livedatanode.h \
    inc/logger.h \
    inc/motorcontrolmodel.h \
    inc/networkcontroller/networkcontroller.h \
    inc/networkcontroller/relaytcpcontroller.h \
    inc/networkcontroller/relayudpcontroller.h \
    inc/podcontroller.h \
    inc/podstate.h \
    inc/livedatamodel/livedatamodel.h \
    inc/pressuresenssormodel.h \
    inc/torchicmodel.h

