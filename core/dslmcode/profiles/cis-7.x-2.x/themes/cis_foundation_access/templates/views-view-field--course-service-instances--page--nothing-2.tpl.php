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
    $color = '#AAFFAA';
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
      switch ($step) {
        case 1:
          // scipt started
          $text = t('Starting error checking');
          $color = '#FFFFAA';
        break;
        case 2:
          // right before drush si
          $text = t('Installing @service', array('@service' => $service));
          $color = '#FFFFCC';
        break;
        case 3:
          // right after drush si
          $text = t('Verifying install');
          $color = '#FFAAAA';
        break;
        case 4:
          // after drush commands
          $text = t('Verification complete');
          $color = '#FFCCCC';
        break;
        case 5:
          $text = t('Integrating with network');
          $color = '#CCFFCC';
        break;
        case 6:
          $text = t('Finished');
          $color = '#AAFFAA';
        break;
      }
    }
    elseif (file_exists($filepath . '.processed')) {
      // job just about finished
      $text = t('Almost there..');
      $color = '#AAFFAA';
    }
    elseif (file_exists($filepath)) {
      // job hasn't started yet
      $text = t('Waiting for server');
      $color = '#FFFFFF';
    }
  }
  // make sure we have something to render
  if (isset($text)) {
    print '<div style="line-height:2rem; background-color:' . $color . '"><div title="' . $text . '" class="icon-ecd-black etb-modal-icons"></div><span>' . $text . '</span></div>';
  }
?>








