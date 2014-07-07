<?php

/**
 * @file
 * Hooks provided by Security Kit.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter the Security Kit settings.
 *
 * @param array $options
 *   Array of runtime options.
 *
 * @see _seckit_get_options().
 */
function hook_seckit_options_alter(&$options) {
  $options['seckit_clickjacking']['x_frame'] = SECKIT_X_FRAME_SAMEORIGIN;
}

/**
 * @} End of "addtogroup hooks".
 */
