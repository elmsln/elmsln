#!/usr/bin/sh
# Pull in a elmsln deployment from another server and mirror it locally
# this is useful when you need to move deployments between environments
# like prod, stage, dev or down to local dev
# @todo we need to write into the local config.cfg variables the settings from remote
# otherwise we'll have pulled in these stacks and they won't be able to run since it uses
# the grouping unit in the site-alias script and the university variable during this script
# to rewrite the connection addresses
# @todo make sure we verify A WHOLE BUNCH OF TIMES BEFORE LETTING THIS RUN :)
source /var/www/elmsln/config/scripts/drush-create-site/config.cfg
txtbld=$(tput bold)             # Bold
bldgrn=$(tput setaf 2) #  green
bldred=${txtbld}$(tput setaf 1) #  red
txtreset=$(tput sgr0)
elmslnecho(){
  echo "${bldgrn}$1${txtreset}"
}
elmslnwarn(){
  echo "${bldred}$1${txtreset}"
}

elmslnwarn 'This is going to establish a connection to a real server you have, then pull down the code and database in question and mirror it in this system so you can work elsewhere.'
elmslnwarn "If these things sound scary then you probably shouldn't use this! Hit control and C to back out!"

# location of config and domain directories as shortcuts
dir="$configsdir"
domains="${webdir}/"
MYSQL=`which mysql`
localdbsu=$dbsu
localdbsupw=$dbsupw
# make sure we escape the . character when passing these around
localaddress=$address
localserviceaddress=$serviceaddress
localprefix=$(echo "$serviceprefix" | sed 's/\./\\./g')
localprotocol=$protocol
# tmp directory for the migration
dbs="/tmp/elmsln-pull-down/"
# ensure this directory exists and is empty
sudo mkdir -p $dbs
# write it to the user in question
sudo chown $USER $dbs
# support for hook architecture in bash call outs
hooksdir="${dir}/scripts/hooks/pull-down"

# hook pre-pull-down.sh
if [ -f  $hooksdir/pre-pull-down.sh ]; then
  # invoke this hook cause we found a file matching the name we need
  bash $hooksdir/pre-pull-down.sh
fi

if [ -z "$1" ]; then
  prompt="What is your user name? "
  read -rp "$prompt" remotename
else
  remotename=$1
fi

if [ -z "$2" ]; then
  prompt="What server do you want to connect to? "
  read -rp "$prompt" remoteaddress
else
  remoteaddress=$2
fi

if [ -z "$3" ]; then
  prompt="What port (usually 22 / 2222 are common)? "
  read -rp "$prompt" remoteport
else
  remoteport=$3
fi


if [ -z "$4" ]; then
  prompt="What email address do you want to sign keys and direct mail to? "
  read -rp "$prompt" remoteemail
else
  remoteemail=$4
fi

if [ -z "$5" ]; then
  prompt="Is this a mirror or a development instance? A mirror would be able to go Prod to Stage then Stage to Prod (for example) without issues. This WILL mirror DB accounts though (as a security notice). A development instance will sanitize user accounts and perform other operations which effectively make it impossible to push correctly to other environemnts.
1. mirror
2. development
"
  read -rp "$prompt" pulldowntype
else
  pulldowntype=$5
fi
if [ -z "$6" ]; then
  prompt="What alias group should we do this to? (@elmsln for everything or @courses-all for all courses for example)"
  read -rp "$prompt" aliasgroup
else
  aliasgroup=$6
fi

# copy id to the server
ssh-keygen -t rsa -C "$remoteemail"
ssh-copy-id -i ~/.ssh/id_rsa.pub "-p $remoteport $remotename@$remoteaddress"

# keep a back up of local config directory
sudo mv "${dir}" "${dir}_tmp"
# this allows for always using the local pull down hooks
hooksdir="${dir}_tmp/scripts/hooks/pull-down"

#
# START REMOTE STUFF
#

# dump to db export via remote execution
elmslnecho 'spidering database dump of the remote systems'
ssh -p $remoteport $remotename@$remoteaddress "drush $aliasgroup sql-dump --result-file --y"
# rsync full directory from that server
elmslnecho 'rsyncing down the config directory from the remote source, might take awhile...'
rsync -az -e "ssh -p $remoteport" "$remotename@$remoteaddress:${dir}/" "${dir}/"
elmslnecho 'rsyncing domain symlinks from the remote source'
rsync -az -e "ssh -p $remoteport" "$remotename@$remoteaddress:${domains}" "${domains}"
# pull in sql files
elmslnecho 'pull across the database files that we dumped in the previous command'
rsync -az -e "ssh -p $remoteport" "$remotename@$remoteaddress:/home/$remotename/drush-backups/" "$dbs"

