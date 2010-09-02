/*
 * sysinit-pb42.c
 *
 * Copyright (C) 2006 Sebastian Gottschall <gottschall@dd-wrt.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id:
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <syslog.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <sys/klog.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <sys/reboot.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

#include <bcmnvram.h>
#include <shutils.h>
#include <utils.h>
#include <cymac.h>
#define SIOCGMIIREG	0x8948	/* Read MII PHY register.  */
#define SIOCSMIIREG	0x8949	/* Write MII PHY register.  */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/sockios.h>
#include <linux/mii.h>
#include "devices/wireless.c"

void start_sysinit(void)
{
	time_t tm = 0;

	if (!nvram_match("disable_watchdog", "1"))
		eval("watchdog");
	/*
	 * Setup console 
	 */

	cprintf("sysinit() klogctl\n");
	klogctl(8, NULL, atoi(nvram_safe_get("console_loglevel")));
	cprintf("sysinit() get router\n");


	/*
	 * network drivers 
	 */
	fprintf(stderr, "load ATH Ethernet Driver\n");
	insmod("ag7100_mod");

	FILE *fp = fopen("/dev/mtdblock/7", "r");
	if (fp) {
		fseek(fp, 0x7f1000, SEEK_SET);
		unsigned char buf[16];
		fread(&buf[0], 6, 1, fp);
		char mac[16];
		int i;
		unsigned int copy[16];
		for (i = 0; i < 12; i++)
			copy[i] = buf[i] & 0xff;
		sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X", copy[0],
			copy[1], copy[2], copy[3], copy[4], copy[5]);
		fprintf(stderr, "configure ETH0 to %s\n", mac);
		nvram_set("et0macaddr_safe", mac);
		eval("ifconfig", "eth0", "hw", "ether", mac);
		fread(&buf[6], 6, 1, fp);
		for (i = 0; i < 12; i++)
			copy[i] = buf[i] & 0xff;
		sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X", copy[6],
			copy[7], copy[8], copy[9], copy[10], copy[11]);
		fprintf(stderr, "configure ETH1 to %s\n", mac);
		eval("ifconfig", "eth1", "hw", "ether", mac);

		fclose(fp);
	}

	// no mac found, use default
//      eval("ifconfig", "eth0", "hw", "ether", "00:15:6D:FE:00:00");
//      eval("ifconfig", "eth1", "hw", "ether", "00:15:6D:FE:00:01");

//#endif
	eval("ifconfig", "eth0", "up");
	eval("ifconfig", "eth1", "up");
	struct ifreq ifr;
	int s;

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))) {
		char eabuf[32];

		strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);
		ioctl(s, SIOCGIFHWADDR, &ifr);
		nvram_set("et0macaddr",
			  ether_etoa((unsigned char *)ifr.ifr_hwaddr.sa_data,
				     eabuf));
		nvram_set("et0macaddr_safe",
			  ether_etoa((unsigned char *)ifr.ifr_hwaddr.sa_data,
				     eabuf));
		close(s);
	}

	detect_wireless_devices();
#ifndef HAVE_ALFAAP94
	system2("echo 5 >/proc/sys/dev/wifi0/ledpin");
	system2("echo 1 >/proc/sys/dev/wifi0/softled");
	system2("echo 4 >/proc/sys/dev/wifi0/ledpin");
	system2("echo 1 >/proc/sys/dev/wifi0/softled");
	system2("echo 3 >/proc/sys/dev/wifi0/ledpin");
	system2("echo 1 >/proc/sys/dev/wifi0/softled");
#else
	led_control(LED_POWER, LED_ON);

#endif
	/*
	 * Set a sane date 
	 */
	stime(&tm);
	nvram_set("wl0_ifname", "ath0");

	return;
	cprintf("done\n");
}

int check_cfe_nv(void)
{
	nvram_set("portprio_support", "0");
	return 0;
}

int check_pmon_nv(void)
{
	return 0;
}

void start_overclocking(void)
{
}

char *enable_dtag_vlan(int enable)
{
	return "eth0";
}
