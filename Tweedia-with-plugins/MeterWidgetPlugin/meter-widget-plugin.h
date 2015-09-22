#ifndef METERWIDGETPLUGIN_H
#define METERWIDGETPLUGIN_H

#include <QtPlugin>
#include <QWidget>
#include "../Tweedia/widget-plugin-interface.h"

namespace Ui {
class MeterWidgetPlugin;
}

class MeterWidgetPlugin : public QWidget, WidgetPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(WidgetPluginInterface)
    
public:
    explicit MeterWidgetPlugin();
    ~MeterWidgetPlugin();
    int callshow() { return 0; }
    int set_dbinstance(QSqlDatabase *argDatabase) {mDatabase = argDatabase; return 0;}
    int set_obsobjid(int argid) {mObsobjID = argid; return 0;}
    int called_when_DatabaseUpdated();

private:
    Ui::MeterWidgetPlugin *ui;
    QSqlDatabase *mDatabase;
    int mObsobjID;
};

#endif // METERWIDGETPLUGIN_H
