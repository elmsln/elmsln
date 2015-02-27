<?php

/**
 * @file
 * The Node export pages file.
 *
 * Functions for page/form interfaces.
 */

/**
 * Handles the bits of the form that are specific to the token module.
 */
function node_export_settings_token_bits(&$form, $key) {
  if (module_exists('token')) {
    $form[$key . '_token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form[$key . '_token_help']['help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node_export_filename'),
    );
  }
  else {
    $form[$key]['#description'] = t(
      'Get the <a href="@token">token</a> module for more options.',
      array('@token' => url('http://www.drupal.org/project/token'))
    );
  }
}

/**
 * Menu callback to configure module settings.
 */
function node_export_settings($form, &$form_state) {
  $types = node_type_get_names();

  menu_rebuild();

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );

  $format_handlers = node_export_format_handlers();
  $format_options = array();
  foreach ($format_handlers as $format_handler => $format) {
    $display = $format['#title'];
    if (!empty($format['#description'])) {
      $display .= '<div><small>';
      $display .= $format['#description'];
      $display .= '</small></div>';
    }
    $format_options[$format_handler] = $display;

    $format_settings = array();
    if (!empty($format['#settings_callback'])) {
      if (!empty($format['#file']) && is_file($format['#file'])) {
        require_once $format['#file'];
      }
      $format_form = call_user_func($format['#settings_callback'], $form, $form_state);
      $format_settings = $format_settings + $format_form;
    }

  }
  $selected_formats = variable_get('node_export_format', array('drupal'));
  if (!count(array_filter($selected_formats))) {
    $selected_formats = array('drupal');
  }
  if (count($format_options) > 1) {
    $form['basic']['node_export_format'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Format to use when exporting a node'),
      '#default_value' => $selected_formats,
      '#options' => $format_options,
      '#description' => t("If you select multiple formats, they will all be available to the user.  If you select none, or the format handler is not found, it will use the default 'Drupal var export'.  This does not affect imports, the required import format will be used automatically."),
    );
  }
  else {
    $format = key($format_options);
    $form['basic']['node_export_format'] = array(
      '#type' => 'value',
      '#value' => array($format => $format),
    );
  }

  $form['basic'][] = $format_settings;

  $form['basic']['node_export_code'] = array(
    '#type' => 'radios',
    '#title' => t('Node export code delivery'),
    '#options' => array(
      'all' => t('All of the below options on a page'),
      'copy' => t('Textarea filled with export code'),
      'file' => t('Text file download'),
    ),
    '#default_value' => variable_get('node_export_code', 'all'),
  );

  $form['basic']['filename'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filename settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['basic']['filename']['node_export_filename'] = array(
    '#type' => 'textarea',
    '#title' => t('Filename pattern'),
    '#default_value' => variable_get('node_export_filename', 'node-export[node_export_filename:nid-list]([node_export_filename:node-count]-nodes).[node_export_filename:timestamp].[node_export_filename:format]'),
    '#rows' => 1,
    '#wysiwyg' => FALSE,
  );
  node_export_settings_token_bits($form['basic']['filename'], 'node_export_filename');

  $form['basic']['filename']['node_export_file_list'] = array(
    '#type' => 'textfield',
    '#title' => t('Node ID list max'),
    '#default_value' => variable_get('node_export_file_list', 10),
    '#size' => 6,
    '#maxlength' => 30,
    '#description' => t('If there are more than this many nodes, the [node_export_filename:nid-list] token for the filename will not be built.  This is to prevent very long filenames.'),
  );

  $form['basic']['node_export_existing'] = array(
    '#type' => 'radios',
    '#title' => t('When importing a node that already exists'),
    '#options' => array(
      'new' => t('Create a new node'),
      'revision' => t('Create a new revision of the existing node'),
      'skip' => t('Skip the node'),
    ),
    '#description' => t('UUIDs are used to uniquely identify nodes.'),
    '#default_value' => variable_get('node_export_existing', 'new'),
  );

  $form['publishing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reset values on import'),
  );

  foreach ($types as $type => $name) {
    $form['publishing'][$type] = array(
      '#type' => 'fieldset',
      '#title' => $name,
      '#description' => t('Reset these values when importing nodes of type @s.', array('@s' => $name)),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['publishing'][$type]['node_export_reset_status_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Published'),
      '#default_value' => variable_get('node_export_reset_status_' . $type, FALSE),
      '#description' => t('Set to unpublished'),
    );
    $form['publishing'][$type]['node_export_reset_promote_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Promoted to front page'),
      '#default_value' => variable_get('node_export_reset_promote_' . $type, FALSE),
      '#description' => t('Set to not promoted'),
    );
    $form['publishing'][$type]['node_export_reset_sticky_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Sticky at top of lists'),
      '#default_value' => variable_get('node_export_reset_sticky_' . $type, FALSE),
      '#description' => t('Set to not sticky'),
    );
    $form['publishing'][$type]['node_export_reset_author_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Author (will set to user performing the import)'),
      '#default_value' => variable_get('node_export_reset_author_' . $type, TRUE),
      '#description' => t('Recommended since User IDs could be different on import site and the wrong user may gain permission to edit the node.'),
    );
    $form['publishing'][$type]['node_export_reset_created_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Created time (<em>Authored on</em> date/time)'),
      '#default_value' => variable_get('node_export_reset_created_' . $type, TRUE),
    );
    $form['publishing'][$type]['node_export_reset_changed_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Changed time (<em>Last updated</em> date/time)'),
      '#default_value' => variable_get('node_export_reset_changed_' . $type, TRUE),
    );
    $form['publishing'][$type]['node_export_reset_revision_timestamp_'. $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Revision changed time'),
      '#default_value' => variable_get('node_export_reset_revision_timestamp_'. $type, TRUE),
    );
    $form['publishing'][$type]['node_export_reset_last_comment_timestamp_'. $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Last comment time (date/time the last comment was made)'),
      '#default_value' => variable_get('node_export_reset_last_comment_timestamp_'. $type, TRUE),
    );
    $form['publishing'][$type]['node_export_reset_menu_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Menu link'),
      '#default_value' => variable_get('node_export_reset_menu_' . $type, TRUE),
    );
    $form['publishing'][$type]['node_export_reset_path_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('URL path'),
      '#default_value' => variable_get('node_export_reset_path_' . $type, TRUE),
    );
    $form['publishing'][$type]['node_export_reset_book_mlid_' . $type] = array(
      '#type' => 'checkbox',
      '#title' => t('Book menu link'),
      '#default_value' => variable_get('node_export_reset_book_mlid_' . $type, TRUE),
      '#description' => t('Prevents Book node imports causing errors.'),
    );
  }

  $form['file'] = array(
    '#type' => 'fieldset',
    '#title' => t('File fields'),
  );

  $types = node_type_get_names();
  $form['file']['node_export_file_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Files exported for content types'),
    '#default_value' => variable_get('node_export_file_types', array()),
    '#options' => $types,
    '#description' => t('Which content types should export file fields?'),
  );

  $textarea_delivery = $form['basic']['node_export_code']['#default_value'];

  $mode_message_display = ($textarea_delivery != 'file');

  $form['file']['node_export_file_mode'] = array(
    '#type' => 'radios',
    '#title' => t('File export mode'),
    '#default_value' => variable_get('node_export_file_mode', 'inline'),
    '#options' => array(
      'inline' => t('Inline Base64'),
      'local' => t('Local file export'),
      'remote' => t('Remote file export, URL')
     ),
    '#description' => t('Should file exports be inline inside the export code, a local path to the file, or a URL?  Inline Base64 is the easiest option to use but can sometimes exceed PHP post limits, local and remote modes are more useful for power users.  <em>NOTE: Remote mode only works with a public files directory.</em>'),
  );

  $form['file']['node_export_file_assets_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Local file field assets path'),
    '#size' => 60,
    '#maxlength' => 255,
    '#default_value' => variable_get('node_export_file_assets_path', ''),
    '#description' => t(
      'Optionally, copy files to this path when the node is exported.
      The primary advantage of this is to divert exported files into a
      safe location so they can be committed to source control (eg: SVN,
      CVS, Git).  <em>Tip: For install profile developers, setting this
      path to <code>profiles/my_profile/node_export_assets</code> may be
      useful.</em>'
    ),
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name=node_export_file_mode]' => array('value' => 'local'),
      ),
    ),
  );

  $form['file']['node_export_file_supported_fields'] = array(
    '#type' => 'textfield',
    '#title' => t('Supported file field types'),
    '#default_value' => variable_get('node_export_file_supported_fields', 'file, image'),
    '#maxlength' => 512,
    '#description' => t('Comma seperated list of file field types to detect for export/import.'),
  );

  return system_settings_form($form);
}

