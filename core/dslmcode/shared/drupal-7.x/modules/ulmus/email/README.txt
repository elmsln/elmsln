***********
* README: *
***********

DESCRIPTION:
------------
This module provides an email field type.


INSTALLATION:
-------------
1. Place the entire email directory into your Drupal sites/all/modules/
   directory.

2. Enable the email module by navigating to:

     administer > modules


Features:
---------
  * validation of emails
  * turns addresses into mailto links
  * encryption of email addresses with
      o Invisimail (Drupal 5 + 6) (module needs to be installed)
      o SpamSpan (Drupal 6 only) (module needs to be installed)
  * contact form (see Display settings)
  * provides Tokens
  * exposes fields to Views


Note:
-----
To enable encryption of contact form, see settings under the Display fields tabs 


Author:
-------
Matthias Hutterer
mh86@drupal.org
m_hutterer@hotmail.com