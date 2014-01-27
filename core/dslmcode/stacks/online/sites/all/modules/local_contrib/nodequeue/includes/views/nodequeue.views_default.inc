<?php

/**
 * @file
 * Default views for nodequeue. This modifies an exported view; it might
 * actually work better to create the view dynamically. It would be less
 * code and more modifiable later.
 */
function nodequeue_views_default_views() {
  $views = array();
  if (variable_get('nodequeue_view_per_queue', 1) != 1) {
    return $views;
  }

  $queues = nodequeue_load_queues(nodequeue_get_all_qids());
  foreach ($queues as $queue) {
    $view = new view;
    $view->name = "nodequeue_$queue->qid";
    $view->description = t("Display a list of all nodes in queue '@queue'", array('@queue' => $queue->title));
    $view->tag = t('nodequeue');
    $view->view_php = '';
    $view->base_table = 'node';
    $view->is_cacheable = '0';
    $view->api_version = 2;
    $view->disabled = FALSE; // Edit this to true to make a default view disabled initially
    $view->display = array();
    $display = new views_display;
    $display->id = 'default';
    $display->display_title = t('Defaults');
    $display->display_plugin = 'default';
    $display->position = '1';
    $display->display_options = array(
      'style_plugin' => 'default',
      'style_options' => array(),
      'row_plugin' => 'node',
      'row_options' => array(
        'teaser' => 1,
        'links' => 1,
      ),
      'relationships' => array(
        'nodequeue_rel' => array(
          'id' => 'nodequeue_rel',
          'table' => 'node',
          'field' => 'nodequeue_rel',
          'label' => 'queue',
          'required' => 1,
          'limit' => TRUE,
          'qids' => array($queue->qid => $queue->qid),
          'relationship' => 'none',
        ),
      ),
      'fields' => array(
        'title' => array(
          'id' => 'title',
          'table' => 'node',
          'field' => 'title',
          'label' => '',
          'relationship' => 'none',
          'link_to_node' => 1,
        ),
      ),
      'sorts' => array(
        'position' => array(
          'id' => 'position',
          'table' => 'nodequeue_nodes',
          'field' => 'position',
          'order' => 'ASC',
          'relationship' => 'nodequeue_rel',
        ),
      ),
      'arguments' => array(),
      'filters' => array(
        'status_extra' => array(
          'id' => 'status_extra',
          'table' => 'node',
          'field' => 'status_extra',
          'operator' => '=',
          'value' => '',
          'group' => 0,
          'exposed' => FALSE,
          'expose' => array(
            'operator' => FALSE,
            'label' => '',
          ),
          'relationship' => 'none',
        ),
      ),
      'items_per_page' => 10,
      'use_pager' => '1',
      'pager_element' => 0,
      'title' => t("Queue '@queue'", array('@queue' => $queue->title)),
      'use_more' => 1,
    );
    $view->display['default'] = $display;
    $display = new views_display;
    $display->id = 'page';
    $display->display_title = t('Page');
    $display->display_plugin = 'page';
    $display->position = '2';
    $display->display_options = array(
      'defaults' => array(
        'access' => TRUE,
        'title' => TRUE,
        'header' => TRUE,
        'header_format' => TRUE,
        'header_empty' => TRUE,
        'footer' => TRUE,
        'footer_format' => TRUE,
        'footer_empty' => TRUE,
        'empty' => TRUE,
        'empty_format' => TRUE,
        'use_ajax' => TRUE,
        'items_per_page' => TRUE,
        'offset' => TRUE,
        'use_pager' => TRUE,
        'pager_element' => TRUE,
        'use_more' => TRUE,
        'distinct' => TRUE,
        'link_display' => TRUE,
        'style_plugin' => TRUE,
        'style_options' => TRUE,
        'row_plugin' => TRUE,
        'row_options' => TRUE,
        'relationships' => TRUE,
        'fields' => TRUE,
        'sorts' => TRUE,
        'arguments' => TRUE,
        'filters' => TRUE,
      ),
      'relationships' => array(),
      'fields' => array(),
      'sorts' => array(),
      'arguments' => array(),
      'filters' => array(),
      'path' => "nodequeue/$queue->qid",
    );
    $view->display['page'] = $display;
    $display = new views_display;
    $display->id = 'block';
    $display->display_title = t('Block');
    $display->display_plugin = 'block';
    $display->position = '3';
    $display->display_options = array(
      'defaults' => array(
        'access' => TRUE,
        'title' => TRUE,
        'header' => TRUE,
        'header_format' => TRUE,
        'header_empty' => TRUE,
        'footer' => TRUE,
        'footer_format' => TRUE,
        'footer_empty' => TRUE,
        'empty' => TRUE,
        'empty_format' => TRUE,
        'use_ajax' => TRUE,
        'items_per_page' => FALSE,
        'offset' => FALSE,
        'use_pager' => FALSE,
        'pager_element' => FALSE,
        'use_more' => TRUE,
        'distinct' => TRUE,
        'link_display' => TRUE,
        'style_plugin' => FALSE,
        'style_options' => FALSE,
        'row_plugin' => FALSE,
        'row_options' => FALSE,
        'relationships' => TRUE,
        'fields' => TRUE,
        'sorts' => TRUE,
        'arguments' => TRUE,
        'filters' => TRUE,
      ),
      'relationships' => array(),
      'fields' => array(),
      'sorts' => array(),
      'arguments' => array(),
      'filters' => array(),
      'style_plugin' => 'list',
      'style_options' => array(
        'type' => 'ul',
      ),
      'row_plugin' => 'fields',
      'row_options' => array(
        'inline' => array(),
        'separator' => '',
      ),
      'block_description' => t("Queue '@queue'", array('@queue' => $queue->title)),
      'items_per_page' => 5,
      'offset' => 0,
      'use_pager' => '0',
      'pager_element' => 0,
    );
    $view->display['block'] = $display;
    $views[$view->name] = $view;
  }
  return $views;
}
