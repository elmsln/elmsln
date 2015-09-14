<?php

/**
 * @file
 * Hooks provided by Renderable elements module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Return the builds to register.
 */
function hook_rel_build_info() {
  $builds = array();
  $build_id = 'form_id';
  $rel_build = new stdClass;
  $rel_build->build_id = $build_id;
  $rel_build->api_version = 1;
  $rel_build->entity_type = 'node';
  $rel_build->bundle = 'bundle';
  $rel_build->view_mode = 'form';
  // Context can be form or display.
  $rel_build->context = 'form';
  $rel_build->path = 'admin/structure/types/manage/article/fields';
  $rel_build->elements = array(
    'actions' => t('Label'),
    'input' => t('Title'),
  );
  $builds[$build_id] = rel_build;

  return $builds;
}

/**
 * Act on all builds being registered, just before they are going to be cached.
 *
 * @param $builds
 *   A collection of all registered builds.
 */
function hook_rel_build_load_all_alter(&$builds) {
  foreach ($builds as $build_id => $build) {
    if ($build_id == 'this_id') {
      unset($builds[$build_id]);
    }
  }
}

/**
 * Act on a build when registering through the UI, just before saving.
 *
 * @param $build
 *   The build that's going to be saved registered.
 */
function hook_rel_build_register_alter($build) {
  if ($build->bundle == 'my_bundle') {
    if (isset($build->elements['key'])) {
      unset($build->elements['key']);
    }
  }
}

/**
 * Act on a build when registering through the UI, just after saving.
 *
 * @param $build
 *   The build that's being unregistered.
 */
function hook_rel_build_register($build) {
  if ($build->bundle == 'my_bundle') {
    // Do something fance here.
  }
}

/**
 * Act on a build when unregistering through the UI.
 *
 * @param $build
 *   The build that's being unregistered.
 */
function hook_rel_build_unregister($build) {
  $layout_id = $build->entity_type . '|' . $build->bundle . '|form';
  db_delete('ds_layout_settings')
    ->condition('id', $layout_id)
    ->execute();
}

/**
 * @} End of "addtogroup hooks".
 */