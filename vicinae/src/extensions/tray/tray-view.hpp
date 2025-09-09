#pragma once
#include "argument.hpp"
#include "service-registry.hpp"
#include "services/tray/statusNotifierHost.hpp"
#include "services/tray/tray.hpp"
#include "services/window-manager/abstract-window-manager.hpp"
#include "ui/omni-list/omni-list-item-widget.hpp"
#include "ui/omni-list/omni-list.hpp"
#include "ui/views/list-view.hpp"
#include "utils/layout.hpp"
#include <memory>
#include <qlogging.h>

class TrayListItemWidget : public OmniListItemWidget {
  TypographyWidget *m_title = new TypographyWidget();

public:
  void setTitle(const QString &title) { m_title->setText(title); }
  TrayListItemWidget(QWidget *parent = nullptr) : OmniListItemWidget(parent) {
    auto left = HStack().add(m_title);
    auto layout = HStack().add(left);

    layout.imbue(this);
  }
};

class TrayListItem : public OmniList::AbstractVirtualItem {
  QString m_name;

public:
  bool hasUniformHeight() const override { return true; }
  QString generateId() const override { return m_name; }

  bool recyclable() const override { return false; }
  // void refresh(QWidget *widget) const override { return; }

  OmniListItemWidget *createWidget() const override {

    auto item = new TrayListItemWidget;
    item->setTitle(m_name);

    return item;
  }

  TrayListItem(const QString &name) : m_name(name) {}
};

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

    auto &section = m_list->addSection("Tray Items");

    for (StatusNotifierItem item : tray->m_host->registeredItems()) {
      auto new_item = std::shared_ptr<TrayListItem>(new TrayListItem(item.getTitle()));
      section.addItem(new_item);
    }
  }

  void initialize() override {
    auto tray = context()->services->trayService();
    qDebug() << "Initializing TrayView with host " << tray->m_host;
    for (auto item : tray->m_host->registeredItems()) {
      // we dont seem to ever get here so there probably are no registred items
      qDebug() << "item " << item.getTitle();
    }

    connect(tray->m_host, &StatusNotifierHost::trayItemRegistered, this, &TrayView::refreshTrayList);

    setSearchPlaceholderText("Select Tray Item...");
    textChanged(""); // ?
  };

  TrayView() {}
};
