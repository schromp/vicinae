#pragma once

#include "single-view-command-context.hpp"
#include "tray-view.hpp"

class TrayCommand : public BuiltinViewCommand<TrayView> {
  QString id() const override { return "open-tray"; }
  QString name() const override { return "Open Tray"; }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("app-window-list").setBackgroundTint(SemanticColor::Blue);
  }
};
