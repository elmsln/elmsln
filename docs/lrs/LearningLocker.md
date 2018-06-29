# Learning Locker

We REALLY love Learning Locker. It's a great Learning Record Store (LRS) which ELMS:LN has native support for all over the place. This lets you track users in quizzes, H5P activities, and other engagements they have with their courses.

It’s some work to get up and running and will hopefully be fully-scripted in the future but for now, you can follow the directions found in their [Getting started guide](https://learninglocker.net/get-started/).

## Performance optimization related to ELMS:LN
Because of the way ELMS:LN sends xAPI data to learning locker it's important to apply performance optimizations to Learning Locker's mongoDB instance in order to get it to return results faster when ELMS:LN queries it. Create the following index:

```
{
    "statement.object.definition.extensions.https://www.elmsln.org/x-api/elmsln-course" : 1,
    "statement.object.definition.extensions.https://www.elmsln.org/x-api/elmsln-section" : 1
}
```

This is because ELMS:LN uses the extensions part of the xAPI spec in order to maintain course and section context, common points for pulling data back.

## Integration with ELMS:LN
This part is much easier as all the modules to do so are already enabled sitting and waiting behind the scenes when you install ELMS:LN! Add something like this added to `/var/www/elmsln/config/shared/drupal-7.x/settings/shared_settings.php` after you’ve got both systems setup and you’ve configured your Learning Locker instance to have a Learning Record Store (LRS) with an API Client (Manage Clients panel) to talk to ELMS:LN.

```
// change these to match your system / setup
$config['tincanapi_auth_user'] = "CLIENTUSER";
$config['tincanapi_auth_password'] = "CLIENTPASSWORD";
$config['tincanapi_endpoint'] = "http://YOURLRSADDRESS/data/xAPI";
// additional settings, most likely you don't want to touch these
$config['tincanapi_statement_actor'] = '[current-user:name]';
$config['tincanapi_anonymous'] = FALSE;
$config['tincanapi_simplify_id'] = FALSE;
$config['tincanapi_watchdog'] = FALSE;
```
