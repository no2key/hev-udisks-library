/*
 ============================================================================
 Name        : hev-udisks-device.c
 Author      : Heiher <admin@heiher.info>
 Version     : 0.0.1
 Copyright   : Copyright (C) 2011 everyone.
 Description : 
 ============================================================================
 */

#include "hev-udisks-device.h"

#define HEV_UDISKS_DEVICE_GET_PRIVATE(obj)	(G_TYPE_INSTANCE_GET_PRIVATE((obj), HEV_TYPE_UDISKS_DEVICE, HevUDisksDevicePrivate))

typedef struct _HevUDisksDevicePrivate HevUDisksDevicePrivate;

struct _HevUDisksDevicePrivate
{
	gchar c;
};

G_DEFINE_TYPE(HevUDisksDevice, hev_udisks_device, G_TYPE_DBUS_PROXY);

static void hev_udisks_device_dispose(GObject *obj)
{
	HevUDisksDevice *self = HEV_UDISKS_DEVICE(obj);
	HevUDisksDevicePrivate *priv = HEV_UDISKS_DEVICE_GET_PRIVATE(self);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	G_OBJECT_CLASS(hev_udisks_device_parent_class)->dispose(obj);
}

static void hev_udisks_device_finalize(GObject *obj)
{
	HevUDisksDevice *self = HEV_UDISKS_DEVICE(obj);
	HevUDisksDevicePrivate *priv = HEV_UDISKS_DEVICE_GET_PRIVATE(self);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	G_OBJECT_CLASS(hev_udisks_device_parent_class)->finalize(obj);
}

static GObject * hev_udisks_device_constructor(GType type, guint n, GObjectConstructParam *param)
{
	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);
	return G_OBJECT_CLASS(hev_udisks_device_parent_class)->constructor(type, n, param);
}

static void hev_udisks_device_constructed(GObject *obj)
{
	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	G_OBJECT_CLASS(hev_udisks_device_parent_class)->constructed(obj);
}

static void hev_udisks_device_class_init(HevUDisksDeviceClass *klass)
{
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	obj_class->constructor = hev_udisks_device_constructor;
	obj_class->constructed = hev_udisks_device_constructed;
	obj_class->dispose = hev_udisks_device_dispose;
	obj_class->finalize = hev_udisks_device_finalize;

	g_type_class_add_private(klass, sizeof(HevUDisksDevicePrivate));
}

static void hev_udisks_device_init(HevUDisksDevice *self)
{
	HevUDisksDevicePrivate *priv = HEV_UDISKS_DEVICE_GET_PRIVATE(self);
	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);
}

void hev_udisks_device_new(GDBusConnection *connection, GDBusProxyFlags flags,
			GDBusInterfaceInfo *info, const gchar *device_path,
			GCancellable *cancellable, GAsyncReadyCallback callback,
			gpointer user_data)
{
	g_return_if_fail(G_IS_DBUS_CONNECTION(connection));
	g_return_if_fail(NULL!=device_path);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	g_async_initable_new_async(HEV_TYPE_UDISKS_DEVICE,
				G_PRIORITY_DEFAULT, cancellable,
				callback, user_data,
				"g-flags", flags,
				"g-interface-info", info,
				"g-name", "org.freedesktop.UDisks",
				"g-connection", connection,
				"g-object-path", device_path,
				"g-interface-name", "org.freedesktop.UDisks.Device",
				NULL);
}

GObject * hev_udisks_device_new_finish(GAsyncResult *res, GError **error)
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

void hev_udisks_device_partition_table_create(HevUDisksDevice *self,
			const gchar *type, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data)
{
	g_return_if_fail(HEV_IS_UDISKS_DEVICE(self));
	g_return_if_fail(NULL!=type);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	g_dbus_proxy_call(G_DBUS_PROXY(self), "PartitionTableCreate",
				g_variant_new("(sas)", type, NULL),
				G_DBUS_CALL_FLAGS_NONE, -1,
				cancellable, callback, user_data);
}

gboolean hev_udisks_device_partition_table_create_finish(HevUDisksDevice *self,
			GAsyncResult *res, GError **error)
{
	GVariant *rvar = NULL;
	gboolean b = FALSE;

	g_return_if_fail(HEV_IS_UDISKS_DEVICE(self));

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	rvar = g_dbus_proxy_call_finish(G_DBUS_PROXY(self),
				res, error);
	if(rvar)
	{
		b = TRUE;
		g_variant_unref(rvar);
	}

	return b;
}

void hev_udisks_device_partition_create(HevUDisksDevice *self,
			guint64 offset, guint64 size, const gchar *type,
			const gchar *label, const gchar **flags,
			const gchar *fstype, const gchar **fsoptions,
			GCancellable *cancellable, GAsyncReadyCallback callback,
			gpointer user_data)
{
	GVariantBuilder *flags_builder = NULL;
	GVariantBuilder *fsoptions_builder = NULL;

	g_return_if_fail(HEV_IS_UDISKS_DEVICE(self));
	g_return_if_fail(NULL!=type);

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	if(flags)
	{
		gsize i = 0;

		flags_builder = g_variant_builder_new(G_VARIANT_TYPE("as"));
		for(i=0; flags[i]; i++)
		  g_variant_builder_add(flags_builder, "s", flags[i]);
	}
	if(fsoptions)
	{
		gsize i = 0;

		fsoptions_builder = g_variant_builder_new(G_VARIANT_TYPE("as"));
		for(i=0; fsoptions[i]; i++)
		  g_variant_builder_add(fsoptions_builder, "s", fsoptions[i]);
	}
	g_dbus_proxy_call(G_DBUS_PROXY(self), "PartitionCreate",
				g_variant_new("(ttssasassas)", offset, size,
					type, label, flags_builder, NULL,
					fstype, fsoptions_builder),
				G_DBUS_CALL_FLAGS_NONE, -1,
				cancellable, callback, user_data);
	if(flags_builder)
	  g_variant_builder_unref(flags_builder);
	if(fsoptions_builder)
	  g_variant_builder_unref(fsoptions_builder);
}

