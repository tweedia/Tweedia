/* global.h */

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
   Saturday, August 23rd, 2014; Tokyo, Japan
   Initial author: Takenobu Noda
 */

#ifndef GLOBAL_H
#define GLOBAL_H


#include "config.h"
#include <QString>

class TweediaConf {
public:
    enum TypeOfObsformat {
        TXT = 1,
        CSV = 2,
        Default
    };

    QString getTitleOfObsformat(TypeOfObsformat arg) {
        QString result = QString();
        result.clear();
        switch (arg) {
        case TweediaConf::TXT:
            result.append("txt");
            break;
        case TweediaConf::CSV:
            result.append("csv");
            break;
        default:
            break;
        }
        return result;
    }

    TypeOfObsformat getTypeOfObsformat(QString arg){
        for (int i = 0; i < TweediaConf::Default; i++)
            if (arg.compare((const QString)this->getTitleOfObsformat((TypeOfObsformat)i)) == 0)
                return (TypeOfObsformat)i;
        return TweediaConf::TXT;
    }

private:

};

class MetadataOfObsObj {
public:
    QString Tablename;

    QString Col_ID_name;
    QString Col_FLGSELECTED_name;
    QString Col_PID_name;
    QString Col_OBJNAME_name;
    QString Col_OBJPATH_name;
    QString Col_ARGUMENT_name;
    QString Col_OBSTBL_name;
    QString Col_OBSFMT_name;

    QString Col_ID_type;
    QString Col_FLGSELECTED_type;
    QString Col_PID_type;
    QString Col_OBJNAME_type;
    QString Col_OBJPATH_type;
    QString Col_ARGUMENT_type;
    QString Col_OBSTBL_type;
    QString Col_OBSFMT_type;

    QString SqlDrop() { return mSqlDrop; }
    QString SqlCreate() { return mSqlCreate; }

    QString SqlSelectObstblName(int argObsobjID) {
        mSqlSelectObstblName.clear();
        mSqlSelectObstblName.append("SELECT ");
        mSqlSelectObstblName.append(Col_OBSTBL_name);
        mSqlSelectObstblName.append(" FROM ");
        mSqlSelectObstblName.append(Tablename);
        mSqlSelectObstblName.append(" WHERE ");
        mSqlSelectObstblName.append(Col_ID_name);
        mSqlSelectObstblName.append(" = ");
        mSqlSelectObstblName.append(QString::number(argObsobjID));
        return mSqlSelectObstblName;
    }

    MetadataOfObsObj() {
        Tablename = QString("obsobj");

        Col_ID_name = QString("id");
        Col_FLGSELECTED_name = QString("flg_selected");
        Col_PID_name = QString("pid");
        Col_OBJNAME_name = QString("obj_name");
        Col_OBJPATH_name = QString("obj_path");
        Col_ARGUMENT_name = QString("argument");
        Col_OBSTBL_name = QString("obs_tbl");
        Col_OBSFMT_name = QString("obs_fmt");

        Col_ID_type = QString("integer NOT NULL");
        Col_FLGSELECTED_type = QString("boolean NOT NULL");
        Col_PID_type = QString("integer");
        Col_OBJNAME_type = QString("character varying");
        Col_OBJPATH_type = QString("character varying");
        Col_ARGUMENT_type = QString("character varying");
        Col_OBSTBL_type = QString("character varying");
        Col_OBSFMT_type = QString("character varying");

        mSqlDrop.clear();
        mSqlDrop.append("DROP TABLE ");
        mSqlDrop.append(Tablename);

        mSqlCreate.clear();
        mSqlCreate.append("CREATE TABLE ");
        mSqlCreate.append(Tablename);
        mSqlCreate.append("(");
        mSqlCreate.append(Col_ID_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_ID_type);
        mSqlCreate.append(",");
        mSqlCreate.append(Col_FLGSELECTED_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_FLGSELECTED_type);
        mSqlCreate.append(",");
        mSqlCreate.append(Col_OBJNAME_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_OBJNAME_type);
        mSqlCreate.append(",");
        mSqlCreate.append(Col_OBJPATH_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_OBJPATH_type);
        mSqlCreate.append(",");
        mSqlCreate.append(Col_ARGUMENT_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_ARGUMENT_type);
        mSqlCreate.append(",");
        mSqlCreate.append(Col_OBSTBL_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_OBSTBL_type);
        mSqlCreate.append(",");
        mSqlCreate.append(Col_OBSFMT_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_OBSFMT_type);
        mSqlCreate.append(",");
        mSqlCreate.append(Col_PID_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_PID_type);
        mSqlCreate.append(",");
        mSqlCreate.append("CONSTRAINT ");
        mSqlCreate.append(Tablename);
        mSqlCreate.append("_pkey PRIMARY KEY (");
        mSqlCreate.append(Col_ID_name);
        mSqlCreate.append(")");
        mSqlCreate.append(")");
    }

private:
    QString mSqlDrop;
    QString mSqlCreate;
    QString mSqlSelectObstblName;
};

