CAS Server
==========

The CAS Server module lets Drupal act as a protocol compliant CAS server.

Do NOT simultaneously enable the CAS and CAS Server modules. Unpredictable
errors may occur.

Requirements
============
 * SSL:
     The CAS protocol requires the CAS server to run over HTTPS (not HTTP).
     Your Drupal site will need to be configured for HTTPS separately. The site
     should also have a valid SSL certificate signed by a trusted Certificate
     Authority. The certificate should be made available to your CAS clients
     for additional security.

Configuration
=============
There is no configuration for the CAS server. Simply enable the module.

If your Drupal site is https://site.example.com/, other CAS enabled
applications should be configured to use https://site.example.com/cas as the
CAS server.

Caveats & Limitations
=====================

Single Sign-Out is not currently supported.
