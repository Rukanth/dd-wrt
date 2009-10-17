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

void start_sysinit(void)
{
	struct utsname name;
	time_t tm = 0;

	unlink("/etc/nvram/.lock");
	cprintf("sysinit() proc\n");
	/*
	 * /proc 
	 */
	mount("proc", "/proc", "proc", MS_MGC_VAL, NULL);
	mount("sysfs", "/sys", "sysfs", MS_MGC_VAL, NULL);
	cprintf("sysinit() tmp\n");

	/*
	 * /tmp 
	 */
	mount("ramfs", "/tmp", "ramfs", MS_MGC_VAL, NULL);
	// fix for linux kernel 2.6
	mount("devpts", "/dev/pts", "devpts", MS_MGC_VAL, NULL);
	mount("devpts", "/proc/bus/usb", "usbfs", MS_MGC_VAL, NULL);
	eval("mkdir", "/tmp/www");
	eval("mknod", "/dev/nvram", "c", "229", "0");
	eval("mknod", "/dev/ppp", "c", "108", "0");

	unlink("/tmp/nvram/.lock");
	eval("mkdir", "/tmp/nvram");

	/*
	 * /var 
	 */
	mkdir("/tmp/var", 0777);
	mkdir("/var/lock", 0777);
	mkdir("/var/log", 0777);
	mkdir("/var/run", 0777);
	mkdir("/var/tmp", 0777);
	cprintf("sysinit() setup console\n");
	if (!nvram_match("disable_watchdog", "1"))
		eval("watchdog");
	/*
	 * Setup console 
	 */

	cprintf("sysinit() klogctl\n");
	klogctl(8, NULL, atoi(nvram_safe_get("console_loglevel")));
	cprintf("sysinit() get router\n");

	/*
	 * Modules 
	 */
	uname(&name);

	/*
	 * network drivers 
	 */
	insmod("ag7100_mod");
	// sleep(1);
	FILE *fp = fopen("/dev/mtdblock/7", "rb");
	unsigned char buf2[256];

#ifdef HAVE_RS
	fseek(fp, 0xfff000, SEEK_SET);
#else
	fseek(fp, 0x7ff000, SEEK_SET);
#endif
	fread(buf2, 256, 1, fp);
	fclose(fp);
	int i;
	int offsetmac1 = -1;
	int offsetmac2 = -1;
	unsigned int copy[256];

	for (i = 0; i < 256; i++)
		copy[i] = buf2[i] & 0xff;
	for (i = 0; i < 256 - 12; i++) {
		if (!strncmp(&buf2[i], "ar7100_esa", 10)) {
			offsetmac1 = i + 11;
		}
		if (!strncmp(&buf2[i], "ar7100_esa_2", 12)) {
			offsetmac2 = i + 13;
		}
	}
	if (offsetmac1 != -1) {
		char mac[32];

		sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
			copy[0 + offsetmac1], copy[1 + offsetmac1],
			copy[2 + offsetmac1], copy[3 + offsetmac1],
			copy[4 + offsetmac1], copy[5 + offsetmac1]);
		fprintf(stderr, "configure eth0 to %s\n", mac);
		eval("ifconfig", "eth0", "hw", "ether", mac);
		/*
		 * Right now the routerstation has no on-board mac stored for the secondary interface (LAN)
		 * to solve this i advised UBNT to use "ar7100_esa_2" as future redboot parameter for the secondary mac address
		 * if this parameter exists, we will take it as secondary mac, if not we increase the primary mac by 1
		 * consider that if you feel you have problems with mac conflicts using multiple routerstations, add this secondary parameter to redboot
		 * this should only happen, if you connect the wan port of a routerstation to the lan port of another one and if these routerstation are 
		 * from the same production batch 
		 * 
		 */
		if (offsetmac2 != -1) {
			sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
				copy[0 + offsetmac2], copy[1 + offsetmac2],
				copy[2 + offsetmac2], copy[3 + offsetmac2],
				copy[4 + offsetmac2], copy[5 + offsetmac2]);
		} else {
			MAC_ADD(mac);
		}
		fprintf(stderr, "configure eth1 to %s\n", mac);
		eval("ifconfig", "eth1", "hw", "ether", mac);
	}

	fp = fopen("/dev/mtdblock/0", "r");
	if (fp) {
		fseek(fp, 0x1f800, SEEK_SET);
		unsigned int signature;

		fread(&signature, 4, 1, fp);
		if (signature == 0x20021103) {
			fprintf(stderr, "Compex WP543 detected\n");
			eval("ifconfig", "eth0", "0.0.0.0", "down");
			eval("ifconfig", "eth1", "0.0.0.0", "down");
			unsigned char buf[16];

			fseek(fp, 0x1f810, SEEK_SET);
			fread(&buf[0], 6, 1, fp);
			char mac[16];
			int i;

			unsigned int copy[16];

			for (i = 0; i < 12; i++)
				copy[i] = buf[i] & 0xff;

			sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X", copy[0],
				copy[1], copy[2], copy[3], copy[4], copy[5]);
			fprintf(stderr, "configure ETH0 to %s\n", mac);
			nvram_set("et0macaddr_safe",mac);
			eval("ifconfig", "eth0", "hw", "ether", mac);
			fseek(fp, 0x1f818, SEEK_SET);
			fread(&buf[6], 6, 1, fp);
			for (i = 0; i < 12; i++)
				copy[i] = buf[i] & 0xff;
			sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X", copy[6],
				copy[7], copy[8], copy[9], copy[10], copy[11]);
			fprintf(stderr, "configure ETH1 to %s\n", mac);
			eval("ifconfig", "eth1", "hw", "ether", mac);
			/* disable led's */
			eval("gpio","enable","3"); // 1
			eval("gpio","enable","4"); // 2
			eval("gpio","enable","5"); //wlan
			eval("gpio","enable","6"); //conn
			eval("gpio","enable","7"); //diag


		}
		fclose(fp);
	}




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

	insmod("ath_hal");
	if (nvram_get("rate_control") != NULL) {
		char rate[64];

		sprintf(rate, "ratectl=%s", nvram_safe_get("rate_control"));
		eval("insmod", "ath_pci", rate);
	} else {
		insmod("ath_pci");
	}
	// insmod("ath_mimo_pci");

#ifdef HAVE_RS
	system2("echo 2 >/proc/sys/dev/wifi0/ledpin");
	system2("echo 1 >/proc/sys/dev/wifi0/softled");
	system2("echo 2 >/proc/sys/dev/wifi1/ledpin");
	system2("echo 1 >/proc/sys/dev/wifi1/softled");
	system2("echo 2 >/proc/sys/dev/wifi2/ledpin");
	system2("echo 1 >/proc/sys/dev/wifi2/softled");
#elif HAVE_WP543
	system2("echo 5 >/proc/sys/dev/wifi0/ledpin");
	system2("echo 1 >/proc/sys/dev/wifi0/softled");
#else
	system2("echo 2 >/proc/sys/dev/wifi0/ledpin");
	system2("echo 1 >/proc/sys/dev/wifi0/softled");
#endif
	insmod("ipv6");

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
