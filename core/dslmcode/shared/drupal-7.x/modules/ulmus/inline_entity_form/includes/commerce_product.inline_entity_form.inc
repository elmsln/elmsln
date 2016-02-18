<?php

/**
 * @file
 * Defines the inline entity form controller for Commerce Products.
 */

class CommerceProductInlineEntityFormController extends EntityInlineEntityFormController {

  public function __construct($entityType, array $settings) {
    $this->entityType = $entityType;
    $this->settings = $settings + $this->defaultSettings();

    // Convert the old product-specific variation language setting.
    if (!empty($settings['use_variation_language']) && empty($settings['override_labels'])) {
      $this->settings['override_labels'] = TRUE;
      $this->settings['label_singular'] = 'variation';
      $this->settings['label_plural'] = 'variations';
      unset($this->settings['use_variation_language']);
    }
  }

  /**
   * Overrides EntityInlineEntityFormController::css().
   */
  public function css() {
    return array(
      'base' => drupal_get_path('module', 'inline_entity_form') . '/theme/commerce-product.css',
    );
  }

  /**
   * Overrides EntityInlineEntityFormController::tableFields().
   */
  public function tableFields($bundles) {
    $fields = array();
    $fields['title'] = array(
      'type' => 'property',
      'label' => t('Variation title'),
      'weight' => 1,
    );
    $fields['sku'] = array(
      'type' => 'property',
      'label' => t('SKU'),
      'weight' => 2,
    );

    // If only one product type is allowed, its fields can be used as columns.
    if (count($bundles) == 1) {
      $bundle = reset($bundles);

      foreach (field_info_instances('commerce_product', $bundle) as $field_name => $instance) {
        $field = field_info_field($field_name);

        // If the product has an imagefield, show it.
        if ($field['type'] == 'image') {
          // Determine the correct image style to use.
          $image_style = 'thumbnail';
          if (!empty($instance['widget']['settings']['preview_image_style'])) {
            $image_style = $instance['widget']['settings']['preview_image_style'];
          }

          $fields[$field_name] = array(
            'type' => 'field',
            'label' => $instance['label'],
            'formatter' => 'image',
            'settings' => array('image_style' => $image_style),
            'delta' => 0,
            'weight' => -10,
          );
          // Don't add any other imagefields. One is enough.
          break;
        }
      }

      // If the type has up to 3 attributes, show them instead of the title field.
      $attributes = $this->attributes($bundle);
      if (count($attributes) <= 3) {
        $fields['title']['visible'] = FALSE;

        foreach ($attributes as $field_name => $attribute) {
          $field_type = field_info_field_types($attribute['field']['type']);
          // Override the default formatter for taxonomy_term_reference.
          if ($field_type['default_formatter'] == 'taxonomy_term_reference_link') {
            $field_type['default_formatter'] = 'taxonomy_term_reference_plain';
          }

          $weight = -3;
          $fields[$field_name] = array(
            'type' => 'field',
            'label' => $attribute['instance']['label'],
            'formatter' => $field_type['default_formatter'],
            'weight' => ++$weight,
          );
        }
      }
    }

    $fields['commerce_price'] = array(
      'type' => 'field',
      'label' => t('Price'),
      'formatter' => 'commerce_price_formatted_amount',
      'weight' => 99,
    );
    $fields['status'] = array(
      'type' => 'property',
      'label' => t('Status'),
      'weight' => 100,
    );

    return $fields;
  }

  /**
   * Overrides EntityInlineEntityFormController::defaultSettings().
   */
  public function defaultSettings() {
    $defaults = parent::defaultSettings();
    $defaults['autogenerate_title'] = FALSE;

    return $defaults;
  }

  /**
   * Overrides EntityInlineEntityFormController::settingsForm().
   */
  public function settingsForm($field, $instance) {
    $form = parent::settingsForm($field, $instance);

    $form['autogenerate_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Auto generate the product title'),
      '#description' => t('This will hide the title input field and generate the title by appending any available attributes to the @entity title.', array('@entity' => $instance['entity_type'])),
      '#default_value' => $this->settings['autogenerate_title'],
    );

    return $form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    global $user;

    // Get the labels (product / variation).
    $labels = $this->labels();

