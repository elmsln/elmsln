<?php
/**
 * @file
 * cis_service_lti.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cis_service_lti_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_global_role_array';
  $strongarm->value = array(
    'Learner' => '7',
    'Instructor' => '4',
    'ContentDeveloper' => '6',
    'Member' => '2',
    'Manager' => '2',
    'Mentor' => '2',
    'Administrator' => '2',
    'TeachingAssistant' => '8',
  );
  $export['lti_tool_provider_global_role_array'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_og_provision_groups_anon';
  $strongarm->value = 1;
  $export['lti_tool_provider_og_provision_groups_anon'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_user_attribute_entity_type';
  $strongarm->value = 'profile2:main';
  $export['lti_tool_provider_user_attribute_entity_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_user_attribute_mapping';
  $strongarm->value = array(
    'lis_person_name_given' => 'none',
    'lis_person_name_family' => 'none',
    'lis_person_name_full' => 'none',
  );
  $export['lti_tool_provider_user_attribute_mapping'] = $strongarm;

  return $export;
}
