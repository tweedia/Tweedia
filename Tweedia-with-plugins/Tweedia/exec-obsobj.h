/* exec-obsobj.h */

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
   Sunday, Novenber 10th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#ifndef EXECOBSOBJ_H
#define EXECOBSOBJ_H

#include <QObject>
#include <QProcess>
#include <QByteArray>

#include <QFile>
#include <QTextStream>

#include <QSqlTableModel>
#include <QSqlQuery>

#include <QList>

#include "global.h"

//#include "mainwindow.h"
#include "log.h"
#include "command.h"

#include "widget-plugin-interface.h"

class ExecObsobj : public QObject
{
    Q_OBJECT
public:
    explicit ExecObsobj(int id,
                        QSqlDatabase db,
                        QObject *parent = 0,
                        MetadataOfObsObj *metadataOfObsobj = 0,
                        MetadataOfObservation *metadataOfObservation = 0);
    virtual ~ExecObsobj();

    enum EErrcode {NoErr = 0, OtherErr = 99};
    EErrcode Errcode(){return mErrcode;}
    int Maxid();
//    QByteArray ObservationWhereMaxid();
    int Id(){return mId;}
//    QByteArray ObservationWhereTheid(int id);
//    QByteArray ObservationWhereTheid(QString strid);
    QString Pathname(){return mPathname;}
    void setPathname(QString arg){mPathname=arg;}
    QString Argument(){return mArgument;}
    void setArgument(QString arg){mArgument=arg;}
    QString Tablename(){return mTablename;}
    void setTablename(QString tablename);
    TweediaEnum Obsformat(){return mObsformat;}
    void setObsformat(TweediaEnum arg){mObsformat = arg;}
    TweediaEnum Method(){return mMethod;}
    void setMethod(TweediaEnum arg){mMethod = arg;}

    void submitCommand(Command *command);

//    void addMdichild(QObject* mdichild);

    void start();
    void stop();
    void importobservation();

private:
    volatile bool m_running;
    EErrcode mErrcode;
    Log* mLog;
    QSqlDatabase mDb;

    int mId;
    QString mPathname;
    QString mArgument;
    QString mTablename;
    TweediaEnum mObsformat;
    TweediaEnum mMethod;
    QProcess *mProcess;

    QSqlTableModel *mTable;
    QString mSqlSelectmaxid;
    QString mSqlSelectobservationwheretheid;

    QByteArray mOutputbuffer;
    QByteArray mObservationWhereTheid;

    MetadataOfObservation *mMetadataOfObservation;
    MetadataOfObsObj *mMetadataOfObsObj;
//    Preferences *mPreferences;

    void submitRecord(QString arg);

signals:
    void DatabaseUpdated(int);

public slots:

private slots:
    void saveobservation();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);

};

#endif // EXECOBSOBJ_H


/* References, Quotation:

   1.   Jasmin Blanchette, Mark Summerfield, "C++ GUI Programming with Qt4,"
        Japanese language edition(ISBN978-4-87311-344-9), O'REILLY JAPAN, p328.
        The code is following:

        class ConvertDialog : public QDialog, public Ui::ConvertDialog
        {
            Q_OBJECT

        public:
            ConvertDialog(QWidget *parent = 0);

        private slots:
            void on_brouwseButton_clicked();
            void on_convertButton_clicked();
            void updateOutputTextEdit();
            void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
            void processError(QProcess::ProcessError error);

        private:
            QProcess process;
            QString targetFile;
        };

        #endif


 */
