<?php

/**
 * @file
 * Contains rules integration for the php module needed during evaluation.
 *
 * @addtogroup rules
 *
 * @{
 */

/**
 * A class implementing a rules input evaluator processing PHP.
 */
class RulesPHPEvaluator extends RulesDataInputEvaluator {

  /**
   * Overrides RulesDataProcessor::editAccess().
   */
  public function editAccess() {
    return parent::editAccess() && (user_access('use PHP for settings') || drupal_is_cli());
  }

  /**
   * Helper function to find variables in PHP code.
   *
   * @param string $text
   *   The PHP code.
   * @param array $var_info
   *   Array with variable names as keys.
   */
  public static function getUsedVars($text, $var_info) {
    if (strpos($text, '<?') !== FALSE) {
      $used_vars = array();
      foreach ($var_info as $name => $info) {
        if (strpos($text, '$' . $name) !== FALSE) {
          $used_vars[] = $name;
        }
      }
      return $used_vars;
    }
  }

  /**
   * Overrides RulesDataInputEvaluator::prepare().
   */
  public function prepare($text, $var_info) {
    // A returned NULL skips the evaluator.
    $this->setting = self::getUsedVars($text, $var_info);
  }

  /**
   * Evaluates PHP code contained in $text.
   *
   * This method doesn't apply $options, thus the PHP code is responsible for
   * behaving appropriately.
   */
  public function evaluate($text, $options, RulesState $state) {
    $vars['eval_options'] = $options;
    foreach ($this->setting as $key => $var_name) {
      $vars[$var_name] = $state->get($var_name);
    }
    return rules_php_eval($text, rules_unwrap_data($vars));
  }

  /**
   * Overrides RulesDataInputEvaluator::help().
   */
  public static function help($var_info) {
    module_load_include('inc', 'rules', 'rules/modules/php.rules');

    $render = array(
      '#type' => 'fieldset',
      '#title' => t('PHP Evaluation'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    ) + rules_php_evaluator_help($var_info);

    return $render;
  }

}

/**
 * A data processor using PHP.
 */
class RulesPHPDataProcessor extends RulesDataProcessor {

  /**
   * Overrides RulesDataProcessor::form().
   */
  protected static function form($settings, $var_info) {
    $settings += array('code' => '');
    $form = array(
      '#type' => 'fieldset',
      '#title' => t('PHP evaluation'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($settings['code']),
      '#description' => t('Enter PHP code to process the selected argument value.'),
    );
    $form['code'] = array(
      '#type' => 'textarea',
      '#title' => t('Code'),
      '#description' => t('Enter PHP code without &lt;?php ?&gt; delimiters that returns the processed value. The selected value is available in the variable $value. Example: %code', array('%code' => 'return $value + 1;')),
      '#default_value' => $settings['code'],
      '#weight' => 5,
    );
    return $form;
  }

  /**
   * Overrides RulesDataProcessor::editAccess().
   */
  public function editAccess() {
    return parent::editAccess() && (user_access('use PHP for settings') || drupal_is_cli());
  }

  /**
   * Overrides RulesDataProcessor::process().
   */
  public function process($value, $info, RulesState $state, RulesPlugin $element) {
    $value = isset($this->processor) ? $this->processor->process($value, $info, $state, $element) : $value;
    return rules_php_eval_return($this->setting['code'], array('value' => $value));
  }

}

/**
 * Action and condition callback: Execute PHP code.
 */
function rules_execute_php_eval($code, $settings, $state, $element) {
  $data = array();
  if (!empty($settings['used_vars'])) {
    foreach ($settings['used_vars'] as $key => $var_name) {
      $data[$var_name] = $state->get($var_name);
    }
  }
  return rules_php_eval_return($code, rules_unwrap_data($data));
}

/**
 * Evaluates the given PHP code, with the given variables defined.
 *
 * @param string $code
 *   The PHP code to run, including <?php and ?>
 * @param array $arguments
 *   Array containing variables to be extracted to the code.
 *
 * @return
 *   The output of the php code.
 */
function rules_php_eval($code, $arguments = array()) {
  extract($arguments);

  ob_start();
  print eval('?>' . $code);
  $output = ob_get_contents();
  ob_end_clean();

  return $output;
}

/**
 * Evaluates the given PHP code, with the given variables defined.
 *
 * This is like rules_php_eval(), but does return the returned data from
 * the PHP code.
 *
 * @param string $code
 *   The PHP code to run, without <?php or ?>
 * @param array $arguments
 *   Array containing variables to be extracted to the code.
 *
 * @return
 *   The return value of the evaled code.
 */
function rules_php_eval_return($code, $arguments = array()) {
  extract($arguments);
  return eval($code);
}

/**
 * @}
 */
