Under Linux, the RTKLIB programsnding store their configuration in
$HOME/.<executable_filename>.conf

The location and name of the configuration file may be overridden via 
the -i switch on the command line.

In the GUI programs (ones with "_qt" at the end or their names, the 
.conf file is normally created on exit whenever the program state 
is changed via command inputs, changing window size, etc., and is
automatically read upon program startup.

If you wish to run multiple instances of a program, you can do so by
manually editing and renaming the .conf file, then using the -i switch
at runtime.  However, you can also store independent configurations  by
copying the executable with a different name.  For example, if you wish 
to run two instances of rtknavi_qt, making a copy named "rtknavi_qt-2" 
will create $HOME/.rtlnavi_qt-2.conf which will be read when that copy 
of the program is executed.

SPECIAL NOTE ABOUT rtknavi_qt:
This program has two independent and incompatible configuration mechanisms.  

First, it will create and update a .conf file as described above.

Second, "Options" dialog buttons allow saving and loading an options
file.  The files created by Options/Save and read by Options/Load 
ARE NOT COMPATIBLE WITH THE AUTOMATICALLY GENERATED .CONF FILES 
DESCRIBED ABOVE.  Files created with Options/Save can ONLY be
read via Options/Load.

The -i command line switch in rtknavi_qt works only with .conf files
automatically created by the program.  It WILL NOT read files created with
Options/Save.
