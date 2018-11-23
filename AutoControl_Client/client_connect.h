#ifndef CLIENT_CONNECT
#define CLIENT_CONNECT

#include <glib.h>
#include <gio/gio.h>
#include <gtk/gtk.h>

struct SocketConnection
{
    GError *SocketError;
    GSocketConnection *Connection;
};

struct SocketConnection * client_connect();

guint8 send_message(GError *socket_error, GSocketConnection *connection, const char* message);

#endif // CLIENT_CONNECT
