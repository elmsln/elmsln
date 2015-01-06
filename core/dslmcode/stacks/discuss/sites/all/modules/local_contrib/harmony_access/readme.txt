Harmony Access provides an access layer (currently no UI) to Harmony Core so that access can be restricted to threads.

Within this module is the submodule Harmony Access OG which provides integration with Organic Groups Access so that threads can belong to private Organic Groups.

Harmony Access works by jumping in when queries (including Views) are tagged with “harmony_access”. In certain cases you may want to bypass this for all users, you can do this by adding a further tag “harmony_access_bypass”.

Modules to check out:

Harmony Forum Access - Restrict access to threads by Category Taxonomy.
https://www.drupal.org/project/harmony_forum_access