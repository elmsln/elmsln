<?php

/**
 * @file
 * Hooks provided by Conditional Fields.
 */

/**
 * Alter the list of states available for dependent fields.
 *
 * These are the jQuery events that are executed when a dependent field changes
 * state (that is, when the dependency changes from untriggered to triggered or
 * vice-versa).
 *
 * To implement a new state, it is necessary to create a jQuery event with the
 * same name, prepended by the "state:" namespace. E.g.:
 *
 * $(document).bind('state:STATE_NAME', function(e) {
 *   if (e.trigger) {
 *     // e.value is true if the conditions are satisfied, false otherwise...
 *   }
 * });
 *
 * @param $states
 *   An associative array of states.
 */
function hook_conditional_fields_states_alter(&$states) {
  // Add a new Form state to the list. The corresponding jQuery event might
  // look like this:
  // $(document).bind('state:addmyclass', function(e) {
  //   if (e.trigger) {
  //     $(e.target).toggleClass('myclass', e.value);
  //   }
  // });
  $states['addmyclass'] = t('With CSS class myclass');

  // Converse states are obtained by prepending an exclamation mark to the name.
  // They are automatically implemented by the States API, but you need to add
  // them explicitly to the list to make them available in the UI.
  $states['!addmyclass'] = t('Without CSS class myclass');

  // A configurable state. The class can be configured implementing an effect
  // (see example in hook_conditional_fields_effects_alter).
  $states['addclass'] = t('With CSS class');
  $states['!addclass'] = t('Without CSS class');
}

/**
 * Alter the list of visual effects available to states.
 *
 * Visual effects may provide settings that are passed to the js object
 * Drupal.settings.conditionalFields.effects and that are automatically
 * made available to the corresponding state change event under event.effect.
 *
 * Dependent field events associated with effects have the effect name appended
 * to the name, separated by a hypen; effect options are passed into the event
 * argument. E.g.:
 *
 * $(document).bind('state:STATE_NAME-EFFECT_NAME', function(e) {
 *   if (e.trigger) {
 *     // Effect options are stored in e.effect...
 *   }
 * });
 *
 * @param $effects
 *   An associative array of effects. Each key is the unique name of the
 *   effect. The value is an associative array:
 *   - label: The human readable name of the effect.
 *   - states: The states that can be associated with this effect.
 *   - options: An associative array of effect options names, field types,
 *     descriptions and default values.
 */
function hook_conditional_fields_effects_alter(&$effects) {
  // Implement an effect for the addclass state.
  // The addclass event would be something like:
  // $(document).bind('state:addclass-toggleclass', function(e) {
  //  if (e.trigger) {
  //    $(e.target).toggleClass(e.effect.class, e.value);
  //  }
  // });
  $effects['toggleclass'] = array(
    'label' => t('CSS Class'),
    // This effect is associated with the following states.
    'states' => array('addclass', '!addclass'),
    // The values under options are form elements that will be inserted in
    // the dependency edit form. The key of this form element is also found in
    // the jQuery event argument under event.effect.class.
    'options' => array(
      'class' => array(
        '#type' => 'textfield',
        '#description' => t('One or more space separated classes that are toggled on the dependent.'),
        '#default_value' => '',
      ),
    ),
  );
}

/**
 * Alter the list of conditions available as dependee states.
 *
 * These are callbacks that are executed by the States API to check if a
 * dependee field matches the required condition.
 * Modules adding conditions using this hook should also add the corresponding
 * callback to the Drupal.states.Trigger.states object.
 *
 * @param $conditions
 *   An associative array of conditions, with names as keys and labels as
 *   values.
 */
function hook_conditional_fields_conditions_alter(&$conditions) {
  // Add a special condition that checks if a field value is an integer greater
  // than 0. The javascript callback could be something like:
  // Drupal.states.Trigger.states.positiveInteger = {
  //   'keyup': function () {
  //     var val = this.val(),
  //         int = parseInt(val);
  //     return val == int && int > 0;
  //   }
  // };
  $conditions['positiveInteger'] = t('An integer greater than 0.');
  // Like states, conditions get a converse automatically.
  $conditions['!positiveInteger'] = t('An integer less than or equal to 0.');
}

/**
 * Alter the list of states handlers.
 *
 * State handlers are callbacks that are executed when adding the #states
 * information to a form element.
 *
 * @param $handlers
 *  An associative array of handlers, with callback as keys and an associative
 *  array of form element properties that are used to match the element with
 *  the right handler.
 *
 * @see conditional_fields_states_handlers()
 */
function hook_conditional_fields_states_handlers_alter(&$handlers) {
  // See conditional_fields_states_handlers() for examples.
}

/**
 * Alter the list of available behaviors.
 *
 * @param $behaviors
 *   An associative array with two keys representing contexts: 'edit' and
 *   'view'. Each key contains an associative array of behaviors that are
 *   executed during the corresponding phase. The keys of the array are
 *   function names and the values are a human readable label of the behavior.
 */
function hook_conditional_fields_behaviors_alter(&$behaviors) {
  // Edit behavior.
  $behaviors['edit']['conditional_fields_example_fancy_edit_behavior'] = t('A fancy edit behavior for my module');
  // View behavior.
  $behaviors['view']['conditional_fields_example_fancy_view_behavior'] = t('A fancy view behavior for my module');
}

/**
 * Example edit behavior callback.
 *
 * @param $form
 *   The form that contains fields with dependencies.
 * @param $form_state
 *   The form state of the form.
 * @param $dependent
 *   The name of the dependent field.
 * @param $dependencis
 *   The dependencies relevant to this dependent.
 */
function conditional_fields_example_fancy_edit_behavior(&$form, &$form_state, $dependent, $dependencies) {
  // Do some fancy stuff...
}

/**
 * Example view behavior callback.
 *
 * @param $dependent
 *   The name of the dependee field.
 * @param $dependee
 *   The name of the dependent field.
 * @param $is_triggered
 *   A boolean indicating whether the dependency was triggered.
 * @param $dependencies
 *   An array of dependencies relevant to this context.
 * @param $build
 *   The entity that is being viewed.
 * @param $entity_type
 *   The entity type that is being viewed.
 */
function conditional_fields_example_fancy_view_behavior($dependee, $dependent, $is_triggered, $dependencies, &$build, $entity_type) {
  // Add some foo before all entities that have triggered dependencies.
  if ($is_triggered) {
    $build['#prefix'] .= 'foo';
  }
}
