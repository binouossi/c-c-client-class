QT += core
QT -= gui

CONFIG += c++11

TARGET = Face_client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    client.h


INCLUDEPATH += /usr/include/opencv2
#INCLUDEPATH += /usr/include/security
#DEPENDPATH += .
#INCLUDEPATH += .
#LIBS += -L/usr/lib
LIBS += -lopencv_core
#LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
#LIBS += -lopencv_ml
#LIBS += -lopencv_video
#LIBS += -lopencv_features2d
#LIBS += -lopencv_calib3d
#LIBS += -lopencv_objdetect
#LIBS += -lopencv_contrib
#LIBS += -lopencv_legacy
#LIBS += -lopencv_flann
#LIBS += -lX11
#LIBS += -lXext
#LIBS += -lpam
