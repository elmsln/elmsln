/**
 * @file
 *
 * Custom module js file.
 */

(function ($) {
  // extend the drupal js namespace by adding in voicecommander
  Drupal.voicecommander = Drupal.voicecommander || { functions: {} }
  // reactivate voice command so we don't get multiple matches
  Drupal.voicecommander.reactivate = function() {
    if (Drupal.settings.voiceCommander.continuous == false) {
      out = setTimeout(function () {
        annyang.abort();
      }, 500);
      $('body').removeClass('voicecommander');
    }
    else {
      annyang.abort();
      $('body').removeClass('voicecommander');
      annyang.start({
        autoRestart: true,
        continuous: true
      });
    }
  };
  // click a link based on the phrase match
  Drupal.voicecommander.clickLink = function(phrase) {
    Drupal.settings.voiceCommander.commands[phrase].object.click();
    Drupal.settings.voiceCommander.commands[phrase].object.focus();
    $('span.voicecommand-phrase').remove();
    $('[data-voicecommand]').removeClass('voicecommander-outline');
    Drupal.voicecommander.reactivate();
  };
  // go to a link, this is most common
  Drupal.voicecommander.goTo = function(phrase) {
    window.location.href = Drupal.settings.basePath + Drupal.settings.voiceCommander.commands[phrase].data;
  };
  // go backward in history
  Drupal.voicecommander.back = function(phrase) {
    window.location.href = window.history.back();
  };
  Drupal.voicecommander.showOptions = function(phrase) {
    if (phrase.indexOf('show') !== -1) {
      $('[data-voicecommand]').each(function(){
        $(this).prepend('<span class="voicecommand-phrase">' + $(this).attr('data-voicecommand') + '</span>');
      }).addClass('voicecommander-outline');
    }
    else {
      $('span.voicecommand-phrase').remove();
      $('[data-voicecommand]').removeClass('voicecommander-outline');
    }
    Drupal.voicecommander.reactivate();
  }
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
      }, 1000);
      return false;
    }
    // travel to the top of the screen
    else if (phrase.indexOf('top') !== -1) {
      $('html, body').animate({
          scrollTop: (0)
      }, 1000);
      return false;
    }
    // travel down the screen, one screen height
    else {
      $('html, body').animate({
        scrollTop: ($(window).scrollTop()+(height*.75))
      }, 1000);
      return false;
    }
  };
  $(document).ready(function() {
    var config = this.config;
    var commands = {};
    if (undefined !== annyang && annyang !== null) {
      function showMessage(message) {
        if (isMobile) {
          $('.voicecommander-mobile .message-area > div.vc-message').text(message);
        } else {
          $('body').addClass('voicecommander');
          $('.voice-commander-rec-window > p').addClass('speak').text(message);

          out = setTimeout(function () {
            annyang.abort();
            $('body').removeClass('voicecommander');
          }, 1500);
        }
      }
      // support for items to be click-able if they define a data attribute
      $('body a:visible,[data-voicecommand]').each(function(){
        var tmpphrase;
        var tmpcommand;
        if ($(this).attr('data-voicecommand')) {
          tmpcommand = $(this).attr('data-voicecommand');
        }
        else {
          tmpcommand = $(this).text().trim();
          if (tmpcommand != '') {
            tmpcommand = Drupal.t('go to') + ' ' + tmpcommand;
          }
        }
        // ensure we have some input if hitting these visible links like this
        if (tmpcommand != '') {
          if (Drupal.settings.voiceCommander.optionalPrefix == true) {
            tmpphrase = '(' + Drupal.settings.voiceCommander.prefix + ') ' + tmpcommand;
          }
          else {
            tmpphrase = Drupal.settings.voiceCommander.prefix + ' ' + tmpcommand;
          }
          tmpphrase = tmpphrase.toLowerCase();
          Drupal.settings.voiceCommander.commands[tmpphrase] = {
            'phrase':tmpphrase,
            'callback':'Drupal.voicecommander.clickLink',
            'object':this
          };
        }
      });
      // loop through and add the callbacks into annyang
      for (var i in Drupal.settings.voiceCommander.commands) {
        var currentKey = Drupal.settings.voiceCommander.commands[i].phrase.toLowerCase();
        // support for wildcards which annyang needs to process directly
        commands[currentKey] = Drupal.settings.voiceCommander.commands[i];
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
      // well now, the future is getting pretty bright; continuous mode overrides all other capabilities
      if (Drupal.settings.voiceCommander.continuous == true) {
        annyang.start({
          autoRestart: true,
          continuous: true
        });
      }
      else {
        // Define callbacks.
        annyang.addCallback('error', function () {
          showMessage(Drupal.settings.voiceCommander.errorCallback);
        });
        annyang.addCallback('errorNetwork', function () {
          showMessage(Drupal.settings.voiceCommander.errorNetworkCallback);
        });
        annyang.addCallback('errorPermissionBlocked', function () {
          showMessage(Drupal.settings.voiceCommander.permissionBlockedCallback);
        });
        annyang.addCallback('errorPermissionDenied', function () {
          showMessage(Drupal.settings.voiceCommander.permissionDeniedCallback);
        });

        var detectMobilePattern = /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);
        var isMobile = (Drupal.settings.voiceCommander.mobile == 1) ? detectMobilePattern : false;

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
              showMessage(Drupal.settings.voiceCommander.waitCallback);

              setTimeout(function () {
                annyang.start();
                message_start();

                annyang.addCallback('start', function () {
                  showMessage(Drupal.settings.voiceCommander.startCallback);
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
      // key combo to activate
      voiceCommanderStr.keydown(function () {
        if (event.ctrlKey && event.altKey && useItOnce) {
          // voicecommand
          $('[data-voicecommand]').each(function(){
            $(this).prepend('<span class="voicecommand-phrase">' + $(this).attr('data-voicecommand') + '</span>');
          }).addClass('voicecommander-outline');
          useItOnce = false;
          if (Drupal.settings.voiceCommander.continuous == false) {
            $('.voice-commander-rec-window > p').removeClass('speak');
            annyang.abort();
            clearTimeout(out);

            setTimeout(function () {
              $('body').addClass('voicecommander');
              $('.voice-commander-rec-window > p').text(Drupal.settings.voiceCommander.waitCallback);
              annyang.start({
                autoRestart: true,
                continuous: true
              });

              annyang.addCallback('start', function () {
                $('.voice-commander-rec-window > p').addClass('speak').text(Drupal.settings.voiceCommander.startCallback);
              });

            }, 300);
          }
        }
      });

      voiceCommanderStr.keyup(function () {
        if (event.ctrlKey || event.altKey) {
          $('span.voicecommand-phrase').remove();
          $('[data-voicecommand]').removeClass('voicecommander-outline');
          useItOnce = true;
          if (Drupal.settings.voiceCommander.continuous == false) {
            $('body').removeClass('voicecommander');
            out = setTimeout(function () {
              annyang.abort();
            }, 500);
          }
        }
      });
    }
  });
})(jQuery);
