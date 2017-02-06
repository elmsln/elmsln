<?php
/**
 * @file Web components ingestion helpers
 */

function webcomponents_polymer_process_component($file) {
  $html = file_get_contents($file);
  // Create a DOM object.
  $html_obj = new simple_html_dom();
  // Load HTML from a string.
  $html_obj->load($html);
  $components = array();
  foreach ($html_obj->find('dom-module') as $rawmatch ) {
    $machine_name = $rawmatch->{'id'};
  }
  // Remove all plain text fragments.
  foreach ($html_obj->find('[data-drupal-component]') as $rawmatch ) {
    // abstract machine name for the new component
    $title = ($rawmatch->{'data-component-name'} ? $rawmatch->{'data-component-name'} : drupal_ucfirst(str_replace('-', ' ', $machine_name)));
    $tag = $rawmatch->tag;
    // estblish all components we find
    $component = array(
      'machine_name' => $machine_name,
      'tag' => $tag,
      'title' => $title,
      'properties' => array(),
    );
    preg_match_all('/({%.*?%}|{{.*?}})/', $rawmatch->innertext, $matches);
    if (isset($matches[0])) {
      foreach ($matches[0] as $match){
        $value = str_replace('{{', '', str_replace('}}', '', $match));
        $component['properties'][$value] = 'String';
      }
    }
  }
  // Release resources to avoid memory leak in some versions.
  $html_obj->clear();
  unset($html_obj);
  return $component;
}