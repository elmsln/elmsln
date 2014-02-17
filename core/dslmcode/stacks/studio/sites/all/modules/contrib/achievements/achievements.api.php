<?php

/**
 * @file
 * Hooks provided by the Achievements module and how to implement them.
 */

/**
 * Define an achievement.
 *
 * This hook describes your achievements to the base module so that it can
 * create the pages and caches necessary for site-wide display. The base
 * module doesn't know how to unlock any of your achievements... instead, you
 * use Drupal's existing hooks, the achievement storage tables, and a few
 * helper functions to complete the workflow. See the remaining documentation
 * in this file for further code samples.
 *
 * There are many different kinds of achievements, and it's accurate enough to
 * say that if you can measure or respond to an action, it can be made into a
 * matching achievement. Be creative. Look at what others are doing. Have fun.
 * Your gamification efforts will fail or be un-fun if you don't have a gamer
 * helping you, if you make everything a mindless grind, or if you simply
 * copy achievements from another site or install.
 *
 * @return
 *   An array whose keys are internal achievement IDs (32 chars max) and whose
 *   values identify properties of the achievement. These properties are:
 *   - title: (required) The title of the achievement.
 *   - description: (required) A description of the achievement.
 *   - points: (required) How many points the user will earn when unlocked.
 *   - images: (optional) An array of (optional) keys 'locked', 'unlocked',
 *     and 'secret' whose values are image file paths. Achievements exist in
 *     three separate display states: unlocked (the user has it), locked (the
 *     user doesn't have it), and secret (the user doesn't have it, and the
 *     achievement is a secret). Each state can have its own default image
 *     associated with it (which administrators can configure), or achievements
 *     can specify their own images for one, some, or all states.
 *   - storage: (optional) If you store statistics for your achievement, the
 *     core module assumes you've used the achievement ID for the storage
 *     location. If you haven't, specify the storage location here. This lets
 *     the core module know what to delete when an administrator manually
 *     removes an achievement unlock from a user. If your achievement
 *     tracks statistics that are NOT set with achievements_storage_get()
 *     or _set, you don't have to define the 'storage' key.
 *   - secret: (optional) The achievement displays on a user's Achievements
 *     tab but does not reveal its title, description, or points until the
 *     user has unlocked it. Compatible with 'invisible'.
 *   - invisible: (optional) The achievement does NOT display on a user's
 *     Achievements tab, but does show up on the leaderboards when necessary.
 *     Compatible with 'secret' (i.e., if another user has unlocked an
 *     invisible achievement, a user who has not unlocked it will see the
 *     placeholder secret text instead of the actual achievement itself).
 *
 *   Achievements can also be categorized into groups. Groups are simply
 *   arrays whose keys are internal group IDs and whose values identify
 *   the 'title' of the group as well as the array of 'achievements' that
 *   correspond to that group. If some achievements are within a group and
 *   some achievements are without a group, the groupless achievements will
 *   automatically be placed into a "Miscellany" category.
 */
function hook_achievements_info() {
  $achievements = array(
    'comment-count-50' => array(
      'title'       => t('Posted 50 comments!'),
      'description' => t("We no longer think you're a spam bot. Maybe."),
      'storage'     => 'comment-count',
      'points'      => 50,
    ),
    'comment-count-100' => array(
      'title'       => t('Posted 100 comments!'),
      'description' => t('But what about the children?!'),
      'storage'     => 'comment-count',
      'points'      => 100,
      'images' => array(
        'unlocked'  => 'sites/default/files/example1.png',
        // 'secret' and 'locked' will use the defaults.
      ),
    ),

    // An example of achievement groups: 'article-creation' is the group ID,
    // "Article creation" is the group title, and all relevant achievements are
    // placed in an 'achievements' array. The ungrouped comment achievements
    // above will be automatically pushed into a "Miscellany" group.
    'article-creation' => array(
      'title' => t('Article creation'),
      'achievements' => array(
        'node-mondays' => array(
          'title'       => t('Published some content on a Monday'),
          'description' => t("Go back to bed: it's still the weekend!"),
          'points'      => 5,
          'images' => array(
            'unlocked'  => 'sites/default/files/example1.png',
            'locked'    => 'sites/default/files/example2.png',
            'secret'    => 'sites/default/files/example3.png',
            // all default images have been replaced.
          ),
        ),
      ),
    ),
  );

  return $achievements;
}

/**
 * Implements hook_comment_insert().
 */
function example_comment_insert($comment) {
  // Most achievements measure some kind of statistical data that must be
  // aggregated over time. To ease the storage of this data, the achievement
  // module ships with achievement_storage_get() and _set(), which allow you
  // to store custom data on a per-user basis. In most cases, the storage
  // location is the same as your achievement ID but in situations where you
  // have progressive achievements (1, 2, 50 comments etc.), it's better to
  // share a single place like we do below. If you don't use the achievement
  // ID for the storage location, you must specify the new location in the
  // 'storage' key of hook_achievements_info().
  //
  // Here we're grabbing the number of comments that the current commenter has
  // left in the past (which might be 0), adding 1 (for the current insert),
  // and then saving the count back to the database. The saved data is
  // serialized so can be as simple or as complex as you need it to be.
  $current_count = achievements_storage_get('comment-count', $comment->uid) + 1;
  achievements_storage_set('comment-count', $current_count, $comment->uid);

  // Note that we're not checking if the user has previously earned any of the
  // commenting achievements yet. There are two reasons: first, we might want
  // to add another commenting achievement for, say, 250 comments, and if we
  // had stopped the storage counter above at 100, someone who currently has
  // 300 comments wouldn't unlock the achievement until they added another 150
  // nuggets of wisdom to the site. Generally speaking, if you need to store
  // incremental data for an achievement, you should continue to store it even
  // after the achievement has been unlocked - you never know if you'll want
  // to add a future milestone that will unlock on higher increments.
  //
  // Secondly, the achievements_unlocked() function below automatically checks
  // if the user has unlocked the achievement already, and will not reward it
  // again if they have. This saves you a small bit of repetitive coding but
  // you're welcome to use achievements_unlocked_already() as needed.
  //
  // Knowing that we currently have 50 and 100 comment achievements, we simply
  // loop through each milestone and check if the current count value matches.
  foreach (array(50, 100) as $count) {
    if ($current_count == $count) {
      achievements_unlocked('comment-count-' . $count, $comment->uid);
    }
  }
}

