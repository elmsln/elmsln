<?php

/**
 * @file
 * Display scheduled dates in 'countdown' format for use in Views.
 *
 * @see scheduler.views.inc
 */

/**
 * Field handler to display a countdown until a scheduled action.
 *
 * Defines class scheduler_handler_field_scheduler_countdown.
 *
 * @see http://www.ericschaefer.org/blog/2011/01/09/custom-field-handlers-for-views-2-drupal
 */
class scheduler_handler_field_scheduler_countdown extends views_handler_field {
  CONST SECOND_SCALE = 1;
  CONST MINUTE_SCALE = 60;
  CONST HOUR_SCALE = 3600;
  CONST DAY_SCALE = 86400;
  CONST WEEK_SCALE = 604800;

  /**
   * Add the timestamp_field into the SQL query.
   *
   * It is calculated as publish_on - REQUEST_TIME so the result is the number
   * of seconds from now until publishing. If publish_on is in the past then
   * NULL is returned.
   */
  function query() {
    $this->ensure_my_table();
    $this->node_table = $this->query->ensure_table('node', $this->relationship);
    $time_field = $this->definition['timestamp_field'];
    $this->field_alias = $this->query->add_field(NULL, 'CASE WHEN (' . $time_field . ' > ' . REQUEST_TIME . ') THEN (' . $time_field . ' - ' . REQUEST_TIME . ') ELSE NULL END', $this->table_alias . '_' . $this->field);
  }

  /**
   * Define our display options and provide defaults.
   *
   * @return array
   *   An associative array containing the options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['countdown_display'] = array('default' => 'smart');
    $options['units_display'] = array('default' => 'long');
    return $options;
  }

  /**
   * Defines the form for the user to select the display options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['countdown_display'] = array(
      '#title' => t('Display countdown as'),
      '#type' => 'radios',
      '#options' => array(
        'smart' => t('Smart mode'),
        'seconds' => t('Seconds'),
        'minutes' => t('Minutes'),
        'hours' => t('Hours'),
        'days' => t('Days'),
        'weeks' => t('Weeks'),
      ),
      '#default_value' => $this->options['countdown_display'],
    );
    $form['units_display'] = array(
      '#title' => t('Display time units'),
      '#type' => 'radios',
      '#options' => array(
        'long' => t('Long (for example 3 days)'),
        'short' => t('Short (for example 3d)'),
        'none' => t('No units at all'),
      ),
      '#default_value' => $this->options['units_display'],
    );
  }

  /**
   * Callback function to keep only the array scale values which are smaller
   * than the countdown value being displayed.
   */
  function scale_filter_callback($array_value) {
    return ($this->raw_value >= $array_value);
  }

  /**
   * Renders the countdown value in the units required.
   */
  function render($values) {
    $countdown_display = $this->options['countdown_display'];
    $this->raw_value = $values->{$this->field_alias};

    $scales = array(
      'weeks' => self::WEEK_SCALE,
      'days' => self::DAY_SCALE,
      'hours' => self::HOUR_SCALE,
      'minutes' => self::MINUTE_SCALE,
      'seconds' => self::SECOND_SCALE,
    );
    // If the field has been set to 'Smart', determine the right timescale.
    if ($countdown_display == 'smart') {
      $scales = array_filter($scales, array($this, 'scale_filter_callback'));
      $scale = empty($scales) ? self::SECOND_SCALE : reset($scales);
    }
    // Otherwise use the fixed display requested.
    else {
      $scale = $scales[$countdown_display];
    }

    // Get the display value by dividing the original value by the scale.
    $scaled_value = round($this->raw_value / $scale);

    switch ($scale) {
      case self::SECOND_SCALE:
        $long = format_plural($scaled_value, '1 second', '@count seconds', array('@count' => $scaled_value));
        $short = t('@counts', array('@count' => $scaled_value));
        break;

      case self::MINUTE_SCALE:
        $long = format_plural($scaled_value, '1 minute', '@count minutes', array('@count' => $scaled_value));
        $short = t('@countm', array('@count' => $scaled_value));
        break;

      case self::HOUR_SCALE:
        $long = format_plural($scaled_value, '1 hour', '@count hours', array('@count' => $scaled_value));
        $short = t('@counth', array('@count' => $scaled_value));
        break;

      case self::DAY_SCALE:
        $long = format_plural($scaled_value, '1 day', '@count days', array('@count' => $scaled_value));
        $short = t('@countd', array('@count' => $scaled_value));
        break;

      case self::WEEK_SCALE:
        $long = format_plural($scaled_value, '1 week', '@count weeks', array('@count' => $scaled_value));
        $short = t('@countw', array('@count' => $scaled_value));
        break;
    }

    switch ($this->options['units_display']) {
      case 'long':
        return $long;

      case 'short':
        return $short;

      default:
        return $scaled_value;
    }
  }

}