#
# END REMOTE STUFF
#

#
# START LOCAL STUFF
#

# hook pre-rewrites.sh useful for modifications prior to drush being invoked
if [ -f  $hooksdir/pre-rewrites.sh ]; then
  # invoke this hook cause we found a file matching the name we need
  bash $hooksdir/pre-rewrites.sh
fi

# source what the variables are in the remote configuration
source /var/www/elmsln/config/scripts/drush-create-site/config.cfg

# overwrite scripts as these are all local to this deployment and should not change
# this includes db creds / info about the network install here as well as potential
# hooks involved in communicating with this effectively
sudo rm -rf "${dir}/scripts/"
sudo cp -r "${dir}_tmp/scripts/" "${dir}/scripts/"
sudo rm -rf "${dir}_tmp"
# reset hooks back to look in the normal location
hooksdir="${dir}/scripts/hooks/pull-down"

# make sure . doesn't do a wildcard replacement in these files!
serviceprefix=$(echo "$serviceprefix" | sed 's/\./\\./g')
# loop through sites.php files and update urls
for i in $(find ${dir}/stacks/*/sites/sites.php -type f); do
  perl -pi -e "s/$address/$localaddress/g" "$i"
  perl -pi -e "s/$serviceaddress/$localserviceaddress/g" "$i"
  perl -pi -e "s/$serviceprefix/$localprefix/g" "$i"
done
# these live at 2 3 and 4 levels deep in folder nesting at times
for i in $(find ${dir}/stacks/*/sites/*/*/*/*/settings.php -type f); do
  perl -pi -e "s/$address/$localaddress/g" "$i"
  perl -pi -e "s/$serviceaddress/$localserviceaddress/g" "$i"
  perl -pi -e "s/$serviceprefix/$localprefix/g" "$i"
  perl -pi -e "s/$protocol/$localprotocol/g" "$i"
  tmpbase='define("DRUPAL_ROOT", "/var/www/elmsln/config/shared/drupal-7.x/"); include_once "'$i'";'
  tmp=$tmpbase'echo $databases["default"]["default"]["username"];'
  tmpusr=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["password"];'
  tmppwd=$(php -r "$tmp")
  if [ $pulldowntype == '1' ]; then
    Q1="GRANT ALL ON *.* TO '$tmpusr'@'localhost' IDENTIFIED BY '$tmppwd';"
    Q2="FLUSH PRIVILEGES;"
    SQL="${Q1}${Q2}"
    $MYSQL --user=$localdbsu --password=$localdbsupw -e "$SQL"
  else
    perl -pi -e "s/$tmpusr/$localdbsu/g" "$i"
    perl -pi -e "s/$tmppwd/$localdbsupw/g" "$i"
  fi
done
for i in $(find ${dir}/stacks/*/sites/*/*/*/settings.php -type f); do
  perl -pi -e "s/$address/$localaddress/g" "$i"
  perl -pi -e "s/$serviceaddress/$localserviceaddress/g" "$i"
  perl -pi -e "s/$serviceprefix/$localprefix/g" "$i"
  perl -pi -e "s/$protocol/$localprotocol/g" "$i"
  tmpbase='define("DRUPAL_ROOT", "/var/www/elmsln/config/shared/drupal-7.x/"); include_once "'$i'";'
  tmp=$tmpbase'echo $databases["default"]["default"]["username"];'
  tmpusr=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["password"];'
  tmppwd=$(php -r "$tmp")
  if [ $pulldowntype == '1' ]; then
    Q1="GRANT ALL ON *.* TO '$tmpusr'@'localhost' IDENTIFIED BY '$tmppwd';"
    Q2="FLUSH PRIVILEGES;"
    SQL="${Q1}${Q2}"
    $MYSQL --user=$localdbsu --password=$localdbsupw -e "$SQL"
  else
    perl -pi -e "s/$tmpusr/$localdbsu/g" "$i"
    perl -pi -e "s/$tmppwd/$localdbsupw/g" "$i"
  fi
