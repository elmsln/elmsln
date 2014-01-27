
-- SUMMARY --

This is a standalone script developed by sun (http://drupal.org/user/54136) that
only concentrates on re-formatting code and style review.

Coder Format alters source code files directly. Although this script is
state-of-the-art, be sure to backup your source files in front of executing this
script. If executed on a directory, the script automatically creates backup
copies of all changed files.

This is an alternative approach to the Coder module. Having two different
modules with different approaches is in some ways an advantage, since each
becomes - in effect - a unit test upon the other. This is a great way for them
to both improve, and maintain accuracy in what is a very detail oriented area!

See http://drupal.org/node/126938.


-- REQUIREMENTS --

* PHP command line interpreter.
* Path to includes/file.inc of a Drupal core codebase.


-- USAGE --

See coder_format.php.


-- INSTALLATION (WINDOWS) --

Coder Format provides a Windows Explorer context menu extension that allows you
to run Coder Format on single PHP files or complete directory trees.

WARNING: Do not proceed unless you know what you are doing!

- Copy all files of this directory to a central location. If you like to,
  c:\program files\coder_format\ is okay, too.

- Open coder_format.reg in your preferred editor and replace all instances of

  c:\\program files\\coder_format

  with the path of your chosen central location. Be sure to escape backslashes
  with another backslash (as shown above).

- "Merge" coder_format.reg into your Windows Registry using the "Merge" command
  in the context menu.

- Open coder_format.cmd in your preferred editor and replace the path in
  
  set coderFormatPath=c:\program files\coder_format

  with the path of your chosen central location. Afterwards, adjust the location
  of file.inc in

  set fileInc=c:\program files\coder_format\file.inc

  according to your local Drupal installation, i.e.

  set fileInc=c:\inetpub\www\path\to\drupal\includes\file.inc

  It is also possible to copy file.inc from a Drupal 5 installation to the
  central location and adjust the path accordingly.

- Done. Context menus of PHP files and directories should include the following
  commands now:

  - Clean Coding Style...
  - Unclean Coding Style... (directories only)


-- CONTACT --

Current maintainers:
* Daniel F. Kudwien (sun) - dev@unleashedmind.com

This project has been sponsored by:
* UNLEASHED MIND
  Specialized in consulting and planning of Drupal powered sites, UNLEASHED
  MIND offers installation, development, theming, customization, and hosting
  to get you started. Visit http://www.unleashedmind.com for more information.

