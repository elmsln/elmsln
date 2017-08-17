<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php
  // see if we have a cron key, this is easiest indicator its working
  if (isset($row->field_field_cron_key[0]['raw']['value'])) {
    $text = t('Service available');
    $color = 'green-text text-darken-1';
    $icon = FALSE;
  }
  else {
    $course = $row->field_field_machine_name[0]['raw']['value'];
    $service = $row->_field_data['node_field_data_field_services_nid']['entity']->field_machine_name['und'][0]['value'];
    $filepath = variable_get('cis_job_path', CIS_HELPER_JOB_PATH) . '/' . $course . '.' . $service;
    // much more difficult usecases of in progress
    if (file_exists($filepath . '.progress')) {
      $progfile = file_get_contents($filepath . '.progress');
      $progfile = explode("\n", $progfile);
      $step = array_shift($progfile);
      if (count($progfile) > 1) {
        $msg = implode("\n", $progfile);
      }
      $icon = TRUE;
      switch ($step) {
        case 1:
          // scipt started
          $text = t('Starting error checking');
          $color = 'orange-text text-darken-2';
        break;
        case 2:
          // right before drush si
          $text = t('Installing @service', array('@service' => $service));
          $color = 'amber-text text-darken-2';
        break;
        case 3:
          // right after drush si
          $text = t('Verifying install');
          $color = 'yellow-text text-darken-3';
        break;
        case 4:
          // after drush commands
          $text = t('Verification complete');
          $color = 'light-green-text';
        break;
        case 5:
          $text = t('Integrating with network');
          $color = 'green-text text-lighten-1';
        break;
        case 6:
          $text = t('Finished');
          $color = 'green-text text-darken-1';
          $icon = FALSE;
        break;
      }
    }
    elseif (file_exists($filepath . '.processed')) {
      // job just about finished
      $text = t('Almost there..');
      $color = 'grey-text text-lighten-2';
      $icon = TRUE;
    }
    elseif (file_exists($filepath)) {
      // job hasn't started yet
      $text = t('Waiting for server');
      $color = 'grey-text text-lighten-2';
      $icon = TRUE;
    }
  }
  if ($icon) {
    $icon = '<elmsln-loading size="small" color="' . $color . '" style="display:inline-flex;"></elmsln-loading>';
  }
  else {
    $icon = '<iron-icon icon="check" class="' . $color . '"></iron-icon>';
  }
  // make sure we have something to render
  if (isset($text)) {
    print '<paper-button>' . $icon . '<div style="display:inline-flex;">' . $text . '</div></paper-button>';
  }
?>








