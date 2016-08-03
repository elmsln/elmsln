ELMSLN Bakery

This provides automated setup for bakery in elms:ln by allowing
an authority to be defined and configured, as well as all other sites
that are setup automatically. This is a turn it on and it all "JustWorks".

This defaults to cpr (people distro) but can be overidden if needed by setting
the following variable in shared_settings.php:
This example is how you'd set it to cis for example
```
$conf['elmsln_bakery_authority'] = 'cis';
```