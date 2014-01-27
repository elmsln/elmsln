ELMSLN Package

This is the entire ELMS Learning Network as a stack.  It includes installation instructions for getting it stood up on your server as well as multiple git repositories for optimal management.

FAQ
Q. Should I update Drupal modules?
A. Anything that’s included in the enclosed core directory should not be updated outside of the schedule of updating versions of the code from the github repository.  This is to ensure that all sites function properly after upgrades.  This package will be updated on versions once they are tested, any modules that you install in your config directory is on you to manage.  The general rule in Drupal is don’t have core and the same is true with ELMSLN, don’t hack ELMSLN core; apply all your changes you want inside the config directory.

Q. Why doesn’t this look like Drupal?
A. Because it’s Drupal and other packages setup in an optimal format for a network of deployed distributions.  Everything is setup in a manner that has flexibility, sustainability and long term system growth in mind.  It’s using a patched version of a drush extension called DSLM to help manage the symlinks between items but it’s heavily symlinked.  This helps optimize APC as well as make it maintainable for a single person to manage 100s of sites with similar code pushes.

Q. How can I get more involved?
A. Ask, jump in on the issue queues on github, drupal.org, or anywhere else that you can find pieces that will help build upon this work.