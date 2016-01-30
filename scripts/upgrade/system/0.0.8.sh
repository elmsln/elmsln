#!/bin/bash
# not usually our style but this MUST be enables on all things
# previously created prior to the point in time this update exists
# til we resolve #523
~/.composer/vendor/bin/drush @elmsln en elmsln_core --y
