#include <clutter/clutter.h>

#define PARA_TEXT "This is a paragraph of text to check both " \
                  "word wrapping and basic clipping."

void
rect_cb (ClutterTimeline *timeline, 
	 gint             frame_num, 
	 gpointer         data)
{
  ClutterActor *rect = CLUTTER_ACTOR(data);
  gint          x, y;
  static gint   direction = 1;

  x = clutter_actor_get_x (rect);
  y = clutter_actor_get_y (rect);

  if (x > (CLUTTER_STAGE_WIDTH() - 200))
    direction = -1;
      
  if (x < 100)
    direction = 1;

  x += direction;

  clutter_actor_set_position (rect, x, y);
}


void
text_cb (ClutterTimeline *timeline, 
	 gint             frame_num, 
	 gpointer         data)
{
  ClutterLabel *label;
  gchar buf[32];
  gint  opacity;

  label = CLUTTER_LABEL(data);

  opacity = frame_num/2;

  g_snprintf(buf, 32, "--> %i <--", frame_num);

  clutter_label_set_text (label, buf);
  clutter_actor_set_size(CLUTTER_ACTOR(label), 150, 0);
  clutter_label_set_ellipsize (label, PANGO_ELLIPSIZE_END);

  clutter_actor_set_opacity (CLUTTER_ACTOR(label), opacity); 

  clutter_actor_rotate_z (CLUTTER_ACTOR(label),
			    frame_num,
			    clutter_actor_get_width (CLUTTER_ACTOR(label))/2,
			    clutter_actor_get_height (CLUTTER_ACTOR(label))/2);
}

void
para_cb (ClutterTimeline *timeline, 
	 gint             frame_num, 
	 gpointer         data)
{
  

}

static void
key_press_cb (ClutterStage    *stage,
              ClutterKeyEvent *event,
              gpointer         data)
{
  g_print ("key-press-event\n");
}

static void
key_release_cb (ClutterStage    *stage,
                ClutterKeyEvent *event,
                gpointer         data)
{
  g_print ("key-release-event\n");
}

static gboolean
delete_event_cb (ClutterStage *stage,
                 ClutterEvent *event,
                 gpointer      data)
{
  static gboolean res = FALSE;

  g_print ("delete-event: %s\n",
           res == FALSE ? "first attempt" : "second attempt");

  res = !res;

  return res;
}


int
main (int argc, char *argv[])
{
  ClutterActor    *texture, *label, *rect, *para;
  ClutterActor    *stage;
  ClutterTimeline *timeline;
  ClutterColor     rect_col = { 0xff, 0x0, 0x0, 0x99 };
  GdkPixbuf       *pixbuf;

  clutter_init (&argc, &argv);

  stage = clutter_stage_get_default ();
  g_signal_connect (stage, "delete-event",
                    G_CALLBACK (delete_event_cb), NULL);
  g_signal_connect (stage, "key-press-event",
                    G_CALLBACK (key_press_cb), NULL);
  g_signal_connect (stage, "key-release-event",
                    G_CALLBACK (key_release_cb), NULL);
  g_signal_connect (stage, "button-press-event",
		    G_CALLBACK (clutter_main_quit),
		    NULL);
  
  pixbuf = gdk_pixbuf_new_from_file ("clutter-logo-800x600.png", NULL);

  if (!pixbuf)
    g_error("pixbuf load failed");

  texture = clutter_texture_new_from_pixbuf (pixbuf);

  label = clutter_label_new_with_text("Sans Bold 32", "hello");

  clutter_actor_set_opacity (CLUTTER_ACTOR(label), 0x99);
  clutter_actor_set_position (CLUTTER_ACTOR(label), 550, 100);
  clutter_actor_set_size(label, 400, 0);


  rect = clutter_rectangle_new_with_color(&rect_col);
  clutter_actor_set_size(rect, 100, 100);
  clutter_actor_set_position(rect, 100, 100);

  para = clutter_label_new_with_text ("Sans 24", PARA_TEXT);
  clutter_actor_set_position(para, 10, 10);
  clutter_actor_set_size(para, 200, 0);

  clutter_group_add (CLUTTER_GROUP (stage), texture);
  clutter_group_add (CLUTTER_GROUP (stage), label);
  clutter_group_add (CLUTTER_GROUP (stage), rect);
  clutter_group_add (CLUTTER_GROUP (stage), para);

  clutter_actor_set_size (CLUTTER_ACTOR (stage), 800, 600);

  clutter_actor_show_all (CLUTTER_ACTOR (stage));

  timeline = clutter_timeline_new (360, 200);
  g_object_set (timeline, "loop", TRUE, 0);
  g_signal_connect (timeline, "new-frame", G_CALLBACK (text_cb), label);
  clutter_timeline_start (timeline);

  timeline = clutter_timeline_new (1, 30);
  g_object_set (timeline, "loop", TRUE, 0);
  g_signal_connect (timeline, "new-frame", G_CALLBACK (rect_cb), rect);
  clutter_timeline_start (timeline);

  timeline = clutter_timeline_new (1, 10);
  g_object_set (timeline, "loop", TRUE, 0);
  g_signal_connect (timeline, "new-frame", G_CALLBACK (para_cb), rect);
  clutter_timeline_start (timeline);

  clutter_main();

  return 0;
}
