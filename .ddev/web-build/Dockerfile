ARG BASE_IMAGE
FROM $BASE_IMAGE

ENV PHP_VERSION=7.2
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y -o Dpkg::Options::="--force-confnew" --no-install-recommends --no-install-suggests gcc make autoconf libc-dev pkg-config php-pear php7.2-dev libmcrypt-dev
# The "echo" below just forces accepting the "automatic" configuration, the same as hitting <RETURN>
RUN echo | sudo pecl install mcrypt
# Because php7.1-mcrypt is already installed in web container we can just copy its mcrypt.ini
RUN cp /etc/php/7.1/mods-available/mcrypt.ini /etc/php/7.2/mods-available/ && phpenmod mcrypt