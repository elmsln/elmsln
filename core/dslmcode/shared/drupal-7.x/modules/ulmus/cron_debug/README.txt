
Cron Debug 1.2 for Drupal 7.x
------------------------------

Cron Debug will help you find cron processes which

  * fail due to programming or runtime errors
  * time out (PHP, server, database)
  * are very slow

Cron Debug will also allow you to test run specific cron functions while not
running others. This can be nice for developing cron functions where you don't
want to run a full cron.php with all maintenece, alerts and other tasks
everytime you test your own function.

Cron Debug can run cron hooks while registering success and time elapsed for
each. You can see which hooks will be run in which sequence, select which
hooks to run and see their duration in the results as well as in the log.

If a cron process times out, hangs or fails, you can see which ones finished
succesfully and which single one did not finish properly by looking in the log
when returning to Drupal's reports. All Cron Debug log entries are registered
as "cron debug" and can be filtered separately. If the cron run failed, the
usurper will be the top/last entry in the list of Cron Debug entries in the log.

A flag is set when the Cron Debug run is started and removed when it finishes
succesfully and reports its results. If some part of the cron run fails, hangs
or times out, this flag will most likely still be set upon returning to Drupal,
and if you go into Cron Debug again, you will get a message telling you so,
urging you to look in the log to diagnose the problem. Cron Debug will also
try to display details on the failed process when it has halted with an error.

Cron jobs can also be run "individually", meaning that they are not called as
a part of a joint cron run, but called individually as single functions with
immediate return to Cron Debug. This enables you to quickly and easily track
down syntax and runtime errors in a single function and possibly analyze the
output that it might generate; legitimate or erroneous, which can be helpful
in debugging. This way of executing the function will also time it, and give
you the option to analyze the single function's influence on database,
variables, files and other system elements. The start and the end of the run
is marked in the log, and errors logged between these two marks come from that
particular function or functions that it calls.

Notice that your regular cron jobs will run as usual if you have set them up.
You might want to disable cron on the server while debugging with Cron Debug.
This module runs the cron jobs for each module separately from the usual cron
run found in common.inc and invoked by running example.com/cron.php.
Running cron.php will not register any debug code. You will have to run the
Cron Debug routine to get this registration.

Also notice that

  * some modules have local settings, which enable and disable or configure
    cron runs for that module. In such cases it might appear in Cron Debug's
    runs as if the hook ran smoothly even though the function in the module
    might return without having done anything. In order to debug cron jobs
    in such modules, you will have to tamper with the module's own settings
    and enable the relevant cron routines.
  * some custom modules may call external functions and not return properly
    to Drupal in which case they may run as planned, but not register as
    finished in the log. Disable those jobs in order to have a smooth cron run,
    and (hopefully) a successful return to Drupal.


Installation
------------
Cron Debug can be installed like any other Drupal module -- place it in the
modules directory for your site and enable it on the `admin/build/modules` page.
Once it's installed, you find the control of the module in the Debug-tab on
the Cron configuration page - admin/config/system/cron/debug
