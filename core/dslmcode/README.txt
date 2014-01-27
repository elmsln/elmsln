This is the dslm, symlinked stack that feeds the drupal sites for all of ELMSLN.  This is a very untraditional way of structuring a drupal “site” that’s been crafted based on patches and ideas from drupal.org/project/dslm.  Colorado University uses this technique to keep the management of 100s of sites sane.

Benefits of this approach:
- more developer friendly in contributing and managing drupal sites
- support for multi-site, multi-core instance the ELMSLN calls for
- APC is happier as its only caching 1 copy of a lot of files
- tar / backup / downloading of individual stacks / sites still possible
- easier upgrades of Drupal core as well as “core above core” module sets
- easier distribution management
- more straight forward git integration

This plugs into the way that elmsln-build.sh and the drupal-create-site scripts work with the server to ensure that things show up where they should.  The end result are drupal sites that drupal thinks are structured the same as any other site but are far easier to manage at scale.

We are… Singularity
