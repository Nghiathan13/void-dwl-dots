/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cat                 read arbitrary file             path
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * up                  interface is running            interface name (eth0)
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD/FreeBSD
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */
/* battery pill: icon by level (90/65/40/15) + bolt right of icon when charging */
static const struct arg args[] = {
	/* function    	format                    	argument */
	{ run_command, "^bg(1a1a1a) %s ^bg() ",
		"v=$(wpctl get-volume @DEFAULT_AUDIO_SINK@); "
		"case \"$v\" in *MUTED*) printf '%b MUTE' \"\\357\\200\\246\";; "
		"*) p=$(printf '%s' \"$v\" | awk '{printf \"%d\", $2*100}'); "
		"if [ \"$p\" -le 0 ]; then i=\"\\357\\200\\246\"; "
		"elif [ \"$p\" -lt 40 ]; then i=\"\\357\\200\\247\"; "
		"else i=\"\\357\\200\\250\"; fi; "
		"printf '%b %s%%' \"$i\" \"$p\";; "
		"esac" },
	{ run_command, "^bg(1a1a1a) %s ^bg() ",
		"c=$(cat /sys/class/power_supply/BAT0/capacity); "
		"s=$(cat /sys/class/power_supply/BAT0/status); "
		"if [ \"$c\" -ge 90 ]; then i='\\357\\211\\200';"
		"elif [ \"$c\" -ge 65 ]; then i='\\357\\211\\201';"
		"elif [ \"$c\" -ge 40 ]; then i='\\357\\211\\202';"
		"elif [ \"$c\" -ge 15 ]; then i='\\357\\211\\203';"
		"else i='\\357\\211\\204'; fi;"
		"if [ \"$s\" = Charging ]; then b='\\357\\203\\247 ';"
		"else b=''; fi;"
		"printf '%b %b%s%%' \"$i\" \"$b\" \"$c\"" },
	{ run_command, "^bg(1a1a1a) %s ^bg() ",
		"st=$(cat /sys/class/net/wlo1/operstate 2>/dev/null); "
		"if [ \"$st\" != up ]; then printf '%b OFF' \"\\363\\260\\244\\257\"; "
		"else q=$(awk '/wlo1:/ {print int($3*100/70)}' /proc/net/wireless 2>/dev/null); "
		"e=$(iw dev wlo1 link 2>/dev/null | awk '/SSID:/ {sub(/^[ \\t]*SSID: /, \"\"); "
		"print}'); "
		"[ -z \"$q\" ] && q=0; "
		"if [ \"$q\" -ge 75 ]; then i=\"\\363\\260\\244\\250\"; "
		"elif [ \"$q\" -ge 50 ]; then i=\"\\363\\260\\244\\245\"; "
		"elif [ \"$q\" -ge 30 ]; then i=\"\\363\\260\\244\\242\"; "
		"else i=\"\\363\\260\\244\\237\"; fi; "
		"printf '%b %s%% %s' \"$i\" \"$q\" \"$e\"; "
		"fi" },
	{ run_command, 	"^bg(1a1a1a) %s ^bg() ",        "n=$(fcitx5-remote -n 2>/dev/null); case \"$n\" in *unikey*) echo VI;; *) echo EN;; esac" },
	{ datetime,    	"^bg(1a1a1a) %s ^bg()",         "%F %T" },
};
