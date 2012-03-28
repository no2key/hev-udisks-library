/*
 ============================================================================
 Name        : hev-udisks.c
 Author      : Heiher <admin@heiher.info>
 Version     : 0.0.1
 Copyright   : Copyright (C) 2011 everyone.
 Description : 
 ============================================================================
 */

#include "hev-udisks.h"

#define HEV_UDISKS_GET_PRIVATE(obj)	(G_TYPE_INSTANCE_GET_PRIVATE((obj), HEV_TYPE_UDISKS, HevUDisksPrivate))

typedef struct _HevUDisksPrivate HevUDisksPrivate;

struct _HevUDisksPrivate
{
	gchar c;
};

G_DEFINE_TYPE(HevUDisks, hev_udisks, G_TYPE_DBUS_PROXY);

static void hev_udisks_dispose(GObject *obj)
{
	HevUDisks *self = HEV_UDISKS(obj);
	HevUDisksPrivate *priv = HEV_UDISKS_GET_PRIVATE(self);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	G_OBJECT_CLASS(hev_udisks_parent_class)->dispose(obj);
}

static void hev_udisks_finalize(GObject *obj)
{
	HevUDisks *self = HEV_UDISKS(obj);
	HevUDisksPrivate *priv = HEV_UDISKS_GET_PRIVATE(self);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	G_OBJECT_CLASS(hev_udisks_parent_class)->finalize(obj);
}

static GObject * hev_udisks_constructor(GType type, guint n, GObjectConstructParam *param)
{
	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);
	return G_OBJECT_CLASS(hev_udisks_parent_class)->constructor(type, n, param);
}

static void hev_udisks_constructed(GObject *obj)
{
	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	G_OBJECT_CLASS(hev_udisks_parent_class)->constructed(obj);
}

static void hev_udisks_class_init(HevUDisksClass *klass)
{
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	obj_class->constructor = hev_udisks_constructor;
	obj_class->constructed = hev_udisks_constructed;
	obj_class->dispose = hev_udisks_dispose;
	obj_class->finalize = hev_udisks_finalize;

	g_type_class_add_private(klass, sizeof(HevUDisksPrivate));
}

static void hev_udisks_init(HevUDisks *self)
{
	HevUDisksPrivate *priv = HEV_UDISKS_GET_PRIVATE(self);
	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);
}

void hev_udisks_new(GDBusConnection *connection, GDBusProxyFlags flags,
			GDBusInterfaceInfo *info, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data)
{
	g_return_if_fail(G_IS_DBUS_CONNECTION(connection));

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	g_async_initable_new_async(HEV_TYPE_UDISKS,
				G_PRIORITY_DEFAULT, cancellable,
				callback, user_data,
				"g-flags", flags,
				"g-interface-info", info,
				"g-name", "org.freedesktop.UDisks",
				"g-connection", connection,
				"g-object-path", "/org/freedesktop/UDisks",
				"g-interface-name", "org.freedesktop.UDisks",
				NULL);
}

GObject * hev_udisks_new_finish(GAsyncResult *res, GError **error)
{
	GObject *object = NULL, *source_object = NULL;

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	source_object = g_async_result_get_source_object(res);
	g_assert(NULL != source_object);

	object = g_async_initable_new_finish(G_ASYNC_INITABLE(source_object),
				res, error);
	g_object_unref(source_object);

	return object;
}

void hev_udisks_enumerate_devices(HevUDisks *self, gint timeout_msec,
			GCancellable *cancellable, GAsyncReadyCallback callback,
			gpointer user_data)
{
	g_return_if_fail(HEV_IS_UDISKS(self));

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	g_dbus_proxy_call(G_DBUS_PROXY(self), "EnumerateDevices",
				NULL, G_DBUS_CALL_FLAGS_NONE, timeout_msec,
				cancellable, callback, user_data);
}

GVariant * hev_udisks_enumerate_devices_finish(HevUDisks *self,
			GAsyncResult *res, GError **error)
{
	g_return_if_fail(HEV_IS_UDISKS(self));

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	return g_dbus_proxy_call_finish(G_DBUS_PROXY(self),
				res, error);
}

void hev_udisks_find_device_by_device_file(HevUDisks *self,
			const gchar *file, gint timeout_msec, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data)
{
	g_return_if_fail(HEV_IS_UDISKS(self));
	g_return_if_fail(NULL!=file);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	g_dbus_proxy_call(G_DBUS_PROXY(self), "FindDeviceByDeviceFile",
				g_variant_new("(s)", file), G_DBUS_CALL_FLAGS_NONE,
				timeout_msec, cancellable, callback, user_data);
}

gchar * hev_udisks_find_device_by_device_file_finish(HevUDisks *self,
			GAsyncResult *res, GError **error)
{
	gchar *path = NULL;
	GVariant *rvar = NULL;

	g_return_if_fail(HEV_IS_UDISKS(self));

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	rvar = g_dbus_proxy_call_finish(G_DBUS_PROXY(self),
				res, error);
	if(rvar)
	{
		GVariant *v = NULL;

		v = g_variant_get_child_value(rvar, 0);
		path = g_strdup(g_variant_get_string(v, NULL));
	}

	return path;
}

