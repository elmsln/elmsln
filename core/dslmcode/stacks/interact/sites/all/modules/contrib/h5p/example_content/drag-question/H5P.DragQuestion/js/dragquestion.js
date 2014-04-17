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

H5P.DragQuestion = function (options, contentId) {

  var target;
  var $ = H5P.jQuery;
  var score = 0;
  var $container;

  if ( !(this instanceof H5P.DragQuestion) ){
    return new H5P.DragQuestion(options, contentId);
  }

  options = $.extend(true, {}, {
    scoreShow: 'Show score',
    correct: 'Solution',
    question: {
      settings: {
        size: {
          width: 640,
          height: 320
        }
      },
      task: {
        elements: [],
        dropZones: []
      }
    }
  }, options);

  var allAnswered = function() {
    var dropzones = 0;
    var answers = 0;
    target.find('.dropzone').each(function (idx, el) {
      dropzones++;
      if($(el).data('content')) {
        answers++;
      }
    });
    return (dropzones === answers);
  };

  var getMaxScore = function() {
    return target.find('.dropzone').length;
  };

  var getScore = function() {
    if (!$.contains(document.documentElement, target[0])) {
      return score;
    }
    score = 0;
    target.find('.dropzone').each(function (idx, el) {
      var $dropzone = $(el),
        dragIndex = $dropzone.data('content'),
        correctElement = $dropzone.data('correctElements');
      if (dragIndex && (correctElement === '' + (dragIndex - 1))) {
        score++;
      }
    });
    return score;
  };

  var showSolutions = this.showSolutions = function() {
    var score = 0;
    var count = 0;
    target.find('.dropzone').each(function (idx, el) {
      count++;
      var $dropzone = $(el),
        correctElement = $dropzone.data('correctElements');
      var dz = options.question.task.dropZones[idx];
      // If labels are hidden, show them now.
      if (dz.showLabel === undefined || dz.showLabel === false) {
        // Render label
        $dropzone.append('<div class="dragquestion-label">'+$dropzone.data('label')+'</div>');
      }

      // Show correct/wrong style for dropzone.
      var draggableId = $dropzone.data('content'),
        $currentDraggable = $('.draggable-' + draggableId);
      if ((draggableId && (correctElement === '' + (draggableId - 1)))
        || (correctElement === '' && !draggableId)) {
        $dropzone.addClass('dropzone-correct-answer').removeClass('dropzone-wrong-answer');
        $currentDraggable.addClass('draggable-correct').removeClass('draggable-wrong');
        score++;
      }
      else {
        $dropzone.addClass('dropzone-wrong-answer').removeClass('dropzone-correct-answer');
        $currentDraggable.addClass('draggable-wrong').removeClass('draggable-correct');
        // Show correct answer below. Only use first listed correct answer.
        if (correctElement !== '') {
          var text,
            correct = options.question.task.elements[correctElement];
          if (correct.type.library.lastIndexOf('H5P.Text', 0) === 0) {
            text = correct.type.params.text;
          } else if (correct.type.library.lastIndexOf('H5P.Image', 0) === 0) {
            text = correct.type.params.alt;
          }
          $dropzone.append('<div class="dropzone-answer">' + options.correct + ': '+text+'</div>');
        }
      }
    });
    //target.find('.score').html(options.scoreText.replace('@score', score).replace('@total', count));
  };

  var resize = function () {
    var width = $container.width();
    $container.find('.dragndrop').css({
      height: width * (options.question.settings.size.height / options.question.settings.size.width),
      fontSize: 16 * (width / options.question.settings.size.width)
    });
  };

  var attach = function(board) {
    score = 0;
    var $ = H5P.jQuery;
    var dropzones = options.question.task.dropZones;
    var elements = options.question.task.elements;

    $container = target = (typeof(board) === "string" ? $("#" + board) : $(board));
    $container.addClass('h5p-dragquestion');

    var styles = (options.question.settings.background !== undefined ? 'style="background-image:url(\'' + H5P.getPath(options.question.settings.background.path, contentId) + '\')"' : '');
    var $dragndrop = $('<div class="dragndrop"'+ styles + '></div>');

    $container.append($dragndrop);

    // Convert element position data to percentage of the main dragndrop
    // container.  Draggable and animate only create pixel positioned data.
    function percentagePosition($el) {
      var $dnd = $container.find('.dragndrop');
      var positioning = {
        top: (parseInt($el.css('top')) * 100 / $dnd.innerHeight()) + '%',
        left: (parseInt($el.css('left')) * 100 / $dnd.innerWidth()) + '%'
      };
      $el.css(positioning);
    }

    function addElement(id, className, el, z) {
      var $el = $('<div class="'+className+'">' + (el.text !== undefined ? el.text : '') + '</div>');
      if (el.type !== undefined) {
        var elementInstance = new (H5P.classFromName(el.type.library.split(' ')[0]))(el.type.params, contentId);
        elementInstance.attach($el);
      }
      $dragndrop.append($el);
      if (id !== undefined) {
        $el.data('id', id);
      }
      if (z !== undefined) {
        $el.css({'z-index': z});
      }
      // Store draggable drop zones. Will be used later to check for valid
      // draggables in drop zones..
      if (el.dropZones !== undefined) {
        $el.data('dropzones', el.dropZones);
      }
      // Store drop zone correct answers
      if (el.correctElements !== undefined) {
        $el.data('correctElements', el.correctElements);
      }
      if (el.width !== undefined) {
        $el.css({width: el.width + 'em'});
      }
      if (el.height !== undefined) {
        $el.css({height: el.height + 'em'});
      }
      if(el.x !== undefined) {
        $el.css({left: el.x + '%'});
        $el.data('x', el.x);
      }
      if (el.y !== undefined) {
        $el.css({top: el.y + '%'});
        $el.data('y', el.y);
      }
      // Implicitly, all elements can have a label. Semantically, it's only
      // supported in drop zones.
      if (el.label !== undefined) {
        $el.data('label', el.label);
        if (el.showLabel) {
          $el.append('<div class="dragquestion-label">'+el.label+'</div>');
        }
      }
      return $el;
    }

    var buttons = Array();

    // If not in QuestionSet, BoardGame or Course Presentation, add button.
    if (-1 === $.inArray($container.parents('.h5p-content').data('class'),
                         ['H5P.QuestionSet', 'H5P.BoardGame', 'H5P.CoursePresentation'])) {
      buttons.push({
        text: options.scoreShow,
        click: showSolutions,
        className: 'button h5p-show-solution'
      });
    }

    // Add buttons
    for (var i = 0; i < buttons.length; i++) {
      var $button = addElement('lol', buttons[i].className, buttons[i], 1);
      $button.click(buttons[i].click);
    }

    // Add drop zones
    for (var i = 0; i < dropzones.length; i++) {
      addElement((i + 1), 'dropzone dropzone-' + (i + 1), dropzones[i], 1);
    }

    // Add elements (static and draggable)
    for (var i = 0; i < elements.length; i++) {
      var el = elements[i];
      // Add element as draggable if it has any defined drop zones, or static
      // if not.
      if (el.dropZones !== undefined && el.dropZones.length !== 0) {
        addElement((i + 1), 'draggable draggable-' + (i + 1), el, 2);
      }
      else {
        addElement((i + 1), 'static content-' + (i + 1), el, 0);
      }
    }

    // Restore user answers
    if (options.userAnswers !== undefined) {
      for (var dropzoneId in options.userAnswers) {
        var draggableId = options.userAnswers[dropzoneId];
        var $draggable = target.find('.draggable-' + draggableId);
        var $dropzone = target.find('.dropzone-' + dropzoneId);

        // Set attributes
        $dropzone.data('content', draggableId);
        $draggable.data('content', dropzoneId).css('z-index', '1');

        // Move drag to center of drop
        $draggable.css({
          top: Math.round(($dropzone.outerHeight() - $draggable.outerHeight()) / 2) + parseInt($dropzone.css('top'), 10),
          left: Math.round(($dropzone.outerWidth() - $draggable.outerWidth()) / 2) + parseInt($dropzone.css('left'), 10)
        });
        percentagePosition($draggable);
      }
    }

    // Make dropzones
    target.find('.dropzone').each(function (idx, el) {
      $(el).droppable({
        activeClass: 'dropzone-active',
        fit: 'intersect',
        accept: function (draggable) {
          if (target.find(draggable).length === 0) {
            return false;
          }

          var dropZones = $(draggable).data('dropzones');
          var id = $(el).data('id') - 1;

          for (var i = 0; i < dropZones.length; i++) {
            if (parseInt(dropZones[i]) === id) {
              return true;
            }
          }

          return false;
        },
        out: function (event, ui) {
          // TODO: somthing
        },
        drop: function (event, ui) {
          var $dropzone = $(this),
            currentDraggableId = $dropzone.data('content'),
            newDraggableId = ui.draggable.data('id');

          $dropzone.removeClass('dropzone-wrong-answer');

          // If this drag was in a drop area and this drag is not the same
          if (currentDraggableId && newDraggableId !== currentDraggableId) {
            // Remove underlaying drag (move to initial position)
            var $currentDraggable = target.find('.draggable-' + currentDraggableId);
            $currentDraggable.data('content', null)
            .animate({
              left: $currentDraggable.data('x') + '%',
              top:  $currentDraggable.data('y') + '%'
            })
            .removeClass('h5p-connected');
          }

         // Was object in another drop?
         if (ui.draggable.data('content')) {
           // Remove object from previous drop
           $('.dropzone-'+ui.draggable.data('content')).data('content', null);
         }

          // Set attributes
          $dropzone.data('content', newDraggableId);
          ui.draggable.data('content', $dropzone.data('id'));
          ui.draggable.css('z-index', '1');

          // Move drag to center of drop
          ui.draggable.animate({
            top: Math.round(($dropzone.outerHeight() - ui.draggable.outerHeight()) / 2) + parseInt($dropzone.css('top')),
            left: Math.round(($dropzone.outerWidth() - ui.draggable.outerWidth()) / 2) + parseInt($dropzone.css('left'))
          }, {
            complete: function() {
              H5P.jQuery(this).addClass('h5p-connected');
              percentagePosition(H5P.jQuery(this));
            }
          });

          // Store this answer
          if (options.userAnswers === undefined) {
            options.userAnswers = {};
          }
          options.userAnswers[$dropzone.data('id')] = newDraggableId;

          if (allAnswered()){
            $(returnObject).trigger('h5pQuestionAnswered');
          }
          // Store the new score
          getScore();
        }
      });
    });

    // Make draggables
    target.find('.draggable').each(function (idx, el) {
      $(el).draggable({
        revert: 'invalid',
        start: function(event, ui) {
          ui.helper.css('z-index', '2');
          H5P.jQuery(this).removeClass('h5p-connected');
        },
        stop: function(event, ui) {
          var $this = H5P.jQuery(this)
          percentagePosition($this);

          if ($this.data('content') !== undefined) {
            $this.addClass('h5p-connected');
          }
        }
      });
    });

    if (returnObject.preventResize === false) {
      H5P.$window.bind('resize', resize);
    }
    resize();

    return this;
  };

  var returnObject = {
    attach: attach,
    machineName: 'H5P.DragQuestion',
    getScore: function() {
      return getScore();
    },
    getAnswerGiven: function() {
      return allAnswered();
    },
    getMaxScore: function() {
      return getMaxScore();
    },
    showSolutions: showSolutions,
    resize: resize,
    preventResize: false
  };

  return returnObject;
};
