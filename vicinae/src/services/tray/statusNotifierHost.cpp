#include "services/tray/statusNotifierHost.hpp"
#include <qcontainerfwd.h>
#include <qdbuserror.h>
#include <qdbusinterface.h>
#include <qdbusreply.h>
#include <qlogging.h>

StatusNotifierHost::StatusNotifierHost(QObject *parent)
    : QObject(parent), m_bus(QDBusConnection::sessionBus()) {
  qDebug() << "Initializing StatusNotifierHost";
  if (!m_bus.registerService("org.kde.StatusNotifierHost")) {
    qWarning() << "Failed to register service:" << m_bus.lastError();
  }

  if (!m_bus.registerObject("/StatusNotifierHost", this)) {
    qWarning() << "Failed to register object:" << m_bus.lastError();
  }

  m_bus.connect(QString(), "/StatusNotifierWatcher", "org.kde.StatusNotifierWatcher",
                "StatusNotifierItemRegistered", this, SLOT(onItemRegistered(QString)));

  m_bus.connect(QString(), "/StatusNotifierWatcher", "org.kde.StatusNotifierWatcher",
                "StatusNotifierItemUnregistered", this, SLOT(onItemUnregistered(QString)));

  qDebug() << "Getting a list of registered tray items";
  QDBusInterface watcherIface("org.kde.StatusNotifierWatcher", // service
                              "/StatusNotifierWatcher",        // object path
                              "org.kde.StatusNotifierWatcher", // interface
                              QDBusConnection::sessionBus());

  QDBusInterface iface("org.kde.StatusNotifierWatcher", "/StatusNotifierWatcher",
                       "org.freedesktop.DBus.Properties", QDBusConnection::sessionBus());

  QDBusReply<QVariant> reply =
      iface.call("Get", "org.kde.StatusNotifierWatcher", "RegisteredStatusNotifierItems");
  if (reply.isValid()) {
    QStringList trayItems = reply.value().toStringList();
    m_registeredItems = trayItems;
  } else {
    qWarning() << "Failed to get tray items:" << reply.error();
  }

  for (const QString &item : m_registeredItems) {
    qDebug() << "Found tray item:" << item;
  }
}

void StatusNotifierHost::onItemRegistered(const QString &service) {
  if (!m_registeredItems.contains(service)) m_registeredItems.append(service);
  qDebug() << "Tray item registered:" << service;

  emit trayItemRegistered(service);
}

void StatusNotifierHost::onItemUnregistered(const QString &service) {
  m_registeredItems.removeAll(service);
  qDebug() << "Tray item unregistered:" << service;

  emit trayItemUnregistered(service);
}
