<?php

/**
 * @file
 * Admin callbacks for the Achievements module.
 */

/**
 * Configure achievements.
 */
function achievements_settings() {
  $form['achievements_cache'] = array(
    '#type'               => 'fieldset',
    '#title'              => t('Clear cache'),
  );
  $form['achievements_cache']['achievements_clear_info_cache'] = array(
    '#type'               => 'submit', // just like performance cache clears.
    '#submit'             => array('achievements_clear_info_cache_submit'),
    '#value'              => t('Clear achievements information cache'),
  );

  $form['achievements_manual'] = array(
    '#description'        => t("Taking an achievement from a user will <em>not</em> change other users' unlock ranking. <strong>This functionality should be used sparingly for progress-based achievements as it can create odd inconsistencies in the internal statistics.</strong> For example, giving a user the \"125 comments posted\" achievement does <em>not</em> mean they've actually posted 125 comments - if they've only made 15 legitimate comments, they'll still need to post 235 more to achieve \"250 comments posted\". Similarly, taking away an achievement will delete any relevant internal statistics, causing the user to \"start over\" with that achievement even if applicable and countable data remains."),
    '#title'              => t('Manual overrides'),
    '#type'               => 'fieldset',
  );
  $form['achievements_manual']['achievements_manual_user'] = array(
    '#autocomplete_path'  => 'user/autocomplete',
    '#maxlength'          => '60',
    '#title'              => t('Username or UID'),
    '#type'               => 'textfield',
  );
  $form['achievements_manual']['achievements_manual_achievement'] = array(
    '#autocomplete_path'  => 'achievements/autocomplete',
    '#title'              => t('Achievement ID'),
    '#type'               => 'textfield',
  );
  $form['achievements_manual']['actions'] = array('#type' => 'actions');
  $form['achievements_manual']['actions']['achievements_manual_give'] = array(
    '#achievement_action' => 'give',
    '#type'               => 'submit',
    '#submit'             => array('achievements_manual_submit'),
    '#value'              => t('Give achievement'),
  );
  $form['achievements_manual']['actions']['achievements_manual_take'] = array(
    '#achievement_action' => 'take',
    '#type'               => 'submit',
    '#submit'             => array('achievements_manual_submit'),
    '#value'              => t('Take achievement'),
  );

  $form['achievements_rankings'] = array(
    '#description'        => t('These settings affect the <a href="@url">global leaderboard</a>. Enabling the "relative leaderboard" will show the current user\'s position and, optionally, a number of ranks before and after that position. For example, if the current user is ranked 12th and you configure 3 nearby ranks, the relative leaderboard will show ranks 9 through 15.', array('@url' => url('achievements/leaderboard'))),
    '#title'              => t('Leaderboard ranks'),
    '#type'               => 'fieldset',
  );
  $form['achievements_rankings']['achievements_leaderboard_count_per_page'] = array(
    '#type'               => 'select',
    '#title'              => t('Number of top ranks per page'),
    '#default_value'      => variable_get('achievements_leaderboard_count_per_page', 10),
    '#options'            => drupal_map_assoc(array(5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100)),
  );
  $form['achievements_rankings']['achievements_leaderboard_relative'] = array(
    '#type'               => 'radios',
    '#title'              => t('Relative leaderboard display'),
    '#default_value'      => variable_get('achievements_leaderboard_relative', 'nearby_ranks'),
    '#options'            => array(
      'disabled'          => t('Don\'t show the relative leaderboard'),
      'user_only'         => t('Show only the current user'),
      'nearby_ranks'      => t('Show the current user and nearby ranks'),
    ),
  );
  $form['achievements_rankings']['achievements_leaderboard_relative_nearby_ranks'] = array(
    '#type'               => 'select',
    '#title'              => t('Number of nearby ranks to display'),
    '#default_value'      => variable_get('achievements_leaderboard_relative_nearby_ranks', 2),
    '#options'            => drupal_map_assoc(range(1, 10)),
  );

  $form['achievements_config'] = array(
    '#title'              => t('Additional configuration'),
    '#type'               => 'fieldset',
  );
  $module_path = drupal_get_path('module', 'achievements');
  foreach (array('unlocked', 'locked', 'secret') as $image_type) {
    $form['achievements_config']['achievements_image_' . $image_type] = array(
      '#default_value'      => variable_get('achievements_image_' . $image_type, $module_path . '/images/default-' . $image_type . '-70.jpg'),
      '#title'              => t('Default @image_type picture', array('@image_type' => $image_type)),
      '#type'               => 'textfield',
    );
  }
  $form['achievements_config']['achievements_unlocked_move_to_top'] = array(
    '#type'           => 'checkbox',
    '#title'          => t("Move the user's unlocked achievements to the top of their achievement page."),
    '#default_value'  => variable_get('achievements_unlocked_move_to_top', TRUE), // default to gamer-style.
  );

  return system_settings_form($form);
}

/**
 * Submit callback; clear achievement info cache.
 */
function achievements_clear_info_cache_submit() {
  achievements_load(NULL, FALSE, TRUE);
  drupal_set_message(t('Achievements information cache cleared.'));
}

/**
 * Submit callback; give or take away an achievement from a user.
 */
function achievements_manual_submit($form, &$form_state) {
  if (empty($form_state['values']['achievements_manual_user'])) { // ZOMG, it's #required, fool!
    drupal_set_message(t('A username or user ID is required to give or take achievements.'), 'error');
    return;
  }

  if (empty($form_state['values']['achievements_manual_achievement'])) { // HITCHCOCK STABBY STAB.
    drupal_set_message(t('An achievement ID is required to give or take achievements.'), 'error');
    return;
  }

  // well, we've got form values, so load 'em in and check for validity.
  $account = !is_numeric($form_state['values']['achievements_manual_user'])
    ? user_load_by_name($form_state['values']['achievements_manual_user'])
    : user_load($form_state['values']['achievements_manual_user']);
  $achievement = achievements_load($form_state['values']['achievements_manual_achievement']);

  if (!isset($account->uid) || $account->uid == 0) { // Wha? Who?
    drupal_set_message(t('%username is not a valid user.', // I TRIED TO HELP.
      array('%username' => $form_state['values']['achievements_manual_user'])), 'error');
    return;
  }

  if (!isset($achievement['title'])) { // -100 DKP! That's not even funny anymore.
    drupal_set_message(t('%achievement_id is not a valid achievement.', // M... many whelps?
      array('%achievement_id' => $form_state['values']['achievements_manual_achievement'])), 'error');
    return;
  }

  // if we've a valid user and achievement ID, give 'em the achievement, ya freeloaders.
  if ($account && $achievement && $form_state['clicked_button']['#achievement_action'] == 'give') {
    if (!user_access('earn achievements', $account)) { // KLAXON KLAXON CHEATAH.
      drupal_set_message(t('%username does not have permission to earn achievements.',
        array('%username' => $form_state['values']['achievements_manual_user'])), 'error');
      return;
    }

    achievements_unlocked($achievement['id'], $account->uid);
    drupal_set_message(t('%username has been given %achievement.', // yeah, yeah.
      array('%username' => $account->name, '%achievement' => $achievement['title'])));
    return;
  }

  // if we're taking away an achievement, first check if they have it.
  if ($form_state['clicked_button']['#achievement_action'] == 'take') {
    if (!achievements_unlocked_already($achievement['id'], $account->uid)) {
      drupal_set_message(t('%username has not unlocked %achievement.', // palm to forehead.
        array('%username' => $account->name, '%achievement' => $achievement['title'])), 'error');
      return;
    }

    achievements_locked($achievement['id'], $account->uid);
    drupal_set_message(t('%username has had %achievement taken away.', // nope, nope.
      array('%username' => $account->name, '%achievement' => $achievement['title'])));
    return;
  }
}
