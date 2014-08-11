#!/bin/bash

# Step 1
step1() {
  # generate a scripted directory
  if [ ! -d ${moduledir} ];
    then
    sudo mkdir ${moduledir}
    sudo mkdir ${moduledir}/${university}
  fi
  # work on authoring the connector module automatically
  if [ ! -d ${moduledir}/${university}/${cissettings} ];
    then
    sudo mkdir ${moduledir}/${university}/${cissettings}
    infofile=${moduledir}/${university}/${cissettings}/${cissettings}.info
    modulefile=${moduledir}/${university}/${cissettings}/${cissettings}.module
    # write the .info file
    printf "name = ${university} ${host} Settings\ndescription = This contains registry information for all ${host} connection details\ncore = ${core}\npackage = ${university}" >> $infofile
    # write the .module file
    printf "<?php\n\n// service module that makes this implementation specific\n\n/**\n * Implements hook_cis_service_registry().\n */\nfunction ${university}_${host}_settings_cis_service_registry() {\n  \$items = array(\n" >> $modulefile
    # write the array of connection values dynamically
    for distro in "${distros[@]}"
    do
      # array built up to password
      printf "    // ${distro} distro instance called ${stacklist[$COUNTER]}\n    '${distro}' => array(\n      'protocol' => '${protocol}',\n      'service_address' => '${serviceprefix}${stacklist[$COUNTER]}.${serviceaddress}',\n      'address' => '${stacklist[$COUNTER]}.${address}',\n      'user' => 'SERVICE_${distro}_${host}',\n      'mail' => 'SERVICE_${distro}_${host}@${emailending}',\n      'pass' => '" >> $modulefile
      # generate a random 30 digit password
      pass=''
      for i in `seq 1 30`
      do
        let "rand=$RANDOM % 62"
        pass="${pass}${char[$rand]}"
      done
      # write password to file
      printf $pass >> $modulefile
      # finish off array
      printf "',\n      'instance' => ${instances[$COUNTER]},\n" >> $modulefile
      printf "      'default_title' => '${defaulttitle[$COUNTER]}',\n" >> $modulefile
      printf "      'ignore' => ${ignorelist[$COUNTER]},\n    ),\n" >> $modulefile
      COUNTER=$COUNTER+1
   done
    # close out function and file
    printf "  );\n\n  return \$items;\n}\n\n" >> $modulefile
    # add the function to include this in build outs automatically
    printf "/**\n * Implements hook_cis_service_instance_options_alter().\n */\nfunction ${university}_${host}_settings_cis_service_instance_options_alter(&\$options, \$course, \$service) {\n  // modules we require for all builds\n  \$options['en'][] = '$cissettings';\n}\n" >> $modulefile
  fi
}

# Step 2
step2() {
  #add site to the sites array
  printf "\$sites = array(\n  '$online_domain' => 'online/$host',\n" >> $sitedir/sites.php
  printf "  '$online_service_domain' => 'online/services/$host',\n);\n" >> $sitedir/sites.php
  # set base_url
  printf "\n\$base_url= '$protocol://$online_domain';" >> $sitedir/online/$host/settings.php
}

# Step 3
step3() {
  # add in our cache bins now that we know it built successfully
  printf "\n\n\$conf['cache_prefix'] = 'online_$host';" >> $sitedir/online/$host/settings.php
  printf "\n\nrequire_once DRUPAL_ROOT . '/../../shared/drupal-7.x/settings/shared_settings.php';" >> $sitedir/online/$host/settings.php

  # adding servies conf file
  if [ ! -d $sitedir/online/services/$host ];
    then
      sudo mkdir -p $sitedir/online/services/$host
      sudo mkdir -p $sitedir/online/services/$host/files
      sudo chown -R $wwwuser:$webgroup $sitedir/online/services/$host/files
      sudo chmod -R 755 $sitedir/online/services/$host/files
      if [ -f $sitedir/online/$host/settings.php ]; then
        sudo cp $sitedir/online/$host/settings.php $sitedir/online/services/$host/settings.php
      fi
      if [ -f $sitedir/online/services/$host/settings.php ]; then
        printf "\n\n\$conf['restws_basic_auth_user_regex'] = '/^SERVICE_.*/';" >> $sitedir/online/services/$host/settings.php
      fi
  fi

  # perform some clean up tasks
  # piwik directories
  sudo chown -R $wwwuser:$webgroup $elmsln/config/_nondrupal/piwik
  sudo chmod -R 755 $elmsln/config/_nondrupal/piwik
  sudo chown -R $wwwuser:$webgroup $elmsln/core/_nondrupal/piwik
  # check for tmp directory in config area
  if [ ! -d $elmsln/config/_nondrupal/piwik/tmp ];
  then
    sudo mkdir $elmsln/config/_nondrupal/piwik/tmp
    sudo chown -R $wwwuser:$webgroup $elmsln/config/_nondrupal/piwik/tmp
  fi
  sudo chmod -R 0755 $elmsln/config/_nondrupal/piwik/tmp
  # jobs file directory
  sudo chown -R $wwwuser:$webgroup $elmsln/config/jobs
  sudo chmod -R 755 $elmsln/config/jobs
  # make sure everything in that folder is as it should be ownerwise
  sudo chown -R $wwwuser:$webgroup $sitedir/online/$host/files
}