    $product = $entity_form['#entity'];
    $extra_fields = field_info_extra_fields('commerce_product', $product->type, 'form');
    // Assign newly created products to the current user.
    if (empty($product->product_id)) {
      $product->uid = $user->uid;
    }

    $entity_form['product_attributes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Attributes'),
      '#attributes' => array('class' => array('container-inline', 'ief-product-attributes', 'ief-entity-fieldset')),
    );
    $entity_form['product_details'] = array(
      '#type' => 'fieldset',
      '#title' => t('Details'),
      '#attributes' => array('class' => array('ief-product-details', 'ief-entity-fieldset')),
    );

    $entity_form['sku'] = array(
      '#type' => 'textfield',
      '#title' => t('SKU'),
      '#description' => t('Supply a unique identifier using letters, numbers, hyphens, and underscores. Commas may not be used.'),
      '#default_value' => $product->sku,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#fieldset' => 'product_details',
      '#weight' => $extra_fields['sku']['weight'],
    );
    $entity_form['title'] = array(
      '#type' => 'textfield',
      '#title' => t('@label title', array('@label' => drupal_ucfirst($labels['singular']))),
      '#default_value' => $product->title,
      '#maxlength' => 255,
      '#required' => TRUE,
      '#fieldset' => 'product_details',
      // The label might be missing if the Title module has replaced it.
      '#weight' => !empty($extra_fields['title']) ? $extra_fields['title']['weight'] : -9,
    );
    $entity_form['status'] = array(
      '#type' => 'radios',
      '#title' => t('Status'),
      '#default_value' => $product->status,
      '#options' => array(1 => t('Active'), 0 => t('Disabled')),
      '#required' => TRUE,
      '#fieldset' => 'product_details',
      '#weight' => $extra_fields['status']['weight'],
    );

    // Attach fields.
    $langcode = entity_language('commerce_product', $product);
    field_attach_form('commerce_product', $product, $entity_form, $form_state, $langcode);

    // Hide or disable the SKU field if it is auto-generated by Commerce AutoSKU.
    if (module_exists('commerce_autosku') && $settings = commerce_autosku_get_settings($product)) {
      $entity_form['sku']['#required'] = FALSE;
      $entity_form['sku']['#disabled'] = TRUE;
      if ($settings['advanced']['hide_sku']) {
        $entity_form['sku']['#access'] = FALSE;
      }
      else {
        $entity_form['sku']['#description'] = t('Will be auto-generated when the form is saved.');
      }
    }
    // Hide the title field if it is auto-generated.
    if ($this->settings['autogenerate_title']) {
      $entity_form['title']['#required'] = FALSE;
      $entity_form['title']['#access'] = FALSE;
      // Hide the replacement field added by the Title module as well.
      if (module_exists('title')) {
        $title_field = title_field_replacement_info('commerce_product', 'title');
        if ($title_field) {
          $title_field_name = $title_field['field']['field_name'];
          if (isset($entity_form[$title_field_name])) {
            $entity_form[$title_field_name]['#access'] = FALSE;
            $entity_form[$title_field_name]['#required'] = FALSE;
          }
        }
      }
    }

    // Arrange attributes.
    $attributes = $this->attributes($product->type);
    if (empty($attributes)) {
      // Hide the fieldset, it will be empty.
      $entity_form['product_attributes']['#access'] = FALSE;
    }
    else {
      foreach ($attributes as $field_name => $attribute) {
        $entity_form[$field_name]['#fieldset'] = 'product_attributes';
      }
    }

    // Arrange non-attribute fields.
    foreach (field_info_instances('commerce_product', $product->type) as $name => $instance) {
      $field_name = $instance['field_name'];
      $field = field_info_field($field_name);
      if (!isset($attributes[$field_name])) {
        $entity_form[$field_name]['#fieldset'] = 'product_details';
      }
    }

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormValidate().
   */
  public function entityFormValidate($entity_form, &$form_state) {
    $product = $entity_form['#entity'];

    $parents_path = implode('][', $entity_form['#parents']);
    $product_values = drupal_array_get_nested_value($form_state['values'], $entity_form['#parents']);
    $sku = trim($product_values['sku']);

    // If the SKU field is enabled, validate it.
    if (empty($entity_form['sku']['#disabled'])) {
      // Ensure the proposed SKU is unique.
      if (!commerce_product_validate_sku_unique($sku, $product->product_id)) {
        form_set_error($parents_path . '][sku', t('This SKU is already in use and must be unique. Please supply another value.'));
      }
      // Validate the SKU for invalid characters.
      if (!commerce_product_validate_sku($sku)) {
        form_set_error($parents_path . '][sku', t('The SKU %sku contains invalid characters.', array('%sku' => $sku)));
      }
    }

    // Trim leading and trailing whitespace from the SKU.
    drupal_array_set_nested_value($form_state['values'], array_merge($entity_form['#parents'], array('sku')), $sku);

    field_attach_form_validate('commerce_product', $product, $entity_form, $form_state);
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);

    $product = $entity_form['#entity'];
    // Show a temporary message to the user for each auto-generated value.
    if (empty($product->sku) && module_exists('commerce_autosku') && $settings = commerce_autosku_get_settings($product)) {
      $product->sku = t('Will be auto-generated when the form is saved.');
      $product->_remove_sku = TRUE;
    }
    if (empty($product->title) && $this->settings['autogenerate_title']) {
      $product->title = t('Will be auto-generated when the form is saved.');
    }
  }

  /**
   * Returns a list of field names that are used as attributes for the given
   * product type.
   */
  protected function attributes($type) {
    // Attributes are tied to the commerce_cart module.
    if (!module_exists('commerce_cart')) {
      return array();
    }

    $attributes = array();
    // Loop through all the field instances on that product type.
    foreach (field_info_instances('commerce_product', $type) as $name => $instance) {
      // A field qualifies if it is single value, required and uses a widget
      // with a definite set of options. For the sake of simplicity, this is
      // currently restricted to fields defined by the options module.
      $field = field_info_field($instance['field_name']);

      // Get the array of Cart settings pertaining to this instance.
      $commerce_cart_settings = commerce_cart_field_instance_attribute_settings($instance);

      // If the instance is of a field type that is eligible to function as
      // a product attribute field and if its attribute field settings
      // specify that this functionality is enabled...
      if (commerce_cart_field_attribute_eligible($field) && $commerce_cart_settings['attribute_field']) {
        $attributes[$name] = array(
          'field' => $field,
          'instance' => $instance,
          'weight' => $instance['widget']['weight'],
        );
      }
    }

    // Sort the fields by weight.
    uasort($attributes, 'drupal_sort_weight');

    return $attributes;
  }

  /**
   * Overrides EntityInlineEntityFormController::save().
   *
   * Autogenerates the product title if specified, and then saves the product.
   */
  public function save($entity, $context) {
    // Remove the temporary message added in entityFormSubmit() so that
    // Commerce AutoSKU can do its thing.
    if (!empty($entity->_remove_sku)) {
      $entity->sku = NULL;
      unset($entity->_remove_sku);
    }

    // Generate the product title. Take the parent entity title as the base.
    if ($this->settings['autogenerate_title']) {
      $entity->title = entity_label($context['parent_entity_type'], $context['parent_entity']);
      $attributes = $this->attributes($entity->type);
      if (!empty($attributes)) {
        $wrapper = entity_metadata_wrapper('commerce_product', $entity);
        $attribute_values = array();
        foreach ($attributes as $field_name => $attribute) {
          $attribute_label = $wrapper->{$field_name}->label();
          if (!empty($attribute_label)) {
            $attribute_values[] = $attribute_label;
          }
        }

        if (!empty($attribute_values)) {
          $entity->title .= ' (' . implode(', ', $attribute_values) . ')';
        }
      }
    }

    entity_save('commerce_product', $entity);
  }

  /**
   * Overrides EntityInlineEntityFormController::delete().
   *
   * Disables products that can't be deleted (because they are already
   * referenced from a line item, or for some other reason), deletes the rest.
   */
  public function delete($ids, $context) {
    $products = entity_load('commerce_product', $ids);
    foreach ((array) $products as $product_id => $product) {
      if (!commerce_product_can_delete($product)) {
        $product->status = FALSE;
        entity_save('commerce_product', $product);

        unset($products[$product_id]);
      }
    }

    entity_delete_multiple('commerce_product', array_keys($products));
  }
}
