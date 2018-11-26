#include "client_connect.h"

void say_hello (GObject *source_object,
                        GAsyncResult *res,
                        gpointer user_data)
{
    g_print("connecting...\n");
}

struct SocketConnection * client_connect()
{
    struct SocketConnection socket_connect;
    struct SocketConnection *socket_connectp = &socket_connect;
    GError *socket_error = NULL;

    /* create a new connection */
    GSocketConnection *connection = NULL;
    GSocketClient *client = g_socket_client_new();

    /* connect to the host */
    connection = g_socket_client_connect_to_host(client, (gchar*)"localhost", 1500, NULL, &socket_error);
    //connection = g_socket_client_connect_to_host_async(client, (gchar*)"localhost", 1500, NULL, G_CALLBACK (say_hello), NULL);
    //g_socket_set_blocking (client, FALSE);

    /* don't forget to check for errors */
    if (socket_error != NULL)
    {
      g_error (socket_error->message);
    }
    else
    {
      g_print ("Connection successful!\n");
    }

    socket_connect.SocketError = socket_error;
    socket_connect.Connection = connection;

    return socket_connectp;
}

guint8 send_message(GError *socket_error, GSocketConnection *connection, gint buffer[], gint size)
{
    gint i;
    guint error = 0;

    for (i = 0; i < size; i++)
    {
        g_print("\nmessage: %d", buffer[i]);
    }

    /* use the connection */
    GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
    GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));
    g_output_stream_write  (ostream, buffer, size * sizeof(gint), NULL, &socket_error);

    /* check for errors */
    if (socket_error != NULL)
    {
      g_error (socket_error->message);
      error = 1;
    }

    return error;
}