/**
 *  Export GUI function.
 *
 *  @param $nodes
 *    A node, an array of nodes, or an array of nids.
 *  @param $format
 *    The node export format.
 *  @param $delivery
 *    The code delivery format, if NULL will use settings.
 *  @return
 *    The node export form or nothing if calling function to serve file.
 */
function node_export_gui($nodes = NULL, $format = NULL, $delivery = NULL) {
  // Get the $code_string.
  if ($nodes) {
    // $nodes passed in, get the code_string.
    $result = node_export($nodes, $format);
    if ($result['success']) {
      $code_string = $result['output'];
    }
    else {
      foreach ($result['output'] as $output) {
        drupal_set_message($output, 'error');
      }
      return;
    }
    $nids = node_export_nodes_to_nids($nodes);
    $format = $result['format'];
  }
  elseif (!empty($_SESSION['node_export'])) {
    // Nids and code string supplied from session.
    $session_data = array_shift($_SESSION['node_export']);
    $code_string = $session_data['code_string'];
    $nids = $session_data['nids'];
    $format = $session_data['format'];
  }

  $delivery = $delivery ? $delivery : variable_get('node_export_code', 'all');
  if ($delivery != 'file') {
    if (is_object($nodes)) {
      // Single node, output straight away.
      drupal_set_title(t('Node export of !title', array('!title' => $nodes->title)));
      return drupal_get_form('node_export_form', $nids, $code_string, $format);
    }
    elseif ($nodes) {
      // Node operation, add to session and redirect.
      $_SESSION['node_export'][] = array(
        'code_string' => $code_string,
        'nids' => $nids,
        'format' => $format,
      );
      drupal_goto('admin/content/node_export');
    }
    elseif (!$nodes) {
      // No $nodes passed, but $code_string came from session.
      return drupal_get_form('node_export_form', $nids, $code_string, $format);
    }
  }
  else {
    // Get file.
    node_export_get_file($nids, $code_string, $format);
  }
}

