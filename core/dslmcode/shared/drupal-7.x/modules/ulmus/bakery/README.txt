Bakery module, for single sign-on between Drupal sites on the same domain.

In this README:
  * Bakery versions and compatibility
  * Installation and setup
  * How Bakery works
  * Notes on terminology
  * Common problems and support
  * Sharing account information using Bakery
  * Notes on registration/sign-in on subsites
  * Notes on migrating to Bakery
  * Known issues
  * Further information and support

Bakery versions and compatibility:
===========================================
This is the 2.x branch of the Bakery module for Drupal 7. The 2.x branch differs
mainly from the 1.x branch by offering slave site registration and login.

2.x versions between major branches of Drupal are compatible, meaning you can
run a Drupal 7 version of the 2.x branch of Bakery with a Drupal 6 version of
the 2.x branch. 1.x and 2.x branches are not compatible.

Installation and setup:
===========================================
Bakery provides single sign-on (SSO) functionality for two or more sites.
Deploy this module on the authoritative "master" Drupal server and the secondary
"slave" or subsite server. The master and slave must be on the same domain*.

Enable and configure Bakery on the master server first. It is recommended that
you use the UID 1 Drupal account for this configuration.

  1. Enable Bakery at admin/modules
  2. Visit admin/config/system/bakery to configure

This is the master site.

  3. Check the box for "Is this the master site?"
  4. Enter the full URL of this site, including ending forward slash
    - Example: http://example.org/

For SSO to work, Bakery must know the slave, or subsites, to use.

  5. Enter the full URLs of each slave site, separated by newlines
    - Example:  http://store.example.org/
                http://api.example.org/

Two other required fields for Bakery to work are the private key and the cookie
domain.

  6. Enter a long and secure private key
  7. Enter the domain to use for Bakery cookies. These cookies are shared so
      the domain should be the top level, with leading period.
    - Example: .example.org
  8. Save configuration (we'll come back to the other fields)

Now to enable and configure Bakery on the slave or subsite. If possible, you should
log in and use the UID 1 Drupal account for this configuration.

  9. Enable Bakery at admin/modules
  10. Visit admin/config/system/bakery to configure

This is a subsite site.

  11. Do not check the master site box
  12. Enter the full URL of the master site set in step #4
  13. The slave sites textarea can be left blank
  14. Enter the exact same private key set in step #6
  15. Enter the exact same domain set in step #7
  16. Save configuration (we'll come back to the other fields)

Bakery should now be set to work for the master and this slave site. Open a
different browser than the one you are currently using and visit the master
site. Log in with a standard account. Once successful visit the slave site and
confirm that you are also logged in. If you encountered problems at any point
please consult the section here labeled "Problems and support".

You can now enable and configure Bakery for sites in your network if required,
or read the section labeled "Sharing account information using Bakery".

* Master and slave must be on the same domain, but are not required to be at
certain levels. For example, you can have the master be sub.example.com and a
slave be example.com.

How Bakery works:
===========================================
Bakery provides single sign-on between Drupal sites on the same domain using a
shared cookie. When a user authenticates on a site they are sent a cookie by
Drupal, containing a unique identifier for that user. Sub-sequent requests by
that user will contain the identifier, allowing Drupal to recognize that the
request is coming from a specific user, an authenticated user. This process is
handled by Drupal core. Bakery augments the login process and sends an
additional cookie (referred internally to as the CHOCOLATECHIP cookie). Should
the user now visit a sub-site (on the same domain) their browser will send this
Bakery-created cookie. On the sub-site Bakery will recognize the cookie and if
it is valid will authenticate the user (via Drupal core's processes). The user
is now authenticated on both sites while only have to log on to one.

Notes on terminology:
===========================================
Bakery documentation and discussion makes repeated reference to the words
"master" and "slave". The terms stem from the common communication model between
devices or processes in computer systems where one has unidirectional control
over another. In Bakery's case, the master is the site with authoritative
account and authentication information. The master is occasionaly referred to as
the "main" site. The slave site can be referred to as the "subsite", but since
Bakery does not enforce top-level and sub-domains the term "subsite" may be
incorrect for some instances.

Common problems and support:
===========================================
  * Cannot log in, how do I disable Bakery?
    - If you do not have access to disable the Bakery module you'll need 
      access to the Drupal database for the site. To disable Bakery run this
      query: UPDATE system SET status = 0 WHERE name = 'bakery';
      After that you'll also need to clear caches.

Sharing account information using Bakery:
===========================================
A modest amount of account data sharing between Bakery-enabled sites is
supported. The core account fields 'name' and 'mail' are always synchronized.

The following fields from user accounts are optionally synchronized:
  * status
  * user picture
  * language
  * signature
  * timezone

Notes on registration/sign-in on subsites:
===========================================
This feature is important for usability. It's also really easy to configure your
site so that this feature is horrible for usability. A few examples:

Registration:
This feature does not support saving any data other than the username, e-mail 
address, and fields created with the core profile module. If you have other 
modules that modify the registration process to add fields or make the form
behave differently they are unlikely to work properly from the subsite. 

You should keep the "allow registration" and "Require e-mail verification when 
a visitor creates an account" settings the same on all sites. If your
master site disallows registration then no subsites will be allowed to create
accounts either and users will be confused why they see a form but it doesn't
work.

Notes on migrating to Bakery:
===========================================
Migrating to using Bakery can be a fairly simple process. This process will work
for separate sites and for a shared users table, though the latter can require a
few additional steps.

Pre-migration data synchronization is recommended to alleviate potential
account mis-matches. According to Bakery two accounts are in sync when the
username and email are identical and the slave account's init property contains
the URL of the user edit page on the master
(e.g. http://example.org/user/9/edit -- where example.org is the master). The
UID of the accounts do not need to be identical. It is recommended you at least
synchronize usernames and email address for accounts that belong to the same
person across sites.

For people that do not have joint accounts you could ask them via email to
create an account on the site where there account does not exist, to assist the
process.

For accounts that have the same username but different email addresses Bakery
provides a self-service mechanism for synchronizing accounts, but in the event
this is inadequate or confusing you should provide a site administrator contact
mechanism (form or email address) that is easily distinguishable.

In case there are duplicate accounts on one of the sites, the module
http://drupal.org/project/usermerge may help reconcile.

If you have a shared users table solution between sites you will need to remove
that connection before migrating to Bakery. First, populate the other users
tables by synchronizing accounts. Modify settings.php on the shared sites to
remove the table information from the database connection details. If the cookie
domain begins with a leading dot you probably want to remove it, as it could
cause issues when users move between sites.

Once synchronization is complete you can follow the steps listed above on
installation and setup of Baker.

Known issues:
===========================================
  * Values in profile fields exposed on the subsite that are not set on the
    master will not be saved.
  * Bakery is currently incompatible with a configuration that requires
    administrator approval of accounts. An account registered on the slave will
    not be set to blocked on the master.
  * Bakery is not compatible with modules that takeover core Drupal's login and
    registration forms, e.g. ldapprov.

Further information and support:
===========================================
Consult the online documentation at http://drupal.org/node/567410 for more
information.

Please use the public issue queue of Bakery for all bugs and feature requests:
http://drupal.org/project/issues/bakery
