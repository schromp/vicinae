#pragma once

#include <qdbusconnection.h>
#include <qobject.h>
#include <qtmetamacros.h>
#include "statusNotifierItem.hpp"

class StatusNotifierHost : public QObject {
  Q_OBJECT
public:
  StatusNotifierHost(QObject *parent = nullptr);

  QList<StatusNotifierItem> registeredItems() const { return m_registeredItems; }

private:
  QList<StatusNotifierItem> m_registeredItems;
  QDBusConnection m_bus;

  QStringList activeNotifierItems() const;

private Q_SLOTS:
  void onItemRegistered(const QString &service);
  void onItemUnregistered(const QString &service);

signals:
  void trayItemRegistered(const QString &service);
  void trayItemUnregistered(const QString &service);
};
