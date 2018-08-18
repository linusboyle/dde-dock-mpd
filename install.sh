#!/bin/bash

cd $(dirname $0)
echo "欢迎使用dde-dock-mpd"
echo "Welcome to use dde-dock-mpd"
echo 

echo "确保您已经安装qt5,libmpd,dde-dock以及dtk"
echo "make sure you have qt5,libmpd,dde-dock and dtk installed"
echo 

echo "安装需要您的密码"
echo "Installation will need your password"

sudo install -m 755 -p ./libMPDcontroller.so /usr/lib/dde-dock/plugins/libMPDcontroller.so
