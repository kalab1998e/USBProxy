#
# Copyright 2014 Dominic Spill
#
# This file is part of USBProxy.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#
# Based upon the hackrf/ubertooth cmake setup.

project(usbproxy_filters C)
set(PACKAGE usbproxy_filters)

include_directories(${libusbproxy_SOURCE_DIR})
LIST(APPEND PLUGINS_LINK_LIBS USBProxy)

LIST(APPEND PLUGINS PacketFilter_Callback PacketFilter_KeyLogger PacketFilter_ROT13 PacketFilter_UDPHID PacketFilter_MassStorage PacketFilter_Power PacketFilter_StreamLog)

find_package(PCAP)

if( ${PCAP_FOUND} )
	LIST(APPEND PLUGINS PacketFilter_PcapLogger)
	include_directories(${PCAP_INCLUDE_DIRS})
	LIST(APPEND PLUGINS_LINK_LIBS ${PCAP_LIBRARIES})
else( ${PCAP_FOUND} )
	if( USE_PCAP AND NOT ${PCAP_FOUND} )
		message( FATAL_ERROR
			"Cannot find libpcap, which is required for USE_PCAP")
	endif()
endif( ${PCAP_FOUND} )

foreach(plugin ${PLUGINS})
	add_library(${plugin} SHARED ${plugin}.cpp)
	set_source_files_properties(${plugin}.cpp PROPERTIES COMPILE_FLAGS  "-std=c++0x")
	set_target_properties(${plugin} PROPERTIES PREFIX "")
	target_link_libraries(${plugin} ${PLUGINS_LINK_LIBS})
	install(TARGETS ${plugin}
        LIBRARY DESTINATION lib/USBProxy${LIB_SUFFIX}
        COMPONENT sharedlibs
        )
endforeach(plugin)
