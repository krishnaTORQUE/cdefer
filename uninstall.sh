#!/usr/bin/env sh

set -e

macos_std="/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include"
linux_std="/usr/include"
unix_bin="/usr/local/bin"

sudo rm -rf "$macos_std/cdeferlib"
sudo rm -rf "$linux_std/cdeferlib"

sudo rm "$unix_bin/cdefer"
