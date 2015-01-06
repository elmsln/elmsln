<?php

/**
 * @file
 * Harmony specific install steps.
 */

/**
 * Installation task; select which locale to use for the current profile.
 * Copied from /includes/install.core.inc.
 */
function harmony_install_select_locale(&$install_state) {
  // Find all available locales.
  $profilename = $install_state['parameters']['profile'];
  $locales = install_find_locales($profilename);
  $install_state['locales'] += $locales;

  if (!empty($_POST['locale'])) {
    foreach ($locales as $locale) {
      if ($_POST['locale'] == $locale->langcode) {
        $install_state['parameters']['locale'] = $locale->langcode;
        return;
      }
    }
  }

  if (empty($install_state['parameters']['locale'])) {
    // If only the built-in (English) language is available, and we are
    // performing an interactive installation, inform the user that the
    // installer can be localized. Otherwise we assume the user knows what he
    // is doing.
    if (count($locales) == 1) {
      if ($install_state['interactive']) {
        drupal_set_title(st('Choose language'));
        if (!empty($install_state['parameters']['localize'])) {
          $output = '<p>Follow these steps to translate Drupal into your language:</p>';
          $output .= '<ol>';
          $output .= '<li>Download a translation from the <a href="http://localize.drupal.org/download" target="_blank">translation server</a>.</li>';
          $output .= '<li>Place it into the following directory:
<pre>
/profiles/' . $profilename . '/translations/
</pre></li>';
          $output .= '</ol>';
          $output .= '<p>For more information on installing Drupal in different languages, visit the <a href="http://drupal.org/localize" target="_blank">drupal.org handbook page</a>.</p>';
          $output .= '<p>How should the installation continue?</p>';
          $output .= '<ul>';
          $output .= '<li><a href="install.php?profile=' . $profilename . '">Reload the language selection page after adding translations</a></li>';
          $output .= '<li><a href="install.php?profile=' . $profilename . '&amp;locale=en">Continue installation in English</a></li>';
          $output .= '</ul>';
        }
        else {
          include_once DRUPAL_ROOT . '/includes/form.inc';
          $elements = drupal_get_form('install_select_locale_form', $locales, $profilename);
          $output = drupal_render($elements);
        }
        return $output;
      }
      // One language, but not an interactive installation. Assume the user
      // knows what he is doing.
      $locale = current($locales);
      $install_state['parameters']['locale'] = $locale->name;
      return;
    }
    else {
      // Allow profile to pre-select the language, skipping the selection.
      $function = $profilename . '_profile_details';
      if (function_exists($function)) {
        $details = $function();
        if (isset($details['language'])) {
          foreach ($locales as $locale) {
            if ($details['language'] == $locale->name) {
              $install_state['parameters']['locale'] = $locale->name;
              return;
            }
          }
        }
      }

      // We still don't have a locale, so display a form for selecting one.
      // Only do this in the case of interactive installations, since this is
      // not a real form with submit handlers (the database isn't even set up
      // yet), rather just a convenience method for setting parameters in the
      // URL.
      if ($install_state['interactive']) {
        drupal_set_title(st('Choose language'));
        include_once DRUPAL_ROOT . '/includes/form.inc';
        $elements = drupal_get_form('install_select_locale_form', $locales, $profilename);
        return drupal_render($elements);
      }
      else {
        throw new Exception(st('Sorry, you must select a language to continue the installation.'));
      }
    }
  }
}

/**
 * Verifies the requirements for installing Drupal.
 * Again a copy of the core function but customised, this page doesn't offer a
 * button to continue the process which we swap out.
 */
function harmony_install_verify_requirements(&$install_state) {
  // Check the installation requirements for Drupal and this profile.
  $requirements = install_check_requirements($install_state);

  // Verify existence of all required modules.
  $requirements += drupal_verify_profile($install_state);

  // Check the severity of the requirements reported.
  $severity = drupal_requirements_severity($requirements);

  // If there are errors, always display them. If there are only warnings, skip
  // them if the user has provided a URL parameter acknowledging the warnings
  // and indicating a desire to continue anyway. See drupal_requirements_url().
  if ($severity == REQUIREMENT_ERROR || ($severity == REQUIREMENT_WARNING && empty($install_state['parameters']['continue']))) {
    if ($install_state['interactive']) {
      drupal_set_title(st('Requirements issues'));

      $status_report = st('<p>Below are the requirements for Harmony, any warnings or errors will be highlighted.</p>');
      $status_report .= st("<p>Once you've reviewed and resolved any issues click the &quot;Continue&quot; button after the table to re-check and progress.</p>");
      $status_report .= theme('status_report', array('requirements' => $requirements));
      $status_report .= st('<a href="!url" class="btn btn-primary">Continue</a>', array('!url' => check_url(drupal_requirements_url($severity))));
      return $status_report;
    }
    else {
      // Throw an exception showing any unmet requirements.
      $failures = array();
      foreach ($requirements as $requirement) {
        // Skip warnings altogether for non-interactive installations; these
        // proceed in a single request so there is no good opportunity (and no
        // good method) to warn the user anyway.
        if (isset($requirement['severity']) && $requirement['severity'] == REQUIREMENT_ERROR) {
          $failures[] = $requirement['title'] . ': ' . $requirement['value'] . "\n\n" . $requirement['description'];
        }
      }
      if (!empty($failures)) {
        throw new Exception(implode("\n\n", $failures));
      }
    }
  }
}
