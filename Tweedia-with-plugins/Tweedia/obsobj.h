/* obsobj.h */

/* Copyright (C) 2013 Takenobu Noda

   This file is part of Tweedia.

   Tweedia is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Tweedia is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Tweedia. If not, see <http://www.gnu.org/licenses/>.
*/

/* Birthdate:
   Sunday, October 6th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#ifndef OBSOBJ_H
#define OBSOBJ_H

#include "global.h"

#include <QSqlTableModel>
#include <QFileInfo>
#include <QSqlQuery>
#include <QString>
#include <QList>

#include "log.h"
#include "exec-obsobj.h"

#include "widget-plugin-interface.h"

#define OBSOBJ_RC_NOERROR          0
#define OBSOBJ_RC_FAILEDTOFIND     101

class Obsobj : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit Obsobj(QObject *parent = 0,
                    QSqlDatabase db = QSqlDatabase(),
                    MetadataOfObsObj *metadataOfObsobj = 0,
                    MetadataOfObservation *metadataOfObservation = 0);
    ~Obsobj();

    int Errcode(){return mErrcode;}
    int Maxid();
    int IdByRow(int row);
    ExecObsobj* findExecObsobj(int row);
    ExecObsobj* updatedExecObsobj(int row);
    bool FlgSelect(int row);
    QString TableActual(int row);
    QString TableExpected(int row);
    QString Argument(int row);

    int addObsobj(QString argPathname);
    void delObsobj(int row);

    void newExecObsobj(int id);

    void startExecObsobj(int row);
    void stopExecObsobj(int row);

    void connectToAllExecObsobj(WidgetPluginInterface *mdichild, const char* method);

//    void startProcess(int row);

protected:
    int mErrcode;
    Log *mLog;

    QString mTablename;
    QString mSqlSelectmaxid;

    QString mTableActual;
    QString mTableExpected;
    QString mArgument;

    MetadataOfObservation *mMetadataOfObservation;
    MetadataOfObsObj *mMetadataOfObsObj;

    QList<ExecObsobj*> mListExecObsobj;
    ExecObsobj* findExecObsobjById(int argId);

//    QProcess *mProcess;

private:
    TweediaEnum getType(QString arg);
    QString getDefaultObsfmtTitle(QString arg);
    QString getDefaultMethodTitle(QString arg);

signals:

public slots:

};

#endif // OBSOBJ_H

/* References, Quotation:
 */
