(function ($) {

  Drupal.behaviors.expireAdmin = {
    attach: function (context, settings) {

      $('fieldset#edit-expire', context).drupalSetSummary(function(context) {
        var vals = [];

        if ($('#edit-expire-node-override-defaults', context).is(':checked')) {
          vals.push(Drupal.t('Node expiration: settings are overriden'));
        }
        else {
          vals.push(Drupal.t('Node expiration: default settings'));
        }

        if ($('#edit-expire-comment-override-defaults', context).length) {
          if ($('#edit-expire-comment-override-defaults', context).is(':checked')) {
            vals.push(Drupal.t('Comment expiration: settings are overriden'));
          }
          else {
            vals.push(Drupal.t('Comment expiration: default settings'));
          }
        }

        return vals.join(', ');
      });

    }
  };

})(jQuery);
