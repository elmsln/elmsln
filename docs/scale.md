## Scale
elmsln has been built for high scale environments through flexibility in network design.When systems talk to each other they do so pver restful web communications. By dong this, it means the different systems of elmsln can live anywhere as a result. deployments start off generally in one sever but through automated parcial migrations you can gain miltiple servers powering one network.

## PHP-FPM using mod_fastcgi for apache 2.2 and php 5.6
- First remove all your current php modules

```bash
yum remove php php-cli php-common php-devel php-gd php-mbstring php-mcrypt php-mysqlnd php-opcache php-pdo php-pear php-pecl-apcu php-pecl-igbinary php-pecl-jsonc php-pecl-jsonc-devel php-pecl-memcache php-pecl-memcached php-pecl-mongo php-pecl-msgpack php-pecl-sqlite php-pecl-ssh2 php-pecl-yaml php-pecl-zip php-pgsql php-process php-xml 
```
- Re-install them with php5.6 using the remi repo

```bash
yum install --enablerepo=remi-php56 php-fpm php-cli php-common php-devel php-gd php-mbstring php-mcrypt php-mysqlnd php-opcache php-pdo php-pear php-pecl-apcu php-pecl-igbinary php-pecl-jsonc php-pecl-jsonc-devel php-pecl-memcache php-pecl-memcached php-pecl-mongo php-pecl-msgpack php-pecl-sqlite php-pecl-ssh2 php-pecl-yaml php-pecl-zip php-pgsql php-process php-xml 
```
- OPTIONAL - Remove /etc/httpd/conf.d/php.conf.rpmsave

- install the repo for fastcgi and then install fastcgi

```bash
sudo rpm --import http://dag.wieers.com/rpm/packages/RPM-GPG-KEY.dag.txt
sudo rpm -ivh http://pkgs.repoforge.org/rpmforge-release/rpmforge-release-0.5.3-1.el6.rf.x86_64.rpm
sudo yum install mod_fastcgi
```

- create /usr/lib/cgi-bin

``` bash
mkdir -p /usr/lib/cgi-bin
```

- Paste the following to the bottom of /etc/httpd/conf.d/fastcgi.conf

```bash
<IfModule mod_fastcgi.c>
      DirectoryIndex index.html index.shtml index.cgi index.php
      AddHandler php5-fcgi .php
      Action php5-fcgi /php5-fcgi
      Alias /php5-fcgi /usr/lib/cgi-bin/php5-fcgi
      FastCgiExternalServer /usr/lib/cgi-bin/php5-fcgi -host 127.0.0.1:9000 -pass-header Authorization
</IfModule>
```

- Change in /etc/httpd/conf.d/fastcgi.conf

``` bash
# wrap all fastcgi script calls in suexec
FastCgiWrapper On
```

to 

``` bash
# wrap all fastcgi script calls in suexec
FastCgiWrapper Off
```

- restart apache
```bash
service httpd restart
```
- edit /etc/php-fpm.d/www.conf
-- A good starting point for most people would be

```bash
pm.max_children = 20 
pm.start_servers = 3 
pm.min_spare_server = 3 
pm.max_spare_servers = 5
pm.max_requests = 1500
```

- you will want to monitor you memory useage over time and adjust the above settings in very small incremental changes. 

- modify your .htaccess files to allow basic authorization
```
  # Basic authorization when using FCGI
  RewriteRule .* - [E=HTTP_AUTHORIZATION:%{HTTP:Authorization}]
```
- start php-fpm
- 
```bash
service php-fpm start
chkconfig php-fpm on
```

## Vagrant
vagrant is a reverse proxie that can be employed for the delivery of static assets and annonymous cpurse trafdix. if you are planning to acale elmslm for annonymous traffix it ia recommended touse a reverse proxie to hit higher load.

## Pound
