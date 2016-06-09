/**
 * @file
 *
 * Custom module js file.
 */

(function ($) {
  //extend the drupal js object by adding in an voicecommander name-space
  Drupal.voicecommander = Drupal.voicecommander || { functions: {} }
  // go to a link, this is most common
  Drupal.voicecommander.goTo = function(phrase) {
    window.location.href = Drupal.settings.basePath + Drupal.settings.voiceCommanderVoiceCommands[phrase].data;
  };
  Drupal.voicecommander.goToELMSLN = function(phrase) {
    window.location.href = Drupal.settings.voiceCommanderVoiceCommands[phrase].data;
  };
  // go backward in history
  Drupal.voicecommander.back = function(phrase) {
    window.location.href = window.history.back();
  };
  // go forward in history
  Drupal.voicecommander.forward = function(phrase) {
    window.location.href = window.history.forward();
  };
  // voice based scrolling capabilities
  Drupal.voicecommander.scroll = function(phrase) {
    // travel back up the screen
    var height = $(window).height();
    if (phrase.indexOf('up') !== -1) {
      $('html, body').animate({
        scrollTop: ($(window).scrollTop()-(height*0.75))
      }, 500);
    }
    // travel to the top of the screen
    else if (phrase.indexOf('top') !== -1) {
      $('html, body').animate({
          scrollTop: (0)
      }, 500);
    }
    // travel down the screen, one screen height
    else {
      $('html, body').animate({
        scrollTop: ($(window).scrollTop()+(height*.75))
      }, 500);
    }
  }
  $(document).ready(function() {
    var config = this.config;
    var commands = {};
    if (undefined !== annyang && annyang !== null) {

      // Define callbacks.
      annyang.addCallback('error', function () {
        showMessage(Drupal.settings.errorCallback);
      });
      annyang.addCallback('errorNetwork', function () {
        showMessage(Drupal.settings.errorNetworkCallback);
      });
      annyang.addCallback('errorPermissionBlocked', function () {
        showMessage(Drupal.settings.permissionBlockedCallback);
      });
      annyang.addCallback('errorPermissionDenied', function () {
        showMessage(Drupal.settings.permissionDeniedCallback);
      });

      function showMessage(message) {
        if (isMobile) {
          $('.voicecommander-mobile .message-area > div.vc-message').text(message);
        } else {
          $('body').addClass('voicecommander');
          $('.voice-commander-rec-window > p').addClass('speak').text(message);

          out = setTimeout(function () {
            annyang.abort();
            $('body').removeClass('voicecommander');
          }, 2000);
        }
      }
      // loop through and add the callbacks into annyang
      for (var i in Drupal.settings.voiceCommanderVoiceCommands) {
        var currentKey = Drupal.settings.voiceCommanderVoiceCommands[i].phrase.toLowerCase();
        // support for wildcards which annyang needs to process directly
        commands[currentKey] = Drupal.settings.voiceCommanderVoiceCommands[i];
      }
      var commandsWithCallbacks = {};
      // now convert to a method that they'd be able to fire correctly when
      // called instead of the assembled calls
      $.each(commands, function (phrase, value) {
        if (phrase.indexOf(':') == -1 && phrase.indexOf(':') == -1) {
          commandsWithCallbacks[phrase] = function () {
            eval(commands[phrase].callback +"('" + phrase.toLowerCase() + "')");
          };
        }
        else {
          commandsWithCallbacks[phrase] = commands[phrase].callback;
        }
      });
      // Create the function
      annyang.addCommands(commandsWithCallbacks);
      var useItOnce = true;
      var voiceCommanderStr = $('body').append('<div id="voice-commander-rec"></div><div class="voice-commander-rec-window"><div class="icon"></div><p></p></div>');
      var out;

      voiceCommanderStr.keydown(function () {
        if (event.ctrlKey && event.altKey && useItOnce) {

          $('.voice-commander-rec-window > p').removeClass('speak');

          annyang.abort();
          clearTimeout(out);

          setTimeout(function () {
            $('body').addClass('voicecommander');
            $('.voice-commander-rec-window > p').text(Drupal.settings.waitCallback);

            annyang.start({
              autoRestart: false,
              continuous: true
            });

            annyang.addCallback('start', function () {
              $('.voice-commander-rec-window > p').addClass('speak').text(Drupal.settings.startCallback);
            });

          }, 300);

          useItOnce = false;
        }
      });

      voiceCommanderStr.keyup(function () {
        if (event.ctrlKey || event.altKey) {
          $('body').removeClass('voicecommander');

          out = setTimeout(function () {
            annyang.abort();
          }, 1000);

          useItOnce = true;
        }
      });

      var detectMobilePattern = /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);
      var isMobile = (Drupal.settings.voiceCommanderSettingsMobile == 1) ? detectMobilePattern : false;

      if (isMobile) {
        $('body').addClass('voicecommander-mobile').append('<div class="vc-mobile-button"></div>').append('<div class="message-area"><div class="icon"></div><div class="vc-message"></div><div class="vc-abort"></div></div>');
        $('.vc-abort').click(function () {
          annyang.abort();
        });

        var button = $('.voicecommander-mobile > .vc-mobile-button');

        function message_start() {
          var message = $('body.voicecommander-mobile .message-area').css('display', 'block');
          // Message area animation.
          $('body.voicecommander-mobile').animate({
            margin: "20px 0 0 0"
          }, 400);

          function messageAnimation_start() {
            message.animate({
              top: "20px"
            }, 400);
          }
          messageAnimation_start();
        }

        function message_stop() {
          var message = $('body.voicecommander-mobile .message-area').css('display', 'block');
          var icon = $('.voicecommander-mobile .message-area .icon');
          // Message area animation.
          $('body.voicecommander-mobile').css('margin', '0 0 0 0');

          function messageAnimation_stop() {
            message.animate({
              top: "0px"
            }, 400);
          }
          messageAnimation_stop();
        }

        button.hover(function () {
          setTimeout(function () {
            clearTimeout(out);
            annyang.abort();
            showMessage(Drupal.settings.waitCallback);

            setTimeout(function () {
              annyang.start();
              message_start();

              annyang.addCallback('start', function () {
                showMessage(Drupal.settings.startCallback);
                // Icon animation.
                var icon = $('.voicecommander-mobile .message-area .icon');

                function iconAnimation_start() {
                  icon.animate({
                    opacity: 0
                  }, 400).animate({
                    opacity: 1
                  }, 400);
                }

                iconAnimation_start();

                setInterval(function () {
                  iconAnimation_start();
                }, 800);
              });
            }, 300);
          }, 600);
        }, function () {
          message_stop();
          out = setTimeout(function () {
            annyang.abort();
          }, 2000);
        });
      }
    }
  });
})(jQuery);
