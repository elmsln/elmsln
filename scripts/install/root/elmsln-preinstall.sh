#!/bin/bash
# preinstall is all the steps listed in INSTALL.txt but attemps to automate
# as many of them as possible. This will try and establish elmsln
# on the host system, then walk through all the directory operations,
# file system changes, example repo checkout and forking, confg.cfg
# creation, as well as hooking up crontab and the optimizations to
# apc,php,mysql and apache that can help make ELMSLN rock solid.
# It also tries to figure out what OS its installed on and then apply
# changes appropriate to that system. At the very least this can better
# inform you as to what its doing where

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# provide messaging colors for output to console
txtbld=$(tput bold)             # Bold
bldgrn=${txtbld}$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
  return 1
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
  return 1
}
# Define seconds timestamp
timestamp(){
  date +"%s"
}
# generate a uuid
getuuid(){
  uuidgen -rt
}
# check that we are the root user
if [[ $EUID -ne 0 ]]; then
  elmslnwarn "Please run as root"
  exit 0
fi
# we assume you install it in the place that we like
cd /var/www/elmsln

# blow away old repo
rm -rf config
git clone https://github.com/btopro/elmsln-config-example.git config
cd /var/www/elmsln/config
rm -rf .git

# make a new repo
git init
git add -A
git commit -m "initial ELMSLN config"

elmslnecho "Enter the git repo you want to keep config in sync with: (ex: {user}@{YOURPRIVATEREPO}:YOU/elmsln-config-YOURUNIT.git)"
read gitrepo
# ensure they type yes, this is a big deal command
if [ "$gitrepo" != "" ]; then
  elmslnecho "attempting to push current structure to the repo listed"
  git remote add origin $gitrepo
  git push origin master
else
  elmslnwarn "You did not enter a repo so this is in local version control but not tracked remotely. It is highly recommended that you hook this up to a remote repository in the future!"
fi