class MetadataOfObservation {
public:
    QString Tablename_prefix;

    QString Col_ID_name;
    QString Col_OBSERVATION_prefix;
    int NumColsDefault;

    QString Col_ID_type;
    QString Col_OBSERVATION_type;

    MetadataOfObservation() {
        Tablename_prefix = QString("observation_");

        Col_ID_name = QString("_id");
        Col_OBSERVATION_prefix = QString("col");
        NumColsDefault = 16;

        Col_ID_type = QString("integer NOT NULL");
        Col_OBSERVATION_type = QString("bytea");



    }

    QString SqlDrop(int arg) {
        mSqlDrop.clear();
        mSqlDrop.append("DROP TABLE ");
        mSqlDrop.append(Tablename_prefix);
        mSqlDrop.append(QString::number(arg));
        return mSqlDrop;
    }

    QString SqlCreate(int arg, int argNumCols) {
        mSqlCreate.clear();
        mSqlCreate.append("CREATE TABLE ");
        mSqlCreate.append(Tablename_prefix);
        mSqlCreate.append(QString::number(arg));
        mSqlCreate.append("(");
        mSqlCreate.append(Col_ID_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_ID_type);
        for (int i = 0; i < argNumCols; i++) {
            mSqlCreate.append(",");
            mSqlCreate.append(Col_OBSERVATION_prefix);
            mSqlCreate.append(QString::number(i+1));
            mSqlCreate.append(" ");
            mSqlCreate.append(Col_OBSERVATION_type);
        }
        mSqlCreate.append(",");
        mSqlCreate.append("CONSTRAINT ");
        mSqlCreate.append(Tablename_prefix);
        mSqlCreate.append(QString::number(arg));
        mSqlCreate.append("_pkey PRIMARY KEY (");
        mSqlCreate.append(Col_ID_name);
        mSqlCreate.append(")");
        mSqlCreate.append(")");
        return mSqlCreate;
    }

    QString SqlSelectMaxId(int argObsobjId) {
        mSqlSelectMaxId.clear();
        mSqlSelectMaxId.append("SELECT MAX(");
        mSqlSelectMaxId.append(Col_ID_name);
        mSqlSelectMaxId.append(") FROM ");
        mSqlSelectMaxId.append(Tablename_prefix);
        mSqlSelectMaxId.append(QString::number(argObsobjId));
        return mSqlSelectMaxId;
    }

    QString SqlSelectAll(int argObsobjId, int argNumCols) {
        mSqlSelectAll.clear();
        mSqlSelectAll.append("SELECT ");
        mSqlSelectAll.append(Col_ID_name);
        for (int i = 0; i < argNumCols; i++) {
            mSqlSelectAll.append(",");
            mSqlSelectAll.append(Col_OBSERVATION_prefix);
            mSqlSelectAll.append(QString::number(i+1));
        }
        mSqlSelectAll.append(" FROM ");
        mSqlSelectAll.append(Tablename_prefix);
        mSqlSelectAll.append(QString::number(argObsobjId));
        return mSqlSelectAll;
    }

