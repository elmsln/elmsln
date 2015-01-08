
Module: Views Litepager
Author: Nathan Rambeck <http://nathan.rambeck.org>

Description
===========
The Views Litepager module solves a problem of scalability for sites with large
amounts of content. COUNT queries executed on large datasets when using the
InnoDB MySQL engine can be painfully slow. This module adds a new pager option
for Views called "Lite pager" that does not execute the problematic COUNT query.
The Lite pager does not include the total number of pages of content like the
core Drupal pager does, but it does allow users to navigate from page to page.

Installation
============

1. Download the module, unzip the source, and put the resulting directory into the 
   modules/ directory of your Drupal application.
2. Enable the module in Drupal at Administer > Modules > Views

Usage
=====

To use the Lite pager for a specific view, navigate to your view's edit interface
and click to edit the pager settings. You will see a new option called Lite pager.
Simply select this Lite pager option and save your view.
