<?php
/**
 * @file
 * Admin page callbacks for the cis_helper module.
 */

/**
 * Callback for admin settings form.
 */
function cis_helper_admin_settings() {
  // college name used for writing to the file
  $form['cis_college_name'] = array(
    '#type' => 'textfield',
    '#title' => t('College machine name'),
    '#default_value' => variable_get('cis_college_name', ''),
    '#description' => t('Machine name for the college this is installed for, typically this value is just 2-3 letters that are short for the college.  For example, aa for arts and architecture.'),
  );
  // the path for the job to be created on
  $form['cis_job_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Job path'),
    '#default_value' => variable_get('cis_job_path', CIS_HELPER_JOB_PATH),
    '#description' => t('Place to write to for cron jobs to process and create a new course on a service.'),
  );
  // the path for the job to be created on
  $form['cis_build_open'] = array(
    '#type' => 'textfield',
    '#title' => t('Open course extra install'),
    '#default_value' => variable_get('cis_build_open', ''),
    '#description' => t('Additional drush calls when the course is open access'),
  );
  // the path for the job to be created on
  $form['cis_build_authenticated'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication required course extra install'),
    '#default_value' => variable_get('cis_build_authenticated', ''),
    '#description' => t('Additional drush calls when internal authentication is in use'),
  );
  // the path for the job to be created on
  $form['cis_build_lms'] = array(
    '#type' => 'textfield',
    '#title' => t('LMS Authentication required course extra install'),
    '#default_value' => variable_get('cis_build_lms', ''),
    '#description' => t('Additional drush calls when an LMS is used for authentication'),
  );
  // the path for the job to be created on
  $form['cis_build_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Code authenticed course extra install'),
    '#default_value' => variable_get('cis_build_code', ''),
    '#description' => t('Additional drush calls when access codes are in use'),
  );
  return system_settings_form($form);
}
