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
 */
#ifndef USBPROXY_DEVICEPROXY_H
#define USBPROXY_DEVICEPROXY_H

#include <linux/usb/ch9.h>
#include "Proxy.h"

class Configuration;

class DeviceProxy : public Proxy {
public:
	static const __u8 plugin_type=PLUGIN_DEVICEPROXY;
	
	virtual ~DeviceProxy() {}

	//return ETIMEDOUT if it times out
	virtual int connect(int timeout=250)=0;
	virtual void disconnect()=0;
	virtual void reset()=0;
	virtual bool is_connected()=0;

	virtual bool is_highspeed()=0;

	//return -1 to stall
	virtual int control_request(const usb_ctrlrequest *setup_packet, int *nbytes, __u8* dataptr,int timeout=500)=0;

	virtual void send_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8* dataptr,int length)=0;
	virtual bool send_wait_complete(__u8 endpoint,int timeout=500) {return true;}
	virtual void receive_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8** dataptr, int* length,int timeout=500)=0;
	virtual void setConfig(Configuration* fs_cfg,Configuration* hs_cfg,bool hs)=0;
	virtual char* toString() {return NULL;}

	virtual void claim_interface(__u8 interface)=0;
	virtual void release_interface(__u8 interface)=0;

	// wrote 20141017 atsumi@aizulab.com
	// for Initial setting
	virtual int get_configuration()=0;
	virtual int set_configuration(__u8 index)=0;

	virtual __u8 get_address()=0;
};

extern "C" {
	DeviceProxy *get_deviceproxy_plugin(ConfigParser *cfg);
	void destroy_plugin();
}
#endif /* USBPROXY_DEVICEPROXY_H */
