<?php
/**
 * @file
 * Default theme implementation for the typo reports form.
 *
 * Available variables:
 * - $typo_report_form: typo report form made from typo_report_form().
 *
 * @see template_preprocess()
 * @see template_preprocess_typo_report()
 */
?>
<div id="typo-report-content">
  <div id="typo-report-message">
    <div id="typo-message">
<?php
      print t('You are reporting a typo in the following text:');
?>
      <div id="typo-context-div"></div>
<?php
      print t('Simply click the "Send typo report" button to complete the report. You can also include a comment.');
?>
    </div>
    <div id="typo-form">
<?php
    print $typo_report_form;
?>
    </div>
  </div>
  <div id="typo-report-result" style="display: none;">
  </div>
</div>
<div id="tmp"></div>