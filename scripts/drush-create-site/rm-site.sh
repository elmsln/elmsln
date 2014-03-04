#!/bin/bash
#remove a site created by drush-create-site
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

source ../../config/scripts/drush-create-site/config.cfg

if [ -z "$1" ]; then
echo "Usage: $0 <course name> <stack>"
exit 1
fi

if [ -z "$2" ]; then
echo "Usage: $0 <course name> <stack>"
exit 1
fi

#remove sites directory
for sitedata in `find $elmsln/config/stacks/$2 -name $1 | grep -v services` ; do
    echo "found sub-site $sitedata remove(y/n)"
    read rmsitedata
    if [ $rmsitedata == "y" ] || [ $rmsitedata == "yes" ]; then
        dbuser=`grep ^[[:space:]]*\'username $sitedata/settings.php | awk -F\' '{print $4}'`
        database=`grep ^[[:space:]]*\'database $sitedata/settings.php | awk -F\' '{print $4}'`
        echo $database
        echo $dbuser
        echo "remove database $database?(y/n)"
        read rmdatabase
            if [ $rmdatabase == "y" ] || [ $rmdatabase == "yes" ]; then
                echo "This action can NOT be undone. confirm remove of $database(y/n)"
                read rmdbconf
                    if [ $rmdbconf == "y" ] || [ $rmdbconf == "yes" ]; then
                echo "Removing database $database"
                mysql -u$dbsu -p$dbsupw -e "drop database $database"
                    fi

            echo "remove database user $dbuser?(y/n)"
            read rmdbuser
                if [ $rmdbuser == "y" ] || [ $rmdbuser == "yes" ]; then
                    echo "removing $dbuser"
                    mysql -u$dbsu -p$dbsupw -e "drop user $dbuser@localhost;"
                fi
            fi
        echo "removing site data"
            servicestest=`find $elmsln/config/stacks/$2/sites/$2/services/ -name $2`
            echo "services test"
            echo $servicestest
                if [[ $servicestest ]]; then
                    rm -rf $servicestest
                fi
            rm -rf $sitedata

    else
        echo "preserving site data in $sitedata"
    fi
done

#move into config dir for stack
#grep for coursename
cd $elmsln/config/stacks/$2/sites/
sitesphp=`grep -nr $2 sites.php`

while [[ $sitesphp ]]; do
        sitesphp=`grep -nr $2 sites.php`
        grep -nr $2 sites.php
        echo "which line do you want to remove?(x to exit)"
        read rmnum
                validrmnum=`echo $sitesphp | grep $rmnum:`
                if [[ $validrmnum ]]; then
                        cp sites.php sites.php.bak
                        echo "sites.php backed up to sites.php.bak"
                        sed -i ""$rmnum"d" sites.php
                else
                        if [[ $rmnum == "x" ]]; then
                                exit 0
                                else echo $rmnum " is not a valid input"

                        fi
                fi
done


if [ -L $elmsln/domains/$2/$1 ]; then
echo "removing symlink"
rm -rf $1/$2
else
echo "symlink not present"
fi