/**
 * Convert a node, nodes, or nids into an array of nids.
 */
function node_export_nodes_to_nids($nodes) {
  if (is_object($nodes)) {
    $nids = array($nodes->nid);
  }
  else {
    $nids = array();
    foreach ($nodes as $node) {
      if (is_object($node)) {
        $nids[] = $node->nid;
      }
      elseif (is_numeric($node)) {
        $nids[] = $node;
      }
    }
  }
  return $nids;
}

/**
 * Export form.
 *
 * @param $form
 *   The form array.
 * @param $form_state
 *   The form state.
 * @param $nids
 *   An array of node ids that are being exported.
 * @param $code_string
 *   The Node export code.
 * @param $format
 *   The Node export format.
 *
 * @return
 *   The built form array.
 */
function node_export_form($form, &$form_state, $nids, $code_string, $format) {
  $form = array();
  if (variable_get('node_export_code', 'all') == 'all') {
    $form['nids'] = array(
      '#type' => 'hidden',
      '#value' => $nids,
    );
    $form['format'] = array(
      '#type' => 'hidden',
      '#value' => $format,
    );
    $form['download_file'] = array(
      '#type' => 'submit',
      '#value' => t('Download file'),
    );
  }
  $form['export'] = array(
    '#type' => 'textarea',
    '#title' => t('Node export code'),
    '#default_value' => $code_string,
    '#rows' => 30,
    '#description' => t('Copy this code and then on the site you want to import to, go to the <em>Node export: import</em> link under <em>Add content</em>, and paste it in there.'),
    '#attributes' => array(
      'wrap' => 'off',
    ),
    '#wysiwyg' => FALSE,
  );
  return $form;
}

/**
 * Export form submit function.
 *
 * File download was requested.
 */
function node_export_form_submit($form, &$form_state) {
  // Get file.
  $nids = $form_state['values']['nids'];
  $code_string = $form_state['values']['export'];
  $format = $form_state['values']['format'];
  node_export_get_file($nids, $code_string, $format);
}

/**
 * Generate text file.
 *
 * @param $nids
 *   An array of node ids.
 * @param $code_string
 *   The text output.
 * @param $format
 *   The format used.
 */