# detect what OS this is on and make suggestions for settings
cat /etc/*-release
elmslnecho "The above should list information about the systemt this is being installed on. We currently support semi-automated install routines for RHEL, CentOS and Ubuntu. Please verify the above and select one of the following options:"
elmslnecho "1. RHEL / CentOS"
elmslnecho "2. Ubuntu"
elmslnecho "3. other"
read os
if [ $os == '1' ]; then
  elmslnecho "treating this like a RHEL / CentOS install"
  wwwuser='apache'
  elmslnecho "www user automatically set to ${wwwuser}"
  apcini="/etc/php.d/apc.ini"
  elmslnecho "apc.ini automatically set to ${apcini}"
  phpini="/etc/php.ini"
  elmslnecho "php.ini automatically set to ${phpini}"
  mycnf="/etc/my.cnf"
  elmslnecho "my.cnf automatically set to ${mycnf}"
  crontab="/etc/crontab"
  elmslnecho "crontab automatically set to ${crontab}"
  domains="/etc/httpd/conf.d/domains.conf"
  elmslnecho "domains automatically set to ${domains}"
  zzz_performance="/etc/httpd/conf.d/zzz_performance.conf"
  elmslnecho "apache perforamnce tuning automatically set to ${zzz_performance}"
elif [ $os == '2' ]; then
  elmslnecho "treating this like ubuntu"
  wwwuser='www-data'
  elmslnecho "www user automatically set to ${wwwuser}"
  apcini="/etc/php5/conf.d/apc.ini"
  elmslnecho "apc.ini automatically set to ${apcini}"
  phpini="/etc/php5/apache2/php.ini"
  elmslnecho "php.ini automatically set to ${phpini}"
  mycnf="/etc/php5/conf.d/mysql.ini"
  elmslnecho "my.cnf automatically set to ${mycnf}"
  crontab="/etc/crontab"
  elmslnecho "crontab automatically set to ${crontab}"
  domains="/etc/apache2/sites-available/elmsln.conf"
  elmslnecho "domains automatically set to ${domains}"
  zzz_performance="/etc/apache2/sites-available/zzz_performance.conf"
  elmslnecho "apache perforamnce tuning automatically set to ${zzz_performance}"
else
  elmslnecho "need to ask you some more questions"
  # ask about apache
  elmslnecho "www user, what does apache run as? (www-data and apache are common)"
  read wwwuser

  elmslnecho "where is apc.ini? ex: /etc/php.d/apc.ini"
  read apcini

  elmslnecho "where is php.ini? ex: /etc/php.ini"
  read phpini

  elmslnecho "where is my.cnf? ex: /etc/my.cnf"
  read mycnf

  elmslnecho "where is crontab? ex: /etc/crontab"
  read crontab

  elmslnecho "where should elmsln apache domains.conf files live? ex: /etc/httpd/conf.d/domains.conf"
  read domains

  elmslnecho "where should elmsln apache performance tweaks live? ex: /etc/httpd/conf.d/zzz_performance.conf"
  read zzz_performance
fi

# based on where things commonly are. This would allow for non-interactive
# creation if the user approves of what has been found and allow us to
# do an automatic creation flag to establish this stuff without any input!

# work against the config file
config='/var/www/elmsln/config/scripts/drush-create-site/config.cfg'
touch $config
# step through creation of the config.cfg file
cat "#university / institution deploying this instance" >> $config
elmslnecho "what is your uniersity abbreviation? (ex psu)"
read university
cat "university='${university}'" >> $config

elmslnecho "two letter abbreviation for deployment? (ex aa for arts / architecture)"
read host
cat "host='${host}'" >> $config

elmslnecho "default email ending? (ex @psu.edu)"
read emailending
cat "emailending='${emailending}'" >> $config

elmslnecho "base address for deployment? (ex aanda.psu.edu)"
read address
cat "address='${address}'" >> $config

elmslnecho "web service based address for deployment? (ex otherpath.psu.edu. this can be the same as the previous address but for increased security it is recommended you use a different one.)"
read serviceaddress
cat "serviceaddress='${serviceaddress}'" >> $config

elmslnecho "web service prefix? (if calls come from data.courses.otherpath.psu.edu then this would be 'data.' if you don't create domains this way then leave this blank)"
read serviceprefix
cat "serviceprefix='${serviceprefix}'" >> $config

elmslnecho "protocol for web traffic? (think long and hard before you type anything other then 'https'. there's a lot of crazy stuff out there so its better to encrypt everything.. EVERYTHING!)"
read protocol
cat "protocol='${protocol}'" >> $config

cat "#email that the site uses to send mail" >> $config
elmslnecho "site email address to use? (ex siteaddress@you.edu)"
read site_email
cat "site_email='${site_email}'" >> $config

cat "#administrator e-mail or alias" >> $config
elmslnecho "administrator e-mail or alias? (ex admin@you.edu)"
read admin
cat "admin='${admin}'" >> $config

# if there's a scary part it's right in here for some I'm sure
cat "#database superuser credentials" >> $config
elmslnecho "database superuser credentials? (this is only stored in the config.cfg file. it is recommended you create an alternate super user other then true root. user needs full permissions including grant since this is what requests new drupal sites to be produced)"
read dbsu
cat "dbsu='${dbsu}'" >> $config

elmslnecho "database superuser password? (same notice as above)"
read dbsupw
cat "dbsupw='${dbsupw}'" >> $config

# this was read in from above or automatically supplied based on the system type
cat "#www user, what does apache run as? www-data and apache are common" >> $config
cat "wwwuser='${wwwuser}'" >> $config

cat "#webgroup, usually admin if sharing with other developers else leave root" >> $config
elmslnecho "webgroup? (usually admin if sharing with other developers else leave root)"
read webgroup
cat "webgroup='${webgroup}'" >> $config

# append all these settings that we tell people NOT to modify
cat "\n" >> $config
cat "# uncomment the following if you are not using SSO" >> $config
cat "#send_requester_pw=yes" >> $config
cat "# where is elmsln installed, not recommended to move from here" >> $config
cat "elmsln=/var/www/elmsln" >> $config
cat "\n" >> $config
cat "# these vars shouldn't need changing if $elmsln is set properly" >> $config
cat "webdir=$elmsln/domains" >> $config
cat "# jobs location where job files write to" >> $config
cat "fileloc=$elmsln/config/jobs" >> $config
cat "# hosts to allow split groups of elmsln based on college / group" >> $config
cat "hostfile=$elmsln/config/scripts/drush-create-site/hosts" >> $config
cat "# compiled drupal \"stacks\"" >> $config
cat "stacks=$elmsln/core/dslmcode/stacks" >> $config
cat "# location of drupal private files" >> $config
cat "drupal_priv=$elmsln/config/private_files" >> $config
cat "# configsdir" >> $config
cat "configsdir=$elmsln/config" >> $config
# capture automatically generated values that can be used to reference this
# exact deployment of ELMSLN in the future
cat "\n\n" >> $config
cat "# ELMSLN INSTALLER GENERATED VALUES" >> $config
cat "# Do not modify below this line" >> $config
# capture install time; this could be used in the future similar to the
# drup timestamping to see if there are structural upgrade .sh commands needed
# contextually based on when we are installed. This will start to allow for
# hook_update_n style updates but at a bash / deployment level.
installed="$(timestamp)"
cat "elmsln_installed='${installed}'" >> $config
uuid="$(getuuid)"
# a uuid which data can be related on
cat "elmsln_uuid='${uuid}'" >> $config

# allow for opt in participation in our impact program
elmslnecho "Would you like to send anonymous usage statistics to http://elmsln.org for data visualization purposes? (type yes or anything else to opt out)"
read yesprompt
# ensure they type yes, this is a big deal command
if [[ $yesprompt == 'yes' ]]; then
  # include this instance in our statistics program
  cat "elmsln_stats_program='yes'" >> $config
else
  # we respect privacy even if it leads to less cool visualizations :)
  cat "elmsln_stats_program='no'" >> $config
fi

# performance / recommended settings
cat /var/www/elmsln/docs/apc.txt >> $apcini
cat /var/www/elmsln/docs/php.txt >> $phpini
cat /var/www/elmsln/docs/my.txt >> $mycnf
cat /var/www/elmsln/docs/crontab.txt >> $crontab
cp /var/www/elmsln/docs/zzz_performance.conf $zzz_performance

# account for ubuntu being a little different here when it comes to apache
if [ $os == '2' ]; then
  ln -s /etc/apache2/sites-available/elmsln.conf /etc/apache2/sites-enabled/elmsln.conf
  ln -s /etc/apache2/sites-available/zzz_performance.conf /etc/apache2/sites-enabled/zzz_performance.conf
fi

# setup site removal admin tool
ln -s /var/www/elmsln/scripts/drush-create-site /usr/local/bin/drush-create-site
chmod 744 /usr/local/bin/drush-create-site/rm-site.sh

# shortcuts for ease of use
homebash="${HOME}/.bashrc"
touch $homebash
ln -s /var/www/elmsln ~/elmsln
cat "alias g='git'" >> $homebash
cat "alias d='drush'" >> $homebash
cat "alias l='ls -laHD'" >> $homebash
cat "alias drs='/usr/local/bin/drush-create-site/rm-site.sh'" >> $homebash

# setup drush
curl -sS https://getcomposer.org/installer | php
mv composer.phar /usr/local/bin/composer
sed -i '1i export PATH="$HOME/.composer/vendor/bin:$PATH"' $homebash
source $homebash
composer global require drush/drush:6.*
mkdir $HOME/.drush/
# copy in the elmsln server stuff as the baseline for .drush
cp -r /var/www/elmsln/scripts/drush/server/* $HOME/.drush/
# stupid ubuntu drush thing to work with sudo
if [[ $os == '2' ]]; then
  ln -s /root/.composer/vendor/drush/drush /usr/share/drush
fi
drush cc drush

# try to automatically author the domains file(s)
cp /var/www/elmsln/docs/domains.txt $domains
# replace servicedomain partial with what was entered above
sed 's/SERVICEYOURUNIT.edu/${serviceaddress}/g' $domains > $domains
# replace domain partial with what was entered above
sed 's/YOURUNIT.edu/${address}/g' $domains > $domains
# replace servicedomain prefix if available with what was entered above
sed 's/DATA./${serviceprefix}/g' $domains > $domains

# attempt to author the https domain if they picked it, let's hope everyone does
if [[ $protocol == 'https']]; then
  sec=${domains/.conf/_secure.conf}
  cp $domains $sec
  # replace referencese to port :80 w/ 443
  sed 's/<VirtualHost *:80>/<VirtualHost *:443>/g' $sec > $sec
  elmslnecho "${sec} was automatically generated since you said you are using https. please verify this file."
else
  elmslnwarn "You really should use https and invest in certs... seriously do it!"
fi

# ubuntu restarts differently
if [[ $os == '2' ]]; then
  apache2ctl configtest
  service apache2 restart
else
  apachectl configtest
  /etc/init.d/httpd restart
fi

elmslnecho "${domains} was automatically generated but you may want to verify the file regardless of configtest saying everything is ok or not."
elmslnecho "Everything should be in place, we are going to log you out now. Log back in and run the following:"
elmslnecho "bash /var/www/elmsln/scripts/install/elmsln-install.sh"
