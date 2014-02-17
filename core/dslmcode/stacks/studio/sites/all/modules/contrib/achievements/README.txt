
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Creating achievements
 * Optional modules


INTRODUCTION
------------

Current Maintainer: Morbus Iff <morbus@disobey.com>

The Achievements module offers the ability to create achievements and
badges similar to systems seen on Xbox 360, Playstation 3, Foursquare,
Gowalla, GetGlue, and more. For a Drupal site, this could mean commenting a
certain number of times, starting a forum topic, visiting the site every day
of the week, or anything else that can be tracked and coded.

Current features and design:

 * Achievement points are based on milestones, not continuous activity.
   Instead of getting 5 points every time a user posts a node, an equivalent
   milestone might instead reward 20 points for posting 10 nodes. If there's
   no achievement for posting 50 nodes, the user receives no further points.

 * Since achievements are milestones, each one has its own leaderboard
   that lists when a user has met (or "unlocked") the goal and their
   matching rank. A site-wide leaderboard ranks users by points they've
   achieved, but also by timestamp -- if two users share the same point
   total, the person who got there first gets the higher rank.

 * Relative leaderboards are supported and allow the user to see where they
   are in relation to nearby ranks or the top achievers. Leaderboards also
   show the latest achievement earned, allowing users to discover new
   milestones they might want to strive for.

 * Achievements can be made "secret" (if they're not unlocked, a user will
   see "Secret Achievement" placeholder text instead of actual data) and/or
   "invisible" (the achievement doesn't show up on the user's Achievements
   tab until it's unlocked).

 * Achievements can have images (or "badges") in one of three different
   states: unlocked, locked, or secret. Default images can be used for all
   achievements (and some are provided with the module), or you can override
   them on a per-achievement basis.

 * Achievements can be grouped into categories and tabbed with jQuery UI.

 * An adminterface allows you to manually grant or remove achievements. If
   the user is offline, unlocked achievements will display the next time
   the user visits the site.

 * Achievement unlocks fade-in and out at the window's bottom right corner.

 * Your code decides whether achievements are retroactively applied or not.


INSTALLATION
------------

 1. Copy the achievements/ directory to your sites/SITENAME/modules directory.

 2. Enable the module and configure it at admin/config/people/achievements.

 3. Set your desired permissions at admin/people/permissions.

 4. See "Creating achievements" for how to code your own achievements.


CREATING ACHIEVEMENTS
---------------------

I've made two entirely deliberate design decisions:

 1. No achievements are shipped by default. Earning the same achievement
    over and over again at dozens of Drupal sites is mind-numbingly not-fun.
    If you're going to offer achievements, at least _try_ to be creative and
    make them unique to your site.

 2. Creating achievements requires custom code. Achievements that can be
    automated in a user interface tend to be mind-numbingly not-fun and
    grindish ("when user creates $n comments, $n posts", etc.). Quality
    achievements require custom logic tailored to your site.

I _do_ believe that achievement grinds have their place and I _do_ want to
be rewarded for posting 1000 comments or 250 nodes. I just don't want to see
default implementations on every site that uses this module. It's lazy. It's
not-fun. It reflects poorly on my code and achievement whoredom if I promote
cookie-cutter gamification on Drupal sites everywhere.

To begin creating achievements:

 1. You'll need to create or use a custom module to implement the API. Further
    information about module development and the Drupal APIs you can listen on
    to trigger your achievements is available in the "Develop for Drupal" docs
    at http://drupal.org/documentation/develop. At the minimum, read:

     * Module file names and locations: http://drupal.org/node/1074362
     * Telling Drupal about your module: http://drupal.org/node/1075072
     * Implementing your first hook: http://drupal.org/node/1095546

 2. Read about the Achievements API, and examples, in achievements.api.php.

 3. Adding new achievements (or changing the info of existing ones) will
    require you to rebuild the internal cache, which you can refresh from
    admin/config/people/achievements.


OPTIONAL MODULES
----------------

Achievements ships with some tweaky and entirely optional modules:

 * OPTOUT: Some folks just plain ol' hate gamification. With the Opt-out
   module, a new checkbox field is added to the user's edit screen that allows
   them to opt-out (and back in, if they so desire) from earning achievements.

 * POINTLESS: The Pointless module removes all the explicit competitive
   elements of achievements. Milestones will no longer display a user's
   unlock rank or the number of points, and access to the leaderboards is
   disabled. This creates an environment where the user unlocks achievements
   for their own gratification, not to simply one-up another user or to get
   noticed on a nebulous high-score table.

