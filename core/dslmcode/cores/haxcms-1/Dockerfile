FROM php:7.4-apache
# Adds jpeg-support for gd
RUN apt-get update && apt-get install -y \
        libfreetype6-dev \
        libjpeg62-turbo-dev \
        libpng-dev \
        git \
    && docker-php-ext-configure gd --with-freetype-dir=/usr/include/ --with-jpeg-dir=/usr/include/ \
    && docker-php-ext-install -j$(nproc) gd
# Enable rewrite
RUN a2enmod rewrite
# Copy custom apache conf
COPY ./scripts/docker/apache2.conf /etc/apache2/apache2.conf
# Customize the php entrypoint to clean up permissions
COPY ./scripts/docker/docker-php-entrypoint /usr/local/bin/
# Make sure the entrypoint is executable
RUN chmod +x /usr/local/bin/docker-php-entrypoint
# Copy HAXcms into the web root directory
COPY --chown=www-data:www-data . /var/www/html