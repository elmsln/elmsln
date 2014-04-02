<?php

/**
 * @file
 * Export UI overwerites file.
 */

class ctools_export_ui_environment_indicator extends ctools_export_ui {
  /**
   * Render a header to go before the list.
   *
   * This will appear after the filter/sort widgets.
   */
  function list_header($form_state) {
    return theme('environment_indicator_overwritten_header');
  }
}
