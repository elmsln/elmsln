
README
--------------------------------------------------------------------------
This module allows nodes to be published and unpublished on specified dates.

Dates can be entered either as plain text or with Javascript calendar
popups (JSCalendar in Drupal 5, Date Popup in Drupal 6).

JSCalendar is part of the JSTools module (http://drupal.org/project/jstools).
The Date Popup module is part of the the Date module (http://drupal.org/project/date).

Notice:
- Please check if cron is running correctly if scheduler does not publish your
  scheduled nodes.
- Scheduler does only schedule publishing and unpublishing of nodes. If you
  want to schedule any other activity check out Workflow
  (http://drupal.org/project/workflow), Rules (http://drupal.org/project/rules)
  and Actions (http://drupal.org/project/actions).

Scheduler is the work of many people. Some of them are listed here:
http://drupal.org/project/developers/3292. But there are even more: All the
people who created patches but did not check them in themselfs, who posted bug
or feature request and those who provided translations and documentation.

This module has been completely rewritten for Drupal 4.7 by:

Ted Serbinski <hello [at] tedserbinski.com>
  aka "m3avrck" on http://drupal.org


This module was originally written for Drupal 4.5.0 by:

Moshe Weitzman <weitzman [at] tejasa.com>
Gabor Hojtsy <goba [at] php.net>
Tom Dobes <tomdobes [at] purdue.edu>


INSTALLATION
--------------------------------------------------------------------------
1. Copy the scheduler.module to your modules directory
2. Enable module, database schemas will be setup automatically.     
3. Grant users the permission "schedule (un)publishing of nodes" so they can
   set when the nodes they create are to be (un)published.
   
4. Visit admin > settings > content-types and click on any node type and
   check the box "enable scheduled (un)publishing" for this node type
   
5. Repeat for all node types that you want scheduled publishing for

The scheduler will run with Drupal's cron.php, and will (un)publish nodes
timed on or before the time at which cron runs.  If you'd like finer
granularity to scheduler, but don't want to run Drupal's cron more often (due
to its taking too many cycles to run every minute, for example), you can set
up another cron job for the scheduler to run independently.  Scheduler's cron
is at /scheduler/cron; a sample crontab entry to run scheduler every minute
would look like:

* * * * * /usr/bin/wget -O - -q "http://example.com/scheduler/cron"