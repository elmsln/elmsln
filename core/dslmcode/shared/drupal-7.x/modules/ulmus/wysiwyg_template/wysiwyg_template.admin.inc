<?php

/**
 * @file
 * Administrative page callbacks for the Wysiwyg Template module.
 */

/**
 * Wysiwyg template overview page - view templates and edit them
 */
function wysiwyg_template_overview(){
  $rows = array();
  // load the templates and display them on the admin form
  $templateResults = db_query("SELECT * FROM {wysiwyg_templates}");
  foreach ($templateResults as $template){
    $row = array();
    $row[] = $template->title;
    $row[] = $template->description;
    $row[] = l(t('edit'), "admin/config/content/wysiwyg-templates/edit/" . $template->name);
    $row[] = l(t('export'), "admin/config/content/wysiwyg-templates/export/" . $template->name);
    $row[] = l(t('delete'), "admin/config/content/wysiwyg-templates/delete/" . $template->name);
    
    $rows[] = $row;
  }
  
  if (empty($rows)){
    $rows[] = array(array(
      'data' => t('No templates available.'), 
      'colspan' => 5,
    ));
  }
  $rows[] = array(array(
    'data' => l(t('Create a new template'), 'admin/config/content/wysiwyg-templates/add'),
    'colspan' => 5,
  ));
  
  $header = array(t('Name'), t('Description'), array('data' => t('Operations'), 'colspan' => 3));
  
  $help = t('<p>The Wysiwyg Template module allows you to create templates to be used with a Wysiwyg editor of your choice. The template button for the editor will need to be enabled from the !profiles settings. The currently supported editors are FCK Editor, CK Editor and TinyMCE.</p>', array('!profiles' => l(t('WYSIWYG Profile'), 'admin/config/content/filters')));
  
  return $help . theme('table', array(
    'header' => $header,
    'rows' => $rows, 
    'id' => 'wysiwyg_template'
  ));
}

/**
 * Wysiwyg template create/modify form
 */
function wysiwyg_template_template_form($something, $form_state, $template = NULL) {
  if(isset($form_state['confirm_delete'])){
    // Rebuild the form to confirm term deletion.
    $form['name'] = array('#type' => 'value', '#value' => $form_state['values']['name']);
    $form['delete'] = array('#type' => 'value', '#value' => true);
    return confirm_form($form, 
      t('Are you sure you want to delete the template %title?', array('%title' => $form_state['values']['title'])),
      'admin/content/wysiwyg-template',
      t('This action cannot be undone.'),
      t('Delete'),
      t('Cancel')
    );
  }

  if(!empty($template)) {
    // Add the current values as defaults to the form, if editing an existing item.
    $form_state['values'] = $template;
  }

  $form = array();
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Template Name'),
    '#default_value' => isset($form_state['values']['title']) ? $form_state['values']['title'] : '',
    '#description' => t('Select a name for this template.'),
    '#maxlength' => 80,
    '#required' => true
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'wysiwyg_template_name_exists',
      'source' => array('title'),
    ),
    '#description' => t('A unique machine-readable name for this template. It must only contain lowercase letters, numbers, and underscores.'),
  );
  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Template Description'),
    '#default_value' => isset($form_state['values']['description']) ? $form_state['values']['description'] : '',
    '#description' => t('A description to be shown with the template.')
  );
  // load image if it has one
  $image = '';
  if (isset($form_state['values']['fid']) && $form_state['values']['fid']) {
    $image_uri = file_load($form_state['values']['fid'])->uri;
    if ($image_uri) {
      $image = theme('image_style', array('style_name' => 'wysiwyg_template_thumbnail', 'path' => $image_uri));
    }
  }
  $form['template_image'] = array(
    '#type' => 'file',
    '#title' => t('Choose a file'),
    '#size' => 22,
    '#description' => t('A image to be shown with the template.'),
    '#prefix' => $image,
  );
  $form['template_image_fid'] = array(
    '#type' => 'hidden',
    '#default_value' =>  isset($form_state['values']['fid']) ? $form_state['values']['fid'] : 0,
  );
  // add delete button if it has an image
  if (isset($form_state['values']['fid']) && $form_state['values']['fid']) {
    $form['template_image_delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete the Template image.')
    );
  }
  $form['body'] = array(
    '#type' => 'text_format',
    '#title'  => t('HTML Template'),
    '#rows'  =>  10,
    '#format' => NULL,
    '#default_value' => isset($form_state['values']['body']) ? $form_state['values']['body'] : '',
    '#required' => true
  );
  if(module_exists('token')){
    $form['token_help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node', 'custom'),
      '#global_types' => true
    );
    $form['body']['#title'] = theme('token_help', 'node');
  }
  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Save')
  );
  
  if(!empty($template)) {
    if (!empty($form_state['values']['name'])) {
      $form['name']['#default_value'] = $form_state['values']['name'];
      $form['name']['#disabled'] = TRUE;
      $form['name']['#value'] = $form_state['values']['name'];
    }

    // If it's an existing template, offer a delete button.
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete')
    );
  }
  return $form;
}