    QString SqlSelectWhereId(int argObsobjId, int argObservationId, int argNumCols){
        mSqlSelectWhereId.clear();
        mSqlSelectWhereId.append("SELECT ");
        mSqlSelectWhereId.append(Col_ID_name);
        for (int i = 0; i < argNumCols; i++) {
            mSqlSelectWhereId.append(",");
            mSqlSelectWhereId.append(Col_OBSERVATION_prefix);
            mSqlSelectWhereId.append(QString::number(i+1));
        }
        mSqlSelectWhereId.append(" FROM ");
        mSqlSelectWhereId.append(Tablename_prefix);
        mSqlSelectWhereId.append(QString::number(argObsobjId));
        mSqlSelectWhereId.append(" WHERE ");
        mSqlSelectWhereId.append(Col_ID_name);
        mSqlSelectWhereId.append(" = ");
        mSqlSelectWhereId.append(QString::number(argObservationId));
        return mSqlSelectWhereId;

    }

    QString SqlSelectLastObservation(int argObsobjId, int argNumCols){
        mSqlSelectLastObservation.clear();
        mSqlSelectLastObservation.append("SELECT ");
        mSqlSelectLastObservation.append(Col_ID_name);
        for (int i = 0; i < argNumCols; i++) {
            mSqlSelectLastObservation.append(",");
            mSqlSelectLastObservation.append(Col_OBSERVATION_prefix);
            mSqlSelectLastObservation.append(QString::number(i+1));
        }
        mSqlSelectLastObservation.append(" FROM ");
        mSqlSelectLastObservation.append(Tablename_prefix);
        mSqlSelectLastObservation.append(QString::number(argObsobjId));
        mSqlSelectLastObservation.append(" WHERE ");
        mSqlSelectLastObservation.append(Col_ID_name);
        mSqlSelectLastObservation.append(" = ");
        mSqlSelectLastObservation.append("(SELECT MAX(");
        mSqlSelectLastObservation.append(Col_ID_name);
        mSqlSelectLastObservation.append(") FROM ");
        mSqlSelectLastObservation.append(Tablename_prefix);
        mSqlSelectLastObservation.append(QString::number(argObsobjId));
        mSqlSelectLastObservation.append(")");
        return mSqlSelectLastObservation;

    }

    QString Tablename(int arg) {
        mTablename.clear();
        mTablename.append(Tablename_prefix);
        mTablename.append(QString::number(arg));
        return mTablename;

    }

private:
    QString mSqlDrop;
    QString mSqlCreate;
    QString mSqlSelectAll;
    QString mSqlSelectMaxId;
    QString mSqlSelectWhereId;
    QString mSqlSelectLastObservation;
    QString mTablename;

};

//class Preferences {
//public:
//    QString PluginDir;

//    Preferences() {
//        PluginDir = QString("./plugin");
//    }
//};

#define DBMSNAME_PREFERENCES "QSQLITE"

class MetadataOfPluginFiles {
public:
    QString Tablename;

    QString Col_ID_name;
    QString Col_PATH_name;

    QString Col_ID_type;
    QString Col_PATH_type;

    QString SqlDrop() { return mSqlDrop; }
    QString SqlCreate() { return mSqlCreate; }
    QString SqlMaxID() { return mSqlMaxID; }

    MetadataOfPluginFiles() {
        Tablename = QString("plugins");

        Col_ID_name = QString("id");
        Col_PATH_name = QString("path");

        Col_ID_type = QString("integer NOT NULL");
        Col_PATH_type = QString("character varying");

        mSqlDrop.clear();
        mSqlDrop.append("DROP TABLE ");
        mSqlDrop.append(Tablename);

        mSqlCreate.clear();
        mSqlCreate.append("CREATE TABLE ");
        mSqlCreate.append(Tablename);
        mSqlCreate.append("(");
        mSqlCreate.append(Col_ID_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_ID_type);
        mSqlCreate.append(",");
        mSqlCreate.append(Col_PATH_name);
        mSqlCreate.append(" ");
        mSqlCreate.append(Col_PATH_type);
        mSqlCreate.append(",");
        mSqlCreate.append("CONSTRAINT ");
        mSqlCreate.append(Tablename);
        mSqlCreate.append("_pkey PRIMARY KEY (");
        mSqlCreate.append(Col_ID_name);
        mSqlCreate.append(")");
        mSqlCreate.append(")");

        mSqlMaxID.clear();
        mSqlMaxID.append("SELECT MAX(");
        mSqlMaxID.append(Col_ID_name);
        mSqlMaxID.append(") FROM ");
        mSqlMaxID.append(Tablename);
    }

private:
    QString mSqlDrop;
    QString mSqlCreate;
    QString mSqlMaxID;
};


#endif // GLOBAL_H
