/**
 * @file
 * Send h5p statements to statement relay
 */
(function ($) {
  var xapi_events = new Array();
  Drupal.behaviors.h5pTincanBridge = {
    attach: function (context, settings) {
      if (window.H5P) {
        var moduleSettings = settings.h5pTincanBridge;
        H5P.externalDispatcher.on('xAPI', function (event) {
            // support reduction in redundant statements being created
            // this helps with subContentId's such as paged interactions
            // which have multiple content types per "page" from spitting
            // out an overwhelming number of xAPI statements. For example,
            // every key someone presses in an input field or every checkbox
            // selected for a single question in a long quiz
            if (moduleSettings.reduceStatements == true) {
              // capture and wait on triggering subContent interactions to prevent flooding
              if (event.data.statement.verb.id == 'http://adlnet.gov/expapi/verbs/interacted' && event.data.statement.object.definition.extensions.hasOwnProperty("http://h5p.org/x-api/h5p-subContentId") == true) {
                xapi_events.push(event);
              }
              else {
                // see if we've been delaying any sub-statements from sending
                if (xapi_events.length > 0) {
                  // only send the last one
                  var subevent = xapi_events.pop();
                  var delayeddata = {
                    token: moduleSettings.token,
                    statement: JSON.stringify(subevent.data.statement),
                    nid: moduleSettings.nid,
                    tincanapiSettings: Drupal.settings.tincanapi
                  };
                  $.post(moduleSettings.relayUrl, delayeddata);
                  xapi_events = new Array();
                }
                // build the data
                var data = {
                  token: moduleSettings.token,
                  statement: JSON.stringify(event.data.statement),
                  nid: moduleSettings.nid,
                  tincanapiSettings: Drupal.settings.tincanapi
                };
                $.post(moduleSettings.relayUrl, data);
              }
            }
            else {
              // build the data
              var data = {
                token: moduleSettings.token,
                statement: JSON.stringify(event.data.statement),
                nid: moduleSettings.nid,
                tincanapiSettings: Drupal.settings.tincanapi
              };
              $.post(moduleSettings.relayUrl, data);
            }
        });
      }
    }
  };
}(jQuery));