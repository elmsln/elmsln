<?php
/**
 * @file
 * mooc_hax.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mooc_hax_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hax_autoload_element_list';
  $strongarm->value = 'grid-plate tab-list magazine-cover video-player image-compare-slider simple-concept-network license-element self-check multiple-choice oer-schema hero-banner task-list lrn-table media-image lrndesign-blockquote meme-maker a11y-gif-player paper-audio-player wikipedia-query lrn-vocab lrn-math person-testimonial citation-element lrn-calendar code-editor place-holder q-r wave-player pdf-element stop-note';
  $export['hax_autoload_element_list'] = $strongarm;

  return $export;
}
