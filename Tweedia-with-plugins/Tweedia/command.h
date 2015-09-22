/* command.h */

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
   Saturday, Novenber 9th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "global.h"

#include <QString>

/* Command Types: */    // ref.1
enum command_type       // ref.1
{
    cm_start    // <start obs="(obsid: default=active-observation)"/>
    , cm_end    // <end obs="(obsid: default=active-observation)"/>
    , cm_stdin  // <stdin obs="(obsid: default=active-observation)">(input-string)</stdin>
};

class Command
{
public:
    Command();

    command_type gettype(){return type;}
    void settype(command_type arg){type=arg;}

    QString Inputstring(){return mInputstring;}
    void setInputstring(QString arg){mInputstring=arg;}

protected:
    command_type type;  // ref.1
    int flags;          // ref.1
    int line;			// ref.1

    QString mInputstring;

};

#endif // COMMAND_H

/* References, Quotation:
   1.   bash-4.2 command.h
 */
