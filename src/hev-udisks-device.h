/*
 ============================================================================
 Name        : hev-udisks-device.h
 Author      : Heiher <admin@heiher.info>
 Version     : 0.0.1
 Copyright   : Copyright (C) 2011 everyone.
 Description : 
 ============================================================================
 */

#ifndef __HEV_UDISKS_DEVICE_H__
#define __HEV_UDISKS_DEVICE_H__

#include <gio/gio.h>

G_BEGIN_DECLS

#define HEV_TYPE_UDISKS_DEVICE	(hev_udisks_device_get_type())
#define HEV_UDISKS_DEVICE(obj)	(G_TYPE_CHECK_INSTANCE_CAST((obj), HEV_TYPE_UDISKS_DEVICE, HevUDisksDevice))
#define HEV_IS_UDISKS_DEVICE(obj)	(G_TYPE_CHECK_INSTANCE_TYPE((obj), HEV_TYPE_UDISKS_DEVICE))
#define HEV_UDISKS_DEVICE_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST((klass), HEV_TYPE_UDISKS_DEVICE, HevUDisksDeviceClass))
#define HEV_IS_UDISKS_DEVICE_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), HEV_TYPE_UDISKS_DEVICE))
#define HEV_UDISKS_DEVICE_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), HEV_TYPE_UDISKS_DEVICE, HevUDisksDeviceClass))

typedef struct _HevUDisksDevice HevUDisksDevice;
typedef struct _HevUDisksDeviceClass HevUDisksDeviceClass;

struct _HevUDisksDevice
{
	GDBusProxy parent_instance;
};

struct _HevUDisksDeviceClass
{
	GDBusProxyClass parent_class;
};

GType hev_udisks_device_get_type(void);

void hev_udisks_device_new(GDBusConnection *connection, GDBusProxyFlags flags,
			GDBusInterfaceInfo *info, const gchar *device_path,
			GCancellable *cancellable, GAsyncReadyCallback callback,
			gpointer user_data);
GObject * hev_udisks_device_new_finish(GAsyncResult *res, GError **error);

void hev_udisks_device_partition_table_create(HevUDisksDevice *self,
			const gchar *type, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data);
gboolean hev_udisks_device_partition_table_create_finish(HevUDisksDevice *self,
			GAsyncResult *res, GError **error);

void hev_udisks_device_partition_create(HevUDisksDevice *self,
			guint64 offset, guint64 size, const gchar *type,
			const gchar *label, const gchar **flags,
			const gchar *fstype, const gchar **fsoptions,
			GCancellable *cancellable, GAsyncReadyCallback callback,
			gpointer user_data);
gchar * hev_udisks_device_partition_create_finish(HevUDisksDevice *self,
			GAsyncResult *res, GError **error);

void hev_udisks_device_filesystem_mount(HevUDisksDevice *self,
			const gchar *type, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data);
gchar * hev_udisks_device_filesystem_mount_finish(HevUDisksDevice *self,
			GAsyncResult *res, GError **error);

gboolean hev_udisks_device_is_drive(HevUDisksDevice *self,
			gboolean *is_drive);
gboolean hev_udisks_device_is_removable(HevUDisksDevice *self,
			gboolean *is_removable);
gboolean hev_udisks_device_is_linux_loop(HevUDisksDevice *self,
			gboolean *is_linux_loop);
gboolean hev_udisks_device_get_size(HevUDisksDevice *self,
			guint64 *size);
gboolean hev_udisks_device_get_drive_model(HevUDisksDevice *self,
			gchar **drive_model);
gboolean hev_udisks_device_get_device_file(HevUDisksDevice *self,
			gchar **device_file);

G_END_DECLS

#endif /* __HEV_UDISKS_DEVICE_H__ */