done
for i in $(find ${dir}/stacks/*/sites/*/*/settings.php -type f); do
  perl -pi -e "s/$address/$localaddress/g" "$i"
  perl -pi -e "s/$serviceaddress/$localserviceaddress/g" "$i"
  perl -pi -e "s/$serviceprefix/$localprefix/g" "$i"
  perl -pi -e "s/$protocol/$localprotocol/g" "$i"
  tmpbase='define("DRUPAL_ROOT", "/var/www/elmsln/config/shared/drupal-7.x/"); include_once "'$i'";'
  tmp=$tmpbase'echo $databases["default"]["default"]["username"];'
  tmpusr=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["password"];'
  tmppwd=$(php -r "$tmp")
  tmp=$tmpbase'echo $databases["default"]["default"]["database"];'
  tmpdb=$(php -r "$tmp")
  # @todo dig deeper on this part as to what's not going through; command looks sound
  if [ $pulldowntype == '1' ]; then
    Q1="GRANT ALL ON ${tmpdb}.* TO '$tmpusr'@'localhost' IDENTIFIED BY '$tmppwd';"
    Q2="FLUSH PRIVILEGES;"
    SQL="${Q1}${Q2}"
    $MYSQL --user=$localdbsu --password=$localdbsupw -e "$SQL"
  else
    perl -pi -e "s/$tmpusr/$localdbsu/g" "$i"
    perl -pi -e "s/$tmppwd/$localdbsupw/g" "$i"
  fi
done
# make sure we update the elmsln scripted keychain to match the paths
# otherwise our calls will attempt to go out the door and have the ability to work .. cause its a network
scripted="/var/www/elmsln/config/shared/drupal-7.x/modules/_elmsln_scripted/${university}/${university}_${host}_settings/${university}_${host}_settings.module"
perl -pi -e "s/$address/$localaddress/g" "$scripted"
perl -pi -e "s/$serviceaddress/$localserviceaddress/g" "$scripted"
perl -pi -e "s/$serviceprefix/$localprefix/g" "$scripted"
perl -pi -e "s/$protocol/$localprotocol/g" "$i"

# attempt to create any dbs that are missing
drush $aliasgroup sql-create --y

# make sure we only have the latest possible timestamp in case additional
# backups were brought along for the ride. this way we don't affect the
# environment we copied from but we also get only what we wanted
for i in $(find $dbs*/ -maxdepth 0 -type d); do
  cd $i
  # sort by name which will give us date ordered, then only keep last one
  (ls -t|head -n 1;ls)|sort|uniq -u|xargs rm -rf
done

# now that it's cleaned up, find the sql file in each directory
# directory part one minus _*_ is what we want to throw in as our alias
for i in $(find $dbs*/*/*.sql -type f); do
  dirname=$(dirname $i)
  # turn directory name into an array
  IFS='/' read -a dirarr <<< "$dirname"
  # turn directory part name into alias name
  IFS='_' read -a arr <<< "${dirarr[3]}"
  # turn the array into a drush alias
  # 2 part arrays are authorities
  # 3 part arrays are services
  if [ "${#arr[@]}" == 3 ]; then
      drushalias="@${arr[0]}.${arr[2]}"
    else
      drushalias="@${arr[0]}"
  fi
  # ignore default DBs as they are meaningless
  if [ ${arr[0]} != 'default' ]; then
    drush $drushalias sql-query --file=$i --y
    # if this is a dev instance of any kind then sanitize the data
    if [ $pulldowntype != '1' ]; then
      drush $drushalias sqlsan --y
    fi
  fi
done

drush $aliasgroup rr --y
# sync the registry to match since we brought in a new scripted item
drush @online cis-sync-reg

# hook post-pull-down.sh
if [ -f  $hooksdir/post-pull-down.sh ]; then
  # invoke this hook cause we found a file matching the name we need
  bash $hooksdir/post-pull-down.sh $remoteemail $aliasgroup
fi

# clean up tmp directory
sudo rm -rf $dbs
# run permission clean up
bash /var/www/elmsln/scripts/utilities/harden-security.sh
elmslnecho 'Your site should now be available local to this machine. All communications between sites in the network have been rewritten to talk to each other. Enjoy!'