#pragma once

#include <qobject.h>
#include <qtmetamacros.h>

#include "statusNotifierWatcher.hpp"
#include "statusNotifierHost.hpp"

class TrayService : public QObject {
  Q_OBJECT
private:
  StatusNotifierWatcher *m_watcher;
  StatusNotifierHost *m_host;

public:
  TrayService();
};
