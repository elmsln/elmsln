ELMSLN - domains

This is an example webroot, it is recommended you use this directory and point all domains here that are associated with ELMSLN. This helps keep elmsln as a contained package and allows it to live along side other apps on the same server with less spaghetti code /scripts.

As soon as the ELMSLN automation scripts are enabled on the system and ELMSLN installed correctly, it will automatically try and build a robots100 course and media sites.

This comes with a few symlink items by default though they will need to be manually installed by going to a web address:
— Piwik, analytics
- CIS, online
- Remote Watchdog, courses/watchdog and media/watchdog

@todo we need to automate the creation of these spaces on initial install but they currently fall outside the scope of the crush-create-site script’s capabilities.