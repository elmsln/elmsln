ELMSLN Drush plugins
=====================
These plugins help with development of ELMSLN. It includes a utility to correctly
download new modules into the correct locations in the shared config location, stacks as well as the ulmus global bucket. These serve as a replacement for drush dl as this command
won’t understand where to put the files in order to best optimize usage.

There’s also a plugin to help with the creation of new stacks (tools / domains) and
a related plugin to resync the libraries directory of a stack (in the event that you add
a new library to the shared libraries directory which gets symlinked in to all the other
tools).

