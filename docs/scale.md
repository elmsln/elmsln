## Scale
ELMSLN continues to gain ground in the area of performance. It is being developed with high scale environments in mind, while retaining flexibility in its network design. Its systems talk to each other via web services using restful web communications. By dong this, it means that the different systems of elmsln can live anywhere as a result. 

Deployments start off generally in one sever but through automated partial migrations you can gain miltiple servers powering one network.

## Performance
ELMSLN's latest modification is the use of PHP-FPM and mod_fastcgi.

## A quick guide to installing PHP-FPM using mod_fastcgi for apache 2.2 and php 5.6
If you currently have php <= 5.5 installed you will want to upgrade to php 5.6. You will need the remi repo for this if you don't have it already. 



If you want to upgrade to use php-fpm you will need to perform the steps below.

- You will also want to find what php modules you have installed so you know what all you need to replace. Once you know you can use your package manager to remove and reinstall them sans mod_php.

What we did for our RHEL based system.

```bash
yum list installed | grep php
```

Then we removed all of the php modules so we could start with a clean slate.

```bash
yum remove php php-cli php-common php-devel php-gd php-mbstring php-mcrypt php-mysqlnd php-opcache php-pdo php-pear php-pecl-apcu php-pecl-igbinary php-pecl-jsonc php-pecl-jsonc-devel php-pecl-memcache php-pecl-memcached php-pecl-mongo php-pecl-msgpack php-pecl-sqlite php-pecl-ssh2 php-pecl-yaml php-pecl-zip php-pgsql php-process php-xml 
```
Next we re-installed needed php modules using the remi-php56 repo. Notice that we installed php-fpm and not php this time around.

```bash
yum install --enablerepo=remi-php56 php-fpm php-cli php-common php-devel php-gd php-mbstring php-mcrypt php-mysqlnd php-opcache php-pdo php-pear php-pecl-apcu php-pecl-igbinary php-pecl-jsonc php-pecl-jsonc-devel php-pecl-memcache php-pecl-memcached php-pecl-mongo php-pecl-msgpack php-pecl-sqlite php-pecl-ssh2 php-pecl-yaml php-pecl-zip php-pgsql php-process php-xml 
```


RHEL based systems don't come with mod_fastcgi by default so we needed to install the repo from dag.wiers.com

```bash
sudo rpm --import http://dag.wieers.com/rpm/packages/RPM-GPG-KEY.dag.txt
sudo rpm -ivh http://pkgs.repoforge.org/rpmforge-release/rpmforge-release-0.5.3-1.el6.rf.x86_64.rpm
sudo yum install mod_fastcgi
```

In order for this to work you need to create /usr/lib/cgi-bin

``` bash
mkdir -p /usr/lib/cgi-bin
```

This next bit of config allows php to run globally via the fastcgi module. Paste the following to the bottom of /etc/httpd/conf.d/fastcgi.conf

```bash
<IfModule mod_fastcgi.c>
      DirectoryIndex index.html index.shtml index.cgi index.php
      AddHandler php5-fcgi .php
      Action php5-fcgi /php5-fcgi
      Alias /php5-fcgi /usr/lib/cgi-bin/php5-fcgi
      FastCgiExternalServer /usr/lib/cgi-bin/php5-fcgi -host 127.0.0.1:9000 -pass-header Authorization
</IfModule>
```

While you are editing /etc/httpd/conf.d/fastcgi.conf, you need to change the FastCgiWrapper to not wrap scripts calls in suexec. 

Change 

``` bash
# wrap all fastcgi script calls in suexec
FastCgiWrapper On
```

to 

``` bash
# wrap all fastcgi script calls in suexec
FastCgiWrapper Off
```


Next you need to edit /etc/php-fpm.d/www.conf
A good starting point for most people would look something like this.

```bash
pm.max_children = 20 
pm.start_servers = 3 
pm.min_spare_server = 3 
pm.max_spare_servers = 5
pm.max_requests = 1500
```
The above config says, start up 3 servers that each have 20 children. If needed add more servers up to 5. Each child can allow up to 1500 requests before needing to be respawned. As stated this is just a starting point and you will want to monitor you memory useage over time and adjust the above settings in very small incremental changes. 

You will need to modify your .htaccess files to allow basic authorization if you are using basic authorization via web services. 

```
  # Basic authorization when using FCGI
  RewriteRule .* - [E=HTTP_AUTHORIZATION:%{HTTP:Authorization}]
```


Once you restart apache your new config is compiled.

```bash
service httpd restart
```
Finally you will need to start php-fpm and make sure that it stays on in case of a reboot.

```bash
service php-fpm start
chkconfig php-fpm on
```

## Varnish
Varnish is a reverse proxy that can be employed for the delivery of static assets and anonymous course traffic. If you are planning to scale elmslm for annonymous traffic it ia recommended to use a reverse proxy to hit higher load.

## Pound
