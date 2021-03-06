/*
 * Copyright 2014 Dominic Spill
 * Copyright 2014 Jahmel Harris
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
#ifndef USBPROXY_PLUGIN_MANAGER_H
#define USBPROXY_PLUGIN_MANAGER_H

#include <vector>
#include <unordered_map>
#include <string>

#include "DeviceProxy.h"
#include "HostProxy.h"
#include "PacketFilter.h"
#include "Injector.h"

/* Expand this list as needed */
enum plugin_manager_error {
	PLUGIN_MANAGER_SUCCESS = 0,
	PLUGIN_MANAGER_UNKNOWN_ERROR = 1,
	PLUGIN_MANAGER_CANNOT_FIND_FILE = 2
};

class PluginManager
{
	private:
		std::vector<void*> handleList;
		void *load_shared_lib(std::string plugin_name);

	public:
		/* These should have getter/setters */
		DeviceProxy* device_proxy;
		HostProxy* host_proxy;
		std::vector<PacketFilter*> filters;
		std::vector<Injector*> injectors;
		
		PluginManager(){};
		int load_plugins(ConfigParser *cfg);
		void destroy_plugins();
	
};
#endif /* USBPROXY_PLUGIN_MANAGER_H */
