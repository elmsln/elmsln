![ELMSLN](https://raw.githubusercontent.com/michael-collins/elmsln-logos/master/png-lowres-solid/lowres_square-color.png "ELMS Learning Network")

ELMSLN
==============
This is the ELMS Learning Network (ELMSLN) as a repository.  It includes installation instructions for getting it stood up on your server as well as multiple git repositories for optimal management downstream.

ELMSLN is a network based approach to educational technology design and implementation. The notion is that its no longer about the next products, it's that you will always be needing to produce and innovate in new products. This is a platform to spur innovation while providing an easy to use system that can be integrated into any existing institution.

Learn more about ELMSLN @ [elmsln.org](http://elmsln.org/)

Version | PHP | Includes | Code Status 
------------- | ------  | --- | -------------------------- | -----------
[master](https://travis-ci.org/btopro/elmsln)  | 5.3.0+ | Drupal 7.x, Piwik 2.x | [![Build Status](https://travis-ci.org/btopro/elmsln.svg?branch=master)](https://travis-ci.org/btopro/elmsln)

FAQ
==============
See the [wiki](https://github.com/btopro/elmsln/wiki) for more questions / answers and documentation. If you are developing for ELMSLN there's also [extensive documentation on the API site](http://api.elmsln.org).

###Q. How can I get more involved?
The easiest way is to setup an [ELMSLN Developer](http://github.com/btopro/elmsln-developer) envrionment and run [ELMSLN Vagrant](http://github.com/btopro/elmsln-vagrant). Test, ask, jump in on the issue queues on github, drupal.org, twitter, email, PHONE or anywhere else that you can find pieces that will help build upon this work. We always welcome more issue reports.

###Q. When will there be a stable release?
As soon as the blockers below are resolved (basically just time). If it helps you sleep at night, we've run this in production and have been actively building off of this framework since May 2013. The package is far more stable then the "master" moniker might otherwise suggest. Point releases require a different mindset from a developer / management perspective so we'll get there when the time is right.

May 26, 2015 - We will be releasing 0.1.0 shortly. There have been issue threads marked as release blockers and they are being resolved as we speak. The new user experience will be the default when the system is rolled out as part of 0.1.0. This new UX is already being run in production instances and we want to really bug fix things prior to marking a full release.

You can see the release blockers here: https://github.com/btopro/elmsln/milestones/Release%20blocker

###Q. How would you classify a first release?
Stable. master has been stable with three exceptions since Jan 2014. The branches outside of master are typically for major changes that require additional testing / development to race ahead of master. The many distributions of ELMS have been in usage for several months / years now. This ain't our first rodeo though we understand the desire for people to not be chasing the master branch.

###Q. How awesome is it to try and solve the edtech spaces biggest problem every day you walk into work?
We are here to change the world and love doing so.

LICENSE
=======
ELMSLN is a collection of many, many projects, all individually licensed, all open source. The myiad of License files is why this section is added to avoid confusion.

* ELMSLN code on github (and not referenced or pulled in from other sources) is GPLv3.
* ELMS contributed modules from drupal.org are GPLv2 due to licensing requirements of the drupal.org community.
* Drupal and Drupal contributed modules and themes are GPLv2 due to licensing requirements of the drupal.org community.
* Piwik is GPLv3 via it's original repo (https://github.com/piwik/piwik)
* CKEditor 4.x is GPLv3
* Other included libraries are their respective LICENSE.txt files included local to those pieces of code
