#include <gtk/gtk.h>

guint8 set_ignition (GtkWidget *widget, gpointer user_data)
{
    guint8 ignition;
    if (gtk_switch_get_active(widget) == TRUE)
    {
        ignition = 1;
        g_print("IGNITION ON: %d\n", ignition);
    }
    else
    {
        ignition = 0;
        g_print("IGNITION OFF: %d\n", ignition);
    }

    return ignition;
}

gint16 get_angle (GtkWidget *widget, gpointer user_data)
{
    gint16 angle;
    angle = gtk_range_get_value(widget);
    g_print("Requested steering angle: %d\n", angle);

    return angle;
}

guint16 get_speed (GtkWidget *widget, gpointer user_data)
{
    guint16 speed;
    speed = gtk_range_get_value(widget);
    g_print("Requested speed: %d\n", speed);

    return speed;
}

int main (int   argc, char *argv[])
{
    GtkBuilder *builder;
    GObject *window;
    GObject *ignition_switch;
    GObject *label;
    GObject *angle_slider;
    GObject *speed_slider;
    GtkAdjustment *scale_adjustment;

 /*     GObject *speed_slider;
 *     GObject *gear_button;
 *     GObject *direction_toggle;
 */
    GError *error = NULL;
    gtk_init (&argc, &argv);

    /* Construct a GtkBuilder instance and load our UI description */
    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "builder.ui", &error) == 0)
    {
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
    }

    /* Connect signal handlers to the constructed widgets. */
    window = gtk_builder_get_object (builder, "window");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    ignition_switch = gtk_builder_get_object (builder, "ignitionSwitch");
    g_signal_connect (ignition_switch, "notify::active", G_CALLBACK (set_ignition), NULL);

    angle_slider = gtk_builder_get_object (builder, "angleSlider");
    g_signal_connect (angle_slider, "value-changed", G_CALLBACK (get_angle), NULL);

    speed_slider = gtk_builder_get_object (builder, "speedSlider");
    g_signal_connect (speed_slider, "value-changed", G_CALLBACK (get_speed), NULL);

    label = gtk_builder_get_object(builder, "ignitionLabel");
    label = gtk_builder_get_object(builder, "angleLabel");
    label = gtk_builder_get_object(builder, "speedLabel");

    gtk_main ();

    return 0;
}


