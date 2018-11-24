#ifndef AUTO_SETTING_GUI
#define AUTO_SETTING_GUI

#include <gtk/gtk.h>

struct IndexButtons {
    GtkWidget *ButtonLeft;
    GtkWidget *ButtonRight;
    guint8 *LeftActive;
    guint8 *RightActive;
};

guint8 connect_signal_handlers();

guint8 get_ignition (GtkWidget *widget, gpointer user_data);

guint8 get_index (GtkWidget *widget, struct IndexButtons *button_stucture);

guint8 get_transmission_mode (GtkWidget *widget, gpointer user_data);

gint16 get_angle (GtkWidget *widget, gpointer user_data);

guint16 get_speed (GtkWidget *widget, gpointer user_data);

guint8 connect_and_send (GtkWidget *widget, gpointer user_data);

#endif // AUTO_SETTING_GUI
