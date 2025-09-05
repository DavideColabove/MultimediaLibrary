#!/usr/bin/env bash
set -euo pipefail

echo "[Setup] Installing build tools and Qt6 (base + svg)"

if command -v apt >/dev/null 2>&1; then
  sudo apt update
  sudo apt install -y build-essential qt6-base-dev qt6-svg-dev
elif command -v dnf >/dev/null 2>&1; then
  sudo dnf install -y @development-tools qt6-qtbase-devel qt6-qtsvg-devel
elif command -v pacman >/dev/null 2>&1; then
  sudo pacman -Sy --noconfirm base-devel qt6-base qt6-svg
elif command -v zypper >/dev/null 2>&1; then
  sudo zypper install -y patterns-devel-base-devel_basis libqt6-qtbase-devel libqt6-qtsvg-devel
else
  echo "Unsupported package manager. Please install Qt6 base and QtSvg manually."
  exit 1
fi

echo "[Setup] Done. Next steps:"
echo "  qmake MultimediaLibrary.pro  # or qmake6"
echo "  make"
echo "  ./build/bin/MultimediaLibrary"



