#!/bin/bash
#
# ~/bin/dwm-statusbar
#
# Status bar for dwm. Expanded from:
# https://bitbucket.org/jasonwryan/eeepc/src/73dadb289dead8ef17ef29a9315ba8f1706927cb/Scripts/dwm-status

# Colour codes from dwm/config.h
colour_gry="\x01" # grey on black
#colour_wht="\x02" # white on black
#colour_dgry="\x04" # darkgrey on black
#colour_blk="\x05" # black on darkgrey
#colour_red="\x06" # colour_red on black
#colour_grn="\x07" # green on black
#colour_dylw="\x08" # orange on black
#colour_ylw="\x09" # yellow on black
#colour_blu="\x0A" # colour_blue on darkgrey
#colour_mag="\x0B" # colour_magenta on darkgrey
#colour_cyn="\x0C" # cyan on darkgrey
#colour_vin="\x08" # cyan on darkgrey

# Icon glyphs from font xbmicons.pcf
glyph_msc=""
glyph_cpu=""
glyph_mem=""
glyph_dl=""
glyph_ul=""
glyph_com=""
glyph_eml=""
glyph_vol="墳"
glyph_tim=""
glyph_clock=""
glyph_tor="<"
sep_solid=""
sep_line=""

print_song_info() {
  song_info="$(mpc  | head -n 1 | cut -c 1-200)"
  #song_info="$(mpc '{{{{%a \uE01B }%t}}|{%f}}' | head -n 1 | cut -c 1-200)"
  if [[ $song_info == "volume:100%   repeat: off   random: off   single: off   consume: off" ]]; then
song_info="Off"
  fi
echo -ne "${sep_solid} ${glyph_msc} ${song_info} "
}

print_torrent_status() {
  torrent_status="$(transmission-remote -l | awk -F " +" '$5 ~ /^[0-9]/ {print $5}')"
  if [[ ! $torrent_status ]]; then
torrent_status="Idle"
  fi
echo -ne "${sep_solid}${glyph_tor} ${torrent_status} "
}

print_email_unread() {
  echo -ne "${glyph_eml}"
  for maildir in $(find $HOME/.mutt/maildir/*/inbox/new -type d); do
unread_count="$(ls "${maildir}" | wc -l)"
    echo -n " ${unread_count}"
  done
echo -n " "
}


print_battery() {
 battery_stat="$(acpi -b | awk 'sub(/,/,"") {print $3, $4}')"
 echo -ne "${sep_solid} ${glyph_com} ${battery_stat}" 

}
print_mem_used() {
  mem_used="$(free -m | awk 'NR==2 {print $3}')"
  echo -ne "${sep_line} ${glyph_mem} ${mem_used}M "
}

print_volume() {
  volume="$(amixer get Master | tail -n1 | sed -r 's/.*\[(.*)%\].*/\1/')"
  echo -ne "${sep_solid} ${glyph_vol} ${volume}% "
}

print_datetime() {
  #datetime="$(date "+%a %d %b - %d %H:%M")"
  datetime="$(date "+%a %d %b - %H:%M")"
  echo -ne "${sep_solid} ${glyph_tim} ${datetime} ${glyph_clock}"
}

# network (from: http://dzen.geekmode.org/dwiki/doku.php?id=dzen:network-meter)
# cpu (from: https://bbs.archlinux.org/viewtopic.php?pid=661641#p661641)
rx_old=$(cat /sys/class/net/wlp10s0/statistics/rx_bytes)
tx_old=$(cat /sys/class/net/wlp10s0/statistics/tx_bytes)

while true; do
  # get new cpu idle and total usage
  eval $(awk '/^cpu /{print "cpu_idle_now=" $5 "; cpu_total_now=" $2+$3+$4+$5 }' /proc/stat)
  cpu_interval=$((cpu_total_now-${cpu_total_old:-0}))
  # calculate cpu usage (%)
  let cpu_used="100 * ($cpu_interval - ($cpu_idle_now-${cpu_idle_old:-0})) / $cpu_interval"

  # get new rx/tx counts
  rx_now=$(cat /sys/class/net/wlo1/statistics/rx_bytes)
  tx_now=$(cat /sys/class/net/wlo1/statistics/tx_bytes)
  
  # calculate the rate (K) and total (M)
  # echo $rx_rate
  # echo $tx_rate
  let rx_rate=($rx_now-$rx_old)/1024
  let tx_rate=($tx_now-$tx_old)/1024
  # let rx_total=$rx_now/1048576
  # let tx_total=$tx_now/1048576

  # output vars
  print_cpu_used() {
    printf "%-14b" "${sep_solid} ${glyph_cpu} ${cpu_used}%"
  }
  print_rx_rate() {
    printf "%-15b" "${sep_solid} ${glyph_dl} ${rx_rate}K"
  }
  print_tx_rate() {
    printf "%-14b" "${sep_line} ${glyph_ul} ${tx_rate}K"
  }

  # Pipe to status bar, not indented due to printing extra spaces/tabs
  xsetroot -name "$(print_song_info)\
$(print_torrent_status)\
$(print_email_unread)\
$(print_cpu_used)$(print_mem_used)\
$(print_rx_rate)$(print_tx_rate)\
$(print_battery)\
$(print_volume)\
$(print_datetime)"

  # reset old rates
  rx_old=$rx_now
  tx_old=$tx_now
  cpu_idle_old=$cpu_idle_now
  cpu_total_old=$cpu_total_now
  # loop stats every 1 second
  sleep 1
done
