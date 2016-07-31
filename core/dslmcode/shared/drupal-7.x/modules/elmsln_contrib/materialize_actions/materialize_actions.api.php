<?php

/**
 * Example of how to display a system message via materialize
 * toasts.
 */
 function hook_page_build(&$page) {
  drupal_set_message('You are on a page!', 'notification');
 }
