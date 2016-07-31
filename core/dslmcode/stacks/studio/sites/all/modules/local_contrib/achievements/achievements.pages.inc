<?php

/**
 * @file
 * Page callbacks for the Achievements module.
 */

/**
 * Menu callback; show the site-wide leaderboard.
 *
 * @param $days
 *   If the achievements_recent.module is enabled, it will use the $days
 *   parameter to constrain the leaderboard to one of its day frames.
 */
function achievements_leaderboard_totals($days = NULL) {
  // force no sorting on # so it doesn't get the 'active' CSS, which screws up relative non-header display.
  $header = array(array('data' => t('#'), 'sort' => NULL), t('Who'), t('Points'), t('Unlocks'), t('Latest achievement'));
  $achievers = $rows = array('top' => array(), 'relative' => array());

  // determine whether we're doing a day frame or normal all-time.
  $day_frame = module_exists('achievements_recent') && $days > 0;
  $leaderboard_table = $day_frame ? 'achievement_totals_days' : 'achievement_totals';

  // load up all our achievers for the page.
  $query = db_select($leaderboard_table, 'at')->extend('PagerDefault');
  $query->addTag('achievement_totals')->join('users', 'u', 'u.uid = at.uid');
  $query->fields('at', array('uid', 'points', 'unlocks', 'timestamp', 'achievement_id'))->fields('u', array('name'));
  $day_frame ? $query->condition('days', $days) : NULL; // hey, it's better than a 3 line code-style-friendly if.
  $query->orderBy('at.points', 'DESC')->orderBy('at.timestamp'); // @bug DESC/ASC doesn't index. ever. bastids.
  $query->limit(variable_get('achievements_leaderboard_count_per_page', 10));
  $achievers['top'] = $query->execute()->fetchAllAssoc('uid');

  if (user_is_logged_in() && variable_get('achievements_leaderboard_relative', 'nearby_ranks') != 'disabled') {
    $achievers['relative'] = (variable_get('achievements_leaderboard_relative', 'nearby_ranks') == 'nearby_ranks')
      ? achievements_totals_user(variable_get('achievements_leaderboard_relative_nearby_ranks', 2), NULL, $days)
      : achievements_totals_user(0, NULL, $days); // you and me, togetheRrrr FoReEEvvvVeeEeeRRrRR.
  }

  // display our achievers in "how awesome they are" order.
  // Global rank isn't stored in the database (to prevent us from having
  // complicated rejiggering every time an achievement is unlocked), but
  // the order the query returns is the order of the leaderboard. thus,
  // we start at 1 and increase the rank for every row we're showing.
  // also, be careful to start with the right number on pager queries.
  $rank = 0 + ($GLOBALS['pager_page_array'][0] * variable_get('achievements_leaderboard_count_per_page', 10));
  foreach (array('top', 'relative') as $type) {
    foreach ($achievers[$type] as $achiever) {
      // determine the current rank and set some speshul classes.
      $rank = $achiever->rank = isset($achiever->rank) ? $achiever->rank : $rank + 1;
      $classes = ($achiever->uid == $GLOBALS['user']->uid) ? array('achievement-leaderboard-current-user') : array();
      if ($rank <= 3) {  // give special classes if its the current user or if it's a cherished leader position.
        $classes[] = 'achievement-leaderboard-top-rank';
        $classes[] = 'achievement-leaderboard-top-rank-' . $rank;
      }

      $rows[$type][$achiever->uid] = array(
        'class' => $classes,
        'data'  => array(
          array(
            'data'  => $rank,
            'class' => array('achievement-leaderboard-rank')
          ),
          array(
            'data'  => theme('username', array('account' => $achiever)),
            'class' => array('achievement-leaderboard-username')
          ),
          array(
            'data'  => l($achiever->points, 'user/' . $achiever->uid . '/achievements'),
            'class' => array('achievement-leaderboard-points')
          ),
          array(
            'data'  => l($achiever->unlocks, 'user/' . $achiever->uid . '/achievements'),
            'class' => array('achievement-leaderboard-unlocks')
          ),
        ),
      );

      // since we're showing the "latest achievement" for a user, we have to
      // determine what image to use and respect 'secret' status. we already
      // do this in achievements_template_shared_variables(), so reuse it. we
      // fake an #unlock so the 'unlocked' image is returned; the POV for this
      // achievement display is the ranked user/row, NOT the current user.
      $achievers[$type][$achiever->uid]->latest = array(
        '#theme'        => 'achievement_latest_unlock',
        '#achievement'  => achievements_load($achiever->achievement_id),
        '#unlock'       => array('timestamp' => $achiever->timestamp),
      );
      $rows[$type][$achiever->uid]['data'][] = array(
        'data'    => render($achievers[$type][$achiever->uid]->latest),
        'class'   => array('achievement-leaderboard-latest')
      );
    }
  }

  foreach (array('top', 'relative') as $type) {
    $leaderboard = array(
      'achievers' => $achievers,
      'block'     => FALSE,
      'type'      => $type,
      'render'    => array(
        '#attributes' => array('class' => array('achievement-leaderboard', 'achievement-leaderboard-' . $type)),
        '#header'     => $type == 'top' ? $header : NULL, // relative piggybacks off of top.
        '#empty'      => $type == 'top' ? t('No one has been ranked yet.') : NULL,
        '#rows'       => $rows[$type],
        '#theme'      => 'table',
      ),
    );
    if ($type == 'top' || count($rows['relative'])) {
      drupal_alter('achievements_leaderboard', $leaderboard);
      $build['achievements']['leaderboard'][$type] = $leaderboard['render'];
    }
  }

  $build['achievements']['leaderboard_pager'] = array(
    '#theme'  => 'pager',
  );

  return $build;
}

