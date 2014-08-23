/* global.h */

/* Copyright (C) 2014 Takenobu Noda

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

#define COL_OBSOBJ_ID "id"
#define COL_OBSOBJ_ID_TYPE_SQLITE "integer NOT NULL"
#define COL_OBSOBJ_FLGSELECTED "flg_selected"
#define COL_OBSOBJ_FLGSELECTED_TYPE_SQLITE "boolean NOT NULL"
#define COL_OBSOBJ_PID "pid"
#define COL_OBSOBJ_PID_TYPE_SQLITE "integer"
#define COL_OBSOBJ_OBJNAME "obj_name"
#define COL_OBSOBJ_OBJNAME_TYPE_SQLITE "character varying"
#define COL_OBSOBJ_OBJPATH "obj_path"
#define COL_OBSOBJ_OBJPATH_TYPE_SQLITE "character varying"
#define COL_OBSOBJ_ARGUMENT "argument"
#define COL_OBSOBJ_ARGUMENT_TYPE_SQLITE "character varying"
#define COL_OBSOBJ_OBSTBL "obs_tbl"
#define COL_OBSOBJ_OBSTBL_TYPE_SQLITE "character varying"
#define COL_OBSOBJ_EXPTBL "exp_tbl"
#define COL_OBSOBJ_EXPTBL_TYPE_SQLITE "character varying"

#define TBL_OBSERVATION_WITH_PREFIX TBL_OBSERVATION "_%1"

#define COL_OBSERVATION_ID "id"
#define COL_OBSERVATION_ID_TYPE_SQLITE "integer NOT NULL"
#define COL_OBSERVATION_OBSERVATION "observation"
#define COL_OBSERVATION_OBSERVATION_TYPE_SQLITE "bytea"



#endif // GLOBAL_H
