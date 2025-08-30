#pragma once

#include <qdbusconnection.h>
#include <qobject.h>

class StatusNotifierWatcher : public QObject {
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", "org.kde.StatusNotifierWatcher")
public:
  explicit StatusNotifierWatcher(QObject *parent = nullptr);
  // Add D-Bus methods and signals here as needed

private:
  QStringList m_registeredItems;
  QStringList m_registeredHosts;
  QDBusConnection m_bus;

public slots:
  void RegisterStatusNotifierItem(const QString &service);
  void RegisterStatusNotifierHost(const QString &service);
  // Property getters
  QStringList RegisteredStatusNotifierItems();
  // bool IsStatusNotifierHostRegistered();
  // int ProtocolVersion();

signals:
  void StatusNotifierItemRegistered(const QString &service);
  void StatusNotifierItemUnregistered(const QString &service);
  void StatusNotifierHostRegistered(const QString &service);
};
