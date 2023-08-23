# MATLAB Robot Code
This is the MATLAB robot code. It contains the necessary C code, the MATLAB generated C code and the MATLAB files.
This robot code is compatible with the java server.

## Acknowledgement and History
The MATLAB robot code is robot code controlled by MATLAB generated code C code. The MATLAB code is written by Magnus Isdal Kolbeinsen (2023) in his Master Thesis and specialization project (2022). It was a continuation project of Maria Gilje's project (2022). The motivation behind using MATLAB to generate C code is the ability to utilize higher level functions from MATLAB in creating complex functionality such as a control system.
The robot-application code is made by students at NTNU Gløshaugen.
## Key words/phrases

``robot-application`` is a folder with all the necessary software to run the MATLAB-robot. This includes student made motor drivers, communication modules and the MATLAB generated function "controllerApi".

``matlab-files`` contains the MATLAB files and the MATLAB generated function controllerApi.
 
## Bugs and Known Issues
* Connection with Java Server is known to be a bit unstable.

## User instructions

### Charging The Robot

1. Turn off the power switch on the side of the robot.
2. Turn on the charge switch on the side of the robot.
3. Remove the Wago clips from the black and red wires attached to the batteries.
4. Connect the 11.1V Smart Charger to the wires. Red connects to red and black to black.

### Project Code

nrf5 Software Development Kit (SDK) version 15.0.0 is needed to run the robot. The SDK can be found here:
```
https://www.nordicsemi.com/Products/Development-software/nRF5-SDK/Download?lang=en#infotabs
```

You would also have to download SoftDevices s140 version 6.0.0. This firmware can be found here:
```
https://www.nordicsemi.com/Products/Development-software/S140/Download?lang=en#infotabs
```

Development tools
1. Install VS code ``(https://code.visualstudio.com/download) `` (version 1.73.1 was used during this
project). It is also recommended to install the NRF connect extention for VS code. Very
useful tool for debugging.
1. Install GNU Make for windows ``(https://gnuwin32.sourceforge.net/packages/make.htm)``.
Make sure to add the bin to the environment variables: ”C:\Program Files (x86)\GnuWin32\bin”.
1. Install GNU ARM embedded Toolchain ``(https://developer.arm.com/tools-and-software/open-source-software/ ``
developer-tools/gnu-toolchain/gnu-rm/downloads).
1. Install NRF command line tools ``(https://www.nordicsemi.com/Software-and-tools/Development-Tools/
nRF-Command-Line-Tools/Download).``
Make sure to add the bin to the environment variables:”C:\Program Files (x86)\Nordic
Semiconductor\nrf-command-line-tools\bin”.

### Flashing the NRF52840
1. Move the SoftDevices folder ``s140_nrf52_6.0.0_API`` and nrf5 SDK folder into the same folder. Rename the sdk folder to ``nRF5SDK-root``.
2. Navigate to the ``nRF5SDK-root/examples/robot-application/`` folder with a terminal.
3. Type make to build the code. Make sure that the path in the makefile is correct.
4. Connect with USB to the short side of the NRF and type make flash to flash.

## Contributor Instructions
* Update *Key Words/Phrases* whenever new functionality has been added.
* Update *Bugs and Known Issues* if you discover any.
* Follow naming conventions from the wiki when making changes. 