#ifndef AUTO_SETTING_GUI
#define AUTO_SETTING_GUI

#include <gtk/gtk.h>

struct IndexButtons {
    GtkWidget *ButtonLeft;
    GtkWidget *ButtonRight;
    guint8 *LeftActive;
    guint8 *RightActive;
} Index;

struct TransmissionMode {
    GtkWidget *TModeP;
    GtkWidget *TModeN;
    GtkWidget *TModeR;
    GtkWidget *TModeD;
    guint8 *CurrentMode;
} Transmission;

guint8 connect_signal_handlers();

guint8 get_ignition (GObject *switcher, GParamSpec *pspec, guint8 *user_data);

guint8 get_index (GtkWidget *widget, struct IndexButtons *button_stucture);

guint8 get_transmission_mode (GtkWidget *widget, struct TransmissionMode *t_mode);

gint16 get_angle (GtkWidget *widget, gint16 *requested_angle);

guint16 get_speed (GtkWidget *widget, guint16 *requested_speed);

guint8 connect_and_send (GtkWidget *widget, gpointer user_data);

#endif // AUTO_SETTING_GUI
