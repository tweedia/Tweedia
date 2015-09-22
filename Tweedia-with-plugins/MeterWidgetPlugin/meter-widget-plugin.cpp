#include "meter-widget-plugin.h"
#include "ui_meter-widget-plugin.h"

MeterWidgetPlugin::MeterWidgetPlugin() :
    QWidget(0),
    ui(new Ui::MeterWidgetPlugin)
{
    ui->setupUi(this);
}

MeterWidgetPlugin::~MeterWidgetPlugin()
{
    delete ui;
}

int MeterWidgetPlugin::called_when_DatabaseUpdated()
{
    return 0;
}

Q_EXPORT_PLUGIN2(libMeterWidgetPlugin, MeterWidgetPlugin);

