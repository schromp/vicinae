#include "argument.hpp"

class StatusNotifierItem {
public:
  // QString iconPixmap; // base64 encoded
  // QString tooltip;
  // bool attention = false;

  StatusNotifierItem(QString name);

  bool operator==(const QString &otherService) const { return m_service == otherService; }

  QString toString() const;
  QString getService() const { return m_service; }
  QString getTitle() const { return m_title; }
  QString getIconName() const { return m_iconName; }

private:
  QString m_service;
  QString m_title;
  QString m_iconName;
  QString m_objectPath;
  QString m_getProperty(const QString &property) const;
};
