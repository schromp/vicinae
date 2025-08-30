#pragma once

#include <qdbusconnection.h>
#include <qobject.h>
#include <qtmetamacros.h>

class StatusNotifierHost : public QObject {
  Q_OBJECT
public:
  StatusNotifierHost(QObject *parent = nullptr);

private:
  QStringList m_registeredItems;
  QDBusConnection m_bus;
};
