<?php
/**
 * @file
 * Administration of dependencies.
 */

/**
 * Dependencies administration page.
 *
 * If the callback is called from the overview page, it builds a list of
 * dependencies for each entity type, grouped by bundle.
 * If called from one of the local tasks, it builds a list of dependencies
 * only for the selected entity type.
 * If called from a task under a specific bundle administration page, it
 * builds a list just for that entity type and bundle name pair.
 */
function conditional_fields_dependencies_overview_page($bundle_name = NULL, $entity_type = NULL) {
  // When displaying the page, make sure the list of fields is up-to-date.
  field_info_cache_clear();

  // Gather entities information.
  $entities = $entity_type ? array($entity_type => entity_get_info($entity_type)) : entity_get_info();

  // Extract bundle name from path, if present.
  if ($bundle_name) {
    $bundle_name = strtr($bundle_name, array('-' => '_'));

    // Hacky exception for hanlding comments.
    if ($entity_type == 'comment') {
      $bundle_name = 'comment_node_' . $bundle_name;
    }
  }

  // Unused here, but saves queries in conditional_fields_dependency_add_form().
  if (!$bundle_name) {
    conditional_fields_load_dependencies($entity_type, $bundle_name);
  }

  $build = array();

  if (!$entity_type) {
    $build['#attached']['library'][] = array('system', 'drupal.collapse');
  }

  foreach ($entities as $entity_name => $entity_info) {
    if (!$entity_info['fieldable']) {
      continue;
    }

    $items = array();

    if ($entity_type) {
      $build[$entity_name] = array();
    }
    else {
      $build[$entity_name] = array(
        '#type' => 'fieldset',
        '#title' => $entity_info['label'],
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#attributes' => array(
          'class' => array('collapsible collapsed'),
        ),
      );
    }

    if (empty($entity_info['bundles'])) {
      $build[$entity_name]['no_bundles'] = array(
        '#markup' => $entity_name == 'node' ? t('No content types available.') : t('No bundles available.'),
      );
    }
    else {
      foreach ($entity_info['bundles'] as $bundle_info_name => $bundle_info) {
        if ($bundle_name && $bundle_name != $bundle_info_name) {
          continue;
        }

        $build[$entity_name][$bundle_info_name] = array();

        if (!$bundle_name && count($entity_info['bundles']) > 1) {
          $build[$entity_name][$bundle_info_name]['title'] = array(
            '#markup' => '<h4 class="conditional-fields-bundles-list clearfix">' . $bundle_info['label'] . '</h4>',
          );
        }

        $build[$entity_name][$bundle_info_name] += drupal_get_form('conditional_fields_dependency_add_form_' . $entity_name . '_' . $bundle_info_name);

        if (!$entity_type && !isset($build[$entity_name][$bundle_info_name]['no_fields'])) {
          $build[$entity_name]['#collapsed'] = FALSE;
          $build[$entity_name]['#attributes']['class'] = array('collapsible');
        }
      }
    }
  }

  return $build;
}

/**
 * Dependency add form.
 *
 * @see conditional_fields_dependency_add_form_submit()
 * @see conditional_fields_dependency_add_form_validate()
 * @ingroup forms
 */
