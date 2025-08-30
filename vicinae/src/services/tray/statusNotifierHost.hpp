#pragma once

#include <qdbusconnection.h>
#include <qobject.h>
#include <qtmetamacros.h>

class StatusNotifierHost : public QObject {
  Q_OBJECT
public:
  StatusNotifierHost(QObject *parent = nullptr);

  QStringList registeredItems() const { return m_registeredItems; }

private:
  QStringList m_registeredItems;
  QDBusConnection m_bus;

  QStringList activeNotifierItems() const;

private Q_SLOTS:
  void onItemRegistered(const QString &service);
  void onItemUnregistered(const QString &service);

signals:
  void trayItemRegistered(const QString &service);
  void trayItemUnregistered(const QString &service);
};
