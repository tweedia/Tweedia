QT       += gui sql

TARGET = MeterWidgetPlugin
TEMPLATE = lib

CONFIG         += plugin
INCLUDEPATH    += ../Tweedia

HEADERS += \
    meter-widget-plugin.h

SOURCES += \
    meter-widget-plugin.cpp

FORMS += \
    meter-widget-plugin.ui
