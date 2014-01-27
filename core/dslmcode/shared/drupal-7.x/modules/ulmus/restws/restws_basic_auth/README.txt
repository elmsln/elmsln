--------------------------------------------------------------------------------
                 HTTP Basic Authentication for RESTful Web Services
--------------------------------------------------------------------------------

This module takes the user name and password from HTTP basic authentication
headers to perform a Drupal user login. This is useful for authenticating remote
web service calls with the standard Drupal user access system.

Per default only user names starting with "restws" will be tried to log in. This
can be configured with the "restws_basic_auth_user_regex" variable, which allows
you to define an arbitrary pattern that the user names must match. This avoids
unecessary login attempts for standard human users on protected sites.

You can configure the regex (suitable for preg_match()) in your settings.php,
e.g.:

$conf['restws_basic_auth_user_regex'] = '/^web_service.*/';


Compatibility with Apache + PHP as CGI/FCGI:
--------------------------------------------

Unfortunately PHP_AUTH_USER & PHP_AUTH_PW server variables are not available
when PHP is run as CGI/FCGI under Apache. However, it is possible to make the
module work in such an environment by adding the following line to your
.htaccess file:

  RewriteRule .* - [E=HTTP_AUTHORIZATION:%{HTTP:Authorization}]
