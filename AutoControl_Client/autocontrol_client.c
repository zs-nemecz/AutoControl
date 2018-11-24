#include <gtk/gtk.h>
#include <gio/gio.h>
#include "auto_settings_gui.h"
#include "client_connect.h"

int main (int   argc, char *argv[])
{
    GtkBuilder *builder;
    GObject *window;
    GObject *ignition_switch;
    GObject *label;
    GObject *slider;
    GtkWidget *gear_button_p;
    GtkWidget *gear_button_n;
    GtkWidget *gear_button_r;
    GtkWidget *gear_button_d;

    GtkWidget *button_left;
    GtkWidget *button_right;

    guint8 left_index = 0;
    guint8 right_index = 0;

    struct IndexButtons index_buttons;
    index_buttons.LeftActive = &left_index;
    index_buttons.RightActive = &right_index;

    GtkWidget *button_send;

    GError *error = NULL;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "builder.ui", &error) == 0)
    {
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
    }

    /* initialize glib */
    g_type_init ();

    /* Connect signal handlers to the constructed widgets. */
    window = gtk_builder_get_object (builder, "window");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    ignition_switch = gtk_builder_get_object (builder, "ignitionSwitch");
    g_signal_connect (ignition_switch, "notify::active", G_CALLBACK (get_ignition), NULL);

    slider = gtk_builder_get_object (builder, "angleSlider");
    g_signal_connect (slider, "value-changed", G_CALLBACK (get_angle), NULL);

    slider = gtk_builder_get_object (builder, "speedSlider");
    g_signal_connect (slider, "value-changed", G_CALLBACK (get_speed), NULL);

    gear_button_p = gtk_builder_get_object (builder, "gearP");
    gear_button_n = gtk_builder_get_object (builder, "gearN");
    gear_button_r = gtk_builder_get_object (builder, "gearR");
    gear_button_d = gtk_builder_get_object (builder, "gearD");

    g_signal_connect (gear_button_p, "toggled", G_CALLBACK (get_transmission_mode), 0);
    g_signal_connect (gear_button_n, "toggled", G_CALLBACK (get_transmission_mode), 1);
    g_signal_connect (gear_button_r, "toggled", G_CALLBACK (get_transmission_mode), 2);
    g_signal_connect (gear_button_d, "toggled", G_CALLBACK (get_transmission_mode), 3);

    button_left = gtk_builder_get_object(builder, "indexLeft");
    button_right = gtk_builder_get_object(builder, "indexRight");
    index_buttons.ButtonLeft = button_left;
    index_buttons.ButtonRight = button_right;
    g_signal_connect (button_left, "toggled", G_CALLBACK (get_index), &index_buttons);
    g_signal_connect (button_right, "toggled", G_CALLBACK (get_index), &index_buttons);

    button_send = gtk_builder_get_object(builder, "buttonSend");
    g_signal_connect (button_send, "clicked", G_CALLBACK (connect_and_send), NULL);

    label = gtk_builder_get_object(builder, "ignitionLabel");
    label = gtk_builder_get_object(builder, "angleLabel");
    label = gtk_builder_get_object(builder, "speedLabel");

    gtk_main ();

    return 0;
}
