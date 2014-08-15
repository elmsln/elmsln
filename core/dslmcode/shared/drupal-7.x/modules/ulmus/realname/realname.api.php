<?php

/**
 * @file
 * Hooks provided by the Real name module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter the pattern for a user's real name prior to generation.
 *
 * @param $pattern
 *   The real name pattern string prior to token replacement.
 * @param $account
 *   A user account object.
 *
 * @see realname_update()
 *
 * @ingroup realname
 */
function hook_realname_pattern_alter(&$pattern, $account) {

}

/**
 * Alter a user's real name before it is saved to the database.
 *
 * @param $realname
 *   The user's generated real name.
 * @param $account
 *   A user account object.
 *
 * @see realname_update()
 *
 * @ingroup realname
 */
function hook_realname_alter(&$realname, $account) {

}

/**
 * Respond to updates to an account's real name.
 *
 * @see realname_update()
 *
 * @ingroup realname
 */
function hook_realname_update($realname, $account) {

}

/**
 * @} End of "addtogroup hooks".
 */
