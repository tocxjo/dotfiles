export GTK_IM_MODULE=fcitx
export XMODIFIERS=@im=fcitx
export QT_IM_MODULE=fcitx

setxkbmap -layout latam -option ctrl:swapcaps &
qbittorrent &
syncthing &

exec startxfce4
