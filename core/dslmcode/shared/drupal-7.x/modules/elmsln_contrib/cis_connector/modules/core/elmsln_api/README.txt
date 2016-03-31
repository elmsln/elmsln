ELMSLN API
==========
This is a backend API for ELMSLN to be able to pass around data
via its secure back channel and at a high rate of speed.

NOTE
=====
This only works if you have the system generate your registry of connection
credentials. If you don't do this then the API isn't going to be able
to correctly detect the module and get a match on API credentials.

Yeah... it's THAT low level in the sub-system that it's skipping all
kind of checks including User verification. It's looking for:
- A drupal site (though not hitting index.php for it)
- a hit on elmsln.php with a ?q= filled out
- Basic Authorization headers
- a module that was created by itself for credentials
- matching the two

If the above is TRUE then it will be able to process the API call.
