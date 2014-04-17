var H5P = H5P || {};

if (H5P.getPath === undefined) {
  /**
   * Find the path to the content files based on the id of the content
   *
   * Also identifies and returns absolute paths
   *
   * @param {String} path Absolute path to a file, or relative path to a file in the content folder
   * @param {Number} contentId Identifier of the content requesting the path
   * @returns {String} The path to use.
   */
  H5P.getPath = function (path, contentId) {
    if (path.substr(0, 7) === 'http://' || path.substr(0, 8) === 'https://') {
      return path;
    }

    return H5PIntegration.getContentPath(contentId) + path;
  };
}

H5P.Flashcards = function (options, contentId) {
  var $panel;
  var $target;
  var that = this;
  var $ = H5P.jQuery;
  this.options = $.extend({}, {
    title: "Flashcards",
    description: "What does the card mean?",
    progressText: "Card @card of @total",
    next: "Next",
    previous: "Previous",
    checkAnswerText: "Check answer"
  }, options);

  if ( !(this instanceof H5P.Flashcards) ){
    return new H5P.Flashcards(options, contentId);
  }

  var getScore = function(){
    var score = 0;
    $panel.find('.h5p-input').each(function (idx, el) {
      var i = parseInt(el.id.replace(/^.*-/,''));
      var correct_answer = that.options.cards[i].answer.toLowerCase();
      var answer_given = $(el).val().trim().toLowerCase();
      score += correct_answer == answer_given ? 1 : 0;
    });
    return score;
  }

  var getAnswerGiven = function(){
    var answers = 0;
    $panel.find('.h5p-input').each(function (idx, el) {
      var answer_given = $(el).val().trim().toLowerCase();
      if(answer_given != ''){
        answers++;
      }
    });
    return totalScore() == answers;
  };

  var focusElement = function(el){
    var i = Math.round(-parseInt(el.css('left')) / parseInt(el.css('width')));
    $('#'+$panel.attr('id')+'-input-'+i).focus();
  }

  var totalScore = function(){
    var score = 0;
    $panel.find('.h5p-input').each(function (idx, el) {
      score++;
    });
    return score;
  };

  var showScore = function(){
    var left = -parseInt($('#flashcards').css('left'));
    if (isNaN(left)) {
      left = 0;
    }
    var i = Math.round(left / parseInt($('#flashcards').css('width')));
    $('#'+$panel.attr('id')+'-fasit-'+i).fadeIn('slow');

    var $answer = $('#'+$panel.attr('id')+'-input-'+i).attr('disabled', 'disabled');
    var answer_given = $answer.val().trim().toLowerCase();
    if(that.options.cards[i].answer.toLowerCase() == answer_given) {
      $answer.parent().removeClass('wrong-answer').addClass('correct-answer');
    }
    else {
      $answer.parent().removeClass('correct-answer').addClass('wrong-answer');
    }
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
    $target.addClass('flashcard');
    $panel = addElement($target, 'panel-'+$target.attr('data-content-id'), 'panel', { });
    $panel.append('<H2 class="flashcard-title">' + that.options.title + '</h2>');
    addElement($panel, null, 'flashcard-description', { text: that.options.description });

    // Panel setup
    var $cards = addElement($panel, null, 'flashcard-inner-panel', { });
    var $flashcards = addElement($cards, 'flashcards', 'flashcards', { });
    var $navigation = addElement($cards, null, 'h5p-flashcards-nav', { });

    var $prev = addElement($navigation, 'previous-flashcard', 'flashcard-navigation-button', {
      text: that.options.previous,
      click: function() {
        $flashcards.stop(true, true);
        if ($prev.is(':visible')) {
          $flashcards.animate({
            left: '+='+$flashcards.css('width')
          }, 'fast', 'swing', function() {
            if (parseInt($flashcards.css('left')) >= 0) {
              $prev.hide();
            }
            focusElement($flashcards);
          });
          $('#next-flashcard').show();
        }
      }
    });

    var $next = addElement($navigation, 'next-flashcard', 'flashcard-navigation-button', {
      text: that.options.next,
      click: function() {
        $flashcards.stop(true, true);
        if ($next.is(':visible')) {
          $flashcards.animate({
            left: '-='+$flashcards.css('width')
          }, 'fast', 'swing', function() {
            var length = that.options.cards.length * parseInt($flashcards.css('width')) - parseInt($flashcards.css('width'));
            if (-parseInt($flashcards.css('left')) >= length) {
              $next.hide();
            }
            focusElement($flashcards);
          });
          $('#previous-flashcard').show();
        }
      }
    });

    // Add cards
    var max_height = 0;
    var images = Array();
    for(var i=0; i < that.options.cards.length; i++) {
      var question = addElement($flashcards, $panel.attr('id')+'-question-'+i, 'flashcard-question', { left: i * parseInt($cards.css('width'))});
      if(that.options.cards[i].image) {
        var width = "";

        // Scale image if image to wide for question
        if(that.options.cards[i].image.width > question.innerWidth()) {
           width = " width=\""+question.innerWidth()+'px"';
           that.options.cards[i].image.height = question.innerWidth() / (that.options.cards[i].image.width / that.options.cards[i].image.height);
        }

        images[i] = addElement(question, null, 'flashcard-image', { text: '<img '+width+'src="'+H5P.getPath(that.options.cards[i].image.path, contentId)+'"/>' });
        if(that.options.cards[i].image.height > max_height) {
          max_height = that.options.cards[i].image.height;
        }
		  if(that.options.cards[i].text) {
          var textHeight = addElement(images[i], $panel.attr('id')+'-question-'+i, 'flashcard-image-text', { text: that.options.cards[i].text }).innerHeight();
          if (max_height < textHeight) {
            max_height = textHeight;
          }
        }
      }
		else if(that.options.cards[i].text) {
        var textHeight = addElement(question, $panel.attr('id')+'-question-'+i, 'flashcard-text', { text: that.options.cards[i].text }).innerHeight();
        if (max_height < textHeight) {
            max_height = textHeight;
          }
      }
      var input_container = addElement(question, null, 'input-container', { });
      addElement(input_container, $panel.attr('id')+'-fasit-'+i, 'fasit-container', { text: '<span class="fasit">'+that.options.cards[i].answer+'</span>' });
      addElement(input_container, null, 'flashcard-label', { text: that.options.progressText.replace('@card', i + 1).replace('@total', that.options.cards.length)});
      if(that.options.cards[i].answer) {
        // input_container.html('<span><input id="'+$panel.attr('id')+'-input-'+i+'" class="input" type="text"/></span>');
        addElement(input_container, null, 'flashcard-navigation-button flashcard-show-answer', { click: showScore, text: that.options.checkAnswerText });
        addElement(input_container, null, 'flashcard-input', { text: '<input id="'+$panel.attr('id')+'-input-'+i+'" class="h5p-input" type="text"/>' });
      }
    }

    for(var i=0; i < that.options.cards.length; i++) {
      if(images[i]) {
        images[i].css('height', max_height);
        var imageh = max_height - that.options.cards[i].image.height;
        if(imageh) {
           images[i].find('img').css('padding-top', Math.round(imageh / 2));
        }
      }
    }

    $cards.css('height', max_height + input_container.outerHeight() + $navigation.outerHeight() + 5);

    $('#'+$panel.attr('id')+'-input-0').focus();

    return this;
  };

  var returnObject = {
    attach: attach,
    machineName: 'H5P.Flashcards',
    getScore: getScore,
    getAnswerGiven: getAnswerGiven,
    totalScore: totalScore
  };

  return returnObject;
};
