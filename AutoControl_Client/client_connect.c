#include "client_connect.h"

struct SocketConnection * client_connect()
{
    struct SocketConnection socket_connect;
    struct SocketConnection *socket_connectp = &socket_connect;
    GError *socket_error = NULL;

    /* create a new connection */
    GSocketConnection *connection = NULL;
    GSocketClient *client = g_socket_client_new();

    /* connect to the host */
    connection = g_socket_client_connect_to_host (client,
                                               (gchar*)"localhost",
                                                1500, /* your port goes here */
                                                NULL,
                                                &socket_error);
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

guint8 send_message(GError *socket_error, GSocketConnection *connection, const char* message)
{
    guint error = 0;
    //g_print("%d", strlen(message));
    /* use the connection */
    GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
    GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));
    g_output_stream_write  (ostream,
                          message, /* your message goes here */
                          strlen(message), /* length of your message */
                          NULL,
                          &socket_error);
    /* don't forget to check for errors */
    if (socket_error != NULL)
    {
      g_error (socket_error->message);
      error = 1;
    }

    return error;
}
