Authcache Personalization API
=============================

The personalization API provides means to simplify substitution of
personalized markup with placeholders as well as an alternative light weight
front controller capable of rendering and delivering personalized fragments of
a page without requiring a full Drupal bootstrap.


Installation
------------

Enable this module along with Authcache Ajax and/or Authcache ESI. Also enable
all the Authcache modules providing support for the following core/contrib
modules if you use them:
* Block
* Comment
* Contact
* Field
* Flag
* Form
* Forum
* Menu (Support for local tasks and local actions)
* Page Manager (Only if you use panels)
* Panels
* Poll
* Search
* Views

For production environments it is strongly recommended to use the safe front
controller script by following the instructions contained in
safe_frontcontroller/authcache.php

Reasons for installing the safe front controller are shorter URLs and reduced
likeliness of experiencing potential side effects due to the modification of
some $_SERVER keys, which is necessary when the front controller script lives
somewhere else than in the Drupal root directory.


Markup Substitution
-------------------

Three methods of markup substitution are supported by this module.
* fragment: Replace a fragment on a page by a placeholder. One request to the
  front controller is issued for each substituted fragment on a page. (e.g.
  form tokens by the Form module).
* setting: Load a Drupal.setting using the front controller and run the
  Drupal.attachBehaviors JavaScript function on the result. (e.g. contact
  details by the Contact module).
* assembly: Load multiple fragments in one request and inject them via
  JavaScript into the DOM (e.g. flags by the Flag module).

Rendering of the substitution markup is left to client-modules. Currently
Authcache ships with two of them, namely Authcache Ajax and Authcache ESI. The
former uses Ajax to call back to the front controller directly from the users
browser while the latter embeds ESI tags, such that markup substitution
already can take place on a reverse proxy server (e.g. Varnish).


Light Weight Front Controller
-----------------------------

The personalization front controller by default does not perform a full
bootstrap. This results in much quicker response times if only a selected
subset of functionality is required to render a fragment. For example in order
to generate the tokens necessary to protect forms against CSRF attacks, a
bootstrap level of DRUPAL_BOOTSTRAP_SESSION is sufficient.

Fragments delivered through the personalization front controller also may have
different cache lifetimes than the pages they are displayed on. E.g. on a
blog, the recent-comments block may have a cache-lifetime of 10 minutes while
an article page can be setup with a cache lifetime of 24 hours.
