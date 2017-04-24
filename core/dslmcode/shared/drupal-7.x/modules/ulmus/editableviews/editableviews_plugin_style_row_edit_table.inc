<?php

/**
 * Plugin class for the Editable Table style.
 */
class editableviews_plugin_style_row_edit_table extends views_plugin_style_table {

  /**
   * Initialize a style plugin.
   */
  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);

    // Get the helper object. This abstracts out a number of things we do here,
    // in order that other style plugins can use them too.
    $this->helper = new editableviews_style_helper($this);
  }

  function option_definition() {
    $options = parent::option_definition();

    // Todo: this should technically be on the helper, but it's faffy as it
    // is apparently not always there, if Views code with the same
    // pattern is anything to go by!
    $options['relationship_creation_bundle'] = array('default' => array());
    $options['save_messages'] = array('default' => 'individual');
    $options['batch'] = array('default' => FALSE, 'bool' => TRUE);
    $options['batch_size'] = array('default' => 10);

    return $options;
  }

  /**
   * The options form for the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Everything we add to the options form is common and thus in the helper.
    $this->helper->options_form($form, $form_state);
  }

  function validate() {
    $errors = parent::validate();

    $relationship_handlers = $this->display->handler->get_handlers('relationship');
    $field_handlers_grouped = $this->helper->get_editable_field_handlers_grouped();
    //dsm($field_handlers_grouped);

    foreach ($relationship_handlers as $relationship_id => $relationship_handler) {
      // We don't care about required relationships.
      if ($relationship_handler->options['required']) {
        continue;
      }

      //dsm($relationship_handler);

      // We don't care if there are no editable fields on the relationship.
      if (empty($field_handlers_grouped[$relationship_id])) {
        continue;
      }

      if (!isset($relationship_handler->definition['editableviews_direction'])) {
        $errors[] = t("The relationship '@relationship' is not compatible with editable fields that may cause creation of entities for empty data. The relationship should be set to be 'required'.", array(
          '@relationship' => $relationship_handler->options['label']
        ));
      }

      if (!isset($this->options['relationship_creation_bundle'][$relationship_id])) {
        $errors[] = t("Display @display is set to use a editable fields and the '@relationship' relationship is not set to be required: the bundle of entities to create on this relationship must be set in the Editable Table options.", array(
          '@display' => $this->display->display_title,
          '@relationship' => $relationship_handler->options['label']
        ));
      }
    }

    return $errors;
  }

  /**
   * Add anything to the query that we might need to.
   */
  function query() {
    parent::query();

    // Everything we do to the query is common and thus in the helper.
    $this->helper->query();
  }

  /**
   * Helper to get the handlers for editable fields.
   *
   * @return
   *  An array of field handlers, in the same format as get_handlers() returns,
   *  but containing only those handlers which are for editable fields.
   */
  function get_edit_field_handlers() {
    $handlers = $this->display->handler->get_handlers('field');

    $edit_field_handlers = array();
    foreach ($handlers as $key => $handler) {
      if (!empty($handler->editable)) {
        $edit_field_handlers[$key] = $handler;
      }
    }

    return $edit_field_handlers;
  }

  /**
   * Render all of the fields for a given style and store them on the object.
   *
   * @param $result
   *   The result array from $view->result
   */
  function render_fields($result) {
    if (!$this->uses_fields()) {
      return;
    }

    if (!isset($this->rendered_fields)) {
      parent::render_fields($result);

      $this->insert_form_elements($result);
    }

    return $this->rendered_fields;
  }

  /**
   * Insert the field form elements into the rendered View fields.
   *
   * @param $result
   *   The result array from $view->result
   */
  function insert_form_elements($result) {
    //dsm($result, '$result');
    // Get our edit field handlers.
    $edit_field_handlers = $this->get_edit_field_handlers();
    if (empty($edit_field_handlers)) {
      // There's nothing to do!
      return;
    }
    //dsm($edit_field_handlers, '$edit_field_handlers');
    $relationship_handlers = $this->display->handler->get_handlers('relationship');

    //dsm($this->view->relationship);

    // Build an array of the field names to make editable.
    // The keys are the id keys of the Views handlers.
    // For non-field-API fields, the definition must include this property.
    $edit_fields = array();
    // Create the keys in this so they exist even for relationships with no
    // editable fields.
    $edit_field_handlers_grouped = array_fill_keys(array_keys($relationship_handlers), array());
    $edit_field_handlers_grouped[$this->view->base_table] = array();

    foreach ($edit_field_handlers as $handler_id => $handler) {
      //dsm($handler, "field handler $handler_id");
      $edit_fields[$handler_id] = $handler->field_name();

      // Build an array of handlers grouped by relationship ID.
      // This is for the form builder to only work on the handlers that are
      // relevant to the entity's relationship.
      $field_handler_relationship_id = $handler->options['relationship'];
      if ($field_handler_relationship_id == 'none') {
        $field_handler_relationship_id = $this->view->base_table;
      }

      $edit_field_handlers_grouped[$field_handler_relationship_id][$handler_id] = $handler;
    }

    // Build an array of entities that we should be working with. We load the
    // that are implicit in the view result, creating new ones if there are any
    // gaps.
    // The entity ID fields have been added to the view result by query().
    $result_entities = array();
    foreach ($result as $index => $result_row) {
      foreach ($this->helper->relationship_entity_fields as $relationship_id => $relationship_entity_data) {
        $entity_type = $relationship_entity_data['entity_type'];
        // Get the entity ID out of the result.
        $entity_id = $result_row->{$relationship_entity_data['id_field_alias']};

        // Get the entities we work with, and build an array of them.
        if (isset($entity_id)) {
          $entity = entity_load_single($entity_type, $entity_id);

          $result_entities[$entity_type][$entity_id] = $entity;
        }
        else {
          if (count($edit_field_handlers_grouped[$relationship_id])) {
            // If there is no entity, and the relationship has editable fields,
            // we create one (i.e., make the object without saving it). We give
            // this a fake entity id, composed of the relationship handler id
            // and the index so it's unique.
            $entity_id = $relationship_id . ':' . $index;

            $entity = $this->helper->entity_create($relationship_id);

            $result_entities[$entity_type][$entity_id] = $entity;
          }
        }

        // Build a lookup from entity type and entity to the result row index
        // and relationship. It helps to conceptualize this as giving us
        // coordinates for where the entity has fields in the view table:
        // the index gives the row, and the relationship gives the column(s).
        // This is for the form builder to be able to get to the right result
        // row and to know which handlers to get form elements from.
        $result_indexes[$entity_type][$entity_id] = array($relationship_id, $index);

        // Build a lookup array of the same coordinates, but towards the entity:
        // keys are relationship ID then index, values are entity type and entity.
        $result_indexes_reverse[$relationship_id][$index] = array($entity_type, $entity_id);
      }
    }
    //dsm($result_entities, '$result_entities');
    //dsm($result_indexes_reverse, '$result_indexes_reverse');

    // Make a combined array of coordinate lookups, both forward and reverse.
    // TODO: eventually replace everything to work with this arrays instead of
    // the two separate ones.
    $results_coordinates = array(
      'entities_to_results' => $result_indexes,
      'results_to_entities' => $result_indexes_reverse,
    );

    // Build up some lookups pertaining to field handlers, and set the editable
    // fields on new entities.
    $result_entity_ids = array();
    foreach ($result as $index => $result_row) {
      foreach ($edit_field_handlers as $handler_id => $handler) {
        // Get the entity type and entity for this field handler from the
        // relationship lookup.
        $field_handler_relationship_id = $handler->options['relationship'];
        if ($field_handler_relationship_id == 'none') {
          $field_handler_relationship_id = $this->view->base_table;
        }

        // Add the field_name for this field handler to the list on the entity
        // which keeps track of them.
        list($entity_type, $entity_id) = $result_indexes_reverse[$field_handler_relationship_id][$index];
        if (!is_numeric($entity_id)) {
          $entity = $result_entities[$entity_type][$entity_id];
          $entity->editableviews_exposed_fields[] = $handler->field_name();
        }

        // Build a lookup array from index and field handler to the entity type
        // and entity. This is to get to the right form element to include when
        // we finally render our fields.
        // Just get the entity coordinates from the relationship lookup.
        $result_entity_ids[$index][$handler_id] = $result_indexes_reverse[$field_handler_relationship_id][$index];
      }
    }
    //dsm($result_entity_ids, '$result_entity_ids');

    // Now we have built up all our entities, go over them again and add
    // the connecting properties to any new ones.
    // In other words:
    //  - On a forward relationship, the existing entity on the relationship's
    //    base needs to point to the new entity that is (potentially) about to
    //    be saved.
    //  - On a reverse relationship, the new entity that is about to be created
    //    needs to point back to the existing entity on the relationship's base.
    // Here we figure out the id we need to point to, and the property to point
    // to it in.
    $this->helper->connect_new_entities($result_entities, $results_coordinates, $edit_field_handlers_grouped);
    //dsm($result_entities, '$result_entities post connect');

    // Load up the form render array.
    $this->get_form($result_entities, $results_coordinates, $edit_field_handlers_grouped);

    // Doctor the view's rendered fields to add in the form elements for
    // the appropriate entity and field.
    foreach ($this->rendered_fields as $index => $rendered_fields) {
      foreach ($edit_fields as $handler_id => $field_name) {
        // Get the already rendered field.
        $rendered_field = $this->rendered_fields[$index][$handler_id];

        // Get the entity type and entity that this field handler shows from our
        // lookup array, so that we can pick out the form element to render
        // for it.
        list($entity_type, $entity_id) = $result_entity_ids[$index][$handler_id];

        // TODO! theme this!!
        $this->rendered_fields[$index][$handler_id] = '<div class="views-row-edit-static">' . $rendered_field . '</div>';
        $this->rendered_fields[$index][$handler_id] .= '<div class="views-row-edit-edit">' . drupal_render($this->form[$entity_type][$entity_id][$field_name]) . '</div>';
      }
    }
  }

  /**
   * Helper method. Retrieves the form render array.
   *
   * @param $entities
   *  An array of entities to get the form for, keyed first by entity type and
   *  then by entity id.
   * @param $results_coordinates
   *  An array containing coordinates lookups for getting entity type and entity
   *  from row id and relationship, and the same the other way round. Contains:
   *  - 'entities_to_results': A nested array keyed by entity type then entity
   *    id. The final values are flat arrays of the relationship id and result
   *    index.
   *  - 'results_to_entities': A nested array keyed by relationship id then
   *    result index. The final values are flat arrays of the entity type and
   *    entity id.
   * @param $edit_field_handlers
   *  An array of field handlers to provide form elements for, grouped by
   *  their relationship.
   *  See editableviews_entity_form() for details.
   */
  function get_form($entities, $results_coordinates, $edit_field_handlers) {
    // Create a dynamic form ID using the base name (for quick recognition
    // in hook_forms()) and the view name. This allows hook_form_alter() to
    // target forms for specific views. We don't add the display name as there's
    // no clean way to mark the separation between that and the view name.
    // @see editableviews_forms()
    $form_id = 'editableviews_entity_form' . '_' . $this->view->name;

    // We store this rather than return it, as it's used in different places.
    $this->form = drupal_get_form($form_id, $entities, $results_coordinates, $edit_field_handlers, $this->view);
  }

  /**
   * Render the display in this style.
   */
  function render() {
    // Get the rendered view output.
    $view_render = parent::render();

    // Stick it INSIDE the form as plain markup, so that the HTML FORM element
    // goes around everything.
    $this->form['view'] = array(
      '#markup' => $view_render,
    );

    return $this->form;
  }

}

