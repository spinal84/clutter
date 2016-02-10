/*
 * Clutter.
 *
 * An OpenGL based 'interactive canvas' library.
 *
 * Copyright (C) 2010  Intel Corporation.
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

 * Authors:
 *  Adel Gadllah
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>

#include "clutter-stage-window.h"
#include "clutter-stage-private.h"
#include "clutter-stage-eglnative.h"
#include "clutter-egl.h"
#include <cogl/cogl.h>

static ClutterStageWindowIface *clutter_stage_window_parent_iface = NULL;

static void clutter_stage_window_iface_init (ClutterStageWindowIface *iface);

#define clutter_stage_eglnative_get_type _clutter_stage_eglnative_get_type

G_DEFINE_TYPE_WITH_CODE (ClutterStageEglNative,
                         clutter_stage_eglnative,
                         CLUTTER_TYPE_STAGE_COGL,
                         G_IMPLEMENT_INTERFACE (CLUTTER_TYPE_STAGE_WINDOW,
                                                clutter_stage_window_iface_init));

static gboolean
clutter_stage_eglnative_can_clip_redraws (ClutterStageWindow *stage_window)
{
  return TRUE;
}

static void
clutter_stage_eglnative_class_init (ClutterStageEglNativeClass *klass)
{
}

static void
clutter_stage_eglnative_init (ClutterStageEglNative *stage_eglnative)
{
}

static void
clutter_stage_window_iface_init (ClutterStageWindowIface *iface)
{
  clutter_stage_window_parent_iface = g_type_interface_peek_parent (iface);

  iface->can_clip_redraws = clutter_stage_eglnative_can_clip_redraws;
}

struct _ClutterEglOutput
{
  ClutterStageCoglView parent_instance;
};

struct _ClutterEglOutputClass
{
  ClutterStageCoglViewClass parent_instance;
};

G_DEFINE_TYPE (ClutterEglOutput, clutter_egl_output,
               CLUTTER_TYPE_STAGE_COGL_VIEW)

static void
clutter_egl_output_init (ClutterEglOutput *output)
{
}

static void
clutter_egl_output_class_init (ClutterEglOutputClass *klass)
{
}

ClutterEglOutput *
clutter_egl_stage_add_output (ClutterStage *stage)
{
  ClutterStageWindow *stage_window;
  ClutterStageCogl *stage_cogl;
  ClutterEglOutput *output;

  stage_window = _clutter_stage_get_window (stage);
  stage_cogl = CLUTTER_STAGE_COGL (stage_window);

  output = g_object_new (clutter_egl_output_get_type (), NULL);
  clutter_stage_cogl_add_view (stage_cogl, CLUTTER_STAGE_COGL_VIEW (output));
  return output;
}

ClutterEglOutput *
clutter_egl_stage_remove_output (ClutterStage     *stage,
                                 ClutterEglOutput *output)
{
  ClutterStageWindow *stage_window;
  ClutterStageCogl *stage_cogl;

  stage_window = _clutter_stage_get_window (stage);
  stage_cogl = CLUTTER_STAGE_COGL (stage_window);

  output = g_object_new (clutter_egl_output_get_type (), NULL);
  clutter_stage_cogl_add_view (stage_cogl, CLUTTER_STAGE_COGL_VIEW (output));
}

void
clutter_egl_output_set_rect (ClutterEglOutput            *output,
                             const cairo_rectangle_int_t *rect)
{
  clutter_stage_cogl_view_set_rect (CLUTTER_STAGE_COGL_VIEW (output), rect);
}

void
clutter_egl_output_set_transform (ClutterEglOutput          *output,
                                  ClutterEglOutputTransform  transform)
{
  clutter_stage_cogl_view_set_transform (CLUTTER_STAGE_COGL_VIEW (output),
                                         transform);
}
