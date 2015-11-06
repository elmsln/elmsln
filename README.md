![ELMSLN](https://raw.githubusercontent.com/michael-collins/elmsln-logos/master/png-lowres-solid/lowres_square-color.png "ELMS Learning Network")

ELMSLN
==============

ELMS Learning Network (ELMSLN) is an open source educational technology platform for building and sustaining innovation in course technologies. It accomplishes this by taking a Suite of Tools approach to learning design, allowing several systems to make up the different aspects of a course learning environment.  Each course effectively forms a network of technologies (hence the name) which can then be better tailored to each individual course's needs.

Learn more about ELMSLN @ [elmsln.org](http://elmsln.org/)

Version | PHP | Includes | Code Status 
------------- | ------  | --- | -------------------------- | -----------
[master](https://travis-ci.org/elmsln/elmsln)  | 5.3.0+ | Drupal 7.x, Piwik 2.x | [![Build Status](https://travis-ci.org/elmsln/elmsln.svg?branch=master)](https://travis-ci.org/elmsln/elmsln)

[![Join the chat at https://gitter.im/elmsln/elmsln](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/elmsln/elmsln?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[Read the Docs](http://docs.elmsln.org/)

Issues
==============
If you notice an issue or have a question please file it in our [issue queue]((https://github.com/elmsln/elmsln/issues).

FAQ
==============
See the [wiki](https://github.com/elmsln/elmsln/wiki) for more questions / answers and documentation. If you are developing for ELMSLN there's also [extensive documentation on the API site](http://api.elmsln.org).

###Q. How can I get more involved?
There are many ways you can get involved in helping build ELMSLN; not all of which are technical in nature. The easiest way is to click the issues button in this repository. Submit feedback, help, questions, pedagogy, ideas, fan-art anything that helps us further our mission! All help and outreach is welcome and responded to.

If you'd like to try out ELMSLN for yourself, clone this repo and issue `vagrant up`. There's an included Vagrantfile which sets up a Virtual Machine on your computer to try out ELMSLN locally. For detailed directions on how to do this if you've never run vagrant before, see the [ELMSLN Vagrant instructions](https://github.com/elmsln/elmsln/wiki/Vagrant:-Step-by-Step-setup).

If you are looking to join active project team development,[ELMSLN Developer](http://github.com/elmsln/elmsln-developer) is the place for you. This structures your desktop with a repo that helps put things in place to manage multiple elmsln deployments and keep things sane. It's what the project's founders use to develop the project and keep multiple deployments in check (along with robots, obviously).

Test, ask, jump in on the issue queues on github, drupal.org, twitter, email, phone, drupalcamps, edtech events, our offices, or anywhere else that you can find pieces that will help build upon this work. We are here to make the future awesome together.

###Q. When will there be a stable release?
As soon as the blockers below are resolved (basically just time). If it helps you sleep at night, we've run this in production and have been actively building off of this framework since May 2013.

Sep 23, 2015 - We've got all the tools we planned on having in an initial release in the package. All initial UX items have been handled and stabilized as we're running it in production. The remaining issues have to do with infrastructure items we'd rather not have to provide upgrade paths for after creation.

You can see the release blockers here: https://github.com/elmsln/elmsln/milestones/Release%20blocker

###Q. How awesome is it to try and solve the edtech spaces biggest problem every day you walk into work?
We are here to change the world

LICENSE
=======
ELMSLN is a collection of many, many projects, all individually licensed, all open source. The myiad of License files is why this section is added to avoid confusion.

* ELMSLN code on github (and not referenced or pulled in from other sources) is GPLv3.
* ELMS contributed modules from drupal.org are GPLv2 due to licensing requirements of the drupal.org community.
* Drupal and Drupal contributed modules and themes are GPLv2 due to licensing requirements of the drupal.org community.
* Piwik is GPLv3 via it's original repo (https://github.com/piwik/piwik)
* CKEditor 4.x is GPLv3
* Other included libraries are their respective LICENSE.txt files included local to those pieces of code
