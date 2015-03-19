# a script to install server dependencies

# using yum to install the main packages
yes | yum -y install patch git nano gcc make mysql mysql-server httpd php php-gd php-xml php-pdo php-mbstring php-mysql php-pear php-devel php-pecl-ssh2 php-pecl-apc

yes | yum groupinstall 'Development Tools'

# using pecl to install uploadprogress
pecl channel-update pecl.php.net
# uploadprogress to get rid of that warning
pecl install uploadprogress

# adding uploadprogresss to php conf files
touch /etc/php.d/uploadprogress.ini
echo extension=uploadprogress.so > /etc/php.d/uploadprogress.ini

# set httpd_can_sendmail so drupal mails go out
setsebool -P httpd_can_sendmail on
# run the handsfree installer that's the same for all deployments
# todo pipe in values making this specific to the type of server its on
mkdir -p /var/www/elmsln
cd /var/www
git clone https://github.com/btopro/elmsln.git elmsln
# kick off hands free deployment
bash /var/www/elmsln/scripts/install/handsfree-install.sh
