#!/bin/bash
# where am i? move to where I am. This ensures source is properly sourced
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# move back to install root
cd ../
# CLI arguments passed into the request engine
# operation and site name are the args supported via this method
php system/api.php --op=$1 --siteName=$2 --iamUser=$3
