{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  name = "vicinae-devshell";

  buildInputs = with pkgs; [
    # build tooling
    cmake
    ninja
    pkg-config
    which
    rsync
    breakpointHook
    ccache

    # node / TS ecosystem
    nodejs
    typescript
    protobuf
    grpc-tools
    protoc-gen-js

    # Qt + KDE deps
    qt6.qtbase
    qt6.qtsvg
    qt6.qttools
    qt6.qtwayland
    qt6.qtdeclarative
    qt6.qt5compat
    kdePackages.qtkeychain
    kdePackages.layer-shell-qt
    wayland

    # C++ / other deps
    rapidfuzz-cpp
    minizip
    minizip-ng
    cmark-gfm
    libqalculate
  ];

  # replaceStdenv = pkgs.ccacheStdenv;

  # You can set env vars for convenience
  shellHook = ''
    export QT_PLUGIN_PATH=${pkgs.qt6.qtbase}/lib/qt-6/plugins
    export QML_IMPORT_PATH=${pkgs.qt6.qtdeclarative}/lib/qt-6/qml
    export QML2_IMPORT_PATH=${pkgs.qt6.qtdeclarative}/lib/qt-6/qml
    echo "🚀 Vicinae devshell ready (Qt runtime paths set)"
  '';
}