function conditional_fields_dependency_add_form($form, &$form_state, $entity_type, $bundle_name) {
  $form = array();
  $instances = field_info_instances($entity_type, $bundle_name);

  if (count($instances) < 2) {
    $form['no_fields'] = array(
      '#markup' => t('Add at least two fields to enable dependencies.'),
    );

    return $form;
  }

  $dependencies = conditional_fields_load_dependencies($entity_type, $bundle_name);

  $form['table'] = array(
    '#type' => 'conditional_fields_table',
    '#entity_type' => $entity_type,
    '#bundle_name' => $bundle_name,
    '#header' => array(
      t('Dependent'),
      t('Dependees'),
      array('data' => t('Description'), 'colspan' => 2),
      array('data' => t('Operations'), 'colspan' => 2),
    ),
    '#attributes' => array(
      'class' => array('conditional-fields-overview'),
    ),
    'dependencies' => array(),
  );

  $form['table']['#attached']['css'][] = drupal_get_path('module', 'conditional_fields') . '/conditional_fields.css';

  if ($dependencies) {
    $destination = drupal_get_destination();
    $grouping_count = array();

    foreach ($dependencies['dependents'] as $dependent => $dependees) {
      uasort($dependees, '_conditional_fields_sort_dependees');

      // Enable row grouping by operator.
      $first_row = $show_AND = $show_OR = $show_XOR = TRUE;
      if (!isset($grouping_count[$dependent])) {
        $grouping_count[$dependent] = array(
          'AND' => 0,
          'OR' => 0,
          'XOR' => 0,
        );
        foreach ($dependees as $dependency) {
          $grouping_count[$dependent][$dependency['options']['grouping']]++;
        }
      }

      foreach ($dependees as $id => $dependency) {
        $form['table']['dependencies'][$id] = array();
        $dependee_count = count($dependees);

        // Dependencies come ordered by dependent, so by adding it only to the
        // first row they will appear grouped.
        if ($first_row == TRUE) {
          $form['table']['dependencies'][$id]['dependent'] = array(
            '#markup' => check_plain($instances[$dependent]['label']) . ' (' . $dependent . ')',
            '#rowspan' => $dependee_count,
          );

          $first_row = FALSE;
        }

        $row = array(
          'dependee' => array(
            '#markup' => check_plain($instances[$dependency['dependee']]['label']) . ' (' . $dependency['dependee'] . ')',
          ),
        );

        // To avoid clutter, collect information about groupings so we can show each
        // operator once per dependent.
        if ($dependee_count > 1) {
          if (${'show_' . $dependency['options']['grouping']}) {
            $row['group'] = array(
              '#markup' => $dependency['options']['grouping'],
              '#rowspan' => $grouping_count[$dependent][$dependency['options']['grouping']],
            );
            ${'show_' . $dependency['options']['grouping']} = FALSE;
          }
        }
        else {
          $row['description']['#colspan'] = 2;
        }

        $row['description']['#markup'] = conditional_fields_dependency_description($instances[$dependency['dependee']]['label'], $instances[$dependent]['label'], $dependency['options']);

        $row['edit'] = array(
          '#type' => 'link',
          '#title' => t('edit'),
          '#href' => 'admin/structure/dependencies/edit/' . $id,
          '#options' => array('query' => $destination, 'attributes' => array('title' => t('Edit dependency settings.'))),
          '#query' => drupal_get_destination(),
        );
        $row['delete'] = array(
          '#type' => 'link',
          '#title' => t('delete'),
          '#href' => 'admin/structure/dependencies/delete/' . $id,
          '#options' => array('query' => $destination, 'attributes' => array('title' => t('Delete dependency.'))),
        );

        $form['table']['dependencies'][$id] += $row;
      }
    }
  }

  // Build list of available fields.
  $fields = array();

  foreach ($instances as $field) {
    $fields[$field['id']] = check_plain($field['label'] . ' (' . $field['field_name'] . ')');
  }

  asort($fields);

  // Build list of states.
  $states = array_map('drupal_strtolower', conditional_fields_states());

  // Build list of conditions.
  foreach (conditional_fields_conditions() as $condition => $label) {
    $conditions[$condition] = $condition == 'value' ? t('has value...') : t('is !label', array('!label' => drupal_strtolower($label)));
  }

  // Add new dependency row.
  $form['table']['add_new_dependency'] = array(
    'dependent' => array(
      '#type' => 'select',
      '#title' => t('Dependent'),
      '#title_display' => 'invisible',
      '#description' => t('Dependent'),
      '#options' => $fields,
      '#prefix' => '<div class="add-new-placeholder">' . t('Add new dependency') . '</div>',
    ),
    'dependee' => array(
      '#type' => 'select',
      '#title' => t('Dependee'),
      '#title_display' => 'invisible',
      '#description' => t('Dependee'),
      '#options' => $fields,
      '#prefix' => '<div class="add-new-placeholder">&nbsp;</div>',
    ),
    'state' => array(
      '#type' => 'select',
      '#title' => t('State'),
      '#title_display' => 'invisible',
      '#options' => $states,
      '#default_value' => 'visible',
      '#prefix' => t('The dependent field is') . '&nbsp;<span class="description-select">',
      '#suffix' => '</span>&nbsp;' . t('when the dependee'),
    ),
    'condition' => array(
      '#type' => 'select',
      '#title' => t('Condition'),
      '#title_display' => 'invisible',
      '#options' => $conditions,
      '#default_value' => 'value',
      '#prefix' => '&nbsp;<span class="description-select">',
      '#suffix' => '</span>',
    ),
    'actions' => array(
      'submit' => array(
        '#type' => 'submit',
        '#value' => t('Add dependency'),
      ),
    ),
  );

  return $form;
}

