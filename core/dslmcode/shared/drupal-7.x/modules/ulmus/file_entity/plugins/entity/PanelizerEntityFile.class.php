<?php
/**
 * @file
 * Class for the Panelizer file entity plugin.
 */

/**
 * Panelizer Entity file plugin class.
 *
 * Handles file specific functionality for Panelizer.
 */
class PanelizerEntityFile extends PanelizerEntityDefault {
  public $entity_admin_root = 'admin/structure/file-types/manage/%';
  public $entity_admin_bundle = 4;
  public $views_table = 'file_managed';

  public function entity_access($op, $entity) {
    return file_entity_access($op, $entity);
  }

  /**
   * Implement the save function for the entity.
   */
  public function entity_save($entity) {
    file_save($entity);
  }

  /**
   * Implement the save function for the entity.
   */
  public function entity_allows_revisions($entity) {
    return array(FALSE, FALSE);

  }

  public function settings_form(&$form, &$form_state) {
    parent::settings_form($form, $form_state);

    $warn = FALSE;
    foreach ($this->plugin['bundles'] as $info) {
      if (!empty($info['status'])) {
        $warn = TRUE;
        break;
      }
    }

    if ($warn) {
      $task = page_manager_get_task('file_view');
      if (!empty($task['disabled'])) {
        drupal_set_message('The file template page is currently not enabled in page manager. You must enable this for Panelizer to be able to panelize files.', 'warning');
      }

      $handler = page_manager_load_task_handler($task, '', 'file_view_panelizer');
      if (!empty($handler->disabled)) {
        drupal_set_message('The panelizer variant on the file template page is currently not enabled in page manager. You must enable this for Panelizer to be able to panelize files.', 'warning');
      }
    }
  }

  public function entity_identifier($entity) {
    return t('This file');
  }

  public function entity_bundle_label() {
    return t('File type');
  }

  function get_default_display($bundle, $view_mode) {
    // For now we just go with the empty display.
    // @todo come up with a better default display.
    return parent::get_default_display($bundle, $view_mode);
  }

  /**
   * Implements a delegated hook_page_manager_handlers().
   *
   * This makes sure that all panelized entities have the proper entry
   * in page manager for rendering.
   */
  public function hook_default_page_manager_handlers(&$handlers) {
    page_manager_get_task('file_view');

    $handler = new stdClass;
    $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler->api_version = 1;
    $handler->name = 'file_view_panelizer';
    $handler->task = 'file_view';
    $handler->subtask = '';
    $handler->handler = 'panelizer_node';
    $handler->weight = -100;
    $handler->conf = array(
      'title' => t('File panelizer'),
      'context' => 'argument_entity_id:file_1',
      'access' => array(),
    );
    $handlers['file_view_panelizer'] = $handler;

    return $handlers;
  }

  /**
   * Implements a delegated hook_form_alter.
   *
   * We want to add Panelizer settings for the bundle to the file type form.
   */
  public function hook_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id == 'file_entity_file_type_form') {
      if (isset($form['#file_type'])) {
        $bundle = $form['#file_type']->type;
        $this->add_bundle_setting_form($form, $form_state, $bundle, array('machine_name'));
      }
    }
  }

  public function hook_page_alter(&$page) {

  }

  public function hook_views_plugins_alter(&$plugins) {

  }

}
