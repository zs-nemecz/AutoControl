#include "auto_settings_gui.h"
#include "client_connect.h"

/*TODO: fix return value*/
guint8 get_ignition (GtkWidget *widget, gpointer user_data)
{

    char* messagep;
    struct SocketConnection *socket_connect;

    guint8 ignition;
    if (gtk_switch_get_active(widget) == TRUE)
    {
        ignition = 1;
        g_print("IGNITION ON: %d\n", ignition);
        char message[] = "Ignition on";
        messagep = &message;
    }
    else
    {
        ignition = 0;
        g_print("IGNITION OFF: %d\n", ignition);
        char message[] = "Ignition off";
        messagep = &message;
    }

    socket_connect = client_connect();
    send_message(socket_connect->SocketError, socket_connect->Connection, messagep);

    return ignition;
}

guint8 get_index (GtkWidget *widget, struct IndexButtons *button_stucture)
{
    GtkWidget *other_button;
    guint8 *index_active;

    /*Check which index button was pushed*/
    if (button_stucture->ButtonLeft == widget)
    {
        other_button = button_stucture->ButtonRight;
        g_print("Left button toggled\n");
        index_active = button_stucture->LeftActive;
    }
    else if (button_stucture->ButtonRight == widget)
    {
        other_button = button_stucture->ButtonLeft;
        g_print("Right button toggled.\n");
        index_active = button_stucture->RightActive;
    }
    else
    {
        g_print("Error: object unknown!\n");
    }

    if(gtk_toggle_button_get_active(widget) == TRUE)
    {
        *index_active = 1;
        gtk_toggle_button_set_active(other_button, FALSE); //deselect other button
    }
    else if (gtk_toggle_button_get_active(widget) == FALSE)
    {
        *index_active = 0;
    }

    return *index_active;
}

/*TODO:  ide egy struktura kellene input argumentnek: minden radio button plusz egy uint transmission_mode*/
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
            t_mode = 255;
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

/*TODO: fix return value use "user_data"*/
gint16 get_angle (GtkWidget *widget, gpointer user_data)
{
    gint16 angle;
    angle = gtk_range_get_value(widget);
    g_print("Requested steering angle: %d\n", angle);

    return angle;
}

/*TODO: fix return value - use "user_data"*/
guint16 get_speed (GtkWidget *widget, gpointer user_data)
{
    guint16 speed;
    speed = gtk_range_get_value(widget);
    g_print("Requested speed: %d\n", speed);

    return speed;
}
