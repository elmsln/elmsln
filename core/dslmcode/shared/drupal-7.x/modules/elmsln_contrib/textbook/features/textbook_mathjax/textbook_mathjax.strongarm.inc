<?php
/**
 * @file
 * textbook_mathjax.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function textbook_mathjax_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mathjax_config_string';
  $strongarm->value = 'MathJax.Hub.Config({
  extensions: [\'tex2jax.js\'],
  jax: [\'input/TeX\',\'output/HTML-CSS\'],
  tex2jax: {
    inlineMath: [ [\'$\',\'$\'], [\'\\\\(\',\'\\\\)\'] ],
    processEscapes: true,
    processClass: \'tex2jax\',
    menuSettings: { 
      zoom: "hover"
    }
  },
  "HTML-CSS": { 
     scale: 150
   },
  showProcessingMessages: false,
  messageStyle: \'none\',
  menuSettings: { 
    zoom: "Double-Click"
  }
});';
  $export['mathjax_config_string'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mathjax_config_type';
  $strongarm->value = '1';
  $export['mathjax_config_type'] = $strongarm;

  return $export;
}
