#ifndef TEMPLATE_WIDGETPLUGIN_H         // Revise this to your class name
#define TEMPLATE_WIDGETPLUGIN_H         // Revise this to your class name

#include <QtPlugin>
#include <QWidget>
#include "../Tweedia/widget-plugin-interface.h"

namespace Ui {
class Template_WidgetPlugin;            // Revise this to your class name
}

class Template_WidgetPlugin :           // Revise this to your class name
        public QWidget, WidgetPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(WidgetPluginInterface)
    
public:
    explicit Template_WidgetPlugin();   // Revise this to your class name
    ~Template_WidgetPlugin();           // Revise this to your class name
    int callshow() { return 0; }
    int set_dbinstance(QSqlDatabase *argDatabase) {mDatabase = argDatabase; return 0;}
    int set_obsobjid(int argid) {mObsobjID = argid; return 0;}
    int called_when_DatabaseUpdated();

private:
    Ui::Template_WidgetPlugin *ui;      // Revise this to your class name
    QSqlDatabase *mDatabase;
    int mObsobjID;
};

#endif // TEMPLATE_WIDGETPLUGIN_H       // Revise this to your class name
