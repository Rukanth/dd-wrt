dhcpforwarder:
	cd dhcpforwarder && ./configure --host=$(ARCH)-linux-elf --sysconfdir=/tmp/dhcp-fwd CC=$(ARCH)-linux-uclibc-gcc CFLAGS="$(COPTS) -DHAVE_MALLOC=1 -Drpl_malloc=malloc" 
	$(MAKE) -C dhcpforwarder

dhcpforwarder-install:
	#install -D dhcpforwarder/dhcp-fwd $(INSTALLDIR)/dhcpforwarder/usr/sbin/dhcp-fwd
	#$(STRIP) $(INSTALLDIR)/dhcpforwarder/usr/sbin/dhcp-fwd
	@true
	
dhcpforwarder-clean:
	$(MAKE) -C dhcpforwarder clean