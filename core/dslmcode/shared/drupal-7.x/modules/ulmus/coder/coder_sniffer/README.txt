-------------------------------------------------------------------------------
                            Drupal Code Sniffer
-------------------------------------------------------------------------------

Drupal Code Sniffer is a coding standard validation tool for Drupal and contributed
modules/themes.

Online documentation: https://drupal.org/node/1419980


Installation: PEAR
------------------

Requirements:
  - PEAR
  - PHPCS 1.4.1 or newer

- Install PEAR  ( http://pear.php.net/manual/en/installation.php )
- Install PHPCS ( http://pear.php.net/package/PHP_CodeSniffer )
- Sym-link the drupalcs directory into the standards folder for PHP_CodeSniffer.
  The code for that looks like this:

$> sudo ln -sv /path/to/coder/coder_sniffer/Drupal $(pear config-get php_dir)/PHP/CodeSniffer/Standards

Please see the online documentation for more detailed instructions:

  https://drupal.org/node/1419988


Installation: Drush
-------------------

While Coder Sniffer can be used as a standalone set of rules for PHP_CodeSniffer,
drush command support is included to facilitate ease of use, installation,
and leveraging of drush features such as site aliasing.

Extract the contents of the Coder project into one of the locations specified
in the drush README.txt COMMANDS section, such as the subdirectory of the
.drush folder in your home directory.  For other alternatives, please see
http://drupal.org/node/1419988


Installation: Composer
----------------------

You can also use Coder Sniffer as a library with Composer:

    "require": {
        "drupal/coder": "*"
    }

"composer install" will fetch all necessary dependencies and you can then use/execute
PHPCS locally in your project:

./vendor/bin/phpcs --standard=coder_sniffer/Drupal /path/to/code/to/review


Usage (running in a shell)
--------------------------

$> phpcs --standard=Drupal --extensions=php,module,inc,install,test,profile,theme /path/to/drupal_module

Usage (drush)
-------------

$> drush drupalcs sites/all/modules/custom

Working with Editors
--------------------
Drupal Code Sniffer can be used with various editors.

Editors:

eclipse: http://drupal.org/node/1420004
Komodo: http://drupal.org/node/1419996
Netbeans: http://drupal.org/node/1420008
Sublime Text: http://drupal.org/node/1419996
vim: http://drupal.org/node/1419996


Attention
---------
This is still a draft!!
Please cross check with http://drupal.org/coding-standards and
http://drupal.org/project/coder if the validation is correct

Known Issues:
Documentation Tags just rarly supported - there are many missing / disabled sniffs