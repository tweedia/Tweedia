QT       += gui sql

TARGET = Template_WidgetPlugin  # Revise this to your class name
TEMPLATE = lib

CONFIG         += plugin
INCLUDEPATH    += ../Tweedia

HEADERS += \
    template_widget-plugin.h    # Revise this to your file name

SOURCES += \
    template_widget-plugin.cpp  # Revise this to your file name

FORMS += \
    template_widget-plugin.ui   # Revise this to your file name