/**
 * Block callback; show the global leaderboard.
 */
function achievements_leaderboard_block() {
  $header = array(array('data' => t('#'), 'sort' => NULL), t('Who'), t('Pts'));
  $achievers = $rows = array('top' => array(), 'relative' => array());

  $query = db_select('achievement_totals', 'at');
  $query->addTag('achievement_totals')->join('users', 'u', 'u.uid = at.uid');
  $query->fields('at', array('uid', 'points', 'unlocks'))->fields('u', array('name'));
  $query->orderBy('at.points', 'DESC')->orderBy('at.timestamp'); // @bug DESC/ASC doesn't index.
  $query->range(0, variable_get('achievements_leaderboard_block_count_top', 5));
  $achievers['top'] = $query->execute()->fetchAllAssoc('uid');

  if (user_is_logged_in() && !isset($achievers['top'][$GLOBALS['user']->uid]) && variable_get('achievements_leaderboard_block_relative', 'nearby_ranks') != 'disabled') {
    $achievers['relative'] = (variable_get('achievements_leaderboard_block_relative', 'nearby_ranks') == 'nearby_ranks')
      ? achievements_totals_user(variable_get('achievements_leaderboard_block_relative_nearby_ranks', 1))
      : achievements_totals_user(); // you and me, togetheRrrr almost nEveVvaeeeeEEERrrrrR111!
  }

  $rank = 0; // innocent widdle variable!
  foreach (array('top', 'relative') as $type) {
    foreach ($achievers[$type] as $achiever) {
      $rank = $achiever->rank = isset($achiever->rank) ? $achiever->rank : $rank + 1;
      $classes = ($achiever->uid == $GLOBALS['user']->uid) ? array('achievement-leaderboard-current-user') : array();
      if ($rank <= 3) {  // give special classes if its the current user or if it's a cherished leader position.
        $classes[] = 'achievement-leaderboard-top-rank';
        $classes[] = 'achievement-leaderboard-top-rank-' . $rank;
      }

      $rows[$type][$achiever->uid] = array(
        'class' => $classes,
        'data'  => array(
          array(
            'data'  => $rank,
            'class' => array('achievement-leaderboard-rank')
          ),
          array(
            'data'  => theme('username', array('account' => $achiever)),
            'class' => array('achievement-leaderboard-username')
          ),
          array(
            'data'  => l($achiever->points, 'user/' . $achiever->uid . '/achievements'),
            'class' => array('achievement-leaderboard-points')
          ),
        ),
      );
    }
  }

  foreach (array('top', 'relative') as $type) {
    $leaderboard = array(
      'achievers' => $achievers,
      'block'     => TRUE,
      'type'      => $type,
      'render'    => array(
        '#attributes' => array('class' => array('achievement-leaderboard', 'achievement-leaderboard-' . $type)),
        '#header'     => $type == 'top' ? $header : NULL, // relative piggybacks off of top.
        '#empty'      => $type == 'top' ? t('No one has been ranked yet.') : NULL,
        '#rows'       => $rows[$type],
        '#theme'      => 'table',
      ),
    );
    if ($type == 'top' || count($rows['relative'])) {
      drupal_alter('achievements_leaderboard', $leaderboard);
      $build['achievements']['leaderboard'][$type] = $leaderboard['render'];
    }
  }

  $build['achievements']['see-more'] = array(
    '#prefix' => '<div class="achievement-see-more">',
    '#markup' =>  l(t('View full leaderboard »'), 'achievements/leaderboard'),
    '#suffix' => '</div>',
  );

  return $build;
}

