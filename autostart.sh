#!/bin/sh
xrandr --newmode "1920x1080_60.00"  173.00  1920 2048 2248 2576  1080 1083 1088 1120 -hsync +vsync &
#xrandr --addmode eDP1 1920x1080_60.00 &
dunst -lb 12f20 -lf c49b7c -nb 1a2f20 -nf c49b7c &
mopidy &
mpdscribble &
compton &
batterymon &
/home/chupy35/.fehbg &
sleep 2s && /usr/bin/resolucion
#trayer --expand true --widthtype request --transparent true --alpha 255 --align right & 
#nm-applet &
touchegg & 
 /home/chupy35/colors/colors/colors -en  16 '/home/chupy35/imagenes/wallpapers/japawave.png' | /home/chupy35/colors/colors/toxrdb | xrdb -merge & 
 lxsession &
 viper start &
