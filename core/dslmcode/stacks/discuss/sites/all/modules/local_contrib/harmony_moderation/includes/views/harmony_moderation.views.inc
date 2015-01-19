<?php

/**
 * @file
 * Provide additional Views fields for entity content.
 */

/**
 * Implements hook_views_data_alter().
 *
 * We need to use this hook instead of hook_views_data() as
 * entity API already provides data for our custom entity type.
 */
 function harmony_moderation_views_data_alter(&$data) {
  // Quick view post content link.
  $data['harmony_post']['harmony_moderation_view_reports'] = array(
    'field' => array(
      'title' => t('Link to, or AJAX load the reports'),
      'help' => t('Provide a link to view the reports in a modal window if JavaScript is enabled.'),
      'handler' => 'harmony_moderation_views_handler_view_reports',
    ),
  );

  // Flagging view "other" reporting field.
  $data['flagging']['harmony_moderation_report_other_view'] = array(
    'field' => array(
      'title' => t('Link to, or AJAX load the "other" reason for reporting'),
      'help' => t('Provide a link to view any extra information that the user submitted relating to the reported post.'),
      'handler' => 'harmony_moderation_views_handler_report_other_view',
    ),
  );

  $data['flagging']['harmony_moderation_remove_report'] = array(
    'field' => array(
      'title' => t('Link to remove or AJAX remove a report.'),
      'help' => t('Note that this field will not work with any flag except the Harmony Moderation one.'),
      'handler' => 'harmony_moderation_views_handler_remove_report',
    ),
  );
}
