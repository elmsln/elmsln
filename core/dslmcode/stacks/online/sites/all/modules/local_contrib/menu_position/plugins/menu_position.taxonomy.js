(function ($) {

/**
 * Provide the summary information for the taxonomy plugin's vertical tab.
 */
Drupal.behaviors.menuPositionTaxonomy = {
  attach: function (context) {
    $('fieldset#edit-taxonomy', context).drupalSetSummary(function (context) {
      if ($('input[name="term"]', context).val()) {
        return Drupal.t('Taxonomy: %term', {'%term' : $('input[name="term"]', context).val()});
      }
      else if ($('select[name="vid"]', context).val() != 0) {
        return Drupal.t('Vocabulary: %vocab', {'%vocab' : $('select[name="vid"] option:selected', context).text()});
      }
      else {
        return Drupal.t('Any vocabulary or taxonomy');
      }
    });
    // Reset the taxonomy term autocomplete object when the vocabulary changes.
    $('fieldset#edit-taxonomy #edit-vid', context).change(function () {
      $input = $('#edit-term');
      // Remove old terms.
      $input.val('');
      // Unbind the original autocomplete handlers.
      $input.unbind('keydown');
      $input.unbind('keyup');
      $input.unbind('blur');
      // Set new autocomplete handlers.
      uri = Drupal.settings.menu_position_taxonomy_url + '/' + $(this).val();
      $('#edit-term-autocomplete').val(uri);
      new Drupal.jsAC($input, new Drupal.ACDB(uri));
    });
  }
};

})(jQuery);