/**
 * Dependency add form validate.
 *
 * @see conditional_fields_dependency_add_form()
 * @see conditional_fields_dependency_add_form_submit()
 */
function conditional_fields_dependency_add_form_validate($form, &$form_state) {
  if ($form_state['values']['dependee'] == $form_state['values']['dependent']) {
    form_set_error('dependent', t('You should select two different fields.'));
    form_set_error('dependee', t('You should select two different fields.'));
    // Workaround to avoid duplicate error messages.
    array_pop($_SESSION['messages']['error']);
  }
}

/**
 * Dependency add form submit.
 *
 * @see conditional_fields_dependency_add_form()
 * @see conditional_fields_dependency_add_form_validate()
 */
function conditional_fields_dependency_add_form_submit($form, &$form_state) {
  $options = array(
    'state' => $form_state['values']['state'],
    'condition' => $form_state['values']['condition']
  );

  if (!$id = conditional_fields_dependency_insert($form_state['values']['dependee'], $form_state['values']['dependent'], $options)) {
    drupal_set_message(t('There was an error while trying to create the dependency.'), 'error');
    return;
  }

  $destination = drupal_get_destination();
  drupal_goto("admin/structure/dependencies/edit/$id", array('query' => $destination));
}

/**
 * Returns HTML for Conditional Fields dependencies tables.
 *
 * @param $variables
 *   An associative array containing:
 *   - elements: An associative array containing a Form API structure to be
 *     rendered as a table.
 *
 * @ingroup themeable
 */
function theme_conditional_fields_table($variables) {
  $elements = $variables['elements'];
  $table = array();

  // Add table headers and attributes.
  foreach (array('header', 'attributes') as $key) {
    if (isset($elements["#$key"])) {
      $table[$key] = $elements["#$key"];
    }
  }

  // Dependencies rows.
  foreach (element_children($elements['dependencies']) as $dependency) {
    foreach (element_children($elements['dependencies'][$dependency]) as $cell_key) {
      $cell = array(
        'data' => drupal_render($elements['dependencies'][$dependency][$cell_key]),
      );
      foreach (array('#colspan', '#rowspan') as $row_attribute) {
        if (isset($elements['dependencies'][$dependency][$cell_key][$row_attribute])) {
          $cell[ltrim($row_attribute, '#')] = $elements['dependencies'][$dependency][$cell_key][$row_attribute];
        }
      }
      $table['rows'][$dependency][] = $cell;
    }
  }

  // Add new dependency row.
  $table['rows'][] = array(
    drupal_render($elements['add_new_dependency']['dependent']),
    drupal_render($elements['add_new_dependency']['dependee']),
    array(
      'data' => drupal_render($elements['add_new_dependency']['state']) . drupal_render($elements['add_new_dependency']['condition']),
      'colspan' => 2,
    ),
    array(
      'data' => drupal_render($elements['add_new_dependency']['actions']),
      'colspan' => 2,
    ),
  );

  return theme('table', $table);
}

