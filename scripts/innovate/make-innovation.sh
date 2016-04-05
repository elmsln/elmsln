#!/bin/bash
# this script allows anyone to become an innovator. With this script, we start to
# truly unlock the potential of innovators out there regardless of ability. If
# you can "Site build" you will now be able to contribute meaningful, sustainable
# ideas to ELMSLN and the future of learning networks. With this script, we start
# the only truly sustainable system, one without self.

# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# load config
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

# see which site produced this so we can mirror it
if [ -z $1 ]; then
  elmslnwarn "You must supply a project name"
  exit 1
fi
# ensure we have a project name for this innovation
if [ -z $2 ]; then
  elmslnwarn "You must supply a project name"
  exit 1
fi
# ensure we have an author name
if [ -z $3 ]; then
  elmslnwarn "You must supply a project author"
  exit 1
fi
# ensure we have a drupal version
if [ -z $4 ]; then
  elmslnwarn "You must supply the Drupal version (7.x)"
  exit 1
fi

sitename=$1
projectname=$2
username=$3
major=$4

# go back to home directory
cd ~
# clone the repo local so we can issue a PR
git clone https://github.com/elmsln/innovations.git
cd innovations
# hard reset in case they made other stuff not yet accepted
git fetch --all
git reset --hard origin/master
git checkout -b "${username}-${projctname}"
# run commands to pull files down here
mkdir -p innovators/${username}/
cp -R {elmsln}/core/dslmcode/profiles/ulmus-${major}-1.x innovators/${username}/${major}/${projectname}
cd innovators/${username}/${major}/${projectname}
# step into the files and bulk target and replace the previous name spaces with the new ones
renames=('.travis.yml' 'drupal-org.make' 'local.make.example' 'drecipes/elmsln_ulmus.drecipe' 'ulmus.info' 'ulmus.install' 'ulmus.profile' 'themes/SUB_foundation_access/SUB_foundation_access.info' 'themes/SUB_foundation_access/css/SUB_styles.css' 'themes/SUB_foundation_access/template.php')
for rename in "${renames[@]}"
  do
  sed -i '' "s/ulmus/$projectname/g" $rename
  sed -i '' "s/SUB/$projectname/g" $rename
done
# move everything around
mv ulmus.info $projectname.info
mv ulmus.profile $projectname.profile
mv ulmus.install $projectname.install
mv drecipes/elmsln_ulmus.drecipe "drecipes/elmsln_${projectname}.drecipe"
mv themes/SUB_foundation_access/css/SUB_styles.css "themes/SUB_foundation_access/css/${projectname}_styles.css"
mv themes/SUB_foundation_access/SUB_foundation_access.info "themes/SUB_foundation_access/${projectname}_foundation_access.info"
mv themes/SUB_foundation_access "themes/${projectname}"

# ensure these are enabled through they should be
drush @innovate.${sitename} en profiler_builder features_builder --y
# build in this directory
drush @innovate.${sitename} fb --y
# @todo copy these over since we should be able to find them
# cp -R $elmsln/domains/${sitename}/sites/all/modules/build/* modules/features/
# @todo finisht his DDT statement so we can store that
drush @none ddt @innovate.${sitename}
# back out to the top git repo
cd ~/innovations
git add -a
# git commit credit the author so others can see who these innovators are
git commit -m "A new innovation called ${projectname} is knocking" --author="${username}"
# push to the repo branch we made
git push origin "${username}-${projctname}"
git request-pull https://github.com/elmsln/innovations.git "${username}-${projctname}":master