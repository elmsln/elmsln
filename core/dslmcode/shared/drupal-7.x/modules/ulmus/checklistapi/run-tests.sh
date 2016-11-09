#!/usr/bin/env sh

# @file
# This script runs automated tests for Checklist API module.

# Usage: $ ./run-tests.sh [web-server-shell-user] (defaults to "www-data")
# e.g., $ ./run-tests.sh
# or $ ./run-tests.sh apache

server_user=${1:-www-data}

drush test-run ChecklistapiUnitTestCase,ChecklistapiWebTestCase sudo -u ${server_user}
