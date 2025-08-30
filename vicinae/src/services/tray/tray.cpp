#include "tray.hpp"
#include <qdbusconnection.h>
#include <qdbusinterface.h>
#include <qdebug.h>
#include <qtmetamacros.h>

TrayService::TrayService() {
  m_watcher = new StatusNotifierWatcher(this);
  m_host = new StatusNotifierHost(this);
}
