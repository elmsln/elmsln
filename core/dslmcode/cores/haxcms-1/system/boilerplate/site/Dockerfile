FROM elmsln/haxcms:2.0.9 as haxcms

FROM php:7.3-apache

RUN a2enmod rewrite
COPY ./services/haxcms/apache2.conf /etc/apache2/apache2.conf

COPY . /var/www/html
COPY --from=haxcms /var/www/html/build /var/www/html/build
COPY --from=haxcms /var/www/html/dist /var/www/html/dist
COPY --from=haxcms /var/www/html/system /var/www/html/system
COPY --from=haxcms /var/www/html/assets/babel-top.js /var/www/html/assets/babel-top.js
COPY --from=haxcms /var/www/html/assets/babel-bottom.js /var/www/html/assets/babel-bottom.js
COPY --from=haxcms /var/www/html/wc-registry.json /var/www/html/wc-registry.json
RUN chown -R www-data:www-data /var/www/html
