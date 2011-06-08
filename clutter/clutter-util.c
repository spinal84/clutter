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
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

/**
 * SECTION:clutter-util
 * @short_description: Utility functions
 *
 * Various miscellaneous utilility functions.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib/gi18n-lib.h>

#include "clutter-util.h"
#include "clutter-main.h"

/**
 * clutter_util_next_p2:
 * @a: Value to get the next power
 *
 * Calculates the nearest power of two, greater than or equal to @a.
 *
 * Return value: The nearest power of two, greater or equal to @a.
 *
 * Deprecated: 1.2
 */
gint
clutter_util_next_p2 (gint a)
{
  int rval = 1;

  while (rval < a)
    rval <<= 1;

  return rval;
}

/*< private >
 * _clutter_gettext:
 * @str: a string to localize
 *
 * Retrieves the localized version of @str, using the Clutter domain
 *
 * Return value: the translated string
 */
const gchar *
_clutter_gettext (const gchar *str)
{
  return g_dgettext (GETTEXT_PACKAGE, str);
}

/* Help macros to scale from OpenGL <-1,1> coordinates system to
 * window coordinates ranging [0,window-size]
 */
#define MTX_GL_SCALE_X(x,w,v1,v2) ((((((x) / (w)) + 1.0f) / 2.0f) * (v1)) + (v2))
#define MTX_GL_SCALE_Y(y,w,v1,v2) ((v1) - (((((y) / (w)) + 1.0f) / 2.0f) * (v1)) + (v2))
#define MTX_GL_SCALE_Z(z,w,v1,v2) (MTX_GL_SCALE_X ((z), (w), (v1), (v2)))

void
_clutter_util_fully_transform_vertices (const CoglMatrix *modelview,
                                        const CoglMatrix *projection,
                                        const int *viewport,
                                        const ClutterVertex *vertices_in,
                                        ClutterVertex *vertices_out,
                                        int n_vertices)
{
  CoglMatrix modelview_projection;
  int i;

  /* XXX: we should find a way to cache this per actor */
  cogl_matrix_multiply (&modelview_projection,
                        projection,
                        modelview);

  for (i = 0; i < n_vertices; i++)
    {
      const ClutterVertex *vertex_in = &vertices_in[i];
      ClutterVertex *vertex_out = &vertices_out[i];
      gfloat x, y, z, w;

      x = vertex_in->x;
      y = vertex_in->y;
      z = vertex_in->z;
      w = 1.0;

      /* Transform the point using the modelview matrix */
      cogl_matrix_transform_point (&modelview_projection, &x, &y, &z, &w);

      /* Finally translate from OpenGL coords to window coords */
      vertex_out->x = MTX_GL_SCALE_X (x, w, viewport[2], viewport[0]);
      vertex_out->y = MTX_GL_SCALE_Y (y, w, viewport[3], viewport[1]);
      vertex_out->z = MTX_GL_SCALE_Z (z, w, viewport[2], viewport[0]);
    }
}

