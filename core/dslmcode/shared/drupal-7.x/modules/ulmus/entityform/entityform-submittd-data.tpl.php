<?php

/**
 * @file
 * A basic template for entityform submitted data
 *
 * Available variables:
 * - $fields: An array of fields. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $date: The date of the entityform submission.
 * - $name: The username of the suer that submitted the entityform.
 * - $url: The standard URL for viewing the entityform entity
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>

<p><?php print t('Submitted on !date', array('!date' => $date)) ?><br/>
<?php print t('Submitted by user: !name', array('!name' => $name)); ?><br/>
<?php print t('Submitted values are:'); ?></p>

<?php foreach ($fields as $field): ?>
<h2><?php print $field['#title']; ?>:</h2>
<p><?php print render($field); ?></p>
<?php endforeach; ?>

<?php if ($url): ?>
  <?php print t('The results of this submission may be viewed at: !url', array('!url' => $url)); ?>
<?php endif; ?>