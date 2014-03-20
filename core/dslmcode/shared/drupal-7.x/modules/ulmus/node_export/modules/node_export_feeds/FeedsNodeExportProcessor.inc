<?php

/**
 * @file
 * Class definition of FeedsNodeExportProcessor.
 */

/**
 * Creates nodes from feed items.
 */
class FeedsNodeExportProcessor extends FeedsNodeProcessor {
  public $new_nodes = array();

  /**
   * Process the result of the parsing stage.
   *
   * @param FeedsSource $source
   *   Source information about this import.
   * @param FeedsParserResult $parser_result
   *   The result of the parsing stage.
   */
  public function process(FeedsSource $source, FeedsParserResult $parser_result) {

    if (!($source->importer->parser instanceOf FeedsNodeExportParser)) {
      drupal_set_message(
        t('Node export processor must be used with Node export parser.  No nodes imported.'),
        'error',
        FALSE
      );
      return new FeedsParserResult(array());
    }

    parent::process($source, $parser_result);
  }

  /**
   * Creates a new node in memory and returns it.
   */
  /*

  @todo: Should we override this function?

  protected function newEntity(FeedsSource $source) {
    $node = new stdClass();
    $node->type = $this->config['content_type'];
    $node->changed = REQUEST_TIME;
    $node->created = REQUEST_TIME;
    $node->language = LANGUAGE_NONE;
    node_object_prepare($node);
    // Populate properties that are set by node_object_prepare().
    $node->log = 'Created by FeedsNodeProcessor';
    $node->uid = $this->config['author'];
    return $node;
  }
  */

  /**
   * Loads an existing node.
   *
   * If the update existing method is not FEEDS_UPDATE_EXISTING, only the node
   * table will be loaded, foregoing the node_load API for better performance.
   */
  /*

  @todo: Should we override this function?

  protected function entityLoad(FeedsSource $source, $nid) {
    if ($this->config['update_existing'] == FEEDS_UPDATE_EXISTING) {
      $node = node_load($nid, NULL, TRUE);
    }
    else {
      // We're replacing the existing node. Only save the absolutely necessary.
      $node = db_query("SELECT created, nid, vid, type FROM {node} WHERE nid = :nid", array(':nid' => $nid))->fetchObject();
      $node->uid = $this->config['author'];
    }
    node_object_prepare($node);
    // Populate properties that are set by node_object_prepare().
    if ($this->config['update_existing'] == FEEDS_UPDATE_EXISTING) {
      $node->log = 'Updated by FeedsNodeProcessor';
    }
    else {
      $node->log = 'Replaced by FeedsNodeProcessor';
    }
    return $node;
  }
  */

  /**
   * Save a node.
   *
   * This code is similar to some code in node_export_import()
   * which gets executed for each node when the $save param is TRUE.
   *
   * @todo: should we check to make sure FeedsNodeExportParser was used?
   */
  public function entitySave($entity) {
    $node = &$entity;
    node_export_save($node);
    $this->new_nodes[$node->nid] = $node;
    // @todo: Is this what we should do with output messages?
    drupal_set_message(t("Imported node !nid: !node", array('!nid' => $node->nid, '!node' => l($node->title, 'node/' . $node->nid))));
  }

}
