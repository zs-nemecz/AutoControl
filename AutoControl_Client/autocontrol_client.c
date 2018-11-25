#include <gtk/gtk.h>
#include <gio/gio.h>
#include "auto_settings_gui.h"
#include "client_connect.h"

int main (int   argc, char *argv[])
{
    /** Declare GTK+ objects **/
    GtkBuilder *builder;
    GObject *window;
    GtkWidget *ignition_switch;
    GtkWidget *label;
    GtkWidget *slider;
    GtkWidget *gear_button_p;
    GtkWidget *gear_button_n;
    GtkWidget *gear_button_r;
    GtkWidget *gear_button_d;
    GtkWidget *button_left;
    GtkWidget *button_right;
    GtkWidget *button_send;

    /** Declare and initialize settings to be sent **/
    guint8 left_index = 0;
    guint8 right_index = 0;
    guint8 ignition = 0;
    guint8 transmission = 0;

    /** Declare structures to be passed on to widget callbacks **/
    struct IndexButtons index_buttons;
    struct TransmissionMode transmission_modes;

    index_buttons.LeftActive = &left_index;
    index_buttons.RightActive = &right_index;
    transmission_modes.CurrentMode = &transmission;

    /** Init GTK+ **/
    GError *error = NULL;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    if (gtk_builder_add_from_file (builder, "builder.ui", &error) == 0)
    {
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
    }

    /** Connect signal handlers to the constructed widgets. **/
    window = gtk_builder_get_object (builder, "window");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    ignition_switch = gtk_builder_get_object (builder, "ignitionSwitch");
    g_signal_connect (GTK_SWITCH (ignition_switch), "notify::active", G_CALLBACK (get_ignition), &ignition);

    slider = gtk_builder_get_object (builder, "angleSlider");
    g_signal_connect (slider, "value-changed", G_CALLBACK (get_angle), NULL);

    slider = gtk_builder_get_object (builder, "speedSlider");
    g_signal_connect (slider, "value-changed", G_CALLBACK (get_speed), NULL);

    gear_button_p = gtk_builder_get_object (builder, "gearP");
    gear_button_n = gtk_builder_get_object (builder, "gearN");
    gear_button_r = gtk_builder_get_object (builder, "gearR");
    gear_button_d = gtk_builder_get_object (builder, "gearD");
    transmission_modes.TModeP = gear_button_p;
    transmission_modes.TModeN = gear_button_n;
    transmission_modes.TModeR = gear_button_r;
    transmission_modes.TModeD = gear_button_d;

    g_signal_connect (GTK_RADIO_BUTTON(gear_button_p), "toggled", G_CALLBACK (get_transmission_mode), &transmission_modes);
    g_signal_connect (GTK_RADIO_BUTTON(gear_button_n), "toggled", G_CALLBACK (get_transmission_mode), &transmission_modes);
    g_signal_connect (GTK_RADIO_BUTTON(gear_button_r), "toggled", G_CALLBACK (get_transmission_mode), &transmission_modes);
    g_signal_connect (GTK_RADIO_BUTTON(gear_button_d), "toggled", G_CALLBACK (get_transmission_mode), &transmission_modes);

    button_left = gtk_builder_get_object(builder, "indexLeft");
    button_right = gtk_builder_get_object(builder, "indexRight");
    index_buttons.ButtonLeft = button_left;
    index_buttons.ButtonRight = button_right;
    g_signal_connect (button_left, "toggled", G_CALLBACK (get_index), &index_buttons);
    g_signal_connect (button_right, "toggled", G_CALLBACK (get_index), &index_buttons);

    button_send = gtk_builder_get_object(builder, "buttonSend");
    g_signal_connect (button_send, "clicked", G_CALLBACK (connect_and_send), NULL);

    /** Initialize GLIB for TCP connection **/
    g_type_init ();

    gtk_main ();

    return 0;
}
