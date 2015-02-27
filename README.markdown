Version | PHP | Includes | Code Status 
------------- | ------  | --- | -------------------------- | -----------
[master](https://travis-ci.org/btopro/elmsln)  | 5.3.0+ | Drupal 7.x, Piwik 2.x | [![Build Status](https://travis-ci.org/btopro/elmsln.svg?branch=master)](https://travis-ci.org/btopro/elmsln)

ELMSLN
==============
This is the ELMS Learning Network (ELMSLN) as a repository.  It includes installation instructions for getting it stood up on your server as well as multiple git repositories for optimal management downstream.

ELMSLN is a network based approach to educational technology design and implementation. The notion is that its no longer about the next products, it's that you will always be needing to produce and innovate in new products. This is a platform to spur innovation while providing an easy to use system that can be integrated into any existing institution.

Learn more about ELMSLN @ [elmsln.org](http://elmsln.org/)

FAQ
==============
###Q. How can I get more involved?
The easiest way is to setup an [ELMSLN Developer](http://github.com/btopro/elmsln-developer) envrionment and run [ELMSLN Vagrant](http://github.com/btopro/elmsln-vagrant). Test, ask, jump in on the issue queues on github, drupal.org, twitter, email, PHONE or anywhere else that you can find pieces that will help build upon this work. We always welcome more issue reports.

###Q. Why doesn’t this look like Drupal?
Because it’s Drupal and other packages setup in an optimal format for a network of deployed distributions. This is Drupal, we assure you. Think of it more as a "Drupal inside" then Drupal proper though. Everything is still done in a completely core compliant way, it's just structured to maximize needed efficencies of a heavily networked ecosystem (as well as being able to support low-resource environments).

Everything is setup in a manner that has flexibility, sustainability and long term system growth in mind. It’s using a patched version of a drush extension called DSLM to help manage the symlinks between items but it’s heavily symlink. This helps optimize APC as well as make it maintainable for a single person to manage 100s of sites with similar code pushes. the config directory also has all local changes (of any kind) symlinked from it. This allows for the ability to manage the entire ELMSLN deployment as 2 independent repos (1 that's this repo, another that's your own for configuration).

###Q. When will there be a stable release?
As soon as the blockers below are resolved (basically just time). If it helps you sleep at night, we've run this in production and have been actively building off of this framework since May 2013. The package is far more stable then the "master" moniker might otherwise suggest. Point releases require a different mindset from a developer / management perspective so we'll get there when the time is right.

Dec 24, 2014 - This time is fast approaching as the project is now a team of people distributed across institutions. There are 2 full time, 3 part time, and soon to be another 1-3 full time members involved.

Feb 16, 2015 - We will have a 0.1.0 release by March as the platform is starting to roll into production multiple places. From there we will release new verisons on a set interval, most likely every 2 weeks.

###Q. If that's true, what are the blockers for a 0.1 release?
1. An enhanced / unified UX; we have a dedicated UX lead working on this in the MOOC / CIS platforms. Once these two stabilize the rest will fall into place (UX wise, platform wise they have been solid since early 2013). <-- A [visual roadmap](https://projects.invisionapp.com/share/N21TGJ7QZ) has been established and work has begun on foundation_access to be rolled out across MOOC and other systems as the default starting point
2. https://github.com/btopro/elmsln/issues/25 (demo so we can show point releases)

###Q. How would you classify a first release?
Stable. master has been stable with 2 exceptions since Jan 2014. The branches outside of master are typically for major changes that require additional testing / development to race ahead of master. The many distributions of ELMS have been in usage for several months / years now. This ain't our first rodeo though we understand the desire for people to not be chasing the master branch.

###Q. Should I update Drupal modules?
Anything that’s included in the enclosed core directory should not be updated outside of the schedule of updating versions of the code from the github repository (unless you know what you are doing). There are a few projects patched so the best way to get projects upgraded to the latest version is to test it in a vagrant instance, report on it in an issue queue, and then let the ELMSLN community vet the module / theme upgrade.  Once this has happened then it will be rolled into the final package.

This is to ensure that all sites function properly after upgrades.  This package will be updated on versions once they are tested, any modules that you install in your config directory is on you to manage.  The general rule in Drupal is don’t hack core and the same is true with ELMSLN, don’t hack ELMSLN core; apply all your changes you want inside the config directory.

There is a drush edl function that can be used to place modules, drush plugins, themes, profiles, and copies of core in the correct location in the elmsln setup. If you are doing this though you probably are an active developer in the community (so that's awesome).

###Q. How do I run upgrade?
ELMSLN comes with a function to organically find and upgrade your sites whenever new code is released. You as the developer still choose to run the update and you absolutely should do testing before executing one of these upgrades as they are extensive. The command to run though is
bash scripts/upgrade/elmsln-upgrade-system.sh

This will prompt you for a branch and to verify you want to run the update. It will then update its own code, and then start to apply needed drupal updates to all sites it finds to work against the version of the code just pulled down.

###Q. config is empty, what do I put there?
There is an example config repo so you can see how to construct one and build from it. You can check that out here https://github.com/btopro/elmsln-config-example .

The Vagrant instance also has a config location that's managed on its own. Its only useful inside vagrant but if you want to see some ways you can add modules and change settings it's another good example: https://github.com/btopro/elmsln-config-vagrant/

###Q. Where can I add new modules / themes?
All changes should be made inside the config directory in a location that aligns with its counterpart in the core directory.  For example, to add a new module for use in all sites, you’ll want to place it in elmsln/config/shared/drupal-7.x/modules.  This is the same area for themes and libraries.

There’s also a settings/shared_settings.php file that has settings you want applied to all sites by default.  This is where your environmental staging overrides can go, or you can switch the cache bins used by default.  The version that ships with this has APC and file cache support automatically setup and tuned (but disabled).

Also make sure you never place an upgraded module in a different location from its default (such as updating views module by placing it in your config directory).  This will effectively WSOD / brick your site until you run drush rr against the sites that bricked. If you've run the elmsln-install.sh script included in this package, you'll have drush rr. You can repair this relationship then with drush @courses.bricked rr --y (for example).

###Q. Where should I point addresses?
The domains directory is structured in the optimal way for managing sites.  The domains directory is ignored below the initial directories inside of it, meaning that your sites that get written here automatically won’t be pushed through git or updated.  If you remove directories or change the way sites are managed in anyway inside this location, you’ll need to add that area to your .gitignore (or stop using the github version).

You can use this as a starting point and self manage from there but sticking as closely as possible to the structure of ELMSLN will help ensure upgrades down the road take correctly.

###Q. How awesome is it to try and solve the edtech spaces biggest problem every day you walk into work?
You have no idea and it is what attracts us to this work atmosphere. It rocks. Also who said anything about walking into work to solve these problems.. isn't it the weekend or late night or something right now?

Enjoy!

LICENSE
=======
ELMSLN is a collection of many, many projects, all individually licensed, all open source. The myiad of License files is why this section is added to avoid confusion.

* ELMSLN code on github (and not referenced or pulled in from other sources) is GPLv3.
* ELMS contributed modules from drupal.org are GPLv2 due to licensing requirements of the drupal.org community.
* Drupal and Drupal contributed modules and themes are GPLv2 due to licensing requirements of the drupal.org community.
* Piwik is GPLv3 via it's original repo (https://github.com/piwik/piwik)
* CKEditor 4.x is GPLv3
* Other included libraries are their respective LICENSE.txt files included local to those pieces of code
