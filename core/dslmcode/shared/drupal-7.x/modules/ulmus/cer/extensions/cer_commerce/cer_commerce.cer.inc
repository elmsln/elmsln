<?php

/**
 * Implements hook_cer_fields().
 */
function cer_commerce_cer_fields() {
  module_load_include('inc', 'cer', 'cer.cer');
  return _cer_collect_fields_of_type('commerce_product_reference', 'CerCommerceProductReferenceField');
}
