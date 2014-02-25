#!/bin/bash
#remove a site created by drush-create-site
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

source ../../config/scripts/drush-create-site/config.cfg

if [ -z "$1" ]; then
echo "Usage: $0 <webroot> <course name>"
exit 1
fi

if [ -z "$2" ]; then
echo "Usage: $0 <webroot> <course name>"
exit 1
fi

#remove sites directory
for sitedata in `find $1/$2/sites/ -name $2 | grep -v services` ; do
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
			servicestest=`find $1/$2/sites/*/services -name $2`
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

#for database in `mysql -u$dbsu -p$dbsupw -e "show databases" | grep $2` ; do
#echo "found database $database remove?(y/n)"
#read rmdb
#        if [ $rmdb == "y" ] || [ $rmdb == "yes" ]; then
#                echo "This action can NOT be undone. confirm removal of $database(y/n)"
#                read rmdb
#                if [ $rmdb == "y" ] || [ $rmdb == "yes" ]; then
#                echo "removing database $rmdb"
#                mysql -u$dbsu -p$dbsupw -e "drop database $database"
#                fi
#        else
#                echo "preserving database $database"
#        fi
#done
# @todo this part needs rethought now that config lives in the config directory
# right now this ends up copying the sites.php file that's being referenced
# and replaces the symlink w/ the actual file that's been changed.
# it also creates a .bak file in the core / domains locations which creates a
# non committed file in the incorrect location.
sitesphp=`grep -nr $2 $1/$2/sites/sites.php`

while [[ $sitesphp ]]; do
        sitesphp=`grep -nr $2 $1/$2/sites/sites.php`
        grep -nr $2 $1/$2/sites/sites.php
        echo "which line do you want to remove?(x to exit)"
        read rmnum
                validrmnum=`echo $sitesphp | grep $rmnum:`
                if [[ $validrmnum ]]; then
                        cp $1/$2/sites/sites.php $1/$2/sites/sites.php.bak
                        echo "sites.php backed up to $1/$2/sites/sites.php.bak"
                        sed -i ""$rmnum"d" $1/$2/sites/sites.php
                else
                        if [[ $rmnum == "x" ]]; then
                                exit 0
                                else echo $rmnum " is not a valid input"

                        fi
                fi
done

#if [[ $sitesphp ]]; then
#	grep -nr $2 $1/sites/sites.php
#	echo "which line do you want to remove?(k to keep)"
#	read rmnum
#	while [[ ! $rmnum =~ [0-999-k] ]]; do
#	echo "which line do you want to remove?(k to keep)"
#	read rmnum
#	done
#		if [[ $rmnum == "k" ]]; then
#		echo "preserving sites.php"
#		else
#		cp $1/sites/sites.php $1/sites/sites.php.bak
#		echo "sites.php backed up to $1/sites/sites.php.bak"
#		sed -i ""$rmnum"d" $1/sites/sites.php
#		fi
#fi

if [ -L $1/$2 ]; then
echo "removing symlink"
rm -rf $1/$2
else
echo "symlink not present"
fi


