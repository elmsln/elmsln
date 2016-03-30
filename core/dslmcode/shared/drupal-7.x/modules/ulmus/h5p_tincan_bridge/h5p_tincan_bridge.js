/**
 * @file
 * Send h5p statements to statement relay
 */
(function ($) {
    Drupal.behaviors.h5pTincanBridge = {
        attach: function (context, settings) {
            if(window.H5P)
            {
                var moduleSettings = settings.h5pTincanBridge;
                H5P.externalDispatcher.on('xAPI', function (event) {
                    var data = {
                        token: moduleSettings.token,
                        statement: JSON.stringify(event.data.statement)
                    };
                    $.post(moduleSettings.relayUrl, data);
                });
            }
        }
    };
}(jQuery));