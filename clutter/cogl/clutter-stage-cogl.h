#ifndef __CLUTTER_STAGE_COGL_H__
#define __CLUTTER_STAGE_COGL_H__

#include <cairo.h>
#include <clutter/clutter-backend.h>
#include <clutter/clutter-stage.h>

#ifdef COGL_HAS_X11_SUPPORT
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#endif

#include "clutter-marshal.h"

G_BEGIN_DECLS

#define CLUTTER_TYPE_STAGE_COGL                  (_clutter_stage_cogl_get_type ())
#define CLUTTER_STAGE_COGL(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), CLUTTER_TYPE_STAGE_COGL, ClutterStageCogl))
#define CLUTTER_IS_STAGE_COGL(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CLUTTER_TYPE_STAGE_COGL))
#define CLUTTER_STAGE_COGL_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), CLUTTER_TYPE_STAGE_COGL, ClutterStageCoglClass))
#define CLUTTER_IS_STAGE_COGL_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), CLUTTER_TYPE_STAGE_COGL))
#define CLUTTER_STAGE_COGL_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), CLUTTER_TYPE_STAGE_COGL, ClutterStageCoglClass))

#define CLUTTER_TYPE_STAGE_COGL_VIEW                  (clutter_stage_cogl_view_get_type ())
#define CLUTTER_STAGE_COGL_VIEW(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), CLUTTER_TYPE_STAGE_COGL_VIEW, ClutterStageCoglView))
#define CLUTTER_IS_STAGE_COGL_VIEW(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CLUTTER_TYPE_STAGE_COGL_VIEW))
#define CLUTTER_STAGE_COGL_CLASS_VIEW(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), CLUTTER_TYPE_STAGE_COGL_VIEW, ClutterStageCoglViewClass))
#define CLUTTER_IS_STAGE_COGL_VIEW_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), CLUTTER_TYPE_STAGE_COGL_VIEW))
#define CLUTTER_STAGE_COGL_VIEW_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), CLUTTER_TYPE_STAGE_COGL_VIEW, ClutterStageCoglViewClass))

typedef struct _ClutterStageCogl         ClutterStageCogl;
typedef struct _ClutterStageCoglClass    ClutterStageCoglClass;

typedef struct _ClutterStageCoglView      ClutterStageCoglView;
typedef struct _ClutterStageCoglViewClass ClutterStageCoglViewClass;

struct _ClutterStageCogl
{
  GObject parent_instance;

 /* the stage wrapper */
  ClutterStage *wrapper;

  /* back pointer to the backend */
  ClutterBackend *backend;

  CoglOnscreen *onscreen;

  float refresh_rate;
  int pending_swaps;

  CoglFrameClosure *frame_closure;

  gint64 last_presentation_time;
  gint64 update_time;

  /* We only enable clipped redraws after 2 frames, since we've seen
   * a lot of drivers can struggle to get going and may output some
   * junk frames to start with. */
  unsigned int frame_count;

  cairo_rectangle_int_t bounding_redraw_clip;

  ClutterStageCoglView *current_view;
  GList *views;
  gint geometry_width;
  gint geometry_height;
  gint fb_width;
  gint fb_height;

  /* Stores a list of previous damaged areas */
#define DAMAGE_HISTORY_MAX 16
#define DAMAGE_HISTORY(x) ((x) & (DAMAGE_HISTORY_MAX - 1))
  cairo_rectangle_int_t damage_history[DAMAGE_HISTORY_MAX];
  unsigned int damage_index;

  guint initialized_redraw_clip : 1;

  /* TRUE if the current paint cycle has a clipped redraw. In that
     case bounding_redraw_clip specifies the the bounds. */
  guint using_clipped_redraw : 1;

  guint dirty_backbuffer     : 1;
};

typedef enum {
  CLUTTER_STAGE_COGL_TRANSFORM_0,
  CLUTTER_STAGE_COGL_TRANSFORM_90,
  CLUTTER_STAGE_COGL_TRANSFORM_180,
  CLUTTER_STAGE_COGL_TRANSFORM_270,
  CLUTTER_STAGE_COGL_TRANSFORM_FLIPPED_0,
  CLUTTER_STAGE_COGL_TRANSFORM_FLIPPED_90,
  CLUTTER_STAGE_COGL_TRANSFORM_FLIPPED_180,
  CLUTTER_STAGE_COGL_TRANSFORM_FLIPPED_270,
} ClutterStageCoglViewTransform;

struct _ClutterStageCoglClass
{
  GObjectClass parent_class;
};

struct _ClutterStageCoglView
{
  GObject parent_intance;
  cairo_rectangle_int_t rect;
  ClutterStageCoglViewTransform transform;
};

struct _ClutterStageCoglViewClass
{
  GObjectClass parent_class;
};

GType _clutter_stage_cogl_get_type (void) G_GNUC_CONST;

GType clutter_stage_cogl_view_get_type (void) G_GNUC_CONST;


void  clutter_stage_cogl_add_view    (ClutterStageCogl     *stage,
                                      ClutterStageCoglView *view);
void  clutter_stage_cogl_remove_view (ClutterStageCogl     *stage,
                                      ClutterStageCoglView *output);

void  clutter_stage_cogl_view_set_rect      (ClutterStageCoglView          *view,
                                             cairo_rectangle_int_t         *rect);
void  clutter_stage_cogl_view_set_transform (ClutterStageCoglView          *view,
                                             ClutterStageCoglViewTransform  transform);

G_END_DECLS

#endif /* __CLUTTER_STAGE_COGL_H__ */