gchar * hev_udisks_device_partition_create_finish(HevUDisksDevice *self,
			GAsyncResult *res, GError **error)
{
	GVariant *rvar = NULL;
	gchar *path = NULL;

	g_return_if_fail(HEV_IS_UDISKS_DEVICE(self));

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	rvar = g_dbus_proxy_call_finish(G_DBUS_PROXY(self),
				res, error);
	if(rvar)
	{
		GVariant *v = NULL;

		v = g_variant_get_child_value(rvar, 0);
		path = g_strdup(g_variant_get_string(v, NULL));
		g_variant_unref(rvar);
	}

	return path;
}

void hev_udisks_device_filesystem_mount(HevUDisksDevice *self,
			const gchar *type, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data)
{
	g_return_if_fail(HEV_IS_UDISKS_DEVICE(self));

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	g_dbus_proxy_call(G_DBUS_PROXY(self), "FilesystemMount",
				g_variant_new("(sas)", type, NULL),
				G_DBUS_CALL_FLAGS_NONE, -1,
				cancellable, callback, user_data);
}

gchar * hev_udisks_device_filesystem_mount_finish(HevUDisksDevice *self,
			GAsyncResult *res, GError **error)
{
	GVariant *rvar = NULL;
	gchar *path = NULL;

	g_return_if_fail(HEV_IS_UDISKS_DEVICE(self));

	g_debug("%s:%d[%s]", __FILE__, __LINE__, __FUNCTION__);

	rvar = g_dbus_proxy_call_finish(G_DBUS_PROXY(self),
				res, error);
	if(rvar)
	{
		GVariant *v = NULL;

		v = g_variant_get_child_value(rvar, 0);
		path = g_strdup(g_variant_get_string(v, NULL));
		g_variant_unref(rvar);
	}

	return path;
}

gboolean hev_udisks_device_is_drive(HevUDisksDevice *self,
			gboolean *is_drive)
{
	GVariant * rvar = NULL;

	g_return_val_if_fail(HEV_IS_UDISKS_DEVICE(self), FALSE);
	g_return_val_if_fail(NULL!=is_drive, FALSE);

	rvar = g_dbus_proxy_get_cached_property(G_DBUS_PROXY(self),
				"DeviceIsDrive");
	if(!rvar)
	  return FALSE;
	*is_drive = g_variant_get_boolean(rvar);
	g_variant_unref(rvar);

	return TRUE;
}

gboolean hev_udisks_device_is_removable(HevUDisksDevice *self,
			gboolean *is_removable)
{
	GVariant * rvar = NULL;

	g_return_val_if_fail(HEV_IS_UDISKS_DEVICE(self), FALSE);
	g_return_val_if_fail(NULL!=is_removable, FALSE);

	rvar = g_dbus_proxy_get_cached_property(G_DBUS_PROXY(self),
				"DeviceIsRemovable");
	if(!rvar)
	  return FALSE;
	*is_removable = g_variant_get_boolean(rvar);
	g_variant_unref(rvar);

	return TRUE;
}

gboolean hev_udisks_device_is_linux_loop(HevUDisksDevice *self,
			gboolean *is_linux_loop)
{
	GVariant * rvar = NULL;

	g_return_val_if_fail(HEV_IS_UDISKS_DEVICE(self), FALSE);
	g_return_val_if_fail(NULL!=is_linux_loop, FALSE);

	rvar = g_dbus_proxy_get_cached_property(G_DBUS_PROXY(self),
				"DeviceIsLinuxLoop");
	if(!rvar)
	  return FALSE;
	*is_linux_loop = g_variant_get_boolean(rvar);
	g_variant_unref(rvar);

	return TRUE;
}

gboolean hev_udisks_device_get_size(HevUDisksDevice *self,
			guint64 *size)
{
	GVariant * rvar = NULL;

	g_return_val_if_fail(HEV_IS_UDISKS_DEVICE(self), FALSE);
	g_return_val_if_fail(NULL!=size, FALSE);

	rvar = g_dbus_proxy_get_cached_property(G_DBUS_PROXY(self),
				"DeviceSize");
	if(!rvar)
	  return FALSE;
	*size = g_variant_get_uint64(rvar);
	g_variant_unref(rvar);

	return TRUE;
}

gboolean hev_udisks_device_get_drive_model(HevUDisksDevice *self,
			gchar **drive_model)
{
	GVariant * rvar = NULL;

	g_return_val_if_fail(HEV_IS_UDISKS_DEVICE(self), FALSE);
	g_return_val_if_fail(NULL!=drive_model, FALSE);

	rvar = g_dbus_proxy_get_cached_property(G_DBUS_PROXY(self),
				"DriveModel");
	if(!rvar)
	  return FALSE;
	*drive_model = g_strdup(g_variant_get_string(rvar, NULL));
	g_variant_unref(rvar);

	return TRUE;
}

gboolean hev_udisks_device_get_device_file(HevUDisksDevice *self,
			gchar **device_file)
{
	GVariant * rvar = NULL;

	g_return_val_if_fail(HEV_IS_UDISKS_DEVICE(self), FALSE);
	g_return_val_if_fail(NULL!=device_file, FALSE);

	rvar = g_dbus_proxy_get_cached_property(G_DBUS_PROXY(self),
				"DeviceFile");
	if(!rvar)
	  return FALSE;
	*device_file = g_strdup(g_variant_get_string(rvar, NULL));
	g_variant_unref(rvar);

	return TRUE;
}

