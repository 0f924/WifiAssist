#!/bin/bash
rm -f ~/.WifiAssist/client.list

basepath=$(cd "$(dirname "$0")"; pwd)
$basepath/wifi.sh --list-clients ap0 > ~/.WifiAssist/client.list
