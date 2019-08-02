FROM php:7.3-apache

# Adds jpeg-support for gd
RUN apt-get update && apt-get install -y \
        libfreetype6-dev \
        libjpeg62-turbo-dev \
        libpng-dev \
    && docker-php-ext-configure gd --with-freetype-dir=/usr/include/ --with-jpeg-dir=/usr/include/ \
    && docker-php-ext-install -j$(nproc) gd

RUN a2enmod rewrite
COPY ./system/docker/apache2.conf /etc/apache2/apache2.conf

COPY --chown=www-data:www-data . /var/www/html