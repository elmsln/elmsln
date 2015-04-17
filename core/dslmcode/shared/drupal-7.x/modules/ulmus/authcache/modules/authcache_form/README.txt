Authcache Forms
===============

Allow page caching for authenticated users when forms are present on the page.


A note on Ajax forms
--------------------

Ajax forms require the form cache. However entries in the form cache expire
after a hard coded period of 6 hours. When pages should be cached longer and
Ajax forms are in use on them, they will stop working after that period.

In order to circumvent this problem you should install the Cache Object API[1]
module which allows the Authcache Forms module to extend that period to a user
supplied value.

1] http://drupal.org/project/cacheobject
