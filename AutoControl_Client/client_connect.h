#ifndef CLIENT_CONNECT
#define CLIENT_CONNECT

#include <glib.h>
#include <gio/gio.h>
#include <gtk/gtk.h>

guint8 send_message(GError *socket_error, GSocketConnection *connection, const char* message);

#endif // CLIENT_CONNECT
