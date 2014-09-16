// $Id: README.txt,v 1.1 2010/07/11 05:37:21 quicksketch Exp $

AJAX Poll adds the ability for users to vote on polls without reloading the
page. It works with the normal Poll module included with Drupal core. It affects
all polls throughout the site, on teaser, full, and block forms of polls.

This module built by robots: http://www.lullabot.com
Written by Nathan Haug (quicksketch)

Usage
-----

1) Copy the ajax_poll folder to the modules folder in your installation.

2) Enable the module using Administer -> Site building -> Modules
   (/admin/build/modules).

3) All polls on your site will immediately use AJAX-based voting now.
   No configuration options are provided, though you can customize the behavior
   through a custom module or theming (see the FAQ below).

FAQ
---
Q. 1) Why can't a user cancel their vote after voting through the Poll block?
A. 1) This is because the default theming of Poll module does not include the
      "Cancel" button in the block results. To fix this, copy the
      "poll-results-block.tpl.php" file from the modules/poll directory to your
      theme and change it as necessary to match the poll-results.tpl.php file.
      Clear your Drupal caches at admin/settins/performance after copying in the
      new file.

Q. 2) Why isn't the button for "Cancel my vote" centered like the button for
      "Vote" is?
A. 2) For some reason the poll.css file thinks that the voting form should be
      centered but the cancel form should not. To fix this, add this line of CSS
      to your theme's style.css file:
      form.ajax-poll { text-align: center; }

Q. 3) How do I change the text of my buttons to something other than "Vote" and
      "Voting..." or "Cancel my vote" and "Canceling..."?
A. 3) Use hook_form_alter() in a custom module to change these values. The button
      texts are available easily with the $form['submit']['#value'] and
      $form['ajax_text']['#value'] properties.

Support
-------

Please file any bugs with this module in the AJAX Poll issue queue on
Drupal.org. Please send any questions there also:
http://drupal.org/project/issues/ajax_poll
