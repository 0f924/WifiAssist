#!/bin/bash

if [ -d "/usr/local/WifiAssist" ]; then
	echo "Exists Old version,uninstall ..."
	sudo ./uninstall.sh
fi
echo "Install WifiAssist ..."
sudo mkdir /usr/local/WifiAssist
sudo cp WifiAssist /usr/local/WifiAssist/
sudo cp bin/WifiAssist.desktop /usr/local/share/applications
sudo cp etc/com.lzjqsdd.WifiAssist.policy /usr/share/polkit-1/actions/
sudo cp -r bin/ etc/ img/ /usr/local/WifiAssist/
sudo ln -s /usr/local/WifiAssist/WifiAssist /usr/local/bin/WifiAssist
echo "Done."
