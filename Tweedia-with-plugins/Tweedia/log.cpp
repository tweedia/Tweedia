/* log.cpp */

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
   Saturday, September 14th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
*/

#include "log.h"

Log::Log()
{
}

/* This function is adapted from ref.1 */
void Log::WriteLog(int loglevel, const char* msg)
{
    setlogmask (LOG_UPTO (LOG_NOTICE));

    openlog ("Tweedia", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    syslog (loglevel, msg);

    closelog ();
}


/* References, Quotation:
   1.   http://www.gnu.org/software/libc/manual/html_node/Syslog-Example.html
 */
