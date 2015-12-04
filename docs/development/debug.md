Debugging ELMSLN

## Some modules for debugging:
- devel - Drupal developer module, useful for digging into objects / code development
- cis_devel - Disables caching on all webservice calls as well as prints them to the screen so you can see what the response was. Useful when setting up new systems / complex calls.

## A buid failed / seems broken
Sometimes when working through integration issues or point release issues you could experience a drupal site in the network not being built correctly when requested. Here's steps to rebuild / give meaningful feedback to the development team / debug it yourself. Our test here will be called courses_tt_stuff as a new item in the courses stack called stuff
- Go into the database for courses_tt_stuff and delete all tables
- Go to ~/elmsln/config/stacks/courses/sites/courses/tt/stuff/settings.php and comment out the shared_settings requirement at the bottom
- go to http://courses.elmsln.local/stuff/install.php and run through the installer and see if it builds successfully / what the issue is (usually seen during install)
- If there was no issue there, look for the job file `~/elmsln/config/jobs/courses.stuff.processed` and copy the drush commands in this file.
- Append (in another text editor like sublime) @courses.stuff in after the drush command. Also place --y at the end of each command (this is effectively what the job runner is doing)
- run these and see if there are any errors in the output
