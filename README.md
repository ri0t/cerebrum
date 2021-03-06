# Cerebrum

Cerebrum is a RPC-like protocol for calling C functions on AVRs from a host
application connected via serial port. Currently, the only viable host ist a
still incomplete python library. The line protocol is very simple. A short
description is in ```PROTOCOL```.  When a new device is connected, the host
pulls the device's exported functions and parameters via a standardized, special
function at address 0x0000.

## Build process

The device-side code is generated by a python script (```generate.py```) living
in the device directory according to a json configuration file passed to the
top-level build script (```generatefw.py```).

When the device firmware is built, a build config file containing information on
the actual ids of the callbacks and so on is generated. One copy is put in the
```builds/``` folder, another is lzma-compressed and hardcoded into the firmware
to be used by host libraries for device discovery.

## Adding Modules

More modules can be added in form of "module-name.c.tp" files in the respective
device directories (currently implemented are avr and msp430 versions). If
possible, when adding a new module generate.py should not be touched. These .tp
files are mako templates which will be included once for each time the module
is included in the device configuration ```.json```.

### Parameters

A parameter is defined with a format and a function id. The parameter has two
functions: a "getter" and a "setter" function. The getter can be found at the
function id in the parameter spec, to address the setter the id must be
incremented by 1. The getter takes no arguments and returns the current value of
the parameter. The setter takes the new value of the parameter as an argument.

### Format strings

The format strings are as used in the python ```struct``` module. Between host
and device, values are exchanged in binary form as marshaled by the
beforementioned python ```struct``` module according to the format strings given
for function parameters or return values. On the device side, the marshaling and
unmarshaling of the module names still is done by hand, the automation of that
is on the to-do list.

### Module support functions

There are a few python functions which can be used from module templates.

 * ```init_function()``` will be replaced by the unique name of an init function
   for this module instance that is automagically called on startup.
 * ```loop_function()``` will be replaced by the unique name of a loop funtion
   for this moduel that is called regularly (as often as the system finds time
   for it, at most each 100µs). 
 * ```modulevar(name, ctype, fmt, array)``` handles the definition and usage of
   module parameters. When called with ```name``` alone set it will return the
   an name for the named module parameter that is unique down to a module
   instance level. If ```ctype``` and ```fmt``` are also set, the parameter is
   automatically registered as such and getter and setter methods are generated.
    * ```ctype``` is the name of the c type used for this module parameter.
    * ```fmt``` is a string containing the python struct format specification
      string corresponding to the c type used for this module instance
      parameter.
    * ```array``` is an optional parameter which may be set to an integer to
      tell the code generator that this parameter is an array of size
      ```array```.
 * ```module_callback(name, argformat, retformat)``` registers a new module
   callback. This callback will appear in this module instance's ```functions```
   section in the build config. ```argformat``` and ```retformat``` are the
   python struct format strings for the callback's arguments and return value,
   respectively. They can be omitted. The callback is passed three arguments:
    * an uint16_t containing the offset of the current block of data
    * an uint16_t containing the size of the current block of data
    * an uint8_t* pointing to the next block of data
   If more data is sent to the function than ```ARGBUF_SIZE``` bytes (default:
   32), the callback is called repeatedly with increasing ```payload_offset```.

On top of that the templates can access pretty much all of python thanks to
mako.

For more details on the invocation of these helper functions please have a look
at the existing templates as well as the python code.
