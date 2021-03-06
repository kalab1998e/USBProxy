USBProxy
========

Status
------
This project is in the very early stages (alpha), it should be assumed that it
is currently non-functional. In fact, there are many occasions on which git
head doesn't even compile.

Build
-----
Dependencies:
```
sudo apt-get install build-essential cmake
```
Build:
```
mkdir src/build
cd src/build
cmake ..
make
sudo make install
sudo ldconfig
```

If you want to try out the PCAP logger you will need to install libPCAP
headers:
```
sudo apt-get install libpcap-dev
```

Running the tool
----------------
The best way to get started with USBProxy is by trying it out. Connect a device
to the BeagleBone Black and connect the BBB to a host system. Then try running
the following to view packets in real time as they are sent between your device
and host.
```
usb-mitm -l
```

If you have a USB keyboard, try running the following to act as a keylogger:
```
usb-mitm -k
```

What?
-----
A USB man in the middle device using the BeagleBone Black hardware.

Why?
----
Other USB sniffers exist, but I really like the BeagleBone Black as a hardware
platform and I wanted to tinker with the USB device side.  There was also an
article on Hack a Day about sniffing USB with the BeagleBoard-xM, but on further
inspection, it would only build against a relatively old kernel version.

ToDo
----
 * Support alternative chipsets - gadgetfs should take care of this (ish)
 * Clean up code - check return values, etc

License
-------
All files should have a license displayed at the start of the file.  Any code
that we have written is released under the GPL v3 license.

FAQ
---
Q. I need support!

A. Me too buddy, me too.  Let's hug it out.  Your best chance of getting
support is to contact me on IRC (#USBProxy on freenode.net), raise an issue on
GitHub or email me directly.

Q. How is this different to using usbmon on the host?

A. It isn't.  Although there are situations where you may not be able to access
the code running on the host system; for example, when reverse engineering USB
devices for use with closed platforms.

Q. Isn't the Beagle already a USB monitor?

A. The Total Phase Beagle USB monitors are excellent devices for sniffing and
debugging USB connections, in fact, one was used by "AlexP" to reverse engineer
the Microsoft Kinect.  However, they are completely unrelated to the BeagleBone
Black devices produced by TI, which are open source single board computer
systems.  The BeagleBone Black is the intended target device for this software.
