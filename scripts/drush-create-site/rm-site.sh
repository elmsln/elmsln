#!/bin/bash
#remove a site created by drush-create-site
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

source ../../config/scripts/drush-create-site/config.cfg

#provide messaging colors for output to console
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

# check that we are the root user
if [[ $EUID -ne 0 ]]; then
  elmslnwarn "Please run as root"
  exit 1
fi
# check for supplied course name
if [ -z "$1" ]; then
    elmslnwarn "Usage: $0 <course name> <stack>"
    exit 1
fi
# check for supplied stack
if [ -z "$2" ]; then
    elmslnwarn "Usage: $0 <course name> <stack>"
    exit 1
fi

#remove sites directory
for sitedata in `find $elmsln/config/stacks/$2 -name $1 | grep -v services` ; do
    elmslnwarn "found sub-site $sitedata remove(y/n)"
    read rmsitedata
    if [ $rmsitedata == "y" ] || [ $rmsitedata == "yes" ]; then
        dbuser=`grep ^[[:space:]]*\'username $sitedata/settings.php | awk -F\' '{print $4}'`
        database=`grep ^[[:space:]]*\'database $sitedata/settings.php | awk -F\' '{print $4}'`
        elmslnecho $database
        elmslnecho $dbuser
        elmslnecho "remove database $database?(y/n)"
        read rmdatabase
        if [ $rmdatabase == "y" ] || [ $rmdatabase == "yes" ]; then
            elmslnwarn "This action can NOT be undone. confirm remove of $database(y/n)"
            read rmdbconf
            if [ $rmdbconf == "y" ] || [ $rmdbconf == "yes" ]; then
                elmslnecho "Removing database $database"
                mysql -u$dbsu -p$dbsupw -e "drop database $database"
            fi
            elmslnecho "remove database user $dbuser?(y/n)"
            read rmdbuser
            if [ $rmdbuser == "y" ] || [ $rmdbuser == "yes" ]; then
                elmslnecho "removing $dbuser"
                mysql -u$dbsu -p$dbsupw -e "drop user $dbuser@localhost;"
            fi
        fi
        servicestest=`find $elmsln/config/stacks/$2/sites/$2/services/ -name $1`
        elmslnecho "removing services site"
        elmslnecho $servicestest
        if [[ $servicestest ]]; then
            rm -rf $servicestest
        fi
        elmslnecho "removing site"
        rm -rf $sitedata
    else
        elmslnecho "preserving site data in $sitedata"
    fi
done


# clean out the jobs folder
jobtest=`find $elmsln/config/jobs/ -name $1.$2.processed`
if [[ $jobtest ]]; then
    elmslnecho "removing jobs file"
    rm $elmsln/config/jobs/$1.$2.processed
else
    elmslnecho "job file not present"
fi

# ax the symlink
if [ -L $elmsln/domains/$2/$1 ]; then
    elmslnecho "removing symlink"
    rm $elmsln/domains/$2/$1
else
    elmslnecho "symlink not present"
fi

#move into config dir for stack
#grep for coursename
cd $elmsln/config/stacks/$2/sites/
sitesphp=`grep -nr $2 sites.php`

while [[ $sitesphp ]]; do
    sitesphp=`grep -nr $2 sites.php`
    grep -nr $2 sites.php
    elmslnecho "which line do you want to remove? (x to finish)"
    read rmnum
    validrmnum=`echo $sitesphp | grep $rmnum:`
    if [[ $validrmnum ]]; then
        cp sites.php sites.php.bak
        elmslnecho "sites.php backed up to sites.php.bak"
        sed -i ""$rmnum"d" sites.php
    else
        if [[ $rmnum == "x" ]]; then
            elmslnecho "$1 successfully removed from $2 stack"
            exit 1
        else
            elmslnwarn $rmnum " is not a valid input"
        fi
    fi
done
