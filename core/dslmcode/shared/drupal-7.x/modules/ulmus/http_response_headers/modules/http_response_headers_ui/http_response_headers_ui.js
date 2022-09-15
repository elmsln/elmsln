(function ($) {

    /**
     * Provide the summary information for the header rule settings vertical tabs.
     */
    Drupal.behaviors.HttpHeaderRulesSettingsSummary = {
        attach: function (context) {
            // The drupalSetSummary method required for this behavior is not available
            // on the Blocks administration page, so we need to make sure this
            // behavior is processed only if drupalSetSummary is defined.
            if (typeof jQuery.fn.drupalSetSummary == 'undefined') {
                return;
            }

            $('fieldset#edit-path', context).drupalSetSummary(function (context) {
                if (!$('textarea[name="pages"]', context).val()) {
                    return Drupal.t('Not restricted');
                }
                else {
                    return Drupal.t('Restricted to certain pages');
                }
            });

            $('fieldset#edit-node-type', context).drupalSetSummary(function (context) {
                var vals = [];
                $('input[type="checkbox"]:checked', context).each(function () {
                    vals.push($.trim($(this).next('label').text()));
                });
                if (!vals.length) {
                    vals.push(Drupal.t('Not restricted'));
                }
                return vals.join(', ');
            });

            $('fieldset#edit-role', context).drupalSetSummary(function (context) {
                var vals = [];
                $('input[type="checkbox"]:checked', context).each(function () {
                    vals.push($.trim($(this).next('label').text()));
                });
                if (!vals.length) {
                    vals.push(Drupal.t('Not restricted'));
                }
                return vals.join(', ');
            });

            $('fieldset#edit-user', context).drupalSetSummary(function (context) {
                var $radio = $('input[name="custom"]:checked', context);
                if ($radio.val() == 0) {
                    return Drupal.t('Not customizable');
                }
                else {
                    return $radio.next('label').text();
                }
            });
        }
    };
});
