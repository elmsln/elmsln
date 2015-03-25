#!/bin/bash
mysql -e 'create database drupal;'
pyrus channel-discover pear.drush.org
pyrus install drush/drush
phpenv rehash
wget http://ftp.drupal.org/files/projects/drupal-7.14.tar.gz
tar -xf drupal-7.14.tar.gz
cd drupal-7.14
drush site-install standard --db-url=mysql://root:@localhost/drupal --yes