/**
 * Wysiwyg template form submit - delete and save handlers
 */
function wysiwyg_template_template_form_submit($form, &$form_state) {
  //if we're deleting the template
  if ($form_state['clicked_button']['#id'] == 'edit-delete') {
    //show the confirmation
    $form_state['rebuild'] = true;
    $form_state['confirm_delete'] = true;
    return;
  }
  // delete confirmation provided
  if (isset($form_state['values']['delete'])){
    if ($form_state['values']['delete'] === TRUE) {
      // delete image if one was uploaded
      if (!empty($form_state['values']['template_image_fid'])) {
        file_delete($form_state['values']['template_image_fid']);
      }
      wysiwyg_template_delete_template($form_state['values']['name']);
      drupal_set_message(t('The template has been deleted.'));    
      $form_state['redirect'] = 'admin/config/content/wysiwyg-templates';
      return;
    }
  }
  // drop image if selected and checked
  if (isset($form_state['values']['template_image_delete']) && $form_state['values']['template_image_delete']) {
    file_delete(file_load($form_state['values']['template_image_fid']));
    // unset the fid previously used
    $form_state['values']['template_image_fid'] = 0;
  }
  // prepare file if needed
  $filepath = 'public://wysiwyg_template_images/';
  file_prepare_directory($filepath, FILE_CREATE_DIRECTORY);
  // save the image, validate it against file_validate_extensions
  $file = file_save_upload('template_image', array('file_validate_extensions' => array('jpg png gif jpeg')), $filepath);
  if ($file) {
    // set status to permanent
    $file->status = FILE_STATUS_PERMANENT;
    $file = file_save($file);
    if ($file) {
      $form_state['values']['fid'] = $file->fid;
      // delete previous file if it had one
      if ($form_state['values']['template_image_fid']) {
        file_delete(file_load($form_state['values']['template_image_fid']));
      }
    }
  }
  else {
    $form_state['values']['fid'] = $form_state['values']['template_image_fid'];
  }
  // save the template
  if(wysiwyg_template_save_template($form_state['values'])){
    drupal_set_message(t('The template has been saved.'));
  }
  else{
    drupal_set_message(t('There was an error saving the template to the database.'));
  }
  // redirect back to the overview page
  $form_state['redirect'] = 'admin/config/content/wysiwyg-templates';
}

/**
 * Menu callback -- ask for confirmation of rule deletion.
 */
function wysiwyg_template_delete_confirm($something, &$form_state) {
  
  $form['name'] = array(
    '#type' => 'value',
    '#value' => isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : 0,
  );

  $template = wysiwyg_template_load_template(isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : 0);
  return confirm_form($form,
    t('Are you sure you want to delete the template %title?', array('%title' => $template['title'])),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/config/content/wysiwyg-templates',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Execute node deletion.
 */
function wysiwyg_template_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    wysiwyg_template_delete_template($form_state['values']['name']);
  }

  $form_state['redirect'] = 'admin/config/content/wysiwyg-templates';
  return;
}

/**
 * Generate exporting code for a template.
 */
function wysiwyg_template_export_get_code($template, $indent = '') {
  $code = array();
  $code[] = '$template = array();';
  foreach ($template as $key => $value) {
    $code[] = "\$template['{$key}'] = " . var_export($value, TRUE) .";";
  }
  return implode("\n", $code);
}

/**
 * Generate a form for exporting a template.
 */
function wysiwyg_template_export_form($form, &$form_state, $template) {
  drupal_set_title(check_plain($template['title']));
  $code = wysiwyg_template_export_get_code($template);
  $lines = substr_count($code, "\n")  + 1;
  $form['export'] = array(
    '#title' => t('Export data'),
    '#type' => 'textarea',
    '#value' => $code,
    '#rows' => $lines,
    '#description' => t('Copy the export text and paste it into another site using the import function.'),
  );

  return $form;
}

/**
 * Generate a form for importing a template.
 */
function wysiwyg_template_import_form($form, &$form_state) {
  $form['import'] = array(
    '#title' => t('Import data'),
    '#type' => 'textarea',
    '#rows' => 20,
    '#description' => t('Paste the code from template export function.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Form submit. Import the template.
 */
function wysiwyg_template_import_form_submit($form, &$form_state) {
  if (!empty($form_state['input']['import'])) {
    wysiwyg_template_import_from_code($form_state['input']['import']);
    $form_state['redirect'] = 'admin/config/content/wysiwyg-templates';
  }
  else {
    form_set_error('import', $template);
  }
}

/**
 * Helper function to parse template import PHP code and save the template.
 *
 * @param $code
 *   String with template PHP code to parse.
 */
function wysiwyg_template_import_from_code($code) {
  ob_start();
  eval($code);
  ob_end_clean();
  if (!empty($template)) {
    wysiwyg_template_save_template($template);
  }
}
