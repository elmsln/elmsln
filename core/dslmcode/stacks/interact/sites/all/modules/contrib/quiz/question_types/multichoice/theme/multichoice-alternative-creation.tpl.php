<?php
/**
 * @file
 * Handles the layout of the choice creation form.
 *
 *
 * Variables available:
 * - $form
 */

?>
<?php
$p = drupal_get_path('module', 'multichoice');
drupal_add_js($p .'/theme/multichoice-alternative-creation.js', 'module');

// Get the title from the checkbox, and then unset it. We will place it as a table header
$title_correct = check_plain($form['correct']['#title']);
unset($form['correct']['#title']);

// We have to add the required symbol manually
$suf = $form['answer']['#required'] ? '<SPAN CLASS="form-required"> *</SPAN>' : '';

// We store the title for the answer section as well
$title_answer = check_plain($form['answer']['#title']).$suf;
$form['answer']['#title'] = '';

// Now we can render the table
$row[] = drupal_render($form['correct']);
$row[] = drupal_render($form['answer']);
$rows[] = $row;
$header[] = array('data' => $title_correct);
$header[] = array('data' => $title_answer);
print theme('table', array('header' => $header, 'rows' => $rows));

//These lines make things look alot beter if user only has one input format available:
_quiz_format_mod($form['format']);
_quiz_format_mod($form['advanced']['format']);
_quiz_format_mod($form['advanced']['helper']['format']);

print drupal_render($form['format']);
print drupal_render($form['advanced']);
?>
