#include "template_widget-plugin.h"                 // Revise this to your file name
#include "ui_template_widget-plugin.h"              // Revise this to your file name

Template_WidgetPlugin::Template_WidgetPlugin() :    // Revise this to your class name
    QWidget(0),
    ui(new Ui::Template_WidgetPlugin)               // Revise this to your class name
{
    ui->setupUi(this);
}

Template_WidgetPlugin::~Template_WidgetPlugin()     // Revise this to your class name
{
    delete ui;
}

int Template_WidgetPlugin::called_when_DatabaseUpdated()    // Revise this to your class name
{
    return 0;
}

Q_EXPORT_PLUGIN2(libTemplate_WidgetPlugin,          // Revise this to your lib name
                 Template_WidgetPlugin              // Revise this to your class name
                 );

