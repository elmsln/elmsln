Token Filter
-----------

This is a very simple module to make token values available as an input filter.

This initial development version only works for global and user token types.

Installation:

1) Enable the module
2) Go to /admin/settings/filters and enable the token_filter for any of your existing filter type or if you wish, create a new one.

Then in the text where you use that input filter you can use substitution tokens with

[token global site-name] etc.

Tokens typically available are:

global:
-------
user-name
user-id
user-mail
site-url
site-name
site-slogan
site-mail
site-date

user:
-----
user
user-raw
uid
mail
reg-date
reg-since
log-date
log-since
date-in-tz
account-url
account-edit
