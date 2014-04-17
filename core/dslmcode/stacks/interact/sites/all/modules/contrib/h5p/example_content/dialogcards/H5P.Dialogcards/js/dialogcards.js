var H5P = H5P || {};

H5P.Dialogcards = function (options, contentId) {
  var $panel;
  var $target;
  var current = 0;
  var $ = H5P.jQuery;
  this.options = $.extend({}, {
    title: "Dialogue",
    description: "Sit in pairs and make up sentences where you include the expressions below.<br/>Example: I should have said yes, HOWEVER I kept my mouth shut.",
    next: "Next",
    answer: "Turn"
  }, options);

  if ( !(this instanceof H5P.Dialogcards) ){
    return new H5P.Dialogcards(options, contentId);
  }

  function addElement(container, id, className, el) {
    var text = el.text ? el.text : '';
    var $el = $('<div class="'+className+'">'+text+'</div>');
    container.append($el);
    if(el.top) {
      $el.css({ top: el.top});
    }
    if(el.left) {
      $el.css({ left: el.left});
    }
    if(el.right) {
      $el.css({ right: el.right});
    }
    if(el.bottom) {
      $el.css({ bottom: el.bottom});
    }
    if(id) {
      $el.attr('id', id);
    }
    if(el.height) {
      $el.css({ height: el.height });
    }
    if(el.width) {
      $el.css({ width: el.width });
    }
    if(el.click) {
      $el.click(el.click);
    }
    return $el;
  }

  var attach = function (el) {
    $target = $(el);
    $target.addClass('dialogcard');
    $panel = addElement($target, 'panel-'+$target.attr('data-content-id'), 'dialogcard-panel', { });
    $panel.append('<h2 class="dialogcard-title">' + options.title + '</h2>');
    addElement($panel, null, 'dialogcard-description', { text: options.description });

    var $dialog_container = addElement($panel, 'dialogcontainer-'+$target.attr('data-content-id'), 'dialogcontainer', { });
    var $dialog = addElement($dialog_container, 'dialog-'+$target.attr('data-content-id'), 'dialogcard dialogcard-question', { });
    var $dialogtext = addElement($dialog, 'dialog-text', 'dialogcard-text', { text: options.dialogs[0].text });
    var $navigation = addElement($panel, 'navigation-'+$target.attr('data-content-id'), 'dialogcard-navigation', { });

    var $answer = addElement($navigation, 'next-dialogcard', 'dialogcard-navigation-button answer-dialog', {
      text: '<div>'+options.answer+'</div>',
      click: function() {
        $answer.css('display', 'none');
        $dialog.fadeOut('slow', function() {
          $dialog.removeClass('dialogcard-question');
          $dialog.addClass('dialogcard-answer');
			    $dialogtext.html(options.dialogs[current].answer);
          $dialog.fadeIn('fast', function() {
            if(current < options.dialogs.length - 1) {
              $next.css('display', 'inline');
            }
          });
        });
      }
    });
    var $next = addElement($navigation, 'next-dialogcard', 'dialogcard-navigation-button next-dialog', {
      text: '<div>' + options.next + '</div>',
      click: function() {
        current++;
        $next.css('display', 'none');
        $dialog.fadeOut('slow', function() {
          $dialog.addClass('dialogcard-question');
          $dialog.removeClass('dialogcard-answer');
			    $dialogtext.html(options.dialogs[current].text);
          $dialog.fadeIn('fast', function() {
            $answer.css('display', 'inline');
          });
        });
      }
    });

    if(options.dialogs[0].answer) {
      $answer.css('display', 'inline');
    }

    return this;
  };

  var returnObject = {
    attach: attach,
    machineName: 'H5P.Dialogcards'
  };

  return returnObject;
};
