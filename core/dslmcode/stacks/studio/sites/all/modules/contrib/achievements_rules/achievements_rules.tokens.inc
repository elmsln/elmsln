<?php

function achievements_rules_token_info() {
    $type = array(
        'name' => t('Achievement'),
        'description' => t('Tokens related to an achievement.'),
        'needs-data' => 'achievements_achievement',
    );

    $achievement['id'] = array(
        'name' => t("Achievement ID"),
        'description' => t("The achievement ID."),
    );
    $achievement['name'] = array(
        'name' => t("Achievement Name"),
        'description' => t("The achievement name."),
    );
    $achievement['description'] = array(
        'name' => t("Achievement Description"),
        'description' => t("The achievement description."),
    );
    $achievement['points'] = array(
        'name' => t("Achievement Points"),
        'description' => t("The amount of points for this achievement."),
    );

    return array(
        'types' => array('achievements_achievement' => $type),
        'tokens' => array('achievements_achievement' => $achievement),
    );
};

function achievements_rules_tokens($type, $tokens, array $data = array(), array $options = array()) {
    $replacements = array();

    if ($type == 'achievements_achievement' && !empty($data['achievements_achievement'])) {
        $achievement = $data['achievements_achievement'];
        foreach ($tokens as $name => $original) {
            switch ($name) {
                case 'id':
                    $replacements[$original] = !empty($achievement->id) ? $achievement->id : '';
                    break;
                case 'name':
                    $replacements[$original] = !empty($achievement->name) ? $achievement->name : '';
                    break;
                case 'description':
                    $replacements[$original] = !empty($achievement->description) ? $achievement->description : '';
                    break;
                case 'points':
                    $replacements[$original] = !empty($achievement->points) ? $achievement->points : '';
                    break;
            }
        }
    }

    return $replacements;
}
