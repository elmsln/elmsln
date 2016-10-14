# Vagrant Dev

- vagrant ssh
- cd to vagrant home directory
``` 
cd
```
- install NVM and node 6.7
```
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.32.0/install.sh | bash
source .bashrc
nvm install 6.7
```
- cd to the app directory inside of foundation_access
```
cd /var/www/elmsln/core/dslmcode/shared/drupal-7.x/themes/elmsln_contrib/foundation_access/app
```
- update your dev dependancies since they change all the time ;)
```
npm update --save-dev
```
- install gulp locally
```
npm install gulp --save-dev
```
- install bower globally
```
npm install -g bower
```
- install anything else from the node package manager
```
npm install
```
- install bower components
```
bower install
```
- run gulp to watch for file changes
```
./node_modules/.bin/gulp
```
- run gulp-build to build once and exit
```
.node_modules/.bin/gulp build
```
