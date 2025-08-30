#pragma once

#include "command-database.hpp"
#include "tray-command.hpp"

class TrayExtension : public BuiltinCommandRepository {
  QString id() const override { return "Tray"; }
  QString displayName() const override { return "System Tray"; }
  ImageURL iconUrl() const override {
    return ImageURL::builtin("app-window-list").setBackgroundTint(SemanticColor::Blue);
  }

public:
  TrayExtension() { registerCommand<TrayCommand>(); }
};
