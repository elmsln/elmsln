(function ($) {

/**
 * Attach schemaorg behavior for autocomplete.
 */
Drupal.behaviors.schemaorgs = {
  attach: function(context) {
    $.getJSON(Drupal.settings.schemaorguiapiTermsPath, function(data) {
      $("input.schemaorg-ui-autocomplete-types").autocomplete({
        source: data.types,
        delay: 0,
      });
      $("input.schemaorg-ui-autocomplete-properties").autocomplete({
        source: data.properties,
        delay: 0,
      });
   });

  }
};


})(jQuery);
