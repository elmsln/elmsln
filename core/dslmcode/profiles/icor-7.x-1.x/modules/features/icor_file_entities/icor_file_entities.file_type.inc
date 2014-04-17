<?php
/**
 * @file
 * icor_file_entities.file_type.inc
 */

/**
 * Implements hook_file_default_types().
 */
function icor_file_entities_file_default_types() {
  $export = array();

  $file_type = new stdClass();
  $file_type->disabled = FALSE; /* Edit this to true to make a default file_type disabled initially */
  $file_type->api_version = 1;
  $file_type->type = 'icor_html';
  $file_type->label = 'HTML';
  $file_type->description = 'HTML file handler';
  $file_type->mimetypes = array(
    0 => 'text/html',
  );
  $export['icor_html'] = $file_type;

  $file_type = new stdClass();
  $file_type->disabled = FALSE; /* Edit this to true to make a default file_type disabled initially */
  $file_type->api_version = 1;
  $file_type->type = 'icor_zip';
  $file_type->label = 'Zip';
  $file_type->description = 'Handler for archived upload files';
  $file_type->mimetypes = array(
    0 => 'application/zip',
  );
  $export['icor_zip'] = $file_type;

  return $export;
}
