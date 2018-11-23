#include "client_connect.h"

guint8 send_message(GError *socket_error, GSocketConnection *connection, const char* message)
{
    guint error = 0;
    g_print("%d", strlen(message));
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
