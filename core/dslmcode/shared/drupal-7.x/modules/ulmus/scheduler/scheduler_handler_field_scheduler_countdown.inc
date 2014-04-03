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

  private $render_params = array(
    'seconds' => array(
      'scale' => self::SECOND_SCALE,
      'singular' => 'second',
      'plural' => 'seconds',
      'abbreviated' => 's',
    ),
    'minutes' => array(
      'scale' => self::MINUTE_SCALE,
      'singular' => 'minute',
      'plural' => 'minutes',
      'abbreviated' => 'min',
    ),
    'hours' => array(
      'scale' => self::HOUR_SCALE,
      'singular' => 'hour',
      'plural' => 'hours',
      'abbreviated' => 'h',
    ),
    'days' => array(
      'scale' => self::DAY_SCALE,
      'singular' => 'day',
      'plural' => 'days',
      'abbreviated' => 'd',
    ),
    'weeks' => array(
      'scale' => self::WEEK_SCALE,
      'singular' => 'week',
      'plural' => 'weeks',
      'abbreviated' => 'w',
    ),
  );

  /**
   * Add the new timestamp_field into the SQL query.
   *
   * It will be calculated as publish_on - unix_timestamp() so the result is
   * the number of seconds from now until the event.
   */
  function query() {
    $this->ensure_my_table();
    $this->node_table = $this->query->ensure_table('node', $this->relationship);
    $time_field = $this->definition['timestamp_field'];
    $this->field_alias = $this->query->add_field(NULL, 'IF(' . $time_field . ' AND ' . $time_field . ' > UNIX_TIMESTAMP(), ' . $time_field . ' - UNIX_TIMESTAMP(), NULL)', $this->table_alias . '_' . $this->field);
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
   * Renders the countdown value in the units required.
   */
  function render($values) {
    $countdown_display = $this->options['countdown_display'];
    $value = $values->{$this->field_alias};

    if ($countdown_display == 'smart') {
      if ($value > self::WEEK_SCALE) {
        $countdown_display = 'weeks';
      }
      elseif ($value > self::DAY_SCALE) {
        $countdown_display = 'days';
      }
      elseif ($value > self::HOUR_SCALE) {
        $countdown_display = 'hours';
      }
      elseif ($value > self::MINUTE_SCALE) {
        $countdown_display = 'minutes';
      }
      else {
        $countdown_display = 'seconds';
      }
    }
    $params = $this->render_params[$countdown_display];

    $scaled_value = round($value / $params['scale']);
    switch ($this->options['units_display']) {
      case 'long':
        $rendered_value = format_plural($scaled_value, '1 ' . $params['singular'], '@count ' . $params['plural']);
        break;

      case 'short':
        $rendered_value = $scaled_value . $params['abbreviated'];
        break;

      case 'none':
        $rendered_value = $scaled_value;
        break;
    }
    return $rendered_value;
  }

}
