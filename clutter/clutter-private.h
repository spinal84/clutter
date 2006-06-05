/*
 * Clutter.
 *
 * An OpenGL based 'interactive canvas' library.
 *
 * Authored By Matthew Allum  <mallum@openedhand.com>
 *
 * Copyright (C) 2006 OpenedHand
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _HAVE_CLUTTER_PRIVATE_H
#define _HAVE_CLUTTER_PRIVATE_H

#include <config.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include <GL/glx.h>
#include <GL/gl.h>

#include <glib.h>

#include <pango/pangoft2.h>

typedef struct _ClutterMainContext ClutterMainContext;

struct _ClutterMainContext
{
  Display         *xdpy;
  Window           xwin_root;
  int              xscreen;
  XVisualInfo     *xvinfo;
  
  GC               xgc;
  
  PangoFT2FontMap *font_map;
  
  GMutex          *gl_lock;
  guint            update_idle;
  
  guint            main_loop_level;
  GSList          *main_loops;
  
  ClutterStage    *stage;

  guint            is_initialized : 1;
};

#define CLUTTER_CONTEXT()	(clutter_context_get_default ())
ClutterMainContext *clutter_context_get_default (void);

#endif
