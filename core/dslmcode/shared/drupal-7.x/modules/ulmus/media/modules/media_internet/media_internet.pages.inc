<?php

/**
 * @file
 * Supports the addition of Internet media.
 */

/**
 * Provides a form for adding media items from 3rd party sources.
 *
 * @todo Convert the form arguments to just one array of options/parameters.
 */
function media_internet_add($form, &$form_state = array(), $types = NULL) {
  $form['embed_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter a URL to an image'),
    '#description' => t('Enter a URL to an image on the web.'),
    '#attributes' => array('class' => array('media-add-from-url')),
    // There is no standard specifying a maximum length for a URL. Internet
    // Explorer supports up to 2083 (http://support.microsoft.com/kb/208427)
    // so we assume publicly available media URLs are within this limit.
    '#maxlength' => 2083,
    '#required' => TRUE,
  );

  // Create an array to hold potential Internet media providers.
  $providers = array();

  // Determine if there are any visible providers.
  foreach (media_internet_get_providers() as $key => $provider) {
    if (empty($provider['hidden']) || $provider['hidden'] != TRUE) {
      $providers[] = array(
        'data' => check_plain($provider['title']),
        'class' => array(drupal_html_class($provider['title'])),
      );
    }
  }

  // Notify the user of any available providers.
  if ($providers) {
    // If any providers are enabled it is assumed that some kind of embed is supported.
    $form['embed_code']['#title'] = t('Enter an image URL or an embed code');
    $form['embed_code']['#description'] = t('Enter a URL or the embed code from a media provider.');

    // Providers are displayed in an unordered list below the embed input.
    // Providers can easily style their own listing by targeting the unique
    // class assigned to each list item.
    $form['providers'] = array(
      '#theme' => 'item_list',
      '#title' => t('Supported providers'),
      '#items' => $providers,
      '#attributes' => array(
        'class' => array('media-internet-providers'),
      ),
    );
  }

  $form['#validators'] = array();
  if ($types) {
    $form['#validators']['media_file_validate_types'] = array($types);
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Allow stream wrappers to have their chance at validation.
 *
 * Any module that implements hook_media_parse will have an
 * opportunity to validate this.
 *
 * @see media_parse_to_uri()
 */
function media_internet_add_validate($form, &$form_state) {
  // Supporting providers can now claim this input. It might be a URL, but it
  // might be an embed code as well.
  $embed_code = $form_state['values']['embed_code'];

  try {
    $provider = media_internet_get_provider($embed_code);
    $provider->validate();
  }
  catch (MediaInternetNoHandlerException $e) {
    form_set_error('embed_code', $e->getMessage());
    return;
  }
  catch (MediaInternetValidationException $e) {
    form_set_error('embed_code', $e->getMessage());
    return;
  }

  $validators = $form['#validators'];
  $file = $provider->getFileObject();

  if ($validators) {
    try {
      $file = $provider->getFileObject();
    }
    catch (Exception $e) {
      form_set_error('embed_code', $e->getMessage());
      return;
    }

    // Check for errors. @see media_add_upload_validate calls file_save_upload().
    // this code is ripped from file_save_upload because we just want the validation part.
    // Call the validation functions specified by this function's caller.
    $errors = file_validate($file, $validators);

    if (!empty($errors)) {
      $message = t('%url could not be added.', array('%url' => $embed_code));
      if (count($errors) > 1) {
        $message .= theme('item_list', array('items' => $errors));
      }
      else {
        $message .= ' ' . array_pop($errors);
      }
      form_set_error('embed_code', $message);
      return FALSE;
    }
  }

  // @TODO: Validate that if we have no $uri that this is a valid file to
  // save. For instance, we may only be interested in images, and it would
  // be helpful to let the user know they passed the HTML page containing
  // the image accidentally. That would also save us from saving the file
  // in the submit step.

  // This is kinda a hack of the same.

  // This should use the file_validate routines that the upload form users.
  // We need to fix the media_parse_to_file routine to allow for a validation.
}

/**
 * Upload a file from a URL.
 *
 * This will copy a file from a remote location and store it locally.
 *
 * @see media_parse_to_uri()
 * @see media_parse_to_file()
 */
function media_internet_add_submit($form, &$form_state) {
  $embed_code = $form_state['values']['embed_code'];

  try {
    // Save the remote file
    $provider = media_internet_get_provider($embed_code);
    // Providers decide if they need to save locally or somewhere else.
    // This method returns a file object
    $file = $provider->save();
  }
  catch (Exception $e) {
    form_set_error('embed_code', $e->getMessage());
    return;
  }

  if (!$file->fid) {
    form_set_error('embed_code', t('The file %file could not be saved. An unknown error has occurred.', array('%file' => $embed_code)));
    return;
  }
  else {
    $form_state['file'] = $file;
  }

  // Redirect to the file edit page after submission.
  if (file_entity_access('update', $file)) {
    $destination = array('destination' => 'admin/content/file');
    if (isset($_GET['destination'])) {
      $destination = drupal_get_destination();
      unset($_GET['destination']);
    }
    $form_state['redirect'] = array('file/' . $file->fid . '/edit', array('query' => $destination));
  }
  else {
    $form_state['redirect'] = 'admin/content/file';
  }
}
