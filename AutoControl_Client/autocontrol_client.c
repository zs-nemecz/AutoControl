#include <stdint.h>
#include <gtk/gtk.h>

uint8_t set_ignition (GtkWidget *widget, gpointer user_data)
{
    uint8_t ignition;
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

int main (int   argc, char *argv[])
{
    GtkBuilder *builder;
    GObject *window;
    GObject *ignition_switch;
    GObject *ignition_label;
    GObject *button;
/*     GObject *angle_slider;
 *     GObject *speed_slider;
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

    button = gtk_builder_get_object (builder, "quitButton");
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

    ignition_label = gtk_builder_get_object(builder, "ignitionLabel");

    gtk_main ();

    return 0;
}


