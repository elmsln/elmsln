(function ($) {
  Drupal.behaviors.features_override_form = {
    attach: function(context, settings) {
      $('#edit-sources-features-overrides:not(.features-override-processed)', context)
        .prepend(Drupal.t('Advanced usage only. Allows you to select individual changes only to export.'))
        .addClass('features-override-processed');

      $('input[type=checkbox][name^="sources[features_override_items]"]:not(.features-override-form-processed)', context).each(function (i) {
        var $parent_checkbox = $(this);
        $parent_checkbox.addClass('features-override-form-processed');
        var $parent_label = $parent_checkbox.parent().find('label');
        // Create a link that links to the exact differences from the label.
        if (Drupal.settings.features_override_links['main'][this.value]) {
          $parent_label.append('<a href="' + Drupal.settings.features_override_links['main'][this.value] + '" target="_blank" class="features_override_button">' + Drupal.t('view') + '</a>');
        }

        var $child_checkboxes = $('input[type=checkbox][name^="sources[features_overrides]"][value^="' + this.value + '"]').each(function (i) {
          if (Drupal.settings.features_override_links['sub'][this.value]) {
            $($(this).parent()).find('label').append('<a href="' + Drupal.settings.features_override_links['sub'][this.value] + '" target="_blank" class="features_override_button">' + Drupal.t('view') + '</a>');
          }
        }).parents('div.form-type-checkbox');
        $child_checkboxes.wrapAll('<div class="features-override-children-wrapper" id="' + this.id + '-wrapper"></div>');
        var $wrapper = $child_checkboxes.parent();

        // Prepend a label saying what these overrides are for.
        $wrapper.before('<h4>' + Drupal.t('Individual overrides for: ') + $parent_label.html() + '</h4>');
        var fotext = Drupal.t('Full overrides already exported for this item to this feature.')
          + ' '
          + '<a href="#" id="' + this.id + '-refine" class="features_override_button">' + Drupal.t('refine') + '</a>';
        $wrapper.after('<div class="features-override-children-warning" id="' + this.id + '-warning">' + fotext + '</div>');

        // Unchecks the items component to allow indivudal refinment if desired.
        $('#' + this.id + '-refine').bind('click', {id : this.id}, function(event) {
          $('#' + event.data.id).removeAttr('checked').trigger('change');
          return false;
        });

        // Disable child checkboxes when parent is selected
        $parent_checkbox.change(function() {
          features_override_switch_child_info(this.id, this.checked);
        });
        features_override_switch_child_info(this.id, this.checked);
      });
    }
  }
  function features_override_switch_child_info(id, is_checked) {
    if (is_checked) {
      // Jquery bug that hide() doesn't always work when parent hidden.
      $('#' + id + '-wrapper').css('display', 'none');
      $('#' + id + '-warning').css('display', 'block');
    }
    else {
      $('#' + id + '-wrapper').show();
      $('#' + id + '-warning').css('display', 'none');
    }
  }
})(jQuery);
