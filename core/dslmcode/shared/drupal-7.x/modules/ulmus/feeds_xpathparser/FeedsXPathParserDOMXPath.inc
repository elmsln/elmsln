<?php

/**
 * @file
 * Provides a custom version of DOMXPath for use with feeds_xpathparser.
 */
class FeedsXPathParserDOMXPath extends DOMXPath {
  protected $config = array();
  protected $modifiedQueries = array();

  public function __construct(DOMDocument $doc) {
    $this->namespaces = array();
    $simple = simplexml_import_dom($doc);
    // An empty DOMDocument will make $simple NULL.
    if ($simple !== NULL) {
      $this->namespaces = $simple->getNamespaces(TRUE);
    }
    $this->doc = $doc;
    parent::__construct($doc);
  }

  public function setConfig(array $config) {
    $this->config = $config;
  }

  protected function debug($data, $source) {
    $output = "$source : <ul>";
    if ($data instanceof DOMNodeList) {
      foreach ($data as $node) {
        $output .= '<li>' . check_plain($this->doc->saveXML($node)) . '</li>';
      }
    }
    else {
      $output .= '<li>' . check_plain($data) . '</li>';
    }
    $output .= '</ul>';
    drupal_set_message($output);
  }

  /**
   * Executes an XPath query with namespace support.
   *
   * @param $xpath
   *   The DOMXPath object.
   *
   * @param $query
   *   An XPath query.
   *
   * @return array
   *   An array containing the results of the query.
   */
  public function namespacedQuery($query, $context, $source) {
    $this->addDefaultNamespace($query);
    $results = $this->_query($query, $context);
    if (in_array($source, $this->config['debug'])) {
      $this->debug($results, $source);
    }

    if (is_object($this->error) && $this->config['errors']) {

      if ($this->error->level == LIBXML_ERR_ERROR) {
        drupal_set_message(
          t("There was an error during the XPath query: %query.<br />
            Libxml returned the message: %message, with the error code: %code.",
            array('%query'   => $query,
                  '%message' => trim($this->error->message),
                  '%code'    => $this->error->code)),
          'error',
          FALSE);
      }
      elseif ($this->error->level == LIBXML_ERR_WARNING) {
        drupal_set_message(
          t("There was an error during the XPath query: %query.<br />
            Libxml returned the message: %message, with the error code: %code.",
            array('%query'   => $query,
                  '%message' => trim($this->error->message),
                  '%code'    => $this->error->code)),
          'warning',
          FALSE);
      }
    }
    // Some versions of libxml return an empty array, some false on a query
    // that returns no results. We always return an array to make things
    // consistent.
    if ($results === FALSE) {
      return array();
    }
    return $results;
  }

  /**
   * Normalizes XPath queries, adding the default namespace.
   *
   * @param $query
   *   An XPath query string
   */
  protected function addDefaultNamespace(&$query) {
    foreach ($this->namespaces as $prefix => $namespace) {
      if ($prefix === '') {
        $this->registerNamespace('__default__', $namespace);

        // Replace all the elements without prefix by the default prefix.
        if (!isset($this->modifiedQueries[$query])) {
          $parser = new FeedsXPathParserQueryParser($query);
          $modQuery = $parser->getQuery();
          $this->modifiedQueries[$query] = $modQuery;
          $query = $modQuery;
        }
        else {
          $query = $this->modifiedQueries[$query];
        }
      }
      else {
        $this->registerNamespace($prefix, $namespace);
      }
    }
  }

  /**
   * Here we set libxml_use_internal_errors to TRUE because depending on the
   * libxml version, $xml->xpath() might return FALSE or an empty array() when
   * a query doesn't match.
   */
  protected function _query($query, $context = NULL) {
    $use_errors = libxml_use_internal_errors(TRUE);

    // Perfom XPath query.
    if ($context) {
      $results = $this->evaluate($query, $context);
    }
    else {
      $results = $this->query($query);
    }
    $this->error = libxml_get_last_error();
    libxml_clear_errors();
    libxml_use_internal_errors($use_errors);
    return $results;
  }
}
