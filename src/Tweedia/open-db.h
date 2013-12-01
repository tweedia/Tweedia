#ifndef OPENDB_H
#define OPENDB_H

#include <QDialog>
#include <QString>

namespace Ui {
class OpenDb;
}

class OpenDb : public QDialog
{
    Q_OBJECT

public:
    explicit OpenDb(QWidget *parent = 0);
    ~OpenDb();

    QString Dbmsname(){return mDbmsname;}
    QString Hostname(){return mHostname;}
    int     Port(){return mPort;}
    QString Dbname(){return mDbname;}

signals:

private slots:

    void on_buttonBox_accepted();

private:
    Ui::OpenDb *ui;

    QStringList mOptionmDbmsname;
    QStringList mOptionDbname;

    QString mDbmsname;
    QString mHostname;
    int     mPort;
    QString mDbname;

};

#endif // OPENDB_H
