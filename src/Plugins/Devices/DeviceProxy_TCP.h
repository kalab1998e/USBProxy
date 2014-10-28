/*
 * Copyright 2013 Dominic Spill
 * Copyright 2013 Adam Stasiak
 *
 * This file is part of USBProxy.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 *
 * DeviceProxy_TCP.h
 *
 * Created on: Dec 12, 2013
 */

#ifndef USBPROXY_DEVICEPROXY_TCP_H
#define USBPROXY_DEVICEPROXY_TCP_H

#include "DeviceProxy.h"
#include "TCP_Helper.h"

class DeviceProxy_TCP:public DeviceProxy {
private:
	bool p_is_connected;
	TCP_Helper* network;

public:
	static int debugLevel;
	DeviceProxy_TCP(const char* address=NULL);
	DeviceProxy_TCP(ConfigParser *cfg);
	~DeviceProxy_TCP();

	int connect(int timeout=250);
	void disconnect();
	void reset();
	bool is_connected();
	bool is_highspeed();

	int control_request(const usb_ctrlrequest *setup_packet, int *nbytes, __u8 *dataptr, int timeout=500);
	void send_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8* dataptr,int length);
	void receive_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8** dataptr, int* length,int timeout=500);

	void setConfig(Configuration* fs_cfg,Configuration* hs_cfg,bool hs);

	int claim_interface(__u8 interface);
	int release_interface(__u8 interface);

	// wrote 20141017 atsumi@aizulab.com
	// for Initial setting
	int get_configuration() {};
	int set_configuration(__u8 index) {};

	__u8 get_address();
	char* toString() {return (char *) "TCP device proxy";}
};

#endif /* USBPROXY_DEVICEPROXY_TCP_H */
