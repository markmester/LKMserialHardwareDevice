# LKMserialHardwareDevice
A simple loadable kernal module for writing to a serial device. In this example, a usb-serial adapter on the host machine (windows) is mapped to a virtual machine (ubuntu). An LED is attached to the Tx and GND of the serial device and the kernel module is used to blink the device.

## Setup
1. Attach the usb-serial cable to the host machine and find which port it is mapped to (device manager > ports in windows)
2. On your virtual machine manager (virtualbox in my case), enable serial ports, and select the following options:
- Port Number: COM1
- Port Mode: Host Device
- Connect to existing pipe/socket: unchecked
- Path/Address: address of usb-serial device found in device manager
3. Boot up your VM and confirm the device was mapped by cat'ing /proc/ioports
4. Make and load the kernel module: ```make && make load```
