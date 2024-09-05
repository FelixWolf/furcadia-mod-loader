# Furcadia Mod Loader
Mod loader for Furcadia!

Some of those may remember Furnarchy back in the day. This is similar to that,
 as in it will hook into Furcadia.<br/>
The difference here is that instead of patching the executable, we use a method
 called DLL hijacking / forwarding. This works putting wsock32.dll in the
 Furcadia install directory, and then forwarding the wsock32 functions from the
 real module into our new module.<br/>
Our new module, while forwarding wsock32 functions, has additional features,
 that let us load additional plugins.

## How it (will) works
When the module is hooked into furcadia, it add the following commands:
* ``\`mod enable <name>`` - Load (if not already loaded) and enable a module
* ``\`mod disable <name>`` - Unload (if loaded) and disable a module
* ``\`mod load <name>`` - Load a module for the current session
* ``\`mod unload <name>`` - Unload a module for the current session
* ``\`mod reload <name>`` - Reload a module
* ``\`mod list`` - List modules (and show which ones are enabled)

This will load modules from `My Documents/Furcadia/plugins/`, which can also be
 changed by changing the `pluginlist.txt` file in this directory.

Modules can then do whatever they want to do by interacting with the endpoints
 created by the mod loader.

## (To be) Included modules
The mod loader will come with a few modules, including:
* `ctrl_a_fix.dll` - Switch around CTRL + A and CTRL + SHIFT + A, so that CTRL + A is select all, and CTRL + SHIFT + A is "Go to allegria".