INSTALLATION

- Install libraries module (dependency).
- Download jQuery-Placeholder library from https://github.com/mathiasbynens/jquery-placeholder
- Place this library in sites/[all/sitename/default]/libraries/placeholder
  so the jquery.placeholder.js is located at sites/[all/sitename/default]/libraries/placeholder/jquery.placeholder.js
  or glone directly; 'git clone --recursive https://github.com/mathiasbynens/jquery-placeholder placeholder'
  in your libraries folder.

USAGE

- Add a '#placeholder' key or a 'placeholder' element to the '#attributes'
  array of textfields or textareas.

EXAMPLES

---------------- BASIC EXAMPLE ---------------
/**
 * Implements hook_form_FORM_ID_alter().
 */
function placeholder_form_search_block_form_alter(&$form, &$form_state) {
  $form['search_block_form']['#placeholder'] = t('Search here');
  // or ....
  $form['search_block_form']['#attributes']['placeholder'] = t('Search here');
}

function my_custom_module_form() {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Name',
    '#placeholder' => t('Enter your name here'),
  );
  // ....
}

--------------- ANOTHER EXAMPLE -----------------
/**
 * Implements hook_form_alter().
 */
function mymodule_form_alter(&$form, &$form_state, $form_id) {
  // Add placeholder for link fields
  if (isset($form['field_link_url'])) {
    $form['#after_build'][] = 'mymodule_link_field_after_build';
  }
}
function mymodule_link_field_after_build($form, &$form_state) {
  if (module_exists('placeholder')){

    $lang = isset($form['field_link_url']['#language']) ? $form['field_link_url']['#language'] : LANGUAGE_NONE;
    if (isset($form['field_link_url'][$lang])) {
      // Go through each delta
      foreach($form['field_link_url'][$lang] as $delta => $item) {
        // Make sure this is a delta and not just another element.
        // Gross, but there's no clean list of delta items.
        if (is_numeric($delta)) {
          // Sanity check to make sure this is properly formed.
          if (isset($form['field_link_url'][$lang][$delta]['url'])) {
            // Add the placeholder as an attribute, because otherwise it doesn't work.
            $form['field_link_url'][$lang][$delta]['url']['#attributes']['placeholder'] = t('http://www.example.com');
          }
        }
      }
    }

    // Add the library, if it's available.
    if (($library = libraries_load('placeholder', 'minified')) && !empty($library['loaded'])) {
      // Attach the library files.
      libraries_load_files($library);
      // Attach the module js file. This will actually invoke the library.
      $element['#attached']['js'] = array(
        drupal_get_path('module', 'placeholder') . '/placeholder.js',
      );
    }

  }
  return $form;
}

