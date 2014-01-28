#install script goes here
installdir="/usr/local/bin/drush-create-site2"
wwwuser="apache"
jobsdir="/var/wwwjobs"

if [ ! -d $installdir ]; then 
	mkdir $installdir
	/bin/cp drush-create-site $installdir
	/bin/cp config.cfg.example $installdir
	/bin/cp rm-site.sh $installdir
	/bin/cp init-script /etc/init.d/dcs
else 
	echo "Install Directory Exisits. overwrite(y/n)"
	read overwrite

		if [ $overwrite = y ]; then 
			/bin/cp -f drush-create-site $installdir
			/bin/cp -f config.cfg.example $installdir
			/bin/cp rm-site.sh $installdir
			/bin/cp init-script /etc/init.d/dcs
		fi
			
		
fi

#add jobs loc

if [  ! -d $jobsdir ]; then 
	mkdir $jobsdir
	/bin/cp hosts.example $jobsdir/hosts
else
	echo "Jobs Directory Exists. overwrite(y/n)"
	read jobsoverwrite
		if [ $jobsoverwrite = y ]; then 
			/bin/cp -f hosts.example $jobsdir/hosts
		fi
fi
