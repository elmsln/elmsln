#!/bin/bash
#where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

source ../../config/scripts/drush-create-site/config.cfg

# make sure root process has latest bashrc running in its thread
source $HOME/.bashrc

#test for empty vars. if empty required var -- exit
if [ -z $fileloc ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $site_email ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $admin ]; then
  echo "please update your config.cfg file"
  exit 1
fi
if [ -z $webdir ]; then
  echo "please update your config.cfg file"
  exit 1
fi

#test mysql login
mysql -u$dbsu -p$dbsupw -e exit
if [[ $? > 0 ]];then
  echo "mysql connection failed"
  exit 1
fi

date=`date +%Y-%m-%d_%H:%M:%S`


#prevent the script from being run more than once
if [ -f /tmp/drush-lock ]; then
  exit 1
fi
sudo touch /tmp/drush-lock

#read the files in the $fileloc and set vars based on file name.
for coursefile in `find $fileloc -maxdepth 1 ! -name *.swp ! -name '*progress'  ! -name '*processing*' ! -name '*error' ! -name '*processed' ! -name '*example' ! -name '*.md' -type f`
do
  college=`sed -n '2p' $coursefile`
  course=`sed -n '1p' $coursefile`
  service=${coursefile#*.}
  if [ -z $stacks ]; then
    drupalroot=$webdir/$service
  else
    drupalroot=$stacks/$service
  fi
  echo $drupalroot
  coursedb=$service"_"$college"_"$course
  #hostname=$service.$hostnamesearch
  hostname=`sed -n '3p' $coursefile`
  datahostname=`sed -n '4p' $coursefile`
  subdir=$service/$college
  dbpw=`</dev/urandom tr -dc A-Za-z0-9 | head -c14`
  drupalpw=`</dev/urandom tr -dc A-Za-z0-9 | head -c14`
  #drupal user is first bit of admin e-mail
  drupaluid=`echo $admin | cut -d@ -f1`
  collegelen=${#college}
  coursefilelen=${#coursefile}
  #coursedb="courses_"$college"_"$course
  courselen=${#course}
  error=0
  sitename=`sed -n '5p' $coursefile`
  slogan=`sed -n '6p' $coursefile`
  requester=`sed -n '7p' $coursefile`
  insprofile=`sed -n '8p' $coursefile`
  options=`sed -n '9p' $coursefile`

  #makeshift progress indicator start
  echo "1" > $fileloc/$course.$service.progress

  #chartest=`sed -n '1,6' $coursefile`

  ##Error catching here.
  #testing for bad characters. if found any in the course file we exit

  badchars=`sed 's/[a-z A-Z 0-9 _@.,= \: \/ \-]//g' $coursefile`
  if [ $badchars ]; then
    echo "bad characters in the course file" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  if [ $coursefilelen -gt 300 ]; then
    echo "$coursefile is too large." >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  if [ ! -f $drupalroot/index.php ]; then
    echo $date " Drupal doesn't exist in $drupalroot" >> $configsdir/logs/drush-create-site.log
    error=1
  fi


  if [[ -z $sitename ]]; then
    echo ""
    title=$course
  fi

  if [ -z $course ]; then
    echo " $date course is missing. exiting" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  if [ -z $hostname ]; then
    echo " $date hostname is missing" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  if [ -z $college ]; then
    echo " $date college is missing. exiting" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  if [ $collegelen -gt 3 ]; then
    echo " $date college name is too long. expecting 2 chars. exiting" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  if [ $courselen -gt 40 ]; then
    echo " $date Course length is too long, please enter one that's less than 40 chars" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  if [ $? -gt 0 ]; then
    echo " $date errors!" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  # if course length is more then 10, truncate to 10
  if [ $courselen -gt 10 ]; then
    subcourse=${course:0:10}
  else
    subcourse=$course
  fi
  dbprefixtest=''
  dbcount=0
  function userexist {
    userexist=`mysql -u$dbsu -p$dbsupw -e "select user from mysql.user;" | grep ^$dbprefixtest$college$subcourse`
  }
  userexist

  while [ $userexist ]; do
    dbcount=$((dbcount + 1))
    echo "database use exists, adding $dbcount to $dbprefix" >> $configsdir/logs/drush-create-site.log
    dbprefixtest=$dbcount
    userexist
  done

  if [ $dbcount -gt 0 ]; then
    dbprefix=$dbcount
  fi

  #Test if database exists, if does back out with warning
  dbexist=`mysql -u$dbsu -p$dbsupw -e "show databases;" | grep ^"$coursedb"$`
  if [ $dbexist ]; then
    echo " $date database $course exists. exiting" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  #test course name for bad characters
  badchars=`echo "$course" | sed 's/[a-zA-Z0-9_]//g'`
  if [ $badchars ];then
    echo "$date course name has bad characters. exiting" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  #has this course been added?
  if [ -L $drupalroot/$course ]; then
    echo "it appears this course has already been added. exiting" >> $configsdir/logs/drush-create-site.log
    error=1
  fi

  #if errors are found, back out
  if [ $error = 1 ]; then
    sudo mv $coursefile $coursefile.$date.error
    echo "there was an error processing $coursefile. please check the logs" | mail -s "error creating site" $admin
    echo "there was an error processing site, please contact your admin" | mail -s "error creating site" $requester
    echo "error" > $fileloc/$course.$service.progress
    sudo rm /tmp/drush-lock
    exit 1
  fi

  #start processing
  sudo mv $coursefile $coursefile.processing

  #makeshift progress bar
  echo "2" > $fileloc/$course.$service.progress

  cd $drupalroot
  #Install site with drush
  drush -y --root=$drupalroot site-install $insprofile --db-url=mysql://$dbprefix$college$subcourse:$dbpw@localhost/$coursedb --sites-subdir=$course --db-su=$dbsu --db-su-pw=$dbsupw --site-name="$sitename" --account-name=$drupaluid --account-pass=$drupalpw --account-mail=$admin --site-mail=$site_email >> $configsdir/logs/drush-create-site.log


  echo "3" > $fileloc/$course.$service.progress

  #create symlink for subdir
  cd $webdir/$service
  sudo ln -s $drupalroot $course

  sudo mkdir -p $drupalroot/sites/$subdir
  sudo mv $drupalroot/sites/$course $drupalroot/sites/$subdir/$course
  sudo mkdir $drupalroot/sites/$subdir/$course/files/feeds
  sudo chown -R $wwwuser:$webgroup $drupalroot/sites/$subdir/$course/files/feeds
  sudo chown $wwwuser:$webgroup $drupalroot/sites/$subdir/$course/files/feeds -v
  sudo chmod 774 $drupalroot/sites/$subdir/$course/files/feeds -v
  #add site to the sites array

  if [ -f $configsdir/stacks/$service/sites/sites.php ]; then
    arraytest=`grep -e "^\\$sites" $configsdir/stacks/$service/sites/sites.php`
    if [[ -z $arraytest ]]; then
      # modify sites permissions so we can edit it for this operation
      sudo chmod 774 $configsdir/stacks/$service/sites/sites.php
      # add in a sites array placeholder; this is very rare
      echo "\$sites = array(" >> $configsdir/stacks/$service/sites/sites.php
      echo "" >> $configsdir/stacks/$service/sites/sites.php
      echo ");" >> $configsdir/stacks/$service/sites/sites.php
      # set it back safely
      sudo chmod 644 $configsdir/stacks/$service/sites/sites.php
    fi
    sudo sed -i "/^\$sites = array/a \ \t \'$hostname.$course\' =\> \'$subdir\/$course\'\," $configsdir/stacks/$service/sites/sites.php
  	if [[ $datahostname ]]; then
  		sudo sed -i "/^\$sites = array/a \ \t \'$datahostname.$course\' =\> \'$service\/services\/$college\/$course\'\," $configsdir/stacks/$service/sites/sites.php
  	else
  		sudo sed -i "/^\$sites = array/a \ \t \'$serviceprefix.$hostname.$course\' =\> \'$service\/services\/$college\/$course\'\," $configsdir/stacks/$service/sites/sites.php
  	fi
  fi

  # add in our cache bins
  sudo chmod 774 $drupalroot/sites/$subdir/$course/settings.php
  echo "\$conf['cache_prefix'] = '$coursedb';" >> $drupalroot/sites/$subdir/$course/settings.php
  sudo chmod 444 $drupalroot/sites/$subdir/$course/settings.php
  #adding services conf file
  if [ ! -d $drupalroot/sites/$service/services/$college/$course ]; then
      sudo mkdir -p $drupalroot/sites/$service/services/$college/$course
      sudo mkdir $drupalroot/sites/$service/services/$college/$course/files
      sudo chown -R $wwwuser:$webgroup $drupalroot/sites/$service/services/$college/$course/files
      if [ -f $drupalroot/sites/$service/$college/$course/settings.php ]; then
        sudo cp $drupalroot/sites/$service/$college/$course/settings.php $drupalroot/sites/$service/services/$college/$course/settings.php
      fi
      if [ -f $drupalroot/sites/$service/services/$college/$course/settings.php ]; then
        sudo chmod 777 $drupalroot/sites/$service/services/$college/$course/settings.php
        echo "\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $drupalroot/sites/$service/services/$college/$course/settings.php
        sudo sed -i "/\# \$base_url/a \ \t \$base_url= '$protocol://$datahostname/$course';" $drupalroot/sites/$service/services/$college/$course/settings.php
        sudo chmod 444 $drupalroot/sites/$service/services/$college/$course/settings.php
      fi
  fi
  ##set base_url

  sudo sed -i "/\# \$base_url/a \ \t \$base_url= '$protocol://$hostname/$course';" $drupalroot/sites/$subdir/$course/settings.php

  cd $drupalroot
  ###options
  if [[ $requester ]]; then
    if [[ $requester == $admin ]]; then
      echo "requester equals admin"
    else
      requesterpw=`</dev/urandom tr -dc A-Za-z0-9 | head -c14`
      requesterid=`echo $requester | cut -d@ -f1`
      drush -y --root=$drupalroot --uri=$protocol://$hostname.$course user-create $requesterid --mail="$requester"
      drush -y --root=$drupalroot --uri=$protocol://$hostname.$course user-password $requesterid --password="$requesterpw"
      if [[ $send_requester_pw ]]; then
         echo " $protocol://$hostname/$course has been created!  id: $requesterid  password: $requesterpw" | mail -s "$course has been added to $hostname" $requester
      else
         echo " $protocol://$hostname/$course has been created!" | mail -s "$course has been added to $hostname" $requester
      fi
    fi
  fi

  if [[ $slogan ]]; then
    drush -y --root=$drupalroot --uri=$protocol://$hostname.$course vset site_slogan "$slogan"
  fi
  # clean up permissions
  echo "4" >> $fileloc/$course.$service.progress

  ##permissions fun
  find $drupalroot/sites/$subdir/$course/files  -type f | xargs chmod 664
  find $drupalroot/sites/$subdir/$course/files  -type d | xargs chmod 775
  sudo chown -R $wwwuser:$webgroup $drupalroot/sites/$subdir/$course/files

  ##add drupal_priv directories, set permissions
  if [ ! -d $drupal_priv/$service/$course ]; then
    sudo mkdir -p $drupal_priv/$service/$course
    sudo chown $wwwuser:$webgroup $drupal_priv/$service/$course
    sudo chmod g+w $drupal_priv/$service/$course
  fi

  # work through the open ended drush commands
  echo "5" > $fileloc/$course.$service.progress
  # clear drush cache to ensure it hasn't cached aliases
  drush cc drush --y
  if [[ $options ]]; then
    grep ^drush $coursefile.processing | while read drush; do
      drushcommand=`echo $drush | awk '{print $2}'`
      background='TRUE'
      case $drushcommand in
      en)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      background='FALSE'
      ;;
      vset)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      ;;
      feeds-import)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      background='FALSE'
      ;;
      cron)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      ;;
      cc)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      ;;
      dis)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      background='FALSE'
      ;;
      urol)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      background='FALSE'
      ;;
      ucrt)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      background='FALSE'
      ;;
      fr)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      ;;
      pm-uninstall)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      background='FALSE'
      ;;
      vdel)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      ;;
      cook)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      background='FALSE'
      ;;
      uuid-recreate)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      ;;
      ecl)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      ;;
      cis-sck)
      drushcommand=`echo "$drush" | cut -f 2- -d ' '`
      ;;
      *)
      badcommand=`echo "$drush" | cut -f 2- -d ' '`
      drushcommand="NULL"
      ;;
      esac
      if [[ $drushcommand = "NULL" ]]; then
        echo "$badcommand is not a supported drush command."
        rm /tmp/drush-lock
        exit 1
      fi
      echo "5" > $fileloc/$course.$service.progress
      echo "Your site has been installed, doing some clean up and you will be taken there soon!" >> $fileloc/$course.$service.progress
      # use this for debugging as it will print what it is doing to the file
      #echo "drush @$service.$course $drushcommand --y" >> $fileloc/$course.$service.progress
      # do most commands in a background thread
      if [[ $background = 'TRUE' ]]; then
          (drush --y --root=$drupalroot --v --uri=$hostname.$course $drushcommand < /dev/null &) >> $configsdir/logs/drush-create-site.log
        else
          drush --y --root=$drupalroot --v --uri=$hostname.$course $drushcommand >> $configsdir/logs/drush-create-site.log
      fi
    done
  fi
  # done running commands, now we add in our cache bin optimization settings
  sudo chmod 774 $drupalroot/sites/$subdir/$course/settings.php
  echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $drupalroot/sites/$subdir/$course/settings.php
  sudo chmod 444 $drupalroot/sites/$subdir/$course/settings.php
  sudo chmod 777 $drupalroot/sites/$service/services/$college/$course/settings.php
  echo "require_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $drupalroot/sites/$service/services/$college/$course/settings.php
  sudo chmod 444 $drupalroot/sites/$service/services/$college/$course/settings.php
  echo "6" > $fileloc/$course.$service.progress

  echo "$course was added by $requester on $date" | mail -s "$course has been added to $hostname" $admin
  echo "$course was added to $hostname on $date"
  if [[ -f  $coursefile.processing ]]; then
    sudo mv $coursefile.processing $coursefile.processed
  fi

  if [[ -f $fileloc/$course.$service.progress ]]; then
    sudo rm $fileloc/$course.$service.progress
  fi
done
sudo rm /tmp/drush-lock
