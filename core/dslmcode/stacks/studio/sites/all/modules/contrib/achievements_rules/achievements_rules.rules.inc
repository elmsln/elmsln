<?php

/**
 * Implements hook_rules_data_info().
 */
function achievements_rules_rules_data_info() {
  return array(
    'achievements_achievement' => array(
      'label' => t('Achievement'),
      'group' => t('Achievements'),
      'wrap' => true,
      'property info' => achievements_rules_property_achievement_info(),
    ),
  );
}

function achievements_rules_property_achievement_info() {
    return array(
        'achievement_id' => array(
            'type' => 'text',
            'label' => t('Achievement ID'),
        ),
        'achievement_name' => array(
            'type' => 'text',
            'label' => t('Achievement Name'),
        ),
        'achievement_description' => array(
            'type' => 'text',
            'label' => t('Achievement Description'),
        ),
        'achievement_points' => array(
            'type' => 'integer',
            'label' => t('Achievement Points'),
        ),
    );
}

/**
 * Implements hook_rules_event_info().
 */
function achievements_rules_rules_event_info() {
    $events = array();

    $events['achievements_rules_unlocked'] = array(
        'label' => 'Any achievement was unlocked',
        'group' => t('Achievement Unlocked'), 
        'variables' => array(
            'achievement' => array(
                'type' => 'achievements_achievement',
                'label' => 'Unlocked Achievement',
            ),
            'achiever' => array(
                'type' => 'user',
                'label' => 'Achievement Recipent',
            ),
        ),
    );

    $events['achievements_rules_locked'] = array(
        'label' => 'Any achievement was locked',
        'group' => t('Achievement Locked'), 
        'variables' => array(
            'achievement' => array(
                'type' => 'achievements_achievement',
                'label' => 'Locked Achievement',
            ),
            'achiever' => array(
                'type' => 'user',
                'label' => 'Achievement Recipent',
            ),
        ),
    );

    $achievements = achievements_load();
    foreach ($achievements as $achievement) {
        $events['achievements_rules_' . $achievement['id'] . '_unlocked'] = array(
            'label' => (!empty($achievement['group_title']) ? $achievement['group_title'] . ' - ' : '') . $achievement['title'],
            'group' => t('Achievement Unlocked'), 
            'variables' => array(
                'achievement' => array(
                    'type' => 'achievements_achievement',
                    'label' => 'Unlocked Achievement',
                ),
                'achiever' => array(
                    'type' => 'user',
                    'label' => 'Achievement Recipent',
                ),
            ),
        );

        $events['achievements_rules_' . $achievement['id'] . '_locked'] = array(
            'label' => (!empty($achievement['group_title']) ? $achievement['group_title'] . ' - ' : '') . $achievement['title'],
            'group' => t('Achievement Locked'), 
            'variables' => array(
                'achievement' => array(
                    'type' => 'achievements_achievement',
                    'label' => 'Locked Achievement',
                ),
                'achiever' => array(
                    'type' => 'user',
                    'label' => 'Achievement Recipent',
                ),
            ),
        );
    }

    return $events;
}

/**
 * Implements hook_rules_action_info().
 */
function achievements_rules_rules_action_info() {
    return array(
        'achievements_rules_unlock' => array(
            'label' => t('Grant Achievement'),
            'group' => t('Achievements'),
            'base' => 'achievements_rules_action_unlock', 
            'parameter' => array(
                'achievement' => array(
                    'type' => 'text',
                    'label' => t('Achievement to unlock'),
                    'options list' => 'achievements_rules_achievements_options',
                    'restriction' => 'input',
                ),
                'achiever' => array(
                    'type' => 'user',
                    'label' => 'Achievement Recipient',
                ),
            ),
        ),
        'achievements_rules_lock' => array(
            'label' => t('Remove Achievement'),
            'group' => t('Achievements'),
            'base' => 'achievements_rules_action_lock', 
            'parameter' => array(
                'achievement' => array(
                    'type' => 'text',
                    'label' => t('Achievement to remove'),
                    'options list' => 'achievements_rules_achievements_options',
                    'restriction' => 'input',
                ),
                'achiever' => array(
                    'type' => 'user',
                    'label' => 'Achievement Recipient',
                ),
            ),
        ),
    );
}

function achievements_rules_achievements_options() {
    $options = array();
    foreach (achievements_load() as $achievement) {
        $options[$achievement['id']] = (!empty($achievement['group_title']) ? $achievement['group_title'] . ' - ' : '') . $achievement['title'];
    }
    return $options;
}

function achievements_rules_action_unlock($achievement, $account) {
    $achievement = check_plain($achievement);

    if ( strlen($achievement) > 0 ) {
        achievements_unlocked($achievement, $account->uid);
    }
}

function achievements_rules_action_lock($achievement, $account) {
    $achievement = check_plain($achievement);

    if ( strlen($achievement) > 0 ) {
        achievements_locked($achievement, $account->uid);
    }
}
