#!/bin/bash
### Create the links of the required modules and libraries
### on the profile 'testing', then run the tests.

cd $(dirname $0)

### get the paths
drupal_dir=$(drush php-eval 'print realpath(".")')
testing_dir=$drupal_dir/profiles/testing

### list of the required modules (dependencies)
module_list="
    oauth2_client
    oauth2_server
    libraries
    ctools
    entity
    entityreference
    xautoload
"
### link the modules to the profile 'testing'
for module in $module_list
do
    module_path=$(drush php-eval "print drupal_get_path('module', '$module')")
    ln -sf $drupal_dir/$module_path $testing_dir/modules/
done

### link the required library oauth2-server-php
oauth2_server_php=$(drush php-eval 'print libraries_get_path("oauth2-server-php")')
mkdir -p $testing_dir/libraries/
ln -sf $drupal_dir/$oauth2_server_php $testing_dir/libraries/

### run the tests
drush test-clean
drush test-run OAuth2ClientTestCase
