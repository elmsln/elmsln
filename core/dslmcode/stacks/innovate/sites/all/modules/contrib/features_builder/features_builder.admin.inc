<?php

/**
 * @file
 * Features Builder administrative page callbacks.
 */

/**
 * Form to initiate build process.
 */
function features_builder_admin_build_form() {
  $form = array();

  $args = array('!link' => l(t('builders'), 'admin/structure/features/build/builders'));
  $form['build'] = array(
    '#type' => 'fieldset',
    '#title' => t('Build'),
    '#description' => t('Generate Features modules based on the !link installed.', $args),
  );
  $form['build']['enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#description' => t('Enable all Features Builder generated feature modules.'),
  );
  $form['build']['build'] = array(
    '#type' => 'submit',
    '#value' => t('Build'),
    '#submit' => array('features_builder_admin_build_form_build'),
  );

  return $form;
}

/**
 * Submit callback for initiating a build.
 */
function features_builder_admin_build_form_build($form, $form_state) {
  $options['enable'] = !empty($form_state['values']['enable']);
  $batch = features_builder_prep_batch($options);
  batch_set($batch);
}

/**
 * Page callback for displaying feature builders.
 */
function features_builder_admin_build() {

  $builders = features_builder_get_builders();

  $rows = array();

  foreach ($builders as $builder) {
    $row = array(check_plain($builder['label']));

    // List the features modules provided by the builder.
    $items = array();
    foreach ($builder['class']::listFeatures() as $name => $feature) {
      $label = l($feature, "admin/structure/features/build/{$builder['name']}/$name");
      $items[] = t('!label (@name)', array('!label' => $label, '@name' => $name));
    }
    if (count($items) > 0) {
      $row[] = theme('item_list', array('items' => $items));
    }
    else {
      $row[] = t('No features provided.');
    }

    $rows[] = $row;
  }

  return array(
    '#theme' => 'table',
    '#header' => array(t('Builder'), t('Features Modules')),
    '#rows' => $rows,
    '#empty' => t('No features builders available.')
  );
}

/**
 * Page callback for displaying a builder's feature.
 */
function features_builder_admin_builder($builder, $feature) {
  drupal_set_title(t('Builder: !label', array('!label' => $builder['label'])));
  $builder_class = features_builder_get_class($builder['name'], $feature);

  $included_components = $builder_class->components();

  $output = array();

  $exportables = features_builder_get_exportables();
  foreach ($exportables as $component => $exportable) {
    // Get the included exportables for this component.
    $included = (!empty($included_components[$component])) ? $included_components[$component] : array();

    $count = count($exportables[$component]);
    $count_included = count($included);

    $output[$component] = array(
      '#type' => 'fieldset',
      '#title' => check_plain($component),
      '#access' => $count,
    );
    $output[$component]['included'] = array(
      '#prefix' => '<div class="features-builder-2col">',
      '#suffix' => '</div>',
    );
    $output[$component]['not_included'] = array(
      '#prefix' => '<div class="features-builder-2col">',
      '#suffix' => '</div>',
    );
    $output[$component]['included']['head'] = array(
      '#markup' => t('Included'),
      '#prefix' => '<h3>',
      '#suffix' => '</h3>',
    );
    $output[$component]['not_included']['head'] = array(
      '#markup' => t('Not Included'),
      '#prefix' => '<h3>',
      '#suffix' => '</h3>',
    );

    if ($included) {
      $output[$component]['#title'] .= " ($count_included/$count)";
      // $included_components[$component]
      $output[$component]['included']['list'] = array(
        '#theme' => 'item_list',
        '#items' => $included,
      );
    }
    else {
      $output[$component]['#title'] .= " ($count)";
      $output[$component]['included']['list'] = array(
        '#markup' => t('No exportables of this type are included.'),
      );
    }

    // Info on exportables not included in this component.
    $not_included = array_diff_key($exportables[$component], $included);
    if ($not_included) {
      $output[$component]['not_included']['list'] = array(
        '#theme' => 'item_list',
        '#items' => $not_included,
      );
    }
    else {
      $output[$component]['not_included']['list'] = array(
        '#markup' => t('All exportables of this type are included.'),
      );
    }
    $output[$component]['#attributes']['class'][] = 'collapsible';
    $output[$component]['#attributes']['class'][] = 'collapsed';
  }

  $output['#attached']['library'][] = array('system', 'drupal.collapse');
  $output['#attached']['css'][] = drupal_get_path('module', 'features_builder') . '/features_builder.css';

  return $output;
}

/**
 * 
 */
function features_builder_config_form() {
  $form = array();

  $form['features_builder_prefix_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Prefix'),
    '#description' => t('Titles for generated Features modules will be prefixed with this value.'),
    '#default_value' => variable_get('features_builder_prefix_label'),
    '#required' => TRUE,
  );

  $form['features_builder_prefix_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Machine Name Prefix'),
    '#description' => t('Machine names for generated Features modules will be prefixed with this value.'),
    '#default_value' => variable_get('features_builder_prefix_name'),
    '#machine_name' => array(
      'exists' => 'user_access',
      'source' => array('features_builder_prefix_label'),
    ),
    '#required' => TRUE,
  );

  $form['features_builder_base_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Base Directory'),
    '#default_value' => variable_get('features_builder_base_dir'),
  );

  $text = 'Enter components which Features Builder will ignore when creating features modules. Enter one per line, in the format :format';
  $args = array(':format' => t('component_type|component_name'));
  $form['features_builder_ignore'] = array(
    '#type' => 'textarea',
    '#title' => t('Ignored components'),
    '#description' => t($text, $args),
    '#default_value' => variable_get('features_builder_ignore'),
  );

  return system_settings_form($form);
}

/**
 * 
 */
function features_builder_exportable_listing() {

  $exportables = features_builder_get_exportables();

  // We're not interested in reporting these.
  unset($exportables['dependencies']);
  unset($exportables['field']);

  $included = features_builder_get_included_exportables();
  $items = features_builder_get_exportables_counts();

  // Set up the outer shell of the vertical tabs and fieldsets.
  $output = array();
  $output['tabs'] = array(
    '#type' => 'vertical_tabs',
  );

  $states = features_builder_exportable_count_states();
  foreach (array_keys($states) as $state) {
    $output['tabs'][$state] = array(
      '#type' => 'fieldset',
      '#title' => $states[$state],
      '#group' => 'tabs',
    );

    // Build the tables into the fieldsets.
    foreach (array_keys($exportables) as $component) {
      if (!empty($items[$state][$component])) {
        $rows = array();
        foreach ($items[$state][$component] as $name => $label) {
          $row = array(check_plain("$label ($name)"));
          switch ($state) {
            case 'included':
              $keys = array_keys($included[$component][$name]);
              $key = reset($keys);
              $row[] = $included[$component][$name][$key];
              break;
            case 'duplicated':
              $row[] = theme('item_list', array('items' => $included[$component][$name]));
          }
          $rows[] = $row;
        }
        $output['tabs'][$state][$component] = array(
          '#theme' => 'table',
          '#caption' => $component,
          '#header' => array(t('Component')),
          '#rows' => $rows,
        );

        if ($state != 'not_included') {
          $output['tabs'][$state][$component]['#header'][] = t('Provided by');
        }
      }
    }
  }

  return $output;
}
