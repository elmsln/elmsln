<?php

/**
 * User profile template preprocess.
 */
function cpr_foundation_access_preprocess_user_profile(&$vars) {
  $vars['user_profile']['field_photo']['#attributes']['class'] = array('circle');
}