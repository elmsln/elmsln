<?php

/**
 * @file
 * Administrative page callbacks for the Wysiwyg Template module.
 */

/**
 * Wysiwyg template overview page - view templates and edit them
 */
function wysiwyg_template_overview($form, $form_state) {
  $templates = db_select('wysiwyg_templates', 't')
    ->fields('t')
    ->orderBy('t.weight')
    ->execute()
    ->fetchAll();

  $form['wysiwyg_templates'] = array(
    '#tree' => TRUE,
  );

  if (empty($templates)) {
    $form['info_empty'] = array(
      '#markup' => t('No templates available.') . ' ' . l(t('Add you first template.'), 'admin/config/content/wysiwyg-templates/add'),
      '#weight' => 10,
    );
  }
  else {
    $order = 0;
    foreach ($templates as $template) {
      $form['wysiwyg_templates'][$template->name]['#template'] = (object) array(
        'name' => $template->name,
        'title' => $template->title,
        'description' => $template->description,
        'weight' => $order,
        'content_types' => wysiwyg_template_load_template_content_types($template->name),
      );
      $form['wysiwyg_templates'][$template->name]['#weight'] = $order;
      $form['wysiwyg_templates'][$template->name]['weight'] = array(
        '#type' => 'textfield',
        '#title' => t('Weight for @title', array('@title' => $template->title)),
        '#title_display' => 'invisible',
        '#size' => 4,
        '#default_value' => $order,
        '#attributes' => array('class' => array('template-weight')),
      );
      $order++;
    }

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save order'),
      '#submit' => array('wysiwyg_template_overview_submit'),
    );
  }

  return $form;
}

/**
 * Form submit function. Update the template weights.
 */
function wysiwyg_template_overview_submit($form, &$form_state) {
  foreach ($form_state['values']['wysiwyg_templates'] as $name => $template_values) {
    db_update('wysiwyg_templates')
      ->fields(array('weight' => $template_values['weight']))
      ->condition('name', $name)
      ->execute();
  }
  drupal_set_message(t('The Wysiwyg template settings have been updated.'));
}

/**
 * Returns HTML for the wysiwyg template order form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_wysiwyg_template_overview($variables) {
  $form = $variables['form'];

  $rows = array();
  $header = array(t('Name'), t('Weight'), t('Description'), t('Limited to content types'), array('data' => t('Operations'), 'colspan' => 3));
  foreach (element_children($form['wysiwyg_templates']) as $name) {
    $title = $form['wysiwyg_templates'][$name]['#template']->title;
    $row = array();
    $row[] = check_plain($title);
    $row[] = drupal_render($form['wysiwyg_templates'][$name]['weight']);
    $row[] = check_plain($form['wysiwyg_templates'][$name]['#template']->description);
    $row[] = check_plain(implode(', ', $form['wysiwyg_templates'][$name]['#template']->content_types));
    $row[] = l(t('edit'), 'admin/config/content/wysiwyg-templates/' . $name . '/edit');
    $row[] = l(t('export'), 'admin/config/content/wysiwyg-templates/' . $name . '/export');
    $row[] = l(t('delete'), 'admin/config/content/wysiwyg-templates/' . $name . '/delete');

    $rows[] = array('data' => $row, 'class' => array('draggable'));
  }

  drupal_add_tabledrag('wysiwyg-templates', 'order', 'sibling', 'template-weight');

  $output = '<p>' . t('The Wysiwyg Template module allows you to create templates to be used with a Wysiwyg editor of your choice. The template button for the editor will need to be enabled from the !profiles settings. The currently supported editors are FCK Editor, CK Editor and TinyMCE.', array('!profiles' => l(t('WYSIWYG Profile'), 'admin/config/content/filters'))) . '</p>';
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'wysiwyg-templates')));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Wysiwyg template create/modify form
 */
function wysiwyg_template_template_form($form, $form_state, $template = NULL) {
  if (isset($form_state['confirm_delete'])) {
    // Rebuild the form to confirm term deletion.
    $form['name'] = array(
      '#type' => 'value',
      '#value' => $form_state['values']['name']
    );
    $form['delete'] = array('#type' => 'value', '#value' => true);
    return confirm_form($form,
      t('Are you sure you want to delete the template %title?', array('%title' => $form_state['values']['title'])),
      'admin/content/wysiwyg-template',
      t('This action cannot be undone.'),
      t('Delete'),
      t('Cancel')
    );
  }

  if (!empty($template)) {
    // Add the current values as defaults to the form, if editing an existing item.
    $form_state['values'] = $template;
  }

  $content_types = array();
  foreach (node_type_get_types() as $content_type) {
    $content_types[$content_type->type] = $content_type->name;
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
    '#description' => t('A description to be shown with the template.'),
  );
  $form['weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight'),
    '#default_value' => isset($form_state['values']['weight']) ? $form_state['values']['weight'] : 0,
    '#description' => t('The weight of this template for the sort order in lists.'),
  );
  $form['content_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Available for content types'),
    '#options' => $content_types,
    '#default_value' => isset($form_state['values']['content_types']) ? array_keys($form_state['values']['content_types']) : array(),
    '#description' => t('If you select no content type, this template will be available for all content types.'),
    '#access' => (count($content_types) > 1),
  );
  // load image if it has one
  $image = '';
  if (isset($form_state['values']['fid']) && $form_state['values']['fid']) {
    $image_uri = file_load($form_state['values']['fid'])->uri;
    if ($image_uri) {
      $image = theme('image_style', array(
        'style_name' => 'wysiwyg_template_thumbnail',
        'path' => $image_uri
      ));
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
    '#default_value' => isset($form_state['values']['fid']) ? $form_state['values']['fid'] : 0,
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
    '#title' => t('HTML Template'),
    '#rows' => 10,
    '#format' => isset($form_state['values']['format']) ? $form_state['values']['format'] : filter_default_format(),
    '#default_value' => isset($form_state['values']['body']) ? $form_state['values']['body'] : '',
    '#required' => true
  );
  if (module_exists('token')) {
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

  if (!empty($template)) {
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
  if (isset($form_state['values']['delete'])) {
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
  // Flatten body field data.
  $template = $form_state['values'];
  $template['body'] = $form_state['values']['body']['value'];
  $template['format'] = $form_state['values']['body']['format'];
  if (wysiwyg_template_save_template($template)) {
    drupal_set_message(t('The template has been saved.'));
  }
  else {
    drupal_set_message(t('There was an error saving the template to the database.'));
  }
  // redirect back to the overview page
  $form_state['redirect'] = 'admin/config/content/wysiwyg-templates';
}

/**
 * Menu callback -- ask for confirmation of rule deletion.
 */
function wysiwyg_template_delete_confirm($form, &$form_state, $template) {

  $form['#wysiwyg_template'] = $template;

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
    wysiwyg_template_delete_template($form['#wysiwyg_template']['name']);
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
    $code[] = "\$template['{$key}'] = " . var_export($value, TRUE) . ";";
  }
  return implode("\n", $code);
}

/**
 * Generate a form for exporting a template.
 */
function wysiwyg_template_export_form($form, &$form_state, $template) {
  drupal_set_title(check_plain($template['title']));
  $code = wysiwyg_template_export_get_code($template);
  $lines = substr_count($code, "\n") + 1;
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
    form_set_error('import', '$template');
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