/**
 * Menu callback; display a single achievement page with leaderboards.
 */
function achievements_leaderboard_for($achievement) {
  drupal_set_title(t('Achievement: @title', array('@title' => $achievement['title'])), PASS_THROUGH);

  $build['achievements']['achievement'] = array(
    '#achievement'  => $achievement,
    '#unlock'       => achievements_unlocked_already($achievement['id']),
    '#theme'        => 'achievement__leaderboard_for',
  );

  // get stats for first and most recent unlocks.
  $query = db_select('achievement_unlocks', 'au');
  $query->join('achievement_totals', 'at', 'at.uid = au.uid');
  $query->join('users', 'u', 'u.uid = au.uid'); // same basic start for both queries.
  $query->condition('au.achievement_id', $achievement['id']); // ... with a slight tweak.
  $query->fields('au', array('uid', 'rank', 'timestamp'))->fields('at', array('points', 'unlocks'))->fields('u', array('name'));
  $query2 = clone $query; // allows us to save a few lines of duplicate query building. never used clone before. awesome.
  $achievers['first']  = $query->orderBy('rank')->range(0, 10)->execute()->fetchAllAssoc('uid'); // FI... sigh.
  $achievers['recent'] = $query2->orderBy('timestamp', 'DESC')->range(0, 10)->execute()->fetchAllAssoc('uid');

  foreach (array('first', 'recent') as $type) {
    $rows = array(); // clear previous run.
    foreach ($achievers[$type] as $achiever) {
      $rows[$achiever->uid] = array(
        'class' => array(),
        'data' => array(
          array(
            'data'  => $achiever->rank,
            'class' => array('achievement-leaderboard-rank')
          ),
          array(
            'data'  => theme('username', array('account' => $achiever)),
            'class' => array('achievement-leaderboard-username')
          ),
          array(
            'data'  => l($achiever->points, 'user/' . $achiever->uid . '/achievements'),
            'class' => array('achievement-leaderboard-points')
          ),
          array(
            'data'  => format_date($achiever->timestamp, 'short'),
            'class' => array('achievement-leaderboard-when')
          ),
        ),
      );
    }

    $leaderboard = array(
      'achievers' => $achievers,
      'block'     => FALSE,
      'type'      => $type,
      'render'    => array(
        '#attributes' => array('class' => array('achievement-leaderboard-' . $type)),
        '#caption'    => t('@type achievement unlocks', array('@type' => drupal_ucfirst($type))),
        '#header'     => array(t('#'), t('Who'), t('Points'), t('When')),
        '#empty'      => t('No one has unlocked this yet. Keep trying!'),
        '#rows'       => $rows,
        '#theme'      => 'table',
      ),
    );
    drupal_alter('achievements_leaderboard', $leaderboard);
    $build['achievements']['leaderboard'][$type] = $leaderboard['render'];
  }

  return $build;
}

/**
 * Menu callback; display all achievements for the passed user.
 *
 * @param $account
 *   The user object this request applies against.
 */
