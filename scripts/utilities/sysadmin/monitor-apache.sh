#!/bin/bash
# check if apache is still alive, if not bring it back up
# useful for active monitoring systems where you may hit a wall of traffic unexpectedly
# this prevents long term outages in the event you have such a flood of traffic
# based off of http://unix.stackexchange.com/questions/93699/how-to-write-a-shell-script-restart-apache-if-server-reached-maxclients

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# load config
source ../../../config/scripts/drush-create-site/config.cfg

# provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=${txtbld}$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
}

PATH=/bin:/usr/bin
THEDIR=/tmp/apache-watchdog
mkdir -p $THEDIR
# hit the entity iframe consumer page as it has almost nothing to it
pingaddress="${protocol}://online.${address}/entity-iframe-consumer.html"
if ( wget --timeout=20 -q -P $THEDIR $pingaddress )
then
    # we are up
    touch ~/.apache-was-up
else
    # down! but if it was down already, don't keep spamming
    if [[ -f ~/.apache-was-up ]]
    then
        # write a nice e-mail
        echo -n "apache crashed at " > $THEDIR/mail
        date >> $THEDIR/mail
        echo >> $THEDIR/mail
        echo "Access log:" >> $THEDIR/mail
        tail -n 30 /var/log/apache2_access/current >> $THEDIR/mail
        echo >> $THEDIR/mail
        echo "Error log:" >> $THEDIR/mail
        tail -n 30 /var/log/apache2_error/current >> $THEDIR/mail
        echo >> $THEDIR/mail
        # kick apache
        echo "Now kicking apache..." >> $THEDIR/mail
        /etc/init.d/httpd restart >> $THEDIR/mail 2>&1
        # send the mail
        echo >> $THEDIR/mail
        echo "Good luck troubleshooting!" >> $THEDIR/mail
        mail -s "ELMSLN watchdog: apache restarted automatically" $admin < $THEDIR/mail
        rm ~/.apache-was-up
    fi
fi

