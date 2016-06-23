<?php
// you can read the full jwerty API for javascript usage at
// http://keithamus.github.io/jwerty/
// BUT you may not need to do that in order to make this work
// well for your drupal site.
//
// by attaching the html attribute data-jwerty-key to anything
// you output to the screen, jwerty will discover it at run time
// and turn it into a keyboard accessible command

// HTML Example:
?>
<a href="#" title="close window" data-jwerty-key="esc">Close</a>

<?php
// Drupal example from ELMSLN MOOC distribution
function print_links() {
  print l('<div class="mooc-helper-toc-icon icon-courses-black etb-modal-icons"></div><span>Home</span>', '<front>', array('html' => TRUE, 'attributes' => array('data-voicecommand' => t('home'), 'class' => array('mooc-home-button'))));
}