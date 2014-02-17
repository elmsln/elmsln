<?php

/**
 * @file
 * Admin callbacks for the Achievements Recent module.
 */

/**
 * Create and seed the limited achievement leaderboards.
 */
function achievements_recent_settings() {
  $form['achievements_recent_leaderboard_init'] = array(
    '#description'        => t("If your site already has achievements and users with unlocks, you can manually initialize and populate the recent leaderboards below. Otherwise, the recent leaderboards will fill with users as they unlock new achievements. <strong>You do not have to initialize the recent leaderboards if your site has just enabled the Achievements module</strong> - the following options exist primarily for previous installations. <strong>This initialization is a database-intensive operation</strong>, so it will only populate 1000 users at a time. You'll be informed of its progress and whether you need to keep clicking. If you prefer to run these imports via the command line, you can use something like <code>drush ev 'achievements_recent_leaderboard_init(<em>DAYS</em>);'</code>, where <em>DAYS</em> is one of the following: @valid_days.", array('@valid_days' => implode(", ", array_keys(achievements_recent_valid_days())))),
    '#title'              => t('Initialize recent leaderboards'),
    '#type'               => 'fieldset',
  );

  foreach (achievements_recent_valid_days() as $days => $days_human) {
    $form_key = 'achievements_recent_leaderboard_init_' . $days .'_day';
    $form['achievements_recent_leaderboard_init'][$form_key] = array(
      '#achievement_days'   => $days, // Stomach sick... what's... oh:
      '#attributes'         => array('style' => 'margin-top: 9px;'),
      '#type'               => 'submit', // Gasp! Inline spacing! Crap CSS!
      '#submit'             => array('achievements_recent_leaderboard_init_submit'),
      '#value'              => t('Initialize @days_human leaderboard', array('@days_human' => $days_human)),
    );
  }

  return $form;
}

/**
 * Submit callback; initialize a recent leaderboard.
 */
function achievements_recent_leaderboard_init_submit($form, &$form_state) {
  achievements_recent_leaderboard_init($form_state['clicked_button']['#achievement_days']);
}
