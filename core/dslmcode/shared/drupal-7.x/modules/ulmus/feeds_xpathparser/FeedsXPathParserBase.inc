<?php

/**
 * @file
 * Provides the base class for FeedsXPathParserHTML and FeedsXPathParserXML.
 */

/**
 * Base class for the HTML and XML parsers.
 */
abstract class FeedsXPathParserBase extends FeedsParser {

  protected $modified_queries = array();
  protected $rawXML = array();
  protected $doc = NULL;
  protected $xpath = NULL;

  /**
   * Classes that use FeedsXPathParserBase must implement this.
   *
   * @param array $source_config
   *   The configuration for the source.
   * @param FeedsFetcherResult $fetcher_result
   *   A FeedsFetcherResult object.
   *
   * @return DOMDocument
   *   The DOMDocument to perform XPath queries on.
   */
  abstract protected function setup($source_config, FeedsFetcherResult $fetcher_result);

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $source_config = $source->getConfigFor($this);

    if (empty($source_config)) {
      $source_config = $this->getConfig();
    }

    $this->doc = $this->setup($source_config, $fetcher_result);

    $parser_result = new FeedsParserResult();

    $mappings = $this->getOwnMappings();
    $this->rawXML = array_keys(array_filter($source_config['rawXML']));
    // Set link.
    $fetcher_config = $source->getConfigFor($source->importer->fetcher);
    $parser_result->link = $fetcher_config['source'];

    $this->xpath = new FeedsXPathParserDOMXPath($this->doc);
    $config = array();
    $config['debug'] = array_keys(array_filter($source_config['exp']['debug']));
    $config['errors'] = $source_config['exp']['errors'];

    $this->xpath->setConfig($config);
    $all_nodes = $this->xpath->namespacedQuery($source_config['context'], NULL, 'context');