/**
 * Helper class for the style plugin.
 *
 * This abstracts out a number of things the style plugin needs to do, in order
 * that other style plugins can use them too.
 */
class editableviews_style_helper {

  /**
   * A lookup from relationships to the data needed to load their entities.
   *
   * This is an array of the relationships on the view which correspond to
   * entity base tables, including the base table (as a pseudo-relationship).
   * The key is the relationship id (in the case of the base table, this is just
   * the table name itself). Each value is an array containing:
   *  - 'entity_type': The entity type this relationship brings to the view.
   *  - 'id_field_alias': The field alias of the field on the view in which to
   *    find the entity's ID. This field is ensured by our query().
   */
  public $relationship_entity_fields = array();

  function __construct(&$plugin) {
    $this->plugin = &$plugin;
  }

  /**
   * Provide common options for editable style plugins.
   */
  function options_form(&$form, &$form_state) {
    // Add a fieldset to allow setting of a creation bundle for all the
    // relationships that are non-required. This is because a non-required
    // relationship may cause empty data in the result, and if this has editable
    // fields, then entering data into those field's form elements causes the
    // creation of a new entity. Which we need a bundle for.
    $relationship_handlers = $this->plugin->display->handler->get_handlers('relationship');
    // Get our edit field handlers.
    $edit_field_handlers = $this->plugin->get_edit_field_handlers();

    // Collect the relationships these are on.
    $edit_relationship_handlers = array();
    foreach ($edit_field_handlers as $field_handler_id => $field_handler) {
      // Because we're not in the process of querying, the relationship is only
      // set in the options.
      $relationship_id = $field_handler->options['relationship'];

      // Skip edit field handlers that are on the base.
      if ($relationship_id == 'none') {
        continue;
      }

      // Argh, do we need to contend with the alias of the relationship here??

      // Skip a relationship that is required: these will never provide an empty
      // row, and so never require entity creation.
      if ($relationship_handlers[$relationship_id]->options['required']) {
        continue;
      }

      // If we're still here, this is a relationship we need to consider.
      $edit_relationship_handlers[$relationship_id] = $relationship_handlers[$relationship_id];
    }

    // Only show this fieldset if there are relationships to consider.
    if (count($edit_relationship_handlers)) {
      $form['relationship_creation_bundle'] = array(
        '#type' => 'fieldset',
        '#title' => t('Relationship entity creation bundles'),
        '#description' => t('A relationship which is set to not required may produce empty form elements, which thus require the creation of a new entity if populated with data. The bundle for these new entities must be specified here.'),
        '#weight' => -1,
      );

      foreach ($edit_relationship_handlers as $relationship_id => $relationship_handler) {
        // The 'base' of a relationship is the table it brings.
        $table = $relationship_handler->definition['base'];
        // Get the entity type from the table.
        $table_data = views_fetch_data($table);
        $entity_type = $table_data['table']['entity type'];
        $entity_info = entity_get_info($entity_type);

        $options = array();
        foreach ($entity_info['bundles'] as $bundle => $bundle_info) {
          $options[$bundle] = $bundle_info['label'];
        }

        $form['relationship_creation_bundle'][$relationship_id] = array(
          '#type' => 'select',
          '#title' => t('Bundle for new entities created on %label', array(
            '%label' => $relationship_handler->options['label'],
          )),
          '#description' => t('Select the %entity entity bundle for entities created on this relationship.', array(
            '%entity' => $entity_info['label'],
          )),
          '#options' => $options,
          '#required' => TRUE,
        );
        // We have to check the default value, as the key in the array is variable
        // because it's the relationship handler ID. That means that Views won't
        // have it set in option_definition().
        if (isset($this->plugin->options['relationship_creation_bundle'][$relationship_id])) {
          $form['relationship_creation_bundle'][$relationship_id]['#default_value'] = $this->plugin->options['relationship_creation_bundle'][$relationship_id];
        }
      }
    }

    $form['save_messages'] = array(
      '#type' => 'select',
      '#title' => t("Save messages"),
      '#description' => t('The messages to show the user when the view form is saved.'),
      '#options' => array(
        'none' => t('Show no messages'),
        'summary' => t('Show a single message summarizing the changes'),
        'individual' => t('Show a message for each saved entity'),
      ),
      '#default_value' => $this->plugin->options['save_messages'],
    );

    $form['batch'] = array(
      '#type' => 'checkbox',
      '#title' => t("Enable batch support"),
      '#description' => t('Use Batch API to save huge data.'),
      '#default_value' => $this->plugin->options['batch'],
    );

    $form['batch_size'] = array(
      '#type' => 'textfield',
      '#title' => t("Batch size"),
      '#description' => t('Number of entities to process in each batch step.'),
      '#default_value' => $this->plugin->options['batch_size'],
      '#states'=> array(
        'visible' => array(
          ':input[name="style_options[batch]"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  /**
   * Add anything to the query that we might need to.
   *
   * For the base and each relationship that brings an entity table, add the
   * entity ID field for that entity. This ensures that we can load the entities
   * when we need to get form elements for them.
   *
   * We do this for all relationships, not just those which have editable fields
   * on them, because we may need access to entities that editable field
   * entities need to point to when creating entities.
   */
  function query() {
    // For each relationship that provides an entity table (including the base
    // pseudo-relationship), add the field for that entity's ID.
    $base_table = $this->plugin->view->base_table;

    // Do the View base first.
    $table_data = views_fetch_data($this->plugin->view->base_table);
    if (isset($table_data['table']['entity type'])) {
      // We don't need to ensure this field is on the query: the id field on
      // the base table always is.
      $this->relationship_entity_fields[$base_table] = array(
        'entity_type' => $table_data['table']['entity type'],
        // We don't need to find an alias for a field on the base.
        'id_field_alias' => $table_data['table']['base']['field'],
      );
    }

    // Now the relationships.
    $relationship_handlers = $this->plugin->display->handler->get_handlers('relationship');
    foreach ($relationship_handlers as $relationship_id => $relationship_handler) {
      //dsm($relationship_handler, $relationship_id);

      // The 'base' of a relationship is the table it brings.
      $table = $relationship_handler->definition['base'];
      // Get the entity type from the table.
      $table_data = views_fetch_data($table);

      if (!isset($table_data['table']['entity type'])) {
        // Not an entity base table relationship: skip it.
        continue;
      }

      // Get the entity type and the views field that corresponds to the entity
      // id from the table definition.
      //dsm($table_data['table'], 'table data');
      $entity_type = $table_data['table']['entity type'];
      $entity_id_field = $table_data['table']['base']['field'];

      // Force the 're
      if ($relationship_handler->options['relationship'] == 'none') {
        $relationship_relationship = $base_table;
      }
      else {
        $relationship_relationship = $relationship_handler->options['relationship'];
      }
      //dsm($relationship_relationship, '$relationship_relationship');

      // We want the alias for the table the relationship brings, not the table
      // it sits on.
      $table_alias = $relationship_handler->alias;
      //dsm("$relationship_id brings $entity_type, $entity_id_field.\ntable alias is $table_alias");

      $entity_id_field_alias = $this->plugin->view->query->add_field($table_alias, $entity_id_field);

      $this->relationship_entity_fields[$relationship_id] = array(
        'entity_type' => $entity_type,
        'id_field_alias' => $entity_id_field_alias,
      );
    }
    //dsm($this->relationship_entity_fields);
  }

  /**
   * Returns a new (unsaved) entity for the given relationship ID.
   *
   * This is needed when editable field handlers are on a non-required
   * relationship, and a particular result row has no data there. We create a
   * new entity for FieldAPI to work on, and potentially save it on submission
   * if the user enters data.
   *
   * @param $relationship_id
   *  The id of the relationship that requires a new entity.
   *
   * @return
   *  A new, unsaved entity. The entity type is implied by the handler, and
   *  should be known by the caller. The bundle will be set on this, given by
   *  the style plugin's options.
   */
  function entity_create($relationship_id) {
    $entity_type = $this->relationship_entity_fields[$relationship_id]['entity_type'];

    // This is complex. We know the entity type, but we need to be told
    // the bundle: that's one for the plugin settings.
    // Then when it's created, we need to know how to set the relationship
    // field.
    $entity_info = entity_get_info($entity_type);
    // Assume this exists, as it must do if the entity is fieldable, and
    // if your entity is not fieldable, what are you doing here? ;)
    $bundle_key = $entity_info['entity keys']['bundle'];

    $values = array(
      // The bundle of the new entity is set in the options for this
      // style plugin. This has to be set by the user, because there is
      // absolutely no other way to sniff this out!
      // TODO: cloud cuckoo land, but a form element field to specify
      // the bundle for each row would be nice!
      $bundle_key => $this->plugin->options['relationship_creation_bundle'][$relationship_id],
    );

    // Just a little bit of sugar to save this having to be done in a custom
    // form submit handler: for nodes and comments, set the uid property
    // to the current user. We would do this with anything that has a uid
    // property, but entity_get_property_info() calls it 'author' and it's just
    // starting to get faffy now.
    if ($entity_type == 'node' || $entity_type == 'comment') {
      $values['uid'] = $GLOBALS['user']->uid;
    }

    $entity = entity_create($entity_type, $values);

    // Add our own property to the entity, where we keep track of the properties
    // that are exposed as form elements in the view. This is how we will
    // determine whether or not to save it when the form is submitted.
    $entity->editableviews_exposed_fields = array();

    // Add our own property to specify whether this needs to be saved or not.
    // @see editableviews_entity_form_submit_build_values()
    $entity->editableviews_needs_save = FALSE;

    return $entity;
  }

  /**
   * Sets the properties so that new entities connect to existing ones.
   *
   * For a forward relationship, the existing entity must know it has to point
   * to the new entity once it has been saved.
   * For a reverse relationship, the new entity must have the right property set
   * (e.g. an entityreference field) so that it point back to the existing
   * entity.
   *
   * @param $result_entities
   *  The array of result entities from the style plugin. Passed by reference
   *  so the entities can be altered. (TODO: is this actually needed??)
   * @param $results_coordinates
   *  The combined coordinates array, containing both the forward and reverse
   *  lookups for entities and results.
   *  @see editableviews_plugin_style_row_edit_table::get_form() for details.
   * @param $edit_field_handlers_grouped
   *  The edit field handlers, grouped by relationship handler ID.
   */
  function connect_new_entities(&$result_entities, $results_coordinates, $edit_field_handlers_grouped) {
    $relationship_handlers = $this->plugin->display->handler->get_handlers('relationship');

    //dsm($edit_field_handlers_grouped);
    //dsm($result_entities);

    foreach (array_keys($result_entities) as $entity_type) {
      foreach ($result_entities[$entity_type] as $entity_id => $entity) {
        // New entities have a non-numeric fake id we just gave them.
        if (!is_numeric($entity_id)) {
          // Get the views coordinates for this entity.
          list($relationship_id, $index) = $results_coordinates['entities_to_results'][$entity_type][$entity_id];

          $relationship_handler = $relationship_handlers[$relationship_id];
          //dsm($relationship_handler);

          // Get the relationship that the relationship is on, so we can then
          // get the entity for that relationship.
          if (isset($relationship_handler->relationship)) {
            $relationship_relationship = $relationship_handler->relationship;
          }
          else {
            $relationship_relationship = $this->plugin->view->base_table;
          }

          // Only act if the new entity's relationship has editable fields:
          // otherwise it's just an empty bunch of table cells, and there's
          // nothing to connect to or from.
          if (count($edit_field_handlers_grouped[$relationship_relationship]) == 0) {
            continue;
          }

          if ($relationship_handler->definition['editableviews_direction'] == 'forward') {
            // Get the entity on our relationship's relationship -- same
            // as for reverse.
            // Get the entity out of the imaginary Views grid that is on the same
            // row as us, and in the $relationship_relationship relationship...
            list($referring_entity_type, $referring_entity_id) = $results_coordinates['results_to_entities'][$relationship_relationship][$index];
            $referring_entity = $result_entities[$referring_entity_type][$referring_entity_id];

            // Store this entity's details on the current, new entity, so that
            // when (and if!) we save it, we can go and make the referring
            // entity point to it.
            $entity->editableviews_future_reference = array(
              'entity_type' => $referring_entity_type,
              'entity_id' => $referring_entity_id,
              'field_name' => $relationship_handler->definition['field_name'],
            );
          }
          else {
            // Would be nice to factor this out to a helper method, say
            // '$this->new_entity_set_reverse_connection()' but we'd need to
            // pass so many variables it's probably just as faffy.

            // Get the entity out of the imaginary Views grid that is on the same
            // row as us, and in the $relationship_relationship relationship...
            list($referred_entity_type, $referred_entity_id) = $results_coordinates['results_to_entities'][$relationship_relationship][$index];
            $referred_entity = $result_entities[$referred_entity_type][$referred_entity_id];

            // From here on, this is just reverse relationships!
            $wrapper = entity_metadata_wrapper($entity_type, $entity);

            // This is what we need to set on the new entity in a reverse relationship.
            $relationship_field_name = $relationship_handler->definition['field_name'];
            // Make the new entity point to the entity on its relationship's
            // relationship.
            $wrapper->{$relationship_field_name}->set($referred_entity_id);
          }
        }
      }
    }
  }

  /**
   * Get editable field handlers grouped by relationship id.
   */
  function get_editable_field_handlers_grouped() {
    $editable_field_handlers = $this->plugin->get_edit_field_handlers();

    $editable_field_handlers_grouped = array();
    foreach ($editable_field_handlers as $field_handler_id => $field_handler) {
      //dsm($field_handler, '$field_handler');
      $relationship_id = $field_handler->options['relationship'];
      if ($relationship_id == 'none') {
        // TODO: tidy up this WTF!
        $relationship_id = 'base';
      }

      $editable_field_handlers_grouped[$relationship_id][$field_handler_id] = $field_handler;
    }

    return $editable_field_handlers_grouped;
  }

}
