Common developer questions are being added here as a catch all currently. If you have any [please check the issue queue](https://github.com/btopro/elmsln/issues) or [create a new issue](https://github.com/btopro/elmsln/issues/new) and the community will get back to you asap.

## From the issue queue
* [Adding new modules](https://github.com/btopro/elmsln/issues/49)
* [Unable to access added services](https://github.com/btopro/elmsln/issues/48)
* [What is a course?](https://github.com/btopro/elmsln/wiki/Information-Architecture)
* [What am I looking at after a new installation of ELMSLN?](https://github.com/btopro/elmsln/issues/46)
* [CIS - where is the campus list being pulled from?](https://github.com/btopro/elmsln/issues/64)

## From emails
### How can I get the current 'section_id' of a user in code?
There's a function called `_cis_connector_section_context()` which acts similar to the og_context to provide an ID associated with the user based on what they are currently viewing. This lets you know a user is in section "ABC-123" as opposed to another one. This information can be used to act on showing different data based on section in a course or pulling additional details from CIS / other systems that is relevant to that group.

### We're moving hosting from where we started building, what urls need updated
There's 3 places addresses get hard-coded into ELMSLN to keep the web services transactions happy. The first is at time of deployment when the registry keychain is created. This can be found in `/var/www/elmsln/config/shared/drupal-7.x/modules/_elmsln_scripted`'s .module file and has links to all the services in the network.

After that, you'll want to issue `drush @online cis-sync-reg` which will sync the database with some of these values that it stores locally for caching purposes.  Lastly, any services that were created (like courses.elmsln.dev/sing100) will need to have their settings.php files modified to reflect the new domain. This is stored in the `$base_url` variable. Another strategy is to edit the file in `/var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php` to do an overwrite of the different urls if you are passing them around a lot.

### When I look at the System Setup, it looks like you can't change the method of access once it's been created. Is that correct?
If you go into the course in question you can change the permissions to match what you're looking for. These routines are for when the systems are stamped out initially, it's in the roadmap to have jobs retroactively update the systems to keep in sync with the level of access set in CIS. This is a known issue and is marked in https://github.com/btopro/elmsln/issues/71