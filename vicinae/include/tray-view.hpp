#pragma once
#include "argument.hpp"
#include "service-registry.hpp"
#include "services/tray/statusNotifierHost.hpp"
#include "services/tray/tray.hpp"
#include "services/window-manager/abstract-window-manager.hpp"
#include "ui/views/list-view.hpp"

// class TrayListItem : public WindowItem {
//   ItemData data() const override {
//     return {.iconUrl = ImageURL::builtin("app-window"),
//             .name = _window->title(),
//             .subtitle = _window->wmClass(),
//             .accessories = generateWorkspaceAccessories()};
//   }
//
// public:
//   UnamedWindowListItem(const std::shared_ptr<AbstractWindowManager::AbstractWindow> &item)
//       : WindowItem(item) {}
// };

class TrayView : public ListView {
  AbstractWindowManager::WindowList windows;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_lastWindowFetch =
      std::chrono::high_resolution_clock::now();

public:
  void refreshTrayList() {
    // Force a refresh by clearing the cache
    // windows.clear(); // TODO: is this needed?
    textChanged(searchText());
  }

  void textChanged(const QString &s) override {
    auto tray = ServiceRegistry::instance()->trayService();

    auto now = std::chrono::high_resolution_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - m_lastWindowFetch).count();

    if (windows.empty() || elapsedSeconds > 1) {
      auto items = tray->m_host->registeredItems(); // TODO: not auto
      m_lastWindowFetch = now;
    }

    m_list->beginResetModel();

    auto &section = m_list->addSection("Tray Items");

    for (const auto &item : items) {
      section.addItem(std::make_unique<TrayListItem>(item));
    }
  }

  void initialize() override {
    auto tray = context()->services->trayService();

    connect(tray->m_host, &StatusNotifierHost::trayItemRegistered, this, &TrayView::refreshTrayList);

    setSearchPlaceholderText("Select Tray Item...");
    textChanged(""); // ?
  };

  TrayView() {}
};
