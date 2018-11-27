#include <gio/gio.h>
#include <glib.h>

#define BLOCK_SIZE 1024
#define PORT 1500

struct ConnData {
  GSocketConnection *connection;
  gint message[6];
};

void message_ready (GObject * source_object,
    GAsyncResult *res,
    gpointer user_data)
{
    GInputStream *istream = G_INPUT_STREAM (source_object);
    GError *error = NULL;
    struct ConnData *data = user_data;
    int count;

    count = g_input_stream_read_finish (istream,
      res,
      &error);

    if (count == -1) {
    g_error ("Error when receiving message");
        if (error != NULL) {
              g_error ("%s", error->message);
              g_clear_error (&error);
        }
    }

    g_message ("Ignition: \"%d\"\n", data->message[0]);
    g_message ("Steering Angle: \"%d\"\n", data->message[1]);
    g_message ("Speed: \"%d\"\n", data->message[2]);
    g_message ("Transmission: \"%d\"\n", data->message[3]);
    g_message ("Left Index: \"%d\"\n", data->message[4]);
    g_message ("Right Index: \"%d\"\n", data->message[4]);

    g_object_unref (G_SOCKET_CONNECTION (data->connection));
    g_free (data);
}

static gboolean
incoming_callback (GSocketService *service,
    GSocketConnection * connection,
    GObject * source_object,
    gpointer user_data)
{
  g_message ("Received Connection from client!\n");
  GInputStream *istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
  struct ConnData *data = g_new (struct ConnData, 1);

  data->connection = g_object_ref (connection);

  g_input_stream_read_async (istream,
      data->message,
      sizeof (data->message),
      G_PRIORITY_DEFAULT,
      NULL,
      message_ready,
      data);
  return FALSE;
}

int main ()
{
  GSocketService *service;
  GError *error = NULL;
  gboolean ret;

  service = g_socket_service_new ();
  ret = g_socket_listener_add_inet_port (G_SOCKET_LISTENER (service),
      PORT, NULL, &error);

  if (ret && error != NULL)
  {
    g_error ("%s", error->message);
    g_clear_error (&error);
    return 1;
  }

  g_signal_connect (service,
      "incoming",
      G_CALLBACK (incoming_callback),
      NULL);

  g_socket_service_start (service);
  GMainLoop *loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(loop);

  /* Stop service when out of the main loop*/
  g_socket_service_stop (service);
  return 0;
}
