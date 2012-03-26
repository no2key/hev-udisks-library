/*
 ============================================================================
 Name        : hev-udisks.h
 Author      : Heiher <admin@heiher.info>
 Version     : 0.0.1
 Copyright   : Copyright (C) 2011 everyone.
 Description : 
 ============================================================================
 */

#ifndef __HEV_UDISKS_H__
#define __HEV_UDISKS_H__

#include <gio/gio.h>

G_BEGIN_DECLS

#define HEV_TYPE_UDISKS	(hev_udisks_get_type())
#define HEV_UDISKS(obj)	(G_TYPE_CHECK_INSTANCE_CAST((obj), HEV_TYPE_UDISKS, HevUDisks))
#define HEV_IS_UDISKS(obj)	(G_TYPE_CHECK_INSTANCE_TYPE((obj), HEV_TYPE_UDISKS))
#define HEV_UDISKS_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST((klass), HEV_TYPE_UDISKS, HevUDisksClass))
#define HEV_IS_UDISKS_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), HEV_TYPE_UDISKS))
#define HEV_UDISKS_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), HEV_TYPE_UDISKS, HevUDisksClass))

typedef struct _HevUDisks HevUDisks;
typedef struct _HevUDisksClass HevUDisksClass;

struct _HevUDisks
{
	GDBusProxy parent_instance;
};

struct _HevUDisksClass
{
	GDBusProxyClass parent_class;
};

GType hev_udisks_get_type(void);

void hev_udisks_new(GDBusConnection *connection, GDBusProxyFlags flags,
			GDBusInterfaceInfo *info, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data);
GObject * hev_udisks_new_finish(GAsyncResult *res, GError **error);

void hev_udisks_enumerate_devices(HevUDisks *self, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data);
GVariant * hev_udisks_enumerate_devices_finish(HevUDisks *self,
			GAsyncResult *res, GError **error);

void hev_udisks_find_device_by_device_file(HevUDisks *self,
			const gchar *file, GCancellable *cancellable,
			GAsyncReadyCallback callback, gpointer user_data);
gchar * hev_udisks_find_device_by_device_file_finish(HevUDisks *self,
			GAsyncResult *res, GError **error);

G_END_DECLS

#endif /* __HEV_UDISKS_H__ */