function node_export_get_file($nids, $code_string, $format = NULL) {
  $filename_data = array();
  $filename_data['node-count'] = count($nids);
  $filename_data['timestamp'] = REQUEST_TIME;
  $filename_data['format'] = $format ? $format : 'export';

  // Add a list of nids
  if (count($nids) <= variable_get('node_export_file_list', 10)) {
    $filename_data['nid-list'] = '[' . implode(',', $nids) . ']';
  }
  $name = variable_get('node_export_filename', 'node-export[node_export_filename:nid-list]([node_export_filename:node-count]-nodes).[node_export_filename:timestamp].[node_export_filename:format]');
  $data = array('node_export_filename' => (object)$filename_data);
  $name = token_replace($name, $data);

  $formats = node_export_format_handlers();
  $format_data = $formats[$format];
  $mime = !empty($format_data['#mime']) ? $format_data['#mime'] : 'text/plain';

  header('Content-type: ' . $mime);
  header('Content-Disposition: attachment; filename="' . $name . '"');
  print($code_string);
  // Clean exit.
  module_invoke_all('exit');
  exit;
}

/**
 * Import Form.
 *
 *  @param $form
 *    The form array.
 *  @param $form_state
 *    The form state.
 *
 *  @return
 *    The built form array.
 */
function node_export_import_form($form, &$form_state) {

  // Initialise to prevent notices
  $values = array(
    'file' => FALSE,
    'code' => FALSE,
  );

  $form = array();
  $form['#attributes'] = array(
    'enctype' => "multipart/form-data",
  );
  $form['#prefix'] = "<p>";
  $form['#prefix'] .= t('You may import content by pasting or uploading the code exported from Node export.') . " ";
  $form['#prefix'] .= t("Some values may be reset during imports depending on Node export's configuration.");
  $form['#prefix'] .= "</p>";

  $form['upload'] = array(
    '#type' => 'fieldset',
    '#title' => t('Upload file'),
    '#collapsible' => TRUE,
    '#collapsed' => !$values['file'],
  );
  $form['upload']['file'] = array(
    '#type' => 'file',
    '#description' => t('To clear this field, <a href="!reset">reset the form</a>.', array('!reset' => url($_GET['q'])))
  );
  $form['paste'] = array(
    '#type' => 'fieldset',
    '#title' => t('Paste code'),
    '#collapsible' => TRUE,
    '#collapsed' => !$values['code'],
  );
  $form['paste']['code'] = array(
    '#type' => 'textarea',
    '#default_value' => '',
    '#rows' => 30,
    '#description' => t('Paste the code of a node export here.'),
    '#wysiwyg' => FALSE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );
  $form['actions']['reset'] = array(
    '#markup' => l(t('Reset the form'), $_GET['q']),
  );

  return $form;
}

/**
 * Validate function for import form.
 */
function node_export_import_form_validate($form, &$form_state) {
  if (
    $form_state['clicked_button']['#id'] == 'edit-submit' &&
    !$_FILES['files']['name']['file'] &&
    !$form_state['values']['code']
  ) {
    drupal_set_message(t('Please upload a file or paste code to import.'), 'error');
    form_set_error('', NULL);
  }
}

/**
 * Submit function for import form.
 *
 * @todo: is there a way to get the contents of the file without using
 * file_save_upload()?
 */
function node_export_import_form_submit($form, &$form_state) {
  if ($_FILES['files']['name']['file']) {
    $original = $_FILES['files']['name']['file'];
    $save = file_save_upload('file', array('file_validate_extensions' => array()));
    if (!$save) {
      drupal_set_message(t('Error: Node export could not save file.'), 'error');
    }
    else {
      $save->original = $original;
      form_set_value($form['upload']['file'], serialize($save), $form_state);
    }
  }

  if ($form_state['values']['file']) {
    $file = unserialize($form_state['values']['file']);
    if (file_exists($file->uri)) {
      $code_string = file_get_contents($file->uri);
      unlink($file->uri);
    }
    file_delete($file);
  }
  elseif ($form_state['values']['code']) {
    $code_string = trim($form_state['values']['code']);
  }

  if (isset($code_string)) {
    $result = node_export_import($code_string);
    // Output the status or error messages.
    foreach ($result['output'] as $output) {
      drupal_set_message($output, ($result['success'] ? 'status' : 'error'));
    }
    // We need to send this user somewhere, and we know they have permission
    // for this page:
    drupal_goto('node/add/node_export');
  }

}


