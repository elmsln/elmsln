<?php
/**
 * @file
 * Masonry reaction for Context module.
 */

/**
 * Adds Masonry javascript to the page.
 */
class context_reaction_masonry extends context_reaction {

  /**
   * Masonry settings form.
   */
  function options_form($context) {
    $form = array();
    $settings = $this->fetch_from_context($context);

    // Get default Masonry options
    $settings += masonry_default_options();

    $form['container'] = array(
      '#type' => 'textfield',
      '#title' => t('Container'),
      '#default_value' => isset($settings['container']) ? $settings['container'] : NULL,
      '#description' => t('The jQuery selector of the Masonry container (ie, .region-content-inner).'),
    );
    $form['item'] = array(
      '#type' => 'textfield',
      '#title' => t('Item selector'),
      '#default_value' => isset($settings['item']) ? $settings['item'] : NULL,
      '#description' => t('The jQuery selector of the Masonry item container (ie, section).'),
    );

    // Add Masonry options to an existing form
    masonry_options_form($form, $settings);

    $form['masonry_animated_duration']['#states'] = array(
      'visible' => array(
        'input.form-checkbox[name$="[masonry_animated]"]' => array('checked' => TRUE),
      ),
    );

    return $form;
  }

  /**
   * Execution callback.
   */
  function execute() {
    $script = '';
    $styles = '';

    foreach ($this->get_contexts() as $delta => $context) {
      if (!empty($context->reactions['masonry'])) {
        $settings = $context->reactions['masonry'];

        // Add default styling to make grids display properly out-of-the-box
        $css_margin = ($settings['masonry_width_unit'] == 'px') ? '10px' : '2%';
        $css_width = ($settings['masonry_width_unit'] == 'px') ? ($settings['masonry_width'] - 20) . 'px' : ($settings['masonry_width'] - 5) . '%';
        $styles .= '
          ' . $settings['container'] . ' ' . $settings['item'] . ' {
            float: left;
            margin: ' . $css_margin . ';
            width: ' . $css_width . ';
          }
        ';
        if ($settings['masonry_center']) {
          $styles .= '
            ' . $settings['container'] . ' ' . $settings['item'] . ' {
              margin: 0 auto;
            }
          ';
        }

        // Get column width
        if ($settings['masonry_width_unit'] == 'px') {
          $column_width = (int) $settings['masonry_width'];
        }
        else {
          $percentage = $settings['masonry_width'] / 100;
          $column_width = 'function (containerWidth) {
            return containerWidth * ' . $percentage . ';
          }';
        }

        $script .= '
          $("' . $settings['container'] . '").imagesLoaded(function () {
            $("' . $settings['container'] . '").masonry({
              itemSelector: "' . $settings['item'] . '",
              columnWidth: ' . $column_width . ',
              isAnimated: ' . (int) $settings['masonry_animated'] . ',
              animationOptions: {
                duration: ' . (int) $settings['masonry_animated_duration'] . '
              },
              isResizable: ' . (int) $settings['masonry_resizable'] . ',
              isFitWidth: ' . (int) $settings['masonry_center'] . ',
              gutterWidth: ' . (int) $settings['masonry_gutter'] . ',
              isRTL: ' . (int) $settings['masonry_rtl'] . '
            });
          });
        ';
      }
    }

    // Initialize Masonry
    if (!empty($script) && ($library = libraries_load('masonry')) && !empty($library['loaded'])) {
      $script = '(function ($) { ' . $script . ' })(jQuery);';
      drupal_add_css($styles, 'inline');
      drupal_add_js($script, array(
        'type' => 'inline',
        'scope' => 'footer',
      ));
    }
  }
}

