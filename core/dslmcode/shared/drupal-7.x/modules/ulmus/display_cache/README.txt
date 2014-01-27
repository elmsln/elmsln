
-- SUMMARY --

The Display Cache module provides an alternative caching mechanism. The
rendered displays of entities will be cached permanent. The cache entry will be
flushed if the entity has changed. In this way no caching time has to elapse
before updates in entities are shown.

For a full description of the module, visit the project page:
  http://drupal.org/sandbox/Caseledde/1970904

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/1970904


-- REQUIREMENTS --

Entity API
  http://drupal.org/project/entity


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

* Configure user permissions in Administration » People » Permissions:

  - Administer Display Cache

    Grants the permission to administer display cache settings for displays and
    flush the display caches cache.

  Note that the menu items displayed in the administration menu depend on the
  actual permissions of the viewing user. For example, the "People" menu item
  is not displayed to a user who is not a member of a role with the "Administer
  users" permission.

* Customize the display cache settings for displays.

  - Call a display settings page. For example:
    Home » Administration » Structure » Content types » Article » Manage Display

  - Display Cache Display Settings
    Configure the caching method for this display.

  - Display Cache Field Settings
    Configure the caching mechanism for each field. You can only choose lower
    granularity than configured in Display Cache Display Settings.

* Flush Display Cache

  - Call Home » Administration » Configuration » Development » Display Cache
    and submit the form.
