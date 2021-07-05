QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/networkcontroller/relayudpcontroller.cpp \
    src/bmsmodel.cpp \
    src/guicontroller.cpp \
    src/main.cpp \
    src/networkcontroller.cpp \
    src/networkcontroller/relaytcpcontroller.cpp \
    src/podcontroller.cpp \

RESOURCES += qml.qrc

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
    inc/networkcontroller.h \
    inc/networkcontroller.h \
    inc/networkcontroller/relaytcpcontroller.h \
    inc/networkcontroller/relayudpcontroller.h \
    inc/podcontroller.h \
    inc/podstate.h \

