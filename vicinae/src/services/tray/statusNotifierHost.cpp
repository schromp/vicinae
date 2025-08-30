#include "services/tray/statusNotifierHost.hpp"
#include <qcontainerfwd.h>
#include <qdbuserror.h>

StatusNotifierHost::StatusNotifierHost(QObject *parent)
    : QObject(parent), m_bus(QDBusConnection::sessionBus()) {
  if (!m_bus.registerService("org.kde.StatusNotifierHost")) {
    qWarning() << "Failed to register service:" << m_bus.lastError();
  }

  if (!m_bus.registerObject("/StatusNotifierHost", this)) {
    qWarning() << "Failed to register object:" << m_bus.lastError();
  }

  m_bus.connect(QString(), "/StatusNotifierItem", "org.kde.StatusNotifierWatcher",
                "StatusNotifierItemRegistered", this, SLOT(onItemRegistered(QString)));
}

void StatusNotifierHost::onItemRegistered(const QString &service) {
  if (!m_registeredItems.contains(service)) m_registeredItems.append(service);

  emit trayItemRegistered(service);
}

void StatusNotifierHost::onItemUnregistered(const QString &service) {
  m_registeredItems.removeAll(service);

  emit trayItemUnregistered(service);
}
