ELMSLN with ddev
==============

This folder provides an installation routine for running ELMSLN in ddev.

How to use
==============

To set up in ddev simply clone the ELMSLN repository and run `ddev start`

```
mkdir elmsln
cd elmsln
git clone https://github.com/elmsln/elmsln.git .
ddev start
```

Notes
========

#### Restarting ddev containers

You may notice when running `ddev stop` or `ddev restart` that ELMSLN appears to be installing again when you start it up again. This is actually just a restart script, necessary because ELMSLN relies on changes within home directories of certain users, which are cleaned up when restarting a container. The restart script usually only takes a minute or two to complete.

#### Cron

ELMSLN relies on a cron job to build out course sites. Docker can be finicky about running cron and support is built into this installer but if you notice that course sites aren't being built, just ssh into the web container with `ddev ssh -s web` and run the following command:

`sudo bash /var/www/elmsln/scripts/install/handsfree/ddev/drush-create-site-ddev.sh`
