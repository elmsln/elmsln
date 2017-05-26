Exlucde Node Title
===========================


Introduction
---------------------

This module handles a very simple functionality, decide whatever to exclude a node title from full node page or node teasers.

It provides a checkbox on node-edit pages for easier exclusion, or you can use the admin page to manually enter a list of node id's to exclude title.

This module also provides the option to hide all titles of a certain Content type. From the administrative interface you can select a content type to hide title for.


Use case
---------------------
Let's say you create a content type called: Lightbox content, and in your layout lightbox content will have titles set on title attribute of the link, rather than inline on your page, so you would like to exclude title from displaying inline for all your nodes of type Lightbox content, simple, just check the option and voila.


How it works?
----------------------
This project has some other, very simple approaches, like hiding the title from CSS using display: none or applying the template_preprocess_page hook in your theme to make `title` variable null.
Actually `Exclude Node Title` does the same thing, only that you don't have to manually make different hacks, hard to track from the administration interface.



Original Author: Gabriel Ungureanu <gabriel.ungreanu@ag-prime.com>
Current Maintainer: Yonas Yanfa <http://drupal.org/user/473174>
