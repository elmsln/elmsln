<?php

/**
 * Implements hook_cer_fields().
 */
function cer_profile2_cer_fields() {
  $fields = array();

  // Create a fake field for each Profile2 type.
  foreach (array_keys(profile2_get_types()) as $profile_type) {
    // Profiles can only be attached to user accounts.
    $fields["user:user:profile_{$profile_type}"]['class'] = 'CerProfile2Field';
  }

  return $fields;
}

/**
 * Implements hook_cer_fields_alter().
 */
function cer_profile2_cer_fields_alter(array &$fields) {
  foreach (array_keys($fields) as $identifier) {
    list ($entity_type, $bundle) = explode(':', $identifier);

    // If this field is instantiated on a Profile2, make CER treat it like a field
    // collection by first setting its parent field, and setting the 'require parent'
    // flag so that CER won't allow it to stand alone in a field chain.
    if ($entity_type == 'profile2') {
      $fields[$identifier]['parents'][] = "user:user:profile_{$bundle}";
      $fields[$identifier]['require parent'] = TRUE;
    }
  }
}
