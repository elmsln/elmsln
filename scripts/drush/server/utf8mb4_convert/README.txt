REQUIREMENTS
============

1. Ensure Drupal core 7.50 or later is installed, or the patch in
   https://www.drupal.org/node/2488180 is applied if using an earlier version.
2. Ensure the requirements listed in default.settings.php under the utf8mb4
   example related to innodb_large_prefix, MySQL server version and MySQL
   driver version are met.

INSTALLATION
============

1. Run "drush @none dl utf8mb4_convert-7.x" and drush will download it into your
   .drush folder. (Alternately, you can obtain the package another way and copy
   the folder into .drush yourself.)
2. Clear the Drush cache with "drush cc drush".

USAGE
=====

1. Make backups of your databases.
2. Run "drush utf8mb4-convert-databases"
3. Enable utf8mb4 in your settings.php.

NOTES
=====

The recommended collation "utf8mb4_general_ci" will work best for sites using a
Latin-1 character set, sites with non-Latin-1 character sets may wish to instead
use "utf8mb4_unicode_ci".

Only the default database will be converted. To convert other databases, use
arguments like "drush utf8mb4-convert-databases default site2 site3".

If tables should be excluded from conversion, run with an option like
"--exclude=users,sessions". Use with caution, all tables are expected to be
converted.
