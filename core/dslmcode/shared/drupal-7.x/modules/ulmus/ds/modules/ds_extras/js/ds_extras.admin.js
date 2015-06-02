/**
 * @file
 * Javascript functionality for the Display Suite Extras administration UI.
 */

(function ($) {

Drupal.behaviors.DSExtrasSummaries = {
  attach: function (context) {

    $('#edit-additional-settings-fs1', context).drupalSetSummary(function (context) {
      var fieldtemplates = $('#edit-additional-settings-fs1-ds-extras-field-template', context);

      if (fieldtemplates.is(':checked')) {
        var fieldtemplate = $('#edit-additional-settings-fs1-ft-default option:selected').text();
        return Drupal.t('Enabled') + ': ' + Drupal.t(fieldtemplate);
      }

      return Drupal.t('Disabled');
    });

    $('#edit-additional-settings-fs2', context).drupalSetSummary(function (context) {
      var extra_fields = $('#edit-additional-settings-fs2-ds-extras-fields-extra', context);

      if (extra_fields.is(':checked')) {
        return Drupal.t('Enabled');
      }

      return Drupal.t('Disabled');
    });

    $('#edit-additional-settings-fs4', context).drupalSetSummary(function (context) {
      var vals = [];

      $('input:checked', context).parent().each(function () {
        vals.push(Drupal.checkPlain($.trim($('.option', this).text())));
      });

      if (vals.length > 0) {
        return vals.join(', ');
      }
      return Drupal.t('Disabled');
    });
  }
};

/**
 * Field template.
 */
Drupal.behaviors.settingsToggle = {
  attach: function (context) {

    // Bind on click.
    $('.field-formatter-settings-edit-form', context).once('ds-ft', function() {

      var fieldTemplate = $(this);

      // Bind on field template select button.
      fieldTemplate.find('.ds-extras-field-template').change(function() {
        ds_show_expert_settings(fieldTemplate);
      });

      ds_show_expert_settings(fieldTemplate);

    });

    // Show / hide settings on field template form.
    function ds_show_expert_settings(element, open) {
      field = element;
      ft = $('.ds-extras-field-template', field).val();

      if (ft == 'theme_ds_field_expert') {
        // Show second, third, fourth, fifth and sixth label.
        if ($('.lb .form-item:nth-child(1)', field).is(':visible')) {
          $('.lb .form-item:nth-child(2), .lb .form-item:nth-child(3), .lb .form-item:nth-child(4), .lb .form-item:nth-child(5), .lb .form-item:nth-child(6)', field).show();
        }
        // Remove margin from update button.
        $('.ft-update', field).css({'margin-top': '-10px'});
        // Show wrappers.
        $('.lbw, .ow, .fis, .fi', field).show();
        // Show prefix and suffix
        $('.field-prefix', field).show();
        $('.field-suffix', field).show();
      }
      else {
        // Hide second, third, fourth, fifth and sixth  label.
        $('.lb .form-item:nth-child(2), .lb .form-item:nth-child(3), .lb .form-item:nth-child(4), .lb .form-item:nth-child(5), .lb .form-item:nth-child(6)', field).hide();
        // Add margin on update button.
        $('.ft-update', field).css({'margin-top': '10px'});
        // Hide wrappers.
        $('.lbw, .ow, .fis, .fi', field).hide();
        // Hide prefix and suffix
        $('.field-prefix', field).hide();
        $('.field-suffix', field).hide();
      }

      // Colon.
      if (ft == 'theme_field' || ft == 'theme_ds_field_reset') {
        $('.colon-checkbox', field).parent().hide();
      }
      else if ($('.lb .form-item:nth-child(1)', field).is(':visible')) {
        $('.colon-checkbox', field).parent().show();
      }

      // CSS classes.
      if (ft != 'theme_ds_field_expert' && ft != 'theme_ds_field_reset') {
        $('.field-classes', field).show();
      }
      else {
        $('.field-classes', field).hide();
      }
    }

    $('.label-change').change(function() {
      var field = $(this).parents('tr');
      if ($('.field-template', field).length > 0) {
        ft = $('.ds-extras-field-template', field).val();
        if (ft == 'theme_field' || ft == 'theme_ds_field_reset') {
          $('.colon-checkbox', field).parent().hide();
        }
      }
    });
  }
};

})(jQuery);
