/**
 * @file
 *
 * Custom module js file.
 */

(function ($) {
  Drupal.behaviors.voicecommander = {
    attach: function (context, settings) {
      var config = this.config;
      var commands = {};

      if (undefined !== annyang && annyang !== null) {

        // Clear cache function.
        function clearCache() {
          window.location.href = Drupal.settings.basePath + 'admin/config/user-interface/voice-commander/cc_all?destination=' + window.location.pathname.substring(1) + '&token=' + Drupal.settings.secureToken;
        }

        // Add default commands.
        // Clear Cache only for admin.
        var defaultCommands = {'drupal cache': clearCache};
        annyang.addCommands(defaultCommands);

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

        for (var i in Drupal.settings.voiceCommanderAdminMenuData) {
          var currentKey = Drupal.settings.voiceCommanderAdminMenuData[i].title.toLowerCase();
          commands[currentKey] = Drupal.settings.voiceCommanderAdminMenuData[i].href;
        }

        var commandsWithCallbacks = {};

        $.each(commands, function (key, value) {
          commandsWithCallbacks[key] = function () {
            window.location.href = commands[key];
          };
        });

        function showMessage(message) {
          if (isMobile) {
            $('.voicecommander-mobile .message-area > div.vc-message', context).text(message);
          } else {
            $('body', context).addClass('voicecommander');
            $('.voice-commander-rec-window > p', context).addClass('speak').text(message);

            out = setTimeout(function () {
              annyang.abort();
              $('body', context).removeClass('voicecommander');
            }, 2000);
          }
        }

        annyang.addCommands(commandsWithCallbacks);
        autoRestart = false;
        var useItOnce = true;
        var voiceCommanderStr = $('body', context).append('<div id="voice-commander-rec"></div><div class="voice-commander-rec-window"><div class="icon"></div><p></p></div>');
        var out;

        voiceCommanderStr.keydown(function () {
          if (event.ctrlKey && event.altKey && useItOnce) {

            $('.voice-commander-rec-window > p', context).removeClass('speak');

            annyang.abort();
            clearTimeout(out);

            setTimeout(function () {
              $('body', context).addClass('voicecommander');
              $('.voice-commander-rec-window > p', context).text(Drupal.settings.waitCallback);

              annyang.start({
                autoRestart: false,
                continuous: true
              });

              annyang.addCallback('start', function () {
                $('.voice-commander-rec-window > p', context).addClass('speak').text(Drupal.settings.startCallback);
              });

            }, 300);

            useItOnce = false;
          }
        });

        voiceCommanderStr.keyup(function () {
          if (event.ctrlKey || event.altKey) {
            $('body', context).removeClass('voicecommander');

            out = setTimeout(function () {
              annyang.abort();
            }, 2000);

            useItOnce = true;
          }
        });

        var detectMobilePattern = /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);
        var isMobile = (Drupal.settings.voiceCommanderSettingsMobile == 1) ? detectMobilePattern : false;

        if (isMobile) {
          $('body', context).addClass('voicecommander-mobile').append('<div class="vc-mobile-button"></div>').append('<div class="message-area"><div class="icon"></div><div class="vc-message"></div><div class="vc-abort"></div></div>');
          $('.vc-abort', context).click(function () {
            annyang.abort();
          });

          var button = $('.voicecommander-mobile > .vc-mobile-button', context);

          function message_start() {
            var message = $('body.voicecommander-mobile .message-area', context).css('display', 'block');
            // Message area animation.
            $('body.voicecommander-mobile', context).animate({
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
            var message = $('body.voicecommander-mobile .message-area', context).css('display', 'block');
            var icon = $('.voicecommander-mobile .message-area .icon', context);
            // Message area animation.
            $('body.voicecommander-mobile', context).css('margin', '0 0 0 0');

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
                  var icon = $('.voicecommander-mobile .message-area .icon', context);

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
    }
  };
})(jQuery);
