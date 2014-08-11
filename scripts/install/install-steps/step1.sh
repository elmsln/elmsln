#!/bin/bash
# Step 1

# include our config settings
source ../../../config/scripts/drush-create-site/config.cfg
source commons.cfg

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