function achievements_user_page($account) {
  drupal_set_title(t('Achievements for @name', array('@name' => $account->name)));
  $unlocks = achievements_unlocked_already(NULL, $account->uid);
  $achievements_totals_user = achievements_totals_user(0, $account->uid);
  $achiever = array_pop($achievements_totals_user);

  $build['achievements']['stats'] = array(
    '#theme'  => 'achievement_user_stats',
    '#stats'  => array(
      'name'          => $account->name,
      'rank'          => isset($achiever->rank) ? $achiever->rank : 0,
      'points'        => isset($achiever->points) ? $achiever->points : 0,
      'unlocks_count' => count($unlocks),
      'total_count'   => count(achievements_load()),
    ),
  );

  $achievements_grouped = achievements_load(NULL, TRUE);

  // theme wrappers let us wrap our children with a rethemable/overridable DIV.
  $build['achievements']['tabs']['#theme_wrappers'] = array('achievement_groups_wrapper');

  // use jQuery tabs if more than one group.
  if (count($achievements_grouped) > 1) {
    foreach ($achievements_grouped as $group_id => $group) {
      $links['achievement-group-' . $group_id] = array(
        'title'     => $group['title'],
        'fragment'  => 'achievement-group-' . $group_id,
        'href'      => '', // just the fragment, please.
        'external'  => TRUE, // no base_path dammit. GZUS.
      );
    }
    $build['achievements']['tabs']['navigation'] = array('#theme' => 'links', '#links' => $links);
    $build['achievements']['tabs']['navigation']['#attached']['library'][] = array('system', 'ui.tabs');
    $build['achievements']['tabs']['navigation']['#attached']['js']= array( // I AM NOT A JS EXPERT. OOooOH NO.
      'jQuery(document).ready(function(){jQuery("#achievement-groups").tabs();});' => array('type' => 'inline')
    );
  }

  foreach ($achievements_grouped as $group_id => $group) {
    $locked_weight = 0; // we can't use definition order.
    $build['achievements']['tabs']['groups'][$group_id]['#group_id'] = $group_id; // add a DIV in the wrapper.
    $build['achievements']['tabs']['groups'][$group_id]['#theme_wrappers'] = array('achievement_group_wrapper');

    foreach ($group['achievements'] as $achievement_id => $achievement) {
      if (!empty($achievement['invisible']) && !isset($unlocks[$achievement_id])) {
        continue; // invisibles only display if this $account has unlocked them.
      }

      // if it's not an invisible achievement, we've got to show something. $build out what and where.
      $build['achievements']['tabs']['groups'][$group_id][$achievement_id]['#achievement'] = $achievement;
      $build['achievements']['tabs']['groups'][$group_id][$achievement_id]['#theme'] = 'achievement__user_page';

      if (isset($unlocks[$achievement_id])) {
        $build['achievements']['tabs']['groups'][$group_id][$achievement_id]['#unlock'] = $unlocks[$achievement_id];

        if (variable_get('achievements_unlocked_move_to_top', TRUE)) {
          $build['achievements']['tabs']['groups'][$group_id][$achievement_id]['#weight'] = -$unlocks[$achievement_id]['timestamp'];
          // by setting the negative weight to the timestamp, the latest unlocks are always shown at the top.
        }
      }
      elseif (!isset($unlocks[$achievement_id]) && variable_get('achievements_unlocked_move_to_top', TRUE)) {
        // if we're forcing unlocks to the top, locked achievements have to be forced to the bottom.
        $build['achievements']['tabs']['groups'][$group_id][$achievement_id]['#weight'] = $locked_weight++;
      }
    }
  }

  return $build;
}

/**
 * Menu callback; Retrieve autocomplete suggestions for achievement names.
 */
function achievements_autocomplete($string = '') {
  $achievements = achievements_load(); // MmmMMmMm, gooOoaaAaalLLlsss.
  array_walk($achievements, 'achievements_autocomplete_search', $string);
  drupal_json_output(array_slice(array_filter($achievements), 0, 10));
}

/**
 * array_walk helper function for achievements_autocomplete().
 */
function achievements_autocomplete_search(&$value, $key, $string) {
  $value = (stripos($value['title'], $string) === FALSE) ? FALSE : $value['title'];
}

/**
 * Default theme implementation for a user's achievement stats.
 *
 * @param variables
 *   An associative array containing:
 *   - stats: An array which contains the following keys:
 *     name, rank, points, unlocks_count, and total_count.
 */
function theme_achievement_user_stats($variables) {
  $output = '<div class="achievement-user-stats">'; // VERY CONFUSING CODE COMMENT ABOUT PSYNAPTIC. YOU THOUGHT I WAS KIDDING?
  $output .= t('@name is ranked #@rank with @points points. @unlocks_count of @total_count achievements have been unlocked.', array(
    '@name'           => $variables['stats']['name'],
    '@rank'           => $variables['stats']['rank'],
    '@points'         => $variables['stats']['points'],
    '@unlocks_count'  => $variables['stats']['unlocks_count'],
    '@total_count'    => $variables['stats']['total_count'],
  ));
  $output .= '</div>';
  return $output;
}

/**
 * Default theme for the wrapper around a user's achievements page.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: A render containing the user's achievements page.
 */
function theme_achievement_groups_wrapper($variables) {
  return '<div id="achievement-groups">' . $variables['element']['#children'] . '</div>';
}

/**
 * Default theme for the wrapper around an achievement group.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: A render containing the achievement group.
 */
function theme_achievement_group_wrapper($variables) {
  $group_id = 'achievement-group-' . $variables['element']['#group_id'];
  return '<div id="' . $group_id . '" class="achievement-group">' . $variables['element']['#children'] . '</div>';
}
