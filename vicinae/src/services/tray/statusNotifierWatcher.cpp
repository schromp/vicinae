#include <qdbuserror.h>
#include <qdebug.h>
#include <qobject.h>
#include "statusNotifierWatcher.hpp"

StatusNotifierWatcher::StatusNotifierWatcher(QObject *parent)
    : QObject(parent), m_bus(QDBusConnection::sessionBus()) {
  if (!m_bus.registerService("org.kde.StatusNotifierWatcher")) {
    qWarning() << "Failed to register service:" << m_bus.lastError();
  } else {
    qDebug() << "Service registered successfully.";
  }
  if (!m_bus.registerObject("/StatusNotifierWatcher", this,
                            QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals)) {
    qWarning() << "Failed to register object:" << m_bus.lastError().name() << m_bus.lastError().message();
  }
}

void StatusNotifierWatcher::RegisterStatusNotifierItem(const QString &service) {
  qDebug() << "RegisterStatusNotifierItem called with:" << service;
  m_registeredItems.append(service);

  emit StatusNotifierItemRegistered(service);
  // You can store the registered items here if needed
}

void StatusNotifierWatcher::RegisterStatusNotifierHost(const QString &service) {
  qDebug() << "RegisterStatusNotifierItem called with:" << service;
  m_registeredHosts.append(service);

  emit StatusNotifierHostRegistered(service);
  // You can store the registered items here if needed
}

QStringList StatusNotifierWatcher::RegisteredStatusNotifierItems() { return m_registeredItems; }
