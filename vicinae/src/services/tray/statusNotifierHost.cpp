#include "services/tray/statusNotifierHost.hpp"
#include <qdbuserror.h>

StatusNotifierHost::StatusNotifierHost(QObject *parent)
    : QObject(parent), m_bus(QDBusConnection::sessionBus()) {
  if (!m_bus.registerService("org.kde.StatusNotifierHost")) {
    qWarning() << "Failed to register service:" << m_bus.lastError();
  }

  if (!m_bus.registerObject("/StatusNotifierHost", this)) {
    qWarning() << "Failed to register object:" << m_bus.lastError();
  }
}
