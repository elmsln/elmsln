## How do you manage this project?
We've had questions about this in the past, as a result we wanted to document it as it is a very complex project with a unique packaging structure. This answers how university developers are able to manage this project at scale internally while contributing 100% of the code out into the open, while still doing it securely.
## Branch management
We use multiple branches with 1 repo because our project is public and we mirror the repo internally and sync against that. This allows the public version to run ahead of what PSU uses while also ensuring greater security as to the validity of the git repo source (were github to somehow get hacked).
## Testing builds
We use travis CI (seen here http://travis-ci.org/elmsln/elmsln ) to automatically test builds per commit. We generally work in 1 branch unless exploring major functionality changes. We also work on a 'fork' and pull-request mentality for junior devs to be able to participate but not be able to touch the main branch.
## Development workflow
For dev / stage / prod; we have Vagrant for pure dev and have no merged development server (it's always distributed). As we have build scripts that setup our system and pull from the latest code repo, we can ensure with a reasonable sense of accuracy that:
- If travis said the commit was good, it will build
- If local vagrant instance builds, it will build
- If staging accepts the new code and doesn't get angry, it will work

Once we've got these assurances we'll pull a random site down into our staging instance (mind you we have 250+ sites running very similar installation profiles so if it fails in 1 place it isn't going to work else where, if it works one place we're again got a high degree of confidence it just works).

We are working on increasing Behat and Simpletest test coverage for additional code quality assurance. We also use the following pre-commit script (https://github.com/elmsln/elmsln/blob/master/scripts/git/pre-commit.sh) in order ensure that no development statements leak into the project and that all PHP code added to the repo has valid syntax (minor but incredibly useful in reducing gotchas).
## Jenkins
We use Jenkins to orchestrate deployments against the 8 or so ELMSLN instances at PSU as of this writing; including staging which again ensures it's going to play correctly with a reasonably high degree of confidence.
## Managing drupal contrib
As far as contrib, we patch and include them in the repo directly, then use a combination of Features and Drush recipes in order to deploy and play the result. What that might look like is a basic bash script (I hate provisioner formats, just another thing to learn for no real gain unless you start hitting replication and scale of replication but to each their own) that's something like `upgrade.sh`:
- Backup the code, back up the database
- Forcibly pull code in from repo of the production branch (for security but make sure .gitignores are flawless)
- drush rr -- rebuild registries (drupal.org/project/registry_rebuild)
- drush updb
- run drush recipe that plays the changes in question (recipe files are json,xml or yaml which can also live in version control).
- drush cc all
- drush hss node -- seeds caches (see https://www.drupal.org/project/httprl_spider)
All these scripts are packaged with the system if you check out the project repo (actually all the projects above are too) but the two in question that do the above are:
- https://github.com/elmsln/elmsln/blob/master/scripts/upgrade/elmsln-upgrade-system.sh -- tee up the upgrade of the code base
- https://github.com/elmsln/elmsln/blob/master/scripts/upgrade/elmsln-upgrade-sites.sh - loop through and play DRUP recipes (drush recipe upgrade) which is a special kind of recipe which uses timestamps in the name of the file to know which upgrades to play in the right order.
Here are some examples: https://github.com/elmsln/elmsln/tree/master/scripts/upgrade/drush_recipes/d7/global
