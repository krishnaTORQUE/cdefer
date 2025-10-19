#!/usr/bin/env sh

set -e

macos_std="/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include"
linux_std="/usr/include"
unix_bin="/usr/local/bin"

# Create temp directory for build #
temp_dir=$(mktemp -d)
echo "Temp dir: $temp_dir"
cd $temp_dir

# Pull repo #
git clone https://github.com/krishnaTORQUE/cdefer .

# Create directories #
if [ -d $macos_std ]
then
    sudo rm -rf "$macos_std/cdeferlib"
    sudo cp -r lib "$macos_std/cdeferlib"
elif [ -d $linux_std ]
then
    sudo rm -rf "$linux_std/cdeferlib"
    sudo cp -r lib "$linux_std/cdeferlib"
else
    echo "Fail to install"
    exit
fi

# Make & install #
make clean
make build
sudo mv build/main "$unix_bin/cdefer"

# Clean #
rm -rf $temp_dir
