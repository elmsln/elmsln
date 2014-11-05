
WHAT THIS MODULE IS GOOD FOR
----------------------
This module can basically be useful in 2 ways:
1. For making your users passwords readable by admins.
2. As a very simple general purpose AES encryption API to use in other modules.

REQUIREMENTS
----------------------
This module requires an implementation of AES encryption to work. Since 1.4 there are two supported implementations:
1. PHP's Mcrypt extension.
2. PHP Secure Communications Library (phpseclib)

You need to have at least one of these installed (both is fine as well).
Mcrypt is a lot faster than phpseclib (about 60 times faster according to my unscientific testing), so you might want to use Mcrypt if you have it. But if you don't, then phpseclib is a great alternative, and the speed difference probably won't matter in most cases.

If you don't have any of them, then read the next section below.

As far as I can tell, this module also requires a PHP version of at least 4.3.0. However this module has not been tested on anything less 
than PHP 5.2.

Also note that although this module SHOULD work on Windows and with a MySQL database, it has only been tested on Linux with a PostgreSQL 
database.

HOW TO GET AN AES IMPLEMENTATION
----------------------
If you don't have an AES implementation (you'll notice this when you install this module) then the easiest implementation for you to get is probably the PHP Secure Communications Library (phpseclib).

Just download the latest version from http://phpseclib.sourceforge.net/ and extract it into a directory called "phpseclib" inside the aes directory. Note that the zip file of the version of phpseclib that this module was developed with doesn't create the phpseclib directory itself, it just extracts its various directories directly into the location you unzip it, so create that "phpseclib" directory first and then move the zip file into it, and unzip. The complete path to the file which will be included by this module (AES.php) should look like this:
aes/phpseclib/Crypt/AES.php

That's it! Try installing/enabling the module again.

This module was developed using phpseclib version 1.5, but hopefully future versions should work as well (and might contain security bug fixes, so always get the latest). If you've got a version of phpseclib that's newer than 1.5 and you're running into trouble, then please create an issue at drupal.org/project/aes

If you want to use the Mcrypt implementation instead then you can find information on how to install it here: http://php.net/mcrypt
Note that you most likely need to be running your own webserver in order to install Mcrypt. If you're on a shared host you'll probably have to ask your hosting provider to install Mcrypt for you (or use phpseclib instead).

ABOUT KEY STORAGE METHODS
----------------------
Something you should pay attention to (if you want any sort of security) is how you store your encryption key. You have the option of storing it in the database as a normal Drupal variable, this is also the default, but it's the default only because there is no good standard location to store it. Switching to a file-based storage is strongly encouraged since storing the key in the same database as your encrypted strings will sort of nullify the point of them being encrypted in the first place. Also make sure to set the permission on the keyfile to be as restrictive as possible, assuming you're on a unix-like system running apache, I recommend setting the ownership of the file to apache with the owner being the only one allowed to read and write to it (0600). Above all make sure that the file is not readable from the web! The easiest way to do that is probably to place it somewhere outside the webroot.

UPGRADING FROM 1.3 OR EARLIER
----------------------
If you're upgrading from an earlier version than 1.4, and don't want to change anything, then just stick with the Mcrypt implementation since that is the (only) implementation this module used in earlier versions. It should be selected as default when you install/upgrade (remember to run update.php).