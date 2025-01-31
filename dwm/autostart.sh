#!/bin/zsh
fcitx-autostart &
nm-applet &
picom &
nitrogen --restore &
qbittorrent &
easyeffects &
dwmblocks &

setxkbmap -layout latam -option ctrl:swapcaps &
xinput --set-prop 10 \'libinput Accel Speed\' -0.5 &
xset mouse 0 0 &
