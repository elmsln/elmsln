ELMSLN comes with a function to organically find and upgrade your sites whenever new code is released. You as the developer still choose to run the update and you absolutely should do testing before executing one of these upgrades as they are extensive. The command to run though is available via leafy, our command line agent.
`leafy`

Look through the options available and select `upgrade the ELMSLN code base and system`. This will prompt you for a branch and to verify you want to run the update. It will then update its own code, and then start to apply needed drupal updates to all sites it finds to work against the version of the code just pulled down.

If you don't want it to upgrade its own code and instead apply updates to systems already on the server, you can issue the command below it in the list which will just upgrade the sites and not run through the code update.

Though before doing so you should always refresh your drush config with the following (if not running the mega upgrade system command):
`bash /var/www/elmsln/scripts/upgrade/refresh-drush-config.sh`

## Apply server upgrades
Server level upgrades run through advanced bash scripts that bring you on par with the rest of what we’re running. These updates are different from the system upgrade in that it’s upgrading the drupal sites. To run these bash based updates to ensure you’re getting the latest infrastructure updates select `apply server level upgrades (can not be undone)`.

## Example step-by-step guide

### 1. First thing you may want to get the most recent version of ELMSLN available by executing the code below:

  `cd ~/elmsln/`
 
  `git checkout tags/TAG NUMBER`  (  or  `git pull original master` )
 
### 2. For those who isn't yet familiar to Git: if you get Git error message like ` error: Your local changes to the following files would be overwritten by merge: ` , you may want to execute the following

  `git fetch --all` 

  `git reset --hard origin/master`
 
and repeat `git pull original master` swapping out `master` for whatever branch you are using.
 
### 3. At this stage you should get a status message like this one:
  
  `Current version of codebase: XXX`
  `Current version of your system: YYY`
     
Assuming XXX and YYY are different and YYY is older. Now please run
  
  `leafy`
  
and select an approptiate option, at the time it was written (Oct 2017) it is usually 
 
  `2 (upgrade the ELMSLN code base and system)` or `9 ( apply server level upgrades (can not be undone))` or `3 (upgrade just the drupal sites) `
 
### 4. If you still get an outdated Drupal module warnings, you may want to run an extra 
 
  ` drush @elmsln rr --y `
  ` drush @elmsln updb --y `
 
### A note from the core team for Drush users.  
 
Never. and I mean NEVER, run drush @online up unless you are planning on being out of sync with the rest of the project. ELMS:LN while Drupal based, places modules in different locations for better performance and developer experience across the many systems involved. `updb` is fine, we run database layer updates all the time. code updates should happen via `git` and not via direct drush `up` commands.
