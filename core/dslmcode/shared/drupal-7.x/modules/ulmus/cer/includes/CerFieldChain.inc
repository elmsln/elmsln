<?php

/**
 * @file
 *  Contains the CerFieldChain class.
 */

class CerFieldChain extends FieldChain {

  /**
   * Convenience method. Returns a handler for this chain in the context of
   * the given entity.
   *
   * @return CerFieldChainHandler
   */
  public function getHandler(EntityDrupalWrapper $entity) {
    return new CerFieldChainHandler($this, $entity);
  }

  /**
   * Gets a regular expression to match field chain identifiers that this chain
   * can reference, e.g. /^node:(page|article):/
   */
  public function regex() {
    $end = $this->end();
    return '/^' . $end->getTargetType() . ':(' . implode('|', $end->getTargetBundles()) . '):/';
  }

  /**
   * Returns a Features export pipe for this chain, including every field and
   * field instance in it.
   */  
  public function export() {
    $pipe = array();

    foreach ($this->chain as $field) {
      $pipe['field_instance'][] = "{$field->entityType}-{$field->bundle}-{$field->name}";
    }

    return $pipe;
  }

  /**
   * Returns an array of every possible field chain for every field defined in
   * hook_cer_fields().
   *
   * @return array
   */
  public static function collectAll() {
    $chains = array();

    foreach (array_keys(CerField::getPluginInfo()) as $identifier) {
      $chains = array_merge($chains, self::collect($identifier));
    }

    return $chains;
  }

  /**
   * Returns an array of every possible field chain for a single field,
   * identified by its key in hook_cer_fields().
   *
   * @return array
   */
  public static function collect($identifier) {
    $chains = array();

    $chain = new CerFieldChain();
    $chain->addField(CerField::getPlugin($identifier), $chains);

    return $chains;
  }

  /**
   * Constructs and returns a CerFieldChain object from an encoded string
   * of field plugin identifiers glued together with ::.
   *
   * @return CerFieldChain
   */
  public static function unpack($identifier) {
    $chain = new CerFieldChain();

    foreach (array_reverse(explode('::', $identifier)) as $field) {
      $chain->addField(CerField::getPlugin($field));
    }
    
    return $chain;
  }

} 
 