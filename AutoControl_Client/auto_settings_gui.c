#include "auto_settings_gui.h"
#include "client_connect.h"

guint8 get_ignition (GObject *switcher, GParamSpec *pspec, guint8 *user_data)
{
    guint8 *ignition_on = user_data;

    guint8 ignition;
    if (gtk_switch_get_active(switcher) == TRUE)
    {
        *ignition_on = 1;

    }
    else
    {
        *ignition_on = 0;
    }

    g_print("ignition address: %d\n", user_data);
    g_print("ignition value: %d\n", *user_data);

    return *ignition_on;
}

guint8 get_index (GtkWidget *widget, struct IndexButtons *button_stucture)
{
    GtkWidget *other_button;
    guint8 *index_active;

    g_print("index buttons address: %d\n", button_stucture);

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
        g_print("Left Active: %d\n", *(button_stucture->LeftActive));
        g_print("Right Active: %d\n", *(button_stucture->RightActive));
    }
    else if (gtk_toggle_button_get_active(widget) == FALSE)
    {
        *index_active = 0;
    }

    return *index_active;
}

guint8 get_transmission_mode (GtkWidget *widget, struct TransmissionModes *t_mode)
{
    guint8 *current_mode;
    current_mode = t_mode->CurrentMode;
    if(gtk_toggle_button_get_active(widget) == TRUE)
    {
        if(t_mode->TModeP == widget)
        {
            *current_mode = 0;
            g_print("Parking\n");
        }
        else if (t_mode->TModeN == widget)
        {
            *current_mode = 1;
            g_print("Neutral\n");
        }
        else if (t_mode->TModeR == widget)
        {
            *current_mode = 2;
            g_print("Backwards\n");
        }
        else if (t_mode->TModeD == widget)
        {
            *current_mode = 3;
            g_print("Drive\n");
        }
        else
        {
            *current_mode = 255;
            g_print("Transmission mode invalid.\n");
        }
        g_print("transmisson mode: %d\n", *(t_mode->CurrentMode));
    }

    return *current_mode;
}

gint16 get_angle (GtkWidget *widget, gint16 *requested_angle)
{
    gint16 *angle = requested_angle;
    *angle = gtk_range_get_value(widget);
    g_print("Requested steering angle: %d\n", *requested_angle);

    return angle;
}

guint16 get_speed (GtkWidget *widget, guint16 *requested_speed)
{
    guint16 *speed = requested_speed;
    *speed = gtk_range_get_value(widget);
    g_print("Requested speed: %d\n", *requested_speed);

    return *speed;
}

/* gint * pack_values_to_send (struct RequestedSettings *data)
 * {
 *     gint ignition_to_send= ((gint)*(data->IgnitionFlag));
 *     gint angle_to_send = ((gint)*(data->DesiredAngle));
 *     gint speed_to_send = ((gint)*(data->DesiredSpeed));
 *     gint transmission_to_send = ((gint)*(data->TransmissionMode));
 *     gint lindex_to_send = ((gint)*(data->LeftIndex));
 *     gint rindex_to_send = ((gint)*(data->RightIndex));
 *
 *     gint buffer[6] = {ignition_to_send, angle_to_send, speed_to_send, transmission_to_send, lindex_to_send, rindex_to_send};
 *
 *     return buffer;
 * }
 */

guint8 connect_and_send (GtkWidget *widget, struct RequestedSettings *settings)
{

    gint ignition_to_send= ((gint)*(settings->IgnitionFlag));
    gint angle_to_send = ((gint)*(settings->DesiredAngle));
    gint speed_to_send = ((gint)*(settings->DesiredSpeed));
    gint transmission_to_send = ((gint)*(settings->TransmissionMode));
    gint lindex_to_send = ((gint)*(settings->LeftIndex));
    gint rindex_to_send = ((gint)*(settings->RightIndex));

    gint buffer[6] = {ignition_to_send, angle_to_send, speed_to_send, transmission_to_send, lindex_to_send, rindex_to_send};

    struct SocketConnection *socket_connection;

    socket_connection = client_connect();
    if (socket_connection != NULL)
    {
        gint number_to_send = ((gint)*(settings->IgnitionFlag));
        send_message(socket_connection->SocketError, socket_connection->Connection, buffer, sizeof(buffer)/sizeof(buffer[0]));
    }
    else
    {
        g_print("did not find valid pointer");
    }
    return 0;
}
