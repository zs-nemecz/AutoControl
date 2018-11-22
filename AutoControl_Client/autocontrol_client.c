#include <gtk/gtk.h>

struct IndexButtons {
    GtkWidget *ButtonLeft;
    GtkWidget *ButtonRight;
    guint8 *LeftActive;
    guint8 *RightActive;
};

guint8 get_ignition (GtkWidget *widget, gpointer user_data)
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

guint8 get_index (GtkWidget *widget, struct IndexButtons *button_stucture)
{
    GtkWidget *other_button;
    guint8 *index_active;

    if (button_stucture->ButtonLeft == widget)
    {
        other_button = button_stucture->ButtonRight;
        g_print("Left button toggled, ");
        index_active = button_stucture->LeftActive;
    }
    else if (button_stucture->ButtonRight == widget)
    {
        other_button = button_stucture->ButtonLeft;
        g_print("Right button toggled, ");
        index_active = button_stucture->RightActive;
    }
    else
    {
        g_print("Error: object unknown!\n");
    }


    if(gtk_toggle_button_get_active(widget) == TRUE)
    {
        *index_active = 1;
        gtk_toggle_button_set_active(other_button, FALSE);
    }
    else if (gtk_toggle_button_get_active(widget) == FALSE)
    {
        *index_active = 0;
    }

    g_print("active: %d\n", *index_active);

    return index_active;
}


guint8 get_transmission_mode (GtkWidget *widget, gpointer user_data)
{
    guint8 t_mode;
    if(gtk_toggle_button_get_active(widget) == TRUE)
    {
        if(user_data == 0)
        {
            t_mode = 0;
            g_print("Parking\n");
        }
        else if (user_data == 1)
        {
            t_mode = 1;
            g_print("Neutral\n");
        }
        else if (user_data == 2)
        {
            t_mode = 2;
            g_print("Backwards\n");
        }
        else if (user_data == 3)
        {
            t_mode = 3;
            g_print("Drive\n");
        }
        else
        {
            t_mode = 4;
            g_print("Transmission mode invalid.\n");
        }
    }
    else
    {
        t_mode = 4;
    }

    g_print("t_mode: %d\n", t_mode);

    return t_mode;
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
    GObject *slider;
    GtkWidget *gear_button_p;
    GtkWidget *gear_button_n;
    GtkWidget *gear_button_r;
    GtkWidget *gear_button_d;

    GtkWidget *button_left;
    GtkWidget *button_right;
    guint left_index = 0;
    guint right_index = 0;

    struct IndexButtons index_buttons;
    index_buttons.LeftActive = &left_index;
    index_buttons.RightActive = &right_index;

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

    label = gtk_builder_get_object(builder, "ignitionLabel");
    label = gtk_builder_get_object(builder, "angleLabel");
    label = gtk_builder_get_object(builder, "speedLabel");

    gtk_main ();

    return 0;
}
