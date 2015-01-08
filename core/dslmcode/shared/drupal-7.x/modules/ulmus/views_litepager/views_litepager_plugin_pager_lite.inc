<?php
/**
 * @file
 * Extend Full Pager plugin to create Lite pager
 */

class views_litepager_plugin_pager_lite extends views_plugin_pager_full {
  function summary_title() {
    if (!empty($this->options['offset'])) {
      return format_plural($this->options['items_per_page'], 'Lite pager, @count item, skip @skip', 'Lite pager, @count items, skip @skip', array('@count' => $this->options['items_per_page'], '@skip' => $this->options['offset']));
    }
      return format_plural($this->options['items_per_page'], 'Lite pager, @count item', 'Lite pager, @count items', array('@count' => $this->options['items_per_page']));
  }

  function use_count_query() {
    return FALSE;
  }

  function query() {
    parent::query();

    $next_page = TRUE;
    if (!empty($this->options['total_pages'])) {
      if (($this->current_page + 1) >= $this->options['total_pages']) {
        $next_page = FALSE;
      }
    }
    if ($next_page) {
      $limit = $this->options['items_per_page'];
      $this->view->query->set_limit($limit + 1);
    }
  }

  function post_execute(&$result) {
    if (count($result) > $this->options['items_per_page']) {
      array_pop($result);
      $this->next_page = TRUE;
      global $pager_page_array, $pager_total, $pager_total_items;
      $pager_total[$this->options['id']] = $pager_page_array[$this->options['id']] + 1;
    }
  }

  function render($input) {
    global $pager_page_array, $pager_total, $pager_total_items;
    if (empty($pager_page_array[$this->options['id']]) && (!isset($this->next_page) || $this->next_page != TRUE)) {
      return "";
    }
    else {
      $pager_theme = views_theme_functions('pager_lite', $this->view, $this->display);

      $output = theme($pager_theme, array(
        'parameters' => $input, 'element' => $this->options['id']));
      return $output;
    }
  }
}