/**
 * Implements hook_node_insert().
 */
function example_node_insert($node) {
  // Sometimes, we don't need any storage at all.
  if (format_date(REQUEST_TIME, 'custom', 'D') == 'Mon') {
    achievements_unlocked('node-mondays', $node->uid);
  }
}

/**
 * Implements hook_achievements_info_alter().
 *
 * Modify achievements that have been defined in hook_achievements_info().
 * Note that achievement info is cached so if you add or modify this hook,
 * also clear said achievement cache in admin/config/people/achievements.
 *
 * @param &$achievements
 *   An array of defined achievements returned by hook_achievements_info().
 */
function example_achievements_info_alter(&$achievements) {
  $achievements['comment-count-100']['points'] = 200;
}

/**
 * Implements hook_achievements_unlocked().
 *
 * This hook is invoked after an achievement has been unlocked and all
 * the relevant information has been stored or updated in the database.
 *
 * @param $achievement
 *  An array of information about the achievement.
 * @param $uid
 *  The user ID who has unlocked the achievement.
 */
function example_achievements_unlocked($achievement, $uid) {
  // post to twitter or facebook, unlock an additional reward, etc., etc.
}

/**
 * Implements hook_achievements_locked().
 *
 * This hook is invoked after an achievement has been removed from a user and
 * all relevant information has been stored or updated in the database. This
 * is currently only possible from the UI at admin/config/people/achievements.
 *
 * @param $achievement
 *  An array of information about the achievement.
 * @param $uid
 *  The user ID who is having the achievement taken away.
 */
function example_achievements_locked($achievement, $uid) {
  // react to achievement removal. bad user, BaAaDdd UUserrRR!
}

/**
 * Implements hook_achievements_leaderboard_alter().
 *
 * Allows you to tweak or even recreate the leaderboard as required. The
 * default implementation creates leaderboards as HTML tables and this hook
 * allows you to modify that table (new columns, tweaked values, etc.) or
 * replace it entirely with a new render element.
 *
 * @param &$leaderboard
 *   An array of information about the leaderboard. Available keys are:
 *   - achievers: The database results from the leaderboard queries.
 *     Results are keyed by leaderboard type (top, relative, first, and
 *     recent) and then by user ID, sorted in proper ranking order.
 *   - block: A boolean indicating whether this is a block-based leaderboard.
 *   - type: The type of leaderboard being displayed. One of: top (the overall
 *     leaderboard displayed on achievements/leaderboard), relative (the
 *     current-user-centric version with nearby ranks), first (the first users
 *     who unlocked a particular achievement), and recent (the most recent
 *     users who unlocked a particular achievement).
 *   - render: A render array for use with drupal_render(). Default rendering
 *     is with #theme => table, and you'll receive all the keys necessary
 *     for that implementation. You're welcome to insert your own unique
 *     render, bypassing the default entirely.
 */
function example_achievements_leaderboard_alter(&$leaderboard) {
  if ($leaderboard['type'] == 'first') {
    $leaderboard['render']['#caption'] = t('Congratulations to our first 10!');
  }
}

/**
 * Implements hook_query_alter().
 *
 * The following database tags have been created for hook_query_alter() and
 * the matching hook_query_TAG_alter(). If you need more than this, don't
 * hesitate to create an issue asking for them.
 *
 * achievement_totals:
 *   Find the totals of all users in ranking order.
 *
 * achievement_totals_user:
 *   Find the totals of the passed user.
 *
 * achievement_totals_user_nearby:
 *   Find users nearby the ranking of the passed user.
 */
function example_query_alter(QueryAlterableInterface $query) {
  // futz with morbus' logic. insert explosions and singularities.
}

/**
 * Implements hook_achievements_access_earn().
 *
 * Allows you to programmatically determine if a user has access to earn
 * achievements. We do already have an "earn achievements" permission, but
 * this allows more complex methods of determining that privilege. For an
 * example, see the achievements_optout.module, which allows a user to opt-out
 * of earning achievements, even if you've already granted them permission to.
 *
 * @param $uid
 *   The user ID whose access is being questioned.
 *
 * @return
 *   TRUE if the $uid can earn achievements, FALSE if they can't,
 *   or NULL if there's no change to the user's default access.
 */
function example_achievements_access_earn($uid) {
  $account = user_load($uid);
  if ($account->name == 'Morbus Iff') {
    // always, mastah, alllwayyYAYsss.
    return TRUE;
  }
}
