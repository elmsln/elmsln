/**
 * @file
 * Extends the Insert module to validate the ALT and TITLE tags.
 */

(function ($) {
  $(document).bind('insertIntoActiveEditor', function(event, options) {
    if (!options['fields']['alt'] && Drupal.settings.eim.altRequired[0]) {
      // Alert the user and clear the inserted content.
      alert(Drupal.t("You must enter an ALT value for this image before inserting."));
      options['content'] = '';
    }
    if (!options['fields']['title'] && Drupal.settings.eim.titleRequired[0]) {
      // Alert the user and clear the inserted content.
      alert(Drupal.t("You must enter a TITLE value for this image before inserting."));
      options['content'] = '';
    }
  });
})(jQuery);
