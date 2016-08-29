[![Build Status](https://travis-ci.org/lzjqsdd/WifiAssist.svg?branch=master)](https://travis-ci.org/lzjqsdd/WifiAssist)

## WifiAssit
  The easy way to use Wifi through PC.
  类似windows平台下的猎豹免费wifi
  
## Lastest Version(最新版) [Download](https://github.com/lzjqsdd/WifiAssist/archive/v0.8.zip)  
  
  
## TODOLIST
- [x] 简单开启并关闭wifi
- [x] 增加接入点设置、wifi名称、密码设置,重置设置
- [x] 桌面图标启动
- [x] 自动获取系统网卡列表
- [x] 增加名称密码修改后提示
- [x] 应用为单进程
- [x] 问题报告及关于
- [x] 系统托盘控制
- [x] 增加接入设备气泡提示
- [x] 接入设备列表页
- [x] 接入设备列表的设备logo显示
- [ ] 接入设备限速控制、踢人
- [ ] 自动更新

## Install

  ```shell
  git clone https://github.com/lzjqsdd/WifiAssist.git
  cd WifiAssist
  sudo ./install.sh
  ```
  
## 或编译安装(32为系统需要自己编译)
  ```
  sudo apt-get update -qq
  sudo apt-get -y install qtbase5-dev qtdeclarative5-dev libqt5webkit5-dev libsqlite3-dev
  sudo apt-get -y install qt5-default qttools5-dev-tools
  git clone https://github.com/lzjqsdd/WifiAssist.git
  cd WifiAssist/build
  qmake ../WifiAssist.pro
  make
  cd ../INSTALL
  sudo ./install.sh
  ```
  
## 运行
- 终端执行WifiAssist
- 或dash搜索应用WifiAssit，点击图标执行。

## Uninstall
  ```shell
  ./uninstall.sh
  ```
  （建议卸载按照install.sh中的命令对应着逐个删除。）
## Snapshot
![WifiAssit_init1](https://github.com/lzjqsdd/WifiAssist/blob/master/screenshot/WifiAssistForLinux-Main.png)
![WifiAssit_init2](https://github.com/lzjqsdd/WifiAssist/blob/master/screenshot/WifiAssistForLinux-Settings.png)
![WifiAssit_init2](https://github.com/lzjqsdd/WifiAssist/blob/master/screenshot/WifiAssistForLinux-Device.png)
![WifiAssit_init2](https://github.com/lzjqsdd/WifiAssist/blob/master/screenshot/ClientNotify.png)

## Thanks
  create_ap project:https://github.com/oblique/create_ap
