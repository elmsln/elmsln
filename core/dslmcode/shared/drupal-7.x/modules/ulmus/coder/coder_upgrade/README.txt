
CONTENTS OF THIS FILE
---------------------

 * Author
 * Description
 * Installation
 * Dependencies
 * Developers

AUTHOR
------
Jim Berry ("solotandem", http://drupal.org/user/240748)

DESCRIPTION
-----------
This module provides upgrade routines to modify a source code file for changes
to the Drupal core APIs. Currently, the module provides routines for an upgrade
from Drupal 6 to 7.

This module utilizes the Grammar Parser library to modify source code in a
precise and programmatic fashion. The module utilizes the familiar Drupal hook
system to invoke upgrade routines, allowing other modules to enhance or modify
a routine.

Contributed modules that define an API can develop upgrade routines that would
enable other contributed modules relying on that API to upgrade their code.

INSTALLATION
------------
To use this module, install it in a modules directory. See
http://drupal.org/node/895232 for further information.

The included Drush Make file provides a convenient method of downloading and
installing the correct version of the Grammar Parser Library (>=1) dependency.
This project has a short name of "grammar_parser_lib" while the module name is
"gplib." The latter name is included in the .info file. From a command line,
simply invoke:

  drush make coder_upgrade.make

DEPENDENCIES
------------
While the Grammar Parser Library is the only dependency for this module, the
latter has two dependencies: the Libraries API module and the Grammar Parser
"library." All of these dependencies may be easily downloaded and installed
using the Drush Make file included with this project. Otherwise please refer to
the README files of those projects for installation instructions.

DEVELOPERS
----------
In the event of issues with the upgrade routines, debug output may be enabled on
the settings page of this module. It is recommended to enable this only with
smaller files that include the code causing an issue.