/**
 * Dependency edit form.
 *
 * @see conditional_fields_dependency_edit_form_validate()
 * @see conditional_fields_dependency_edit_form_submit()
 * @ingroup forms
 */
function conditional_fields_dependency_edit_form($form, &$form_state, $dependency) {
  $form['#dependency'] = $dependency;

  $form['#attached']['css'][] = drupal_get_path('module', 'conditional_fields') . '/conditional_fields.css';

  // Retrieve needed information from the dependee instance.
  // Since we only have the instance id here (id column of the
  // field_config_instance table), not the entity id (id column of field_config)
  // we can't call field_info_field_by_id. This is needed because we don't
  // want dependencies to be shared between bundles.
  // So we first load instance information to obtain the entity id, then we load
  // the entity using field_info_field().
  $instances = field_read_instances(array('id' => $dependency['dependee']));
  $dependee_instance = array_shift($instances);
  $dependee = field_info_field($dependee_instance['field_name']);

  // Build a dummy field widget to use as form field in single value selection
  // option.
  $dummy_form = array('#parents' => array());
  $dependee_instance['default_value'] = $dependency['options']['value'];
  $dependee_instance['default_value_function'] = '';
  $dependee_instance['required'] = FALSE;

  $dummy_field = field_default_form($dependee_instance['entity_type'], NULL, $dependee, $dependee_instance, LANGUAGE_NONE, array(), $dummy_form, $form_state);

  // Save dependee name in form.
  $form['dependee'] = array(
    '#type' => 'value',
    '#value' => $dependee_instance['field_name'],
  );

  $checkboxes = ($dependee_instance['widget']['type'] == 'options_buttons' && $dependee['cardinality'] != 1) || $dependee_instance['widget']['type'] == 'options_onoff' ? TRUE : FALSE;

  $form['condition'] = array(
    '#type' => 'select',
    '#title' => t('Condition'),
    '#description' => t('The condition that should be met by the dependee %field to trigger the dependency.', array('%field' => $dependee_instance['label'])),
    '#options' => conditional_fields_conditions($checkboxes),
    '#default_value' => $dependency['options']['condition'],
    '#required' => TRUE,
  );

  $form['values_set'] = array(
    '#type' => 'select',
    '#title' => t('Values input mode'),
    '#description' => t('The input mode of the values that trigger the dependency.'),
    '#options' => array(
      CONDITIONAL_FIELDS_DEPENDENCY_VALUES_WIDGET => t('Insert value from widget...'),
      CONDITIONAL_FIELDS_DEPENDENCY_VALUES_REGEX => t('Regular expression...'),
      t('Set of values') => array(
        CONDITIONAL_FIELDS_DEPENDENCY_VALUES_AND => t('All these values (AND)...'),
        CONDITIONAL_FIELDS_DEPENDENCY_VALUES_OR  => t('Any of these values (OR)...'),
        CONDITIONAL_FIELDS_DEPENDENCY_VALUES_XOR => t('Only one of these values (XOR)...'),
        CONDITIONAL_FIELDS_DEPENDENCY_VALUES_NOT => t('None of these values (NOT)...'),
        // TODO: PHP evaluation
      ),
    ),
    '#default_value' => $dependency['options']['values_set'],
    '#required' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="condition"]' => array('value' => 'value'),
      ),
    ),
  );

  $form['value'] = array(
    '#type' => 'fieldset',
    '#title' => t('Insert value from widget'),
    '#description' => t('The dependency is triggered when the field has exactly the same value(s) inserted in the widget below.'),
    '#states' => array(
      'visible' => array(
        ':input[name="values_set"]' => array(
          'value' => (string) CONDITIONAL_FIELDS_DEPENDENCY_VALUES_WIDGET,
        ),
        ':input[name="condition"]' => array('value' => 'value'),
      ),
    ),
    '#tree' => TRUE,
    'field' => $dummy_field,
  );

  $form['values'] = array(
    '#type' => 'textarea',
    '#title' => t('Set of values'),
    '#description' => t('The values of the dependee %field that trigger the dependency.', array('%field' => $dependee_instance['label'])) . '<br>' . t('Enter one value per line. Note: if the dependee has allowed values, these are actually the keys, not the labels, of those values.'),
    '#default_value' => implode("\n", $dependency['options']['values']),
    '#states' => array(
      'visible' => array(
        ':input[name="values_set"]' => array(
          array('value' => (string) CONDITIONAL_FIELDS_DEPENDENCY_VALUES_AND),
          array('value' => (string) CONDITIONAL_FIELDS_DEPENDENCY_VALUES_OR),
          array('value' => (string) CONDITIONAL_FIELDS_DEPENDENCY_VALUES_XOR),
          array('value' => (string) CONDITIONAL_FIELDS_DEPENDENCY_VALUES_NOT),
        ),
        ':input[name="condition"]' => array('value' => 'value'),
      ),
      'required' => array(
        ':input[name="condition"]' => array('value' => 'value'),
      ),
    ),
  );

  $form['regex'] = array(
    '#type' => 'textfield',
    '#title' => t('Regular expression'),
    '#description' => t('The dependency is triggered when all the values of the dependee %field match the regular expression. The expression should be valid both in PHP and in Javascript. Do not include delimiters.', array('%field' => $dependee_instance['label'])) . '<br>' . t('Note: If the dependee has allowed values, these are actually the keys, not the labels, of those values.'),
    '#maxlength' => 2048,
    '#size' => 120,
    '#default_value' => isset($dependency['options']['value']['RegExp']) ? $dependency['options']['value']['RegExp'] : '',
    '#states' => array(
      'visible' => array(
        ':input[name="values_set"]' => array('value' => (string) CONDITIONAL_FIELDS_DEPENDENCY_VALUES_REGEX),
        ':input[name="condition"]' => array('value' => 'value'),
      ),
      'required' => array(
        ':input[name="values_set"]' => array('value' => (string) CONDITIONAL_FIELDS_DEPENDENCY_VALUES_REGEX),
        ':input[name="condition"]' => array('value' => 'value'),
      ),
    ),
  );

  $form['grouping'] = array(
    '#type' => 'radios',
    '#title' => t('Interaction with other dependencies'),
    '#description' => t('When this dependent has more than one dependee, how should this condition be evaluated against the others?') . '<br />' . t('Note that sets will be grouped this way: (ANDs) AND (ORs) AND (XORs).'),
    '#options' => array('AND' => 'AND', 'OR' => 'OR', 'XOR' => 'XOR'),
    '#default_value' => $dependency['options']['grouping'],
    '#required' => TRUE,
  );

  $entity = entity_get_info($dependee_instance['entity_type']);

  $form['entity_edit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit context settings'),
    '#description' => t('These settings apply when the @entity is being added or edited in a form.', array('@entity' => drupal_strtolower($entity['label']))),
    '#collapsible' => FALSE,
  );

  $form['entity_edit']['state'] = array(
    '#type' => 'select',
    '#title' => t('Form state'),
    '#description' => t('The Javascript form state that is applied to the dependent field when the condition is met. Note: this has no effect on server-side logic and validation.'),
    '#options' => conditional_fields_states(),
    '#default_value' => $dependency['options']['state'],
    '#required' => TRUE,
    '#ajax' => array(
      'callback' => 'conditional_fields_ajax_admin_state_callback',
      'wrapper' => 'effects-wrapper',
    ),
  );

  $effects = $effects_options = array();
  $selected_state = isset($form_state['values']['state']) ? $form_state['values']['state'] : $dependency['options']['state'];
  foreach (conditional_fields_effects() as $effect_name => $effect) {
    if (in_array($selected_state, $effect['states'])) {
      $effects[$effect_name] = $effect['label'];
      if (isset($effect['options'])) {
        $effects_options[$effect_name] = $effect['options'];
      }
    }
  }

  $form['entity_edit']['effects_wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'effects-wrapper',
    ),
  );

  $effect = isset($form_state['values']['effect']) ? $form_state['values']['effect'] : $dependency['options']['effect'];

  if (count($effects) == 1) {
    $effects_keys = array_keys($effects);
    $form['entity_edit']['effects_wrapper']['effect'] = array(
      '#type' => 'hidden',
      '#value' => array_shift($effects_keys),
      '#default_value' => array_shift($effects_keys),
    );
  }
  elseif (count($effects) > 1) {
    $form['entity_edit']['effects_wrapper']['effect'] = array(
      '#type' => 'select',
      '#title' => t('Effect'),
      '#description' => t('The effect that is applied to the dependent when its state is changed.'),
      '#options' => $effects,
      '#default_value' => $effect,
      '#states' => array(
        'visible' => array(
          ':input[name="state"]' => array(
            array('value' => 'visible'),
            array('value' => '!visible'),
          ),
        ),
      ),
    );
  }

  $form['entity_edit']['effects_wrapper']['effect_options'] = array('#tree' => TRUE);

  foreach ($effects_options as $effect_name => $effect_options) {
    foreach ($effect_options as $effect_option_name => $effect_option) {
      $effect_option += array(
        '#title' => t('@effect effect option: @effect_option', array('@effect' => $effects[$effect_name], '@effect_option' => $effect_option_name)),
        '#states' => array(
          'visible' => array(
            ':input[name="effect"]' => array(
              array('value' => $effect_name),
            ),
          ),
        ),
      );

      if (isset($form_state['values']['effect_options'][$effect_name][$effect_option_name])) {
        $effect_option['#default_value'] = $form_state['values']['effect_options'][$effect_name][$effect_option_name];
      }
      elseif ($dependency['options']['effect'] == $effect_name) {
        $effect_option['#default_value'] = $dependency['options']['effect_options'][$effect_option_name];
      }

      $form['entity_edit']['effects_wrapper']['effect_options'][$effect_name][$effect_option_name] = $effect_option;
    }
  }

  $form['entity_edit']['element_edit_per_role'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate per user role settings in edit context'),
    '#description' => t('If the user has more than one role, the first matching role will be used.'),
    '#default_value' => $dependency['options']['element_edit_per_role'],
  );

  $behaviors = conditional_fields_behaviors();

  $form['entity_edit']['element_edit'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Edit context settings for all roles'),
    '#title_display' => 'invisible',
    '#options' => $behaviors['edit'],
    '#default_value' => $dependency['options']['element_edit'],
    '#states' => array(
      'visible' => array(
        ':input[name="element_edit_per_role"]' => array('checked' => FALSE),
      ),
    ),
  );

  $roles = user_roles();
  $element_edit_roles = array('element_edit_roles' => array('#tree' => TRUE));
  foreach ($roles as $rid => $role) {
    $element_edit_roles['element_edit_roles'][$rid] = array(
      '#type' => 'checkboxes',
      '#title' => t('Edit context settings for %role', array('%role' => $role)),
      '#options' => $behaviors['edit'],
      '#default_value' => isset($dependency['options']['element_edit_roles'][$rid]) ? $dependency['options']['element_edit_roles'][$rid] : $dependency['options']['element_edit'],
      '#states' => array(
        'visible' => array(
          ':input[name="element_edit_per_role"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  array_push($form['entity_edit'], $element_edit_roles);

  $form['entity_edit']['dependency_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced edit context settings', array('@entity' => drupal_strtolower($entity['label']))),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $selector_description = t('Only use if you know what you are doing, otherwise leave the field empty to let the dependency use an automatically generated selector.');
  $selector_description .= '<br />' . t('You can use the following placeholders:');
  $selector_description .= "<ul>\n";
  $selector_description .= '<li>' . t('%lang: current language of the field.') . "</li>\n";
  $selector_description .= '<li>' . t('%key: part identifier for fields composed of multiple form elements, like checkboxes.') . "</li>\n";
  $selector_description .= '</ul>';

  $form['entity_edit']['dependency_advanced']['selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom jQuery selector for dependee'),
    '#description' => $selector_description,
    '#default_value' => $dependency['options']['selector'],
  );

  $form['entity_view'] = array(
    '#type' => 'fieldset',
    '#title' => t('View context settings'),
    '#description' => t('These settings apply when the @entity is viewed.', array('@entity' => drupal_strtolower($entity['label']))),
    '#collapsible' => FALSE,
  );

  $form['entity_view']['element_view_per_role'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate per user role settings in view context'),
    '#description' => t('If the user has more than one role, the first matching role will be used.'),
    '#default_value' => $dependency['options']['element_view_per_role'],
  );

  $form['entity_view']['element_view'] = array(
    '#type' => 'checkboxes',
    '#title' => t('View context settings for all roles'),
    '#title_display' => 'invisible',
    '#description' => t('Note: Options that need to evaluate if the dependency is triggered only apply if the condition is "Value".'),
    '#options' => $behaviors['view'],
    '#default_value' => $dependency['options']['element_view'],
    '#states' => array(
      'visible' => array(
        ':input[name="element_view_per_role"]' => array('checked' => FALSE),
      ),
    ),
  );

  $element_view_roles = array('element_view_roles' => array('#tree' => TRUE));
  foreach ($roles as $rid => $role) {
    $element_view_roles['element_view_roles'][$rid] = array(
      '#type' => 'checkboxes',
      '#title' => t('View context settings for %role', array('%role' => $role)),
      '#options' => $behaviors['view'],
      '#default_value' => isset($dependency['options']['element_view_roles'][$rid]) ? $dependency['options']['element_view_roles'][$rid] : $dependency['options']['element_view'],
      '#states' => array(
        'visible' => array(
          ':input[name="element_view_per_role"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  array_push($form['entity_view'], $element_view_roles);

  $form['actions'] = array(
    '#type' => 'actions',
    'save' => array(
      '#type' => 'submit',
      '#value' => t('Save settings'),
    ),
  );

  // Redirect to bundle dependencies form if destination is set.
  $destination = drupal_get_destination();
  if ($destination['destination'] != 'admin/structure/dependencies') {
    $form_state['redirect'] = $destination['destination'];
  }

  return $form;
}

/**
 * Dependency edit form validate.
 *
 * @see conditional_fields_dependency_edit_form()
 */
function conditional_fields_dependency_edit_form_validate($form, &$form_state) {
  if ($form_state['values']['condition'] == 'value') {
    if (in_array($form_state['values']['values_set'], array(CONDITIONAL_FIELDS_DEPENDENCY_VALUES_AND, CONDITIONAL_FIELDS_DEPENDENCY_VALUES_OR, CONDITIONAL_FIELDS_DEPENDENCY_VALUES_XOR, CONDITIONAL_FIELDS_DEPENDENCY_VALUES_NOT)) && drupal_strlen(trim($form_state['values']['values'])) == 0) {
      form_set_error('values', t('!name field is required.', array('!name' => t('Set of values'))));
    }
    elseif ($form_state['values']['values_set'] == CONDITIONAL_FIELDS_DEPENDENCY_VALUES_REGEX && drupal_strlen(trim($form_state['values']['regex'])) == 0) {
      form_set_error('regex', t('!name field is required.', array('!name' => t('Regular expression'))));
    }
  }
}

/**
 * Dependency edit form submit.
 *
 * @see conditional_fields_dependency_edit_form()
 */
function conditional_fields_dependency_edit_form_submit($form, &$form_state) {
  $dependee = $form_state['values']['dependee'];
  $widget_type = $form_state['field'][$dependee][LANGUAGE_NONE]['instance']['widget']['type'];

  // TODO: validate values against allowed values.
  // TODO: unify 'value' and 'values' fields.

  $dependency = array(
    'id'        => $form['#dependency']['id'],
    'dependee'  => $form['#dependency']['dependee'],
    'dependent' => $form['#dependency']['dependent'],
    'options'   => array(
      'state'                 => $form_state['values']['state'],
      'condition'             => $form_state['values']['condition'],
      'grouping'              => $form_state['values']['grouping'],
      'effect'                => isset($form_state['values']['effect']) ? $form_state['values']['effect'] : FALSE,
      'effect_options'        => isset($form_state['values']['effect'], $form_state['values']['effect_options'][$form_state['values']['effect']]) ? $form_state['values']['effect_options'][$form_state['values']['effect']] : array(),
      'element_view'          => $form_state['values']['element_view'],
      'element_view_per_role' => $form_state['values']['element_view_per_role'],
      'element_view_roles'    => $form_state['values']['element_view_roles'],
      'element_edit'          => $form_state['values']['element_edit'],
      'element_edit_per_role' => $form_state['values']['element_edit_per_role'],
      'element_edit_roles'    => $form_state['values']['element_edit_roles'],
      'selector'              => $form_state['values']['selector'],
    ),
  );

  // Store values only if the condition requires them.
  if ($form_state['values']['condition'] == 'value') {

    $dependency['options'] += array(
      'values_set' => $form_state['values']['values_set'],
      // Raw user input is needed to build actual value conditions in the
      // #states array, so we store it in 'value_form'.
      'value_form' => $form_state['input']['value']['field'][$dependee][LANGUAGE_NONE],
    );

    if ($dependency['options']['values_set'] == CONDITIONAL_FIELDS_DEPENDENCY_VALUES_WIDGET) {
      $value = array();
      field_default_extract_form_values(NULL, NULL, array('field_name' => $dependee), NULL, LANGUAGE_NONE, $value, $form['value']['field'], $form_state);
      $dependency['options']['value'] = $value;
    }
    elseif ($dependency['options']['values_set'] == CONDITIONAL_FIELDS_DEPENDENCY_VALUES_REGEX) {
      // The regular expression is inserted in an associative array, so it will
      // be converted to a Javascript object.
      // In states_enhancements.js we will then use the "RegExp" key to
      // distinguish the object and evaluate it as a regular expression.
      $dependency['options']['value'] = array('RegExp' => $form_state['values']['regex']);
    }
    else {
      $values = explode("\n", $form_state['values']['values']);
      $values = array_map('trim', $values);
      $values = array_filter($values, 'strlen');
      $dependency['options']['values'] = $values;
    }
  }

  conditional_fields_dependency_update($dependency);
  drupal_set_message(t('Saved dependency configuration.'));
}

/**
 * Ajax callback for effects list.
 */
function conditional_fields_ajax_admin_state_callback($form, &$form_state) {
  return $form['entity_edit']['effects_wrapper'];
}

/**
 * Confirm form for the deletion of a dependency.
 */
function conditional_fields_dependency_delete_form($form, $form_state, $dependency) {
  $destination = drupal_get_destination();

  return confirm_form(
    array(
    'dependency' => array(
      '#type' => 'value',
      '#value' => $dependency['id'],
    ),
  ),
    t('Are you sure you want to delete this dependency?'),
    $destination['destination'],
    t('This action cannot be undone.'),
    t('Delete dependency'),
    t('Cancel')
  );
}

/**
 * Confirm form submit for the deletion of a dependency.
 */
function conditional_fields_dependency_delete_form_submit($form, &$form_state) {
  conditional_fields_dependency_delete(array($form_state['values']['dependency']));
  drupal_set_message(t('The dependency has been deleted.'));
}

/**
 * Uasort callback; sorts dependencies by group operator and dependee name.
 */
function _conditional_fields_sort_dependees($a, $b) {
  if ($a['options']['grouping'] == $b['options']['grouping']) {
    return strcasecmp($a['dependee'], $b['dependee']);
  }
  return strcasecmp($a['options']['grouping'], $b['options']['grouping']);
}
