/*
 * $Id: cpl_log.h,v 1.1.1.1 2005/06/13 16:47:35 bogdan_iancu Exp $
 *
 * Copyright (C) 2001-2003 FhG Fokus
 *
 * This file is part of openser, a free SIP server.
 *
 * openser is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * openser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 * History:
 * -------
 * 2003-09-22: created (bogdan)
 *
 */


#ifndef _CPL_LOG_H_
#define _CPL_LOG_H_

#include <stdarg.h>
#include "../../str.h"


#define MAX_LOG_NR    64

#define ERR     "Error: "
#define ERR_LEN (sizeof(ERR)-1)
#define WARN    "Warning: "
#define WARN_LEN (sizeof(WARN)-1)
#define NOTE     "Notice: "
#define NOTE_LEN (sizeof(NOTE)-1)

#define LF       "\n"
#define LF_LEN   (1)


void reset_logs();

void append_log( int nr, ...);

void compile_logs( str *log);

#endif

