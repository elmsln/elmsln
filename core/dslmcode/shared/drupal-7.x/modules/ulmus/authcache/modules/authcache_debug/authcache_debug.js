(function (Drupal, $) {
  "use strict";

  // Private variables
  var ajaxCount = 0;
  var timeStart = new Date().getTime();
  var cacheRenderTime = null;
  var status = {
    'Cache Status': 'Debug info pending',
  };
  var info = {};

  //
  // Private helper functions
  //
  function isNumeric(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
  }

  /**
   * Inject authcache debug widget into the page
   */
  function widget() {
    $("body").prepend("<div id='authcachedbg' style='max-width: 80em;'><div id='authcache_status_indicator'></div><strong><a href='#' id='authcachehide'>Authcache Debug</a></strong><div id='authcachedebug' style='display:none;'><div id='authcachedebuginfo'></div></div></div>");
    $("#authcachehide").click(function() {
      $("#authcachedebug").toggle();
      return false;
    });

    // Determine the render time if cache_render cookie is set.
    if ($.cookie("cache_render") && $.cookie("cache_render") !== "get") {
      cacheRenderTime = $.cookie("cache_render");
    }

    updateInfoFieldset();

    debugTimer();
  }

  /**
   * Update the info fieldset.
   */
  function updateInfoFieldset() {
    var alertColor = null;

    if (info.cacheStatus) {
      status['Cache Status'] = info.cacheStatus;

      if (info.cacheStatus === 'HIT') {
        alertColor = 'green';
      }
      else if (info.cacheStatus === 'MISS') {
        alertColor = 'orange';
      }
      else {
        alertColor = 'red';
      }
    }

    if (info.messages) {
      $.each(info.messages, function(idx, msg) {
        status['Message ' + (idx + 1)] = msg.label + ': ' + msg.message;
      });
    }

    // Determine page render time
    if (info.pageRender) {
      status["Page Render Time"] = info.pageRender + " ms";
    }

    if (info.cacheStatus === 'HIT' && cacheRenderTime !== null) {
      status["Cache Render Time"] = cacheRenderTime;

      if (isNumeric(cacheRenderTime)) {
        status["Cache Render Time"] += " ms";

        if (cacheRenderTime > 30) {
          alertColor = 'orange';
        }
        else if (cacheRenderTime > 100) {
          alertColor = 'red';
        }
      }
    }

    if (isNumeric(cacheRenderTime)) {
      status.Speedup = Math.round((info.pageRender - cacheRenderTime) / cacheRenderTime * 100).toString().replace(/(\d+)(\d{3})/, '$1' + ',' + '$2') + "% increase";
    }

    // Add some more settings and status information
    if (info.cacheTime) {
      status["Page Age"] = Math.round(timeStart / 1000 - info.cacheTime) + " seconds";
    }

    if (alertColor !== null) {
      $("#authcache_status_indicator").css({"background": alertColor});
    }

    $("#authcachedebuginfo").first().html(debugFieldset("Status", status));
    $("#authcachedebuginfo").first().append(debugFieldset("Settings", info));
  }

  /**
   * Display total JavaScript execution time for this file (including Ajax)
   */
  function debugTimer() {
    var timeMs = new Date().getTime() - timeStart;
    $("#authcachedebug").append("HTML/JavaScript time: " + timeMs + " ms <hr size=1>");
  }

  /**
   * Helper function (renders HTML fieldset)
   */
  function debugFieldset(title, jsonData) {
    var fieldset = '<div style="clear:both;"></div><fieldset style="float:left;min-width:240px;"><legend>' + title + '</legend>';
    $.each(jsonData, function(key, value) {
      if (key[0] !== key[0].toLowerCase()){
        fieldset += "<strong>" + key + "</strong>: " + JSON.stringify(value) + '<br>';
      }
    });
    fieldset += '</fieldset><div style="clear:both;">';
    return fieldset;
  }

  function isEnabled(settings) {
    return (settings.authcacheDebug && ($.cookie('aucdbg') !== null || settings.authcacheDebug.all) && typeof JSON === 'object');
  }

  // Add debug info to widget
  Drupal.behaviors.authcacheDebug = {
    attach: function (context, settings) {
      $('body').once('authcache-debug', function() {
        if (!isEnabled(settings)) {
          return;
        }

        widget();

        $.get(settings.authcacheDebug.url, function(data) {
          info = $.extend(info, data);

          updateInfoFieldset();

          $.authcache_cookie("aucdbg", Math.floor(Math.random()*65535).toString(16));
        });
      });
    }
  };

  $(window).load(function() {
    if (isEnabled(Drupal.settings)) {
      // Reset debug cookies only after all subrequests (images, JS, CSS) are completed.
      $.authcache_cookie("cache_render", "get");
    }
  });
}(Drupal, jQuery));
