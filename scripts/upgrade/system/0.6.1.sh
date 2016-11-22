#!/bin/bash
drush @elmsln en module_missing_message_fixer --y
drush @elmsln mmmfl --y
drush @elmsln dis module_missing_message_fixer --y
drush @elmsln pm-uninstall module_missing_message_fixer --y