    foreach ($all_nodes as $node) {
      $parsed_item = $variables = array();
      foreach ($source_config['sources'] as $source => $query) {
        // Variable substitution.
        $query = strtr($query, $variables);
        // Parse the item.
        $result = $this->parseSourceElement($query, $node, $source);
        if (isset($result)) {
          if (!is_array($result)) {
            $variables['$' . $mappings[$source]] = $result;
          }
          else {
            $variables['$' . $mappings[$source]] = '';
          }
          $parsed_item[$source] = $result;
        }
      }
      if (!empty($parsed_item)) {
        $parser_result->items[] = $parsed_item;
      }
    }
    unset($this->doc);
    unset($this->xpath);
    return $parser_result;
  }

  /**
   * Parses one item from the context array.
   *
   * @param $item
   *   A  SimpleXMLElement from the context array.
   *
   * @param $query
   *   An XPath query.
   *
   * @param $source
   *   The name of the source for this query.
   *
   * @return array
   *   An array containing the results of the query.
   */
  protected function parseSourceElement($query, $context, $source) {

    if (empty($query)) {
      return;
    }

    $node_list = $this->xpath->namespacedQuery($query, $context, $source);
    /**
     * Iterate through the results of the XPath query.  If this source is
     * configured to return raw xml, make it so.
     */
    if ($node_list instanceof DOMNodeList) {
      $results = array();
      if (in_array($source, $this->rawXML)) {
        foreach ($node_list as $node) {
          $results[] = $this->doc->savexML($node);
        }
      }
      else {
        foreach ($node_list as $node) {
          $results[] = $node->nodeValue;
        }
      }
      // Return single result if so.
      if (count($results) === 1) {
        return $results[0];
      }
      // Empty result returns NULL, that way we can check.
      elseif (empty($results)) {
        return;
      }
      else {
        return $results;
      }
    }
    // A value was returned directly.
    elseif (!empty($node_list)) {
      return $node_list;
    }
  }

  /**
   * Source form.
   */
  public function sourceForm($source_config) {
    $form = array();
    $importer = feeds_importer($this->id);
    $importer_config = $importer->getConfig();
    $mappings_ = $importer_config['processor']['config']['mappings'];

    if (empty($source_config)) {
      $source_config = $this->getConfig();
    }

    if (isset($source_config['allow_override']) &&
        !$source_config['allow_override'] &&
        empty($source_config['config'])) {
      return;
    }

    // Add extensions that might get importerd.
    $allowed_extensions = isset($importer_config['fetcher']['config']['allowed_extensions']) ? $importer_config['fetcher']['config']['allowed_extensions'] : FALSE;
    if ($allowed_extensions) {
      if (strpos($allowed_extensions, 'html') === FALSE) {
        $importer->fetcher->config['allowed_extensions'] .= ' html htm';
      }
    }

    $uniques = $mappings = array();
    foreach ($mappings_ as $mapping) {
      if (strpos($mapping['source'], 'xpathparser:') === 0) {
        $mappings[$mapping['source']] = $mapping['target'];
        if ($mapping['unique']) {
          $uniques[] = $mapping['target'];
        }
      }
    }
    $form['xpath'] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => t('XPath Parser Settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    if (empty($mappings)) {
      // Detect if Feeds menu structure has changed. This will take a while to be
      // released, but since I run dev it needs to work.
      $feeds_menu = feeds_ui_menu();
      if (isset($feeds_menu['admin/structure/feeds/list'])) {
        $feeds_base = 'admin/structure/feeds/edit/';
      }
      else {
        $feeds_base = 'admin/structure/feeds/';
      }
      $form['xpath']['error_message']['#markup'] = '<div class="help">' . t('No XPath mappings are defined. Define mappings !link.', array('!link' => l(t('here'), $feeds_base . $this->id . '/mapping'))) . '</div><br />';
      return $form;
    }
    $form['xpath']['context'] = array(
      '#type' => 'textfield',
      '#title' => t('Context'),
      '#required' => TRUE,
      '#description' => t('This is the base query, all other queries will run in this context.'),
      '#default_value' => isset($source_config['context']) ? $source_config['context'] : '',
      '#maxlength' => 1024,
      '#size' => 80,
    );
    $form['xpath']['sources'] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
    );
    if (!empty($uniques)) {
      $items = array(
        format_plural(count($uniques),
          t('Field <strong>!column</strong> is mandatory and considered unique: only one item per !column value will be created.',
            array('!column' => implode(', ', $uniques))),
          t('Fields <strong>!columns</strong> are mandatory and values in these columns are considered unique: only one entry per value in one of these columns will be created.',
            array('!columns' => implode(', ', $uniques)))),
      );
      $form['xpath']['sources']['help']['#markup'] = '<div class="help">' . theme('item_list', array('items' => $items)) . '</div>';
    }
    $variables = array();
    foreach ($mappings as $source => $target) {
      $form['xpath']['sources'][$source] = array(
        '#type' => 'textfield',
        '#title' => check_plain($target),
        '#description' => t('The XPath query to run.'),
        '#default_value' => isset($source_config['sources'][$source]) ? $source_config['sources'][$source] : '',
        '#maxlength' => 1024,
        '#size' => 80,
      );
      if (!empty($variables)) {
        $variable_text = format_plural(count($variables),
          t('The variable ' . implode(', ', $variables) . ' is availliable for replacement.'),
          t('The variables ' . implode(', ', $variables) . ' are availliable for replacement.')
        );
        $form['xpath']['sources'][$source]['#description'] .= '<br />' . $variable_text;
      }
      $variables[] = '$' . $target;
    }
    $form['xpath']['rawXML'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Select the queries you would like to return raw XML or HTML'),
      '#options' => $mappings,
      '#default_value' => isset($source_config['rawXML']) ? $source_config['rawXML'] : array(),
    );
    $form['xpath']['exp'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => TRUE,
      '#title' => t('Debug Options'),
    );
    $form['xpath']['exp']['errors'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show error messages.'),
      '#default_value' => isset($source_config['exp']['errors']) ? $source_config['exp']['errors'] : FALSE,
    );
    if (extension_loaded('tidy')) {
      $form['xpath']['exp']['tidy'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use Tidy'),
        '#description' => t('The Tidy PHP extension has been detected.
                              Select this to clean the markup before parsing.'),
        '#default_value' => isset($source_config['exp']['tidy']) ? $source_config['exp']['tidy'] : FALSE,
      );
      $form['xpath']['exp']['tidy_encoding'] = array(
        '#type' => 'textfield',
        '#title' => t('Tidy encoding'),
        '#description' => t('Set the encoding for tidy. See the !phpdocs for possible values.', array('!phpdocs' => l(t('PHP docs'), 'http://www.php.net/manual/en/tidy.parsestring.php/'))),
        '#default_value' => isset($source_config['exp']['tidy_encoding']) ? $source_config['exp']['tidy_encoding'] : 'UTF8',
        '#states' => array(
          'visible' => array(
            ':input[name$="[tidy]"]' => array(
              'checked' => TRUE,
            ),
          ),
        ),
      );
    }
    $form['xpath']['exp']['debug'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Debug query'),
      '#options' => array_merge(array('context' => 'context'), $mappings),
      '#default_value' => isset($source_config['exp']['debug']) ? $source_config['exp']['debug'] : array(),
    );
    return $form;
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $config = $this->getConfig();
    $config['config'] = TRUE;
    $form = $this->sourceForm($config);
    $form['xpath']['context']['#required'] = FALSE;
    $form['xpath']['#collapsed'] = FALSE;
    $form['xpath']['allow_override'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow source configuration override'),
      '#description' => t('This setting allows feed nodes to specify their own XPath values for the context and sources.'),
      '#default_value' => $config['allow_override'],
    );
    return $form;
  }

  /**
   * Define defaults.
   */
  public function sourceDefaults() {
    return array();
  }

  /**
   * Define defaults.
   */
  public function configDefaults() {
    return array(
      'sources' => array(),
      'rawXML' => array(),
      'context' => '',
      'exp' => array(
        'errors' => FALSE,
        'tidy' => FALSE,
        'debug' => array(),
        'tidy_encoding' => 'UTF8',
      ),
      'allow_override' => TRUE,
    );
  }

  /**
   * Override parent::sourceFormValidate().
   *
   * If the values of this source are the same as the base config we set them to
   * blank to that the values will be inherited from the importer defaults.
   *
   * @param &$values
   *   The values from the form to validate, passed by reference.
   */
  public function sourceFormValidate(&$values) {
    $config = $this->getConfig();
    $values = $values['xpath'];
    $allow_override = $config['allow_override'];
    unset($config['allow_override']);
    ksort($values);
    ksort($config);
    if ($values === $config || !$allow_override) {
      $values = array();
      return;
    }

    $this->configFormValidate($values);
  }

  /**
   * Override parent::sourceFormValidate().
   */
  public function configFormValidate(&$values) {
    $mappings = $this->getOwnMappings();

    // This tests if we're validating configForm or sourceForm.
    $config_form = FALSE;
    if (isset($values['xpath'])) {
      $values = $values['xpath'];
      $config_form = TRUE;
    }
    $class = get_class($this);
    $xml = new SimpleXMLElement('<?xml version="1.0" encoding="UTF-8"?>' . "\n<items></items>");
    $use_errors = libxml_use_internal_errors(TRUE);

    $values['context'] = trim($values['context']);
    if (!empty($values['context'])) {
      $result = $xml->xpath($values['context']);
    }
    $error = libxml_get_last_error();

    // Error code 1219 is undefined namespace prefix.
    // Our sample doc doesn't have any namespaces let alone the one they're
    // trying to use. Besides, if someone is trying to use a namespace in an
    // XPath query, they're probably right.
    if ($error && $error->code != 1219) {
      $element = 'feeds][' . $class . '][xpath][context';
      if ($config_form) {
        $element = 'xpath][context';
      }
      form_set_error($element, t('There was an error with the XPath selector: %error', array('%error' => $error->message)));
      libxml_clear_errors();
    }
    foreach ($values['sources'] as $key => &$query) {
      $query = trim($query);
      if (!empty($query)) {
        $result = $xml->xpath($query);
        $error = libxml_get_last_error();
        if ($error && $error->code != 1219) {
          $variable_present = FALSE;
          // Our variable substitution options can cause syntax errors, check
          // if we're doing that.
          if ($error->code == 1207) {
            foreach ($mappings as $target) {
              if (strpos($query, '$' . $target) !== FALSE) {
                $variable_present = TRUE;
              }
            }
          }
          if (!$variable_present) {
            $element = 'feeds][' . $class . '][xpath][sources][' . $key;
            if ($config_form) {
              $element = 'xpath][sources][' . $key;
            }
            form_set_error($element, t('There was an error with the XPath selector: %error', array('%error' => $error->message)));
            libxml_clear_errors();
          }
        }
      }
    }
    libxml_use_internal_errors($use_errors);
  }

  /**
  * Override parent::getMappingSources().
  */
  public function getMappingSources() {
    $mappings = $this->filterMappings(feeds_importer($this->id)->processor->config['mappings']);
    $next = 0;
    if (!empty($mappings)) {
      $keys = array_keys($mappings);
      $last_mapping = end($keys);
      $next = explode(':', $last_mapping);
      $next = $next[1] + 1;
    }
    return array(
      'xpathparser:' . $next => array(
        'name' => t('XPath Expression'),
        'description' => t('Allows you to configure an XPath expression that will populate this field.'),
      ),
    ) + parent::getMappingSources();
  }

  /**
   * Get the mappings that belong to us i.e. mappings that begin with
   * "xpathparser:".
   *
   * @return array
   *   An array of mappings keyed source => target.
   */
  protected function getOwnMappings() {
    $importer_config = feeds_importer($this->id)->getConfig();
    return $this->filterMappings($importer_config['processor']['config']['mappings']);
  }

  /**
   * Filters mappings, returning the ones that belong to us.
   *
   * @param array $mappings
   *   A mapping array from a processor.
   *
   * @return array
   *   An array of mappings keyed source => target.
   */
  protected function filterMappings($mappings) {
    $our_mappings = array();
    foreach ($mappings as $mapping) {
      if (strpos($mapping['source'], 'xpathparser:') === 0) {
        $our_mappings[$mapping['source']] = $mapping['target'];
      }
    }
    return $our_mappings;
  }

  /**
   * Start custom error handling.
   *
   * @return bool
   *   The previous value of use_errors.
   */
  protected function errorStart() {
    return libxml_use_internal_errors(TRUE);
  }

  /**
   * Stop custom error handling.
   *
   * @param bool $use
   *   The previous value of use_errors.
   * @param bool $print
   *   (Optional) Whether to print errors to the screen. Defaults to TRUE.
   */
  protected function errorStop($use, $print = TRUE) {
    if ($print) {
      foreach (libxml_get_errors() as $error) {
        switch ($error->level) {
          case LIBXML_ERR_WARNING:
          case LIBXML_ERR_ERROR:
            $type = 'warning';
            break;
          case LIBXML_ERR_FATAL:
            $type = 'error';
            break;

        }
        $message = t('%error on line %num. Error code: %code', array('%error' => trim($error->message), '%num' => $error->line, '%code' => $error->code));
        drupal_set_message($message, $type, FALSE);
      }
    }
    libxml_clear_errors();
    libxml_use_internal_errors($use);
  }
}
