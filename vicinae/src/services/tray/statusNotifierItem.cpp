#include "statusNotifierItem.hpp"
#include <qdbusinterface.h>
#include <qdbusreply.h>

StatusNotifierItem::StatusNotifierItem(QString name) {
  int slashIdx = name.indexOf('/');
  if (slashIdx > 0) {
    m_service = name.left(slashIdx);
    m_objectPath = name.mid(slashIdx);
  } else {
    m_service = name;
    m_objectPath = "/StatusNotifierItem";
  }
  m_title = m_getProperty("Title"); // TODO: fallback using pid
  // > gdbus call --session \
  //   --dest org.freedesktop.DBus \
  //   --object-path /org/freedesktop/DBus \
  //   --method org.freedesktop.DBus.GetConnectionUnixProcessID :1.376
  // (uint32 60097,)
  // lk ~/ repos / vicinae tray - service * > cat / proc / 60097 / cmdline m_iconName =
  //     m_getProperty("IconName");

  // iconPixmap = m_getProperty(name, "IconPixmap");
  // tooltip = m_getProperty(name, "ToolTip");
  // attention = m_getProperty(name, "AttentionIconName") != "";
}

QString StatusNotifierItem::m_getProperty(const QString &property) const {

  QDBusInterface iface(m_service, m_objectPath, "org.freedesktop.DBus.Properties",
                       QDBusConnection::sessionBus());

  QDBusReply<QVariant> propertyReply = iface.call("Get", "org.kde.StatusNotifierItem", property);

  if (propertyReply.isValid()) {
    QString propertyString = propertyReply.value().toString();
    qDebug() << "Property" << property << "of" << m_service << "is" << propertyString;
    return propertyString;
  } else {
    qWarning() << "Failed to get property:" << propertyReply.error();
    return ""; // FIX: handle error
  }
}
