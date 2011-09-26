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
 */

#if !defined(__CLUTTER_H_INSIDE__) && !defined(CLUTTER_COMPILATION)
#error "Only <clutter/clutter.h> can be included directly."
#endif

#ifndef __CLUTTER_BACKEND_H__
#define __CLUTTER_BACKEND_H__

#include <cairo.h>
#include <glib-object.h>
#include <pango/pango.h>
#ifdef COGL_ENABLE_EXPERIMENTAL_2_0_API
#include <cogl/cogl.h>
#endif

#include <clutter/clutter-actor.h>
#include <clutter/clutter-device-manager.h>
#include <clutter/clutter-event.h>
#include <clutter/clutter-feature.h>
#include <clutter/clutter-stage.h>
#include <clutter/clutter-stage-window.h>

G_BEGIN_DECLS

#define CLUTTER_TYPE_BACKEND            (clutter_backend_get_type ())
#define CLUTTER_BACKEND(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), CLUTTER_TYPE_BACKEND, ClutterBackend))
#define CLUTTER_IS_BACKEND(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CLUTTER_TYPE_BACKEND))

/**
 * CLUTTER_OSX_BACKEND:
 *
 * Evaluates to the symbolic name of the Quartz Clutter backend.
 *
 * This macro should be used with clutter_check_backend().
 *
 * Since: 1.10
 */
#define CLUTTER_OSX_BACKEND             "osx"

/**
 * CLUTTER_X11_BACKEND:
 *
 * Evaluates to the symbolic name of the X11 Clutter backend.
 *
 * This macro should be used with clutter_check_backend().
 *
 * Since: 1.10
 */

#define CLUTTER_X11_BACKEND             "x11"

/**
 * CLUTTER_WIN32_BACKEND:
 *
 * Evaluates to the symbolic name of the Windows Clutter backend.
 *
 * This macro should be used with clutter_check_backend().
 *
 * Since: 1.10
 */
#define CLUTTER_WIN32_BACKEND           "win32"

/**
 * CLUTTER_EGL_NATIVE_BACKEND:
 *
 * Evaluates to the symbolic name of the EGL framebuffer Clutter backend.
 *
 * This macro should be used with clutter_check_backend().
 *
 * Since: 1.10
 */
#define CLUTTER_EGL_NATIVE_BACKEND      "eglnative"

/**
 * CLUTTER_WAYLAND_BACKEND:
 *
 * Evaluates to the symbolic name of the Wayland client Clutter backend.
 *
 * This macro should be used with clutter_check_backend().
 *
 * Since: 1.10
 */
#define CLUTTER_WAYLAND_BACKEND         "wayland"

/**
 * CLUTTER_GDK_BACKEND:
 *
 * Evaluates to the symbolic name of the GDK Clutter backend.
 *
 * This macro should be used with clutter_check_backend().
 *
 * Since: 1.10
 */
#define CLUTTER_GDK_BACKEND             "gdk"

/**
 * ClutterBackend:
 *
 * <structname>ClutterBackend</structname> is an opaque structure whose
 * members cannot be directly accessed.
 *
 * Since: 0.4
 */
typedef struct _ClutterBackend          ClutterBackend;
typedef struct _ClutterBackendClass     ClutterBackendClass;

GType clutter_backend_get_type    (void) G_GNUC_CONST;

ClutterBackend *clutter_get_default_backend (void);

gdouble                     clutter_backend_get_resolution            (ClutterBackend             *backend);

void                        clutter_backend_set_font_options          (ClutterBackend             *backend,
                                                                       const cairo_font_options_t *options);
const cairo_font_options_t *clutter_backend_get_font_options          (ClutterBackend             *backend);

#if defined (COGL_ENABLE_EXPERIMENTAL_2_0_API) && defined (CLUTTER_ENABLE_EXPERIMENTAL_API)
CoglContext                *clutter_backend_get_cogl_context          (ClutterBackend             *backend);
#endif

G_END_DECLS

#endif /* __CLUTTER_BACKEND_H__ */
