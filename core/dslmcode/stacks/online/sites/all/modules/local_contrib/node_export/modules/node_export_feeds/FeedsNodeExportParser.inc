<?php

/**
 * @file
 * Class definition of FeedsNodeExportParser.
 */

/**
 * Parses a given file as a node export file.
 */
class FeedsNodeExportParser extends FeedsParser {
  public $format = NULL;

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {

    if (!($source->importer->processor instanceOf FeedsNodeExportProcessor)) {
      drupal_set_message(
        t('Node export parser must be used with Node export processor.  No nodes imported.'),
        'error'
      );
      return new FeedsParserResult(array());
    }

    // Get the node export code.
    $code_string = $fetcher_result->getRaw();

    // @todo: Do we need this stuff?
    //$source_config = $source->getConfigFor($this);
    //$state = $source->state(FEEDS_PARSE);

    // Execute node_export_import() but don't have it save the nodes.
    $result = node_export_import($code_string, 't', FALSE);

    // Handle failure.
    if (!$result['success']) {
      foreach ($result['output'] as $error) {
        // @todo: Is this what we should do with output messages?
        drupal_set_message($error, 'error');
      }
      // @todo: Is this the right thing to return for a failure?
      return new FeedsParserResult(array());
    }


    foreach ($result['output'] as $status) {
      // @todo: Is this what we should do with output messages?
      drupal_set_message($status);
    }

    // Feeds needs the nodes to be arrays.
    // @todo: Should we try to get node_export_import() to return arrays in the
    // first place? Or perhaps have the processor accept objects?
    foreach ($result['nodes'] as $node) {
      $items[] = (array)$node;
    }

    // Store the format that was used.
    $this->format = $result['format'];

/*

    // Node export doesn't support batchy stuffs atm.


    // Determine section to parse, parse.
    $start = $state->pointer ? $state->pointer : $parser->lastLinePos();
    $limit = $source->importer->getLimit();
    $rows = $this->parseItems($parser, $iterator, $start, $limit);

    // Report progress.
    $state->total = filesize($fetcher_result->getFilePath());
    $state->pointer = $parser->lastLinePos();
    $progress = $parser->lastLinePos() ? $parser->lastLinePos() : $state->total;
    $state->progress($state->total, $progress);
*/

    // Create a result object and return it.
    return new FeedsParserResult($items);
  }

  /**
   * Override parent::getMappingSources().
   */
  public function getMappingSources() {
    return FALSE;
  }

  /**
   * Override parent::getSourceElement() to use only lower keys.
   */
  public function getSourceElement(FeedsSource $source, FeedsParserResult $result, $element_key) {
    return parent::getSourceElement($source, $result, drupal_strtolower($element_key));
  }

  /**
   * Define defaults.
   */
  public function sourceDefaults() {
    return array();
  }

  /**
   * Source form.
   *
   * Show mapping configuration as a guidance for import form users.
   */
  public function sourceForm($source_config) {
    $form = array();
    return $form;
  }

  /**
   * Define default configuration.
   */
  public function configDefaults() {
    return array();
  }

  /**
   * Build configuration form.
   */
  public function configForm(&$form_state) {
    $form = array();
    $form['info'] = array(
      '#prefix' => '<p>',
      '#markup' => t(
        'This parser uses settings from <a href="!config">node export</a>.',
        array('!config' => url('admin/config/content/node_export'))
      ),
      '#suffix' => '</p>',
    );
    return $form;
  }

  /**
   *
   */
  public function getTemplate() {
    return;
  }

}
