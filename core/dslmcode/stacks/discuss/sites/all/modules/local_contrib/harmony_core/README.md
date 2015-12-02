# Harmony core

[![Build Status](https://travis-ci.org/lohi-io/harmony_core.svg?branch=7.x-1.x)](https://travis-ci.org/lohi-io/harmony_core)

## Features, things of note
+ Thread & Post entities along with fields supplied by Features
+ This module makes the assumptions that the following don't exist and that you're installing on to a vanilla install (hey, this is the core of a distro!) Taxonomy vocabs, Flags.
+ Anonymous cannot create threads or posts

## Frequently asked questions

**I'd like everything at /forum, how can I do that?**
Easily! The listing pages are views so you can change the paths on the page displays, and as for Categories and Threads you can change the URL alias patterns at: Configuration > Search and metadata > URL aliases > Patterns. This page and functionality is provided by the pathauto module which harmony_core requires.

## Language notes
As I'm British, that's the language I've used. Being mindful of those who'd rather have American-English here's a list of words that I've used, to come back and offer some kind of localisation around.
+ Colour

## Harmony core has integration with...

+ Pathauto module (thread entity)
+ Context (Trigger context when viewing a thread with x)
+ Views of course!
+ Inline entity form
+ Actions & Views bulk operations
+ Metatag module, thread & post.
+ Devel & Devel Generate

## Install instructions

Turn it on and go!
There's a sub module "Harmony - Default permissions" which should serve as an example of the sort of permissions you'll need to set for Harmony to behave properly. As a reminder, anonymous users cannot post in Harmony, this is an architectural choice (with enough demand could be changed) and not a permissions issue.

In order for users to be able to view forum content they will need persmission to view both threads and posts.

## How do I use it?

You can add new threads here:
/thread/add

The default listing of posts can be found here:
/forum

You can add and alter fields on the Thread entity here:
/admin/harmony/structure/thread

And post here:
/admin/harmony/structure/post

## Install notes

jQuery update should be set to use 1.7, there are issues with this however, check the settings here:
/admin/config/development/jquery_update

You will also want to use the same version of jQuery on admin pages.

If you want to use At.js you will need to download libraries, I refer you to the instructions for that module.

## Automated tests

Workin on it! Just the one basic proof of concept for now.
