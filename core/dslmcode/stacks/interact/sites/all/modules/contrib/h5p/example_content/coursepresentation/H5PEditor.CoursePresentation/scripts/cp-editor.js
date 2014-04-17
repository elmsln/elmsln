var H5PEditor = H5PEditor || {};

/**
 * Create a field for the form.
 *
 * @param {mixed} parent
 * @param {Object} field
 * @param {mixed} params
 * @param {function} setValue
 * @returns {H5PEditor.Text}
 */
H5PEditor.CoursePresentation = function (parent, field, params, setValue) {

  var that = this;
  if (params === undefined) {
    params = [{
      elements: [],
      keywords: []
    }];

    setValue(field, params);
  }

  this.parent = parent;
  this.field = field;
  this.params = params;
  this.resizing = false;
  // Elements holds a mix of forms and params, not element instances
  this.elements = [];
  this.slideRatio = 1.9753;

  this.passReadies = true;
  parent.ready(function () {
    that.setLocalization();
    that.passReadies = false;
  });
};

/**
 * Finds localization fields and updates value as they change.
 *
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.setLocalization = function () {
  var that = this;

  var fields = H5PEditor.findField('l10n', this.parent).children;
  for (var i = 0; i < fields.length; i++) {
    var field = fields[i];
    switch (field.field.name) {
      case 'prev':
        field.change(function (value) {
          that.cp.$slideination.children('.h5p-previous').text(value);
        });
        break;

      case 'prevSlide':
        field.change(function (value) {
          that.cp.$slideination.children('.h5p-previous').attr('title', value);
        });
        break;

      case 'scrollLeft':
        field.change(function (value) {
          that.cp.$slideination.children('.h5p-scroll-left').attr('title', value);
        });
        break;

      case 'goHome':
        field.change(function (value) {
          that.cp.$slideination.children('.h5p-go-home').attr('title', value);
        });
        break;

      case 'jumpToSlide':
        field.change(function (value) {
          that.cp.$slideinationSlides.children('li').children('a').attr('title', value);
        });
        break;

      case 'scrollRight':
        field.change(function (value) {
          that.cp.$slideination.children('.h5p-scroll-right').attr('title', value);
        });
        break;

      case 'next':
        field.change(function (value) {
          that.cp.$slideination.children('.h5p-next').text(value);
        });
        break;

      case 'nextSlide':
        field.change(function (value) {
          that.cp.$slideination.children('.h5p-next').attr('title', value);
        });
        break;
    }
  }
};

/**
 * Add an element to the current slide and params.
 *
 * @param {String} library
 * @returns {unresolved}
 */
H5PEditor.CoursePresentation.prototype.addElement = function (library) {
  var libraryName = library.split(' ')[0];
  var h = 40, w = 40, params = {};
  switch (libraryName) {
    case 'H5P.Audio':
      h = 15, w = 45;
      break;
    case 'H5P.DragQuestion':
      h = 50, w = 50;
      params = {
        question: {
          settings: {
            size: {
              width: Math.round(this.cp.$current.width() * h / 100),
              height: Math.round(this.cp.$current.height() *h / 100)
            }
          }
        }
      }
      break;
  }
  var elParams = {
    action: {
      library: library,
      params: params
    },
    x: 0,
    y: 0,
    width: w,
    height: h
  };

  this.params[this.cp.$current.index()].elements.push(elParams);
  return this.cp.addElement(elParams);
};

/**
 * Append field to wrapper.
 *
 * @param {type} $wrapper
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.appendTo = function ($wrapper) {
  var that = this;

  this.$item = H5PEditor.$(this.createHtml()).appendTo($wrapper);
  this.$editor = this.$item.children('.editor');
  this.$errors = this.$item.children('.h5p-errors');

  // Create new presentation.
  this.cp = new H5P.CoursePresentation({
    slides: this.params
  }, H5PEditor.contentId, this);
  this.cp.attach(this.$editor);

  // Add drag and drop menu bar.
  that.initializeDNB();

  // Add and bind slide controls.
  H5PEditor.$('<div class="h5p-slidecontrols"><a href="#" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'sortSlide', {':dir': 'left'}) + '" class="h5p-slidecontrols-button">&lt;</a><a href="#" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'sortSlide', {':dir': 'right'}) + '" class="h5p-slidecontrols-button">&gt;</a><a href="#" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'removeSlide') + '" class="h5p-slidecontrols-button">&times;</a><a href="#" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'cloneSlide') + '" class="h5p-clone-slide h5p-slidecontrols-button"></a><a href="#" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'newSlide') + '" class="h5p-slidecontrols-button">+</a></div>').insertAfter(this.cp.$boxWrapper).children('a:first').click(function () {
    that.sortSlide(that.cp.$current.prev(), -1); // Left
    return false;
  }).next().click(function () {
    that.sortSlide(that.cp.$current.next(), 1); // Right
    return false;
  }).next().click(function () {
    that.removeSlide();
    return false;
  }).next().click(function () {
    that.addSlide(H5P.cloneObject(that.params[that.cp.$current.index()],true));
    var slideParams = that.params[that.cp.$current.index()];
    if (slideParams.ct !== undefined) {
      // Make sure we don't replicate the whole continuous text.
      delete slideParams.ct;
    }
    H5P.ContinuousText.Engine.run(that);
    return false;
  }).next().click(function () {
    that.addSlide();
    return false;
  });

  this.cp.resize = function (fullscreen) {
    // Reset drag and drop adjustments.
    if (that.keywordsDNS !== undefined) {
      delete that.keywordsDNS.dnd.containerOffset;
      delete that.keywordsDNS.marginAdjust;
    }
    H5P.CoursePresentation.prototype.resize.apply(that.cp, [fullscreen]);
  };
};

H5PEditor.CoursePresentation.prototype.addDNBButton = function (library) {
  var that = this;
  var id = library.name.split('.')[1].toLowerCase();

  return {
    id: id,
    title: H5PEditor.t('H5PEditor.CoursePresentation', 'insertElement', {':type': library.title.toLowerCase()}),
    createElement: function () {
      return that.addElement(library.uberName);
    }
  };
};

/**
 * Initialize the drag and drop menu bar.
 *
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.initializeDNB = function () {
  var that = this;

  this.$bar = H5PEditor.$('<div class="h5p-dragnbar">' + H5PEditor.t('H5PEditor.CoursePresentation', 'loading') + '</div>').insertBefore(this.cp.$boxWrapper);
  H5PEditor.$.post(H5PEditor.ajaxPath + 'libraries', {libraries: this.field.field.fields[0].field.fields[0].options}, function (libraries) {
    var buttons = [];
    for (var i = 0; i < libraries.length; i++) {
      buttons.push(that.addDNBButton(libraries[i]));
    }

    that.dnb = new H5P.DragNBar(buttons, that.cp.$current);

    // Update params when the element is dropped.
    that.dnb.stopMovingCallback = function (x, y) {
      var params = that.params[that.cp.$current.index()].elements[that.dnb.dnd.$element.index()];
      params.x = x * that.cp.slideWidthRatio;
      params.y = y;
    };

    // Edit element when it is dropped.
    that.dnb.dnd.releaseCallback = function () {
      var params = that.params[that.cp.$current.index()].elements[that.dnb.dnd.$element.index()];

      if (that.dnb.newElement) {
        if (H5P.libraryFromString(params.action.library).machineName === 'H5P.ContinuousText') {
          H5P.ContinuousText.Engine.run(that);
          if (that.ct.counter === 1) {
            that.dnb.dnd.$element.dblclick();
          }
        }
        else {
          that.dnb.dnd.$element.dblclick();
        }
        that.dnb.newElement = false;
      }
    };

    that.dnb.attach(that.$bar);

    if (that.cp.keywordsWidth) {
      // Bind keyword interactions.
      that.initKeywordInteractions();
    }
  });
};

/**
 * Create HTML for the field.
 */
H5PEditor.CoursePresentation.prototype.createHtml = function () {
  return H5PEditor.createItem(this.field.widget, '<div class="editor"></div>');
};

/**
 * Validate the current field.
 */
H5PEditor.CoursePresentation.prototype.validate = function () {
  return true;
};

/**
 * Remove this item.
 */
H5PEditor.CoursePresentation.prototype.remove = function () {
  this.$item.remove();
};

/**
 * Initialize keyword interactions.
 *
 * @returns {undefined} Nothing
 */
H5PEditor.CoursePresentation.prototype.initKeywordInteractions = function () {
  var that = this;

  if (!this.cp.$currentKeyword.next().length && !this.cp.$currentKeyword.children().children().length) {
    // No keywords, insert help text
    this.$keywordsTip = H5PEditor.$('<div class="h5p-keywords-tip">' + H5PEditor.t('H5PEditor.CoursePresentation', 'keywordsTip') + '</div>').appendTo(this.cp.$keywordsWrapper);
  }

  // Keywords removal button.
  H5PEditor.$('<div class="h5p-keywordcontrols"><a href="#" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'disableKeywords') + '" class="h5p-keywordcontrols-button">x</a></div>').insertAfter(this.cp.$boxWrapper).children().click(function () {
    that.removeKeywords(H5PEditor.$(this));
    return false;
  });

  // Add our own menu to the drag and drop menu bar.
  that.$keywordsDNB = H5PEditor.$('<ul class="h5p-dragnbar-ul h5p-dragnbar-left"><li class="h5p-dragnbar-li"><a href="#" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'insertElement', {':type': 'main keyword'}) + '" class="h5p-dragnbar-a h5p-dragnbar-mainkeyword-button"></a></li><li class="h5p-dragnbar-li"><a href="#" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'insertElement', {':type': 'sub keyword'}) + '" class="h5p-dragnbar-a h5p-dragnbar-subkeyword-button"></a></li></ul>').prependTo(this.$bar);

  // We use this awesome library to make things easier.
  this.keywordsDNS = new H5P.DragNSort(this.cp.$keywords);

  this.keywordsDNS.startMovingCallback = function (event) {
    return that.keywordStartMoving(event);
  };

  this.keywordsDNS.moveCallback = function (x, y) {
    that.keywordMove(x, y);
  };

  this.keywordsDNS.swapCallback = function (direction) {
    that.swapKeywords(direction);
  };

  // Keyword events
  var keywordClick = function (event) {
    // Convert keywords into text areas when clicking.
    if (!that.keywordsDNS.moving && that.editKeyword(H5PEditor.$(this)) !== false) {
      event.stopPropagation();
    }
  };
  var keywordMousedown = function (event) {
    that.keywordsDNS.press(H5PEditor.$(this).parent(), event.pageX, event.pageY);
    return false;
  };
  var newKeyword = function ($li, newKeywordString, classes, x, y) {
    if (that.$keywordsTip !== undefined) {
      that.$keywordsTip.remove();
      delete that.$keywordsTip;
    }

    var $ol = $li.children('ol');
    if (!$ol.length) {
      $ol = H5PEditor.$('<ol class="h5p-keywords-ol"></ol>').appendTo($li);
    }
    var $element = H5PEditor.$('<li class="h5p-keywords-li h5p-new-keyword h5p-empty-keyword ' + classes + '"><span>' + newKeywordString + '</span></li>').appendTo($ol).children('span').click(keywordClick).mousedown(keywordMousedown).end();

    that.keywordsDNS.press($element, x, y);
    return false;
  };

  this.cp.$keywords.find('span').click(keywordClick).mousedown(keywordMousedown);

  this.$bar.find('.h5p-dragnbar-left > .h5p-dragnbar-li').click(function () {
    return false;
  }).filter(':first').mousedown(function (event) {
    // Create new keyword.
    var newKeywordString = H5PEditor.t('H5PEditor.CoursePresentation', 'newKeyword');

    // Add to params
    that.params[that.cp.$current.index()].keywords.push({main: newKeywordString});

    return newKeyword(that.cp.$keywords.children('.h5p-current'), newKeywordString, 'h5p-main-keyword', event.pageX, event.pageY);
  }).next().mousedown(function (event) {
    // Create new sub keyword.
    var newKeywordString = H5PEditor.t('H5PEditor.CoursePresentation', 'newKeyword');

    // Add to params
    var keywords = that.params[that.cp.$current.index()].keywords;
    if (!keywords.length) {
      return false;
    }
    keywords = keywords[keywords.length - 1];
    if (keywords.subs === undefined) {
      keywords.subs = [newKeywordString];
    }
    else {
      keywords.subs.push(newKeywordString);
    }

    return newKeyword(that.cp.$keywords.children('.h5p-current').children().children(':last'), newKeywordString, 'h5p-sub-keyword', event.pageX, event.pageY);
  });
};

/**
 * Keyword start moving handler.
 *
 * @param {object} event
 * @returns {Boolean} Indicates if we're ready to start moving.
 */
H5PEditor.CoursePresentation.prototype.keywordStartMoving = function (event) {
  // Make sure we're moving the keywords that belongs to this slide.
  this.keywordsDNS.$parent = this.keywordsDNS.$element.parent().parent();
  if (!this.keywordsDNS.$parent.hasClass('h5p-current')) {
    // Element is a sub keyword.
    if (!this.keywordsDNS.$parent.parent().parent().hasClass('h5p-current')) {
      return false;
    }
  }
  else {
    delete this.keywordsDNS.$parent; // Remove since we're not a sub keyword.
  }

  if (this.keywordsDNS.$element.hasClass('h5p-new-keyword')) {
    // Adjust new keywords to mouse pos.
    var height = this.keywordsDNS.$element.height() / 2;
    this.keywordsDNS.dnd.adjust.x += height;
    this.keywordsDNS.dnd.adjust.y += this.keywordsDNS.$element.offset().top - event.pageY + (height * 1.75);
    this.keywordsDNS.$element.removeClass('h5p-new-keyword');
  }

  this.keywordsDNS.dnd.scrollTop = this.cp.$keywords.scrollTop() - parseInt(this.cp.$keywords.css('marginTop'));
  return true;
};

/**
 * Keyword move handler.
 *
 * @param {int} x
 * @param {int} y
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.keywordMove = function (x, y) {
  // Check if sub keyword should change parent.
  if (this.keywordsDNS.$parent === undefined) {
    return;
  }

  var fontSize = parseInt(this.cp.$wrapper.css('fontSize'));

  // Jump up
  var $prev = this.keywordsDNS.$parent.prev();
  if ($prev.length && y < $prev.offset().top + ($prev.height() + this.keywordsDNS.marginAdjust + parseInt($prev.css('paddingBottom')) - (fontSize/2))) {
    return this.jumpKeyword($prev, 1);
  }

  // Jump down
  var $next = this.keywordsDNS.$parent.next();
  if ($next.length && y + this.keywordsDNS.$element.height() > $next.offset().top + fontSize) {
    return this.jumpKeyword($next, -1);
  }
};

/**
 * Update params after swapping keywords.
 *
 * @param {type} direction
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.swapKeywords = function (direction) {
  var keywords = this.params[this.cp.$current.index()].keywords;
  if (this.keywordsDNS.$parent !== undefined) {
    // We're swapping sub keywords.
    keywords = keywords[this.keywordsDNS.$parent.index()].subs;
  }

  var index = this.keywordsDNS.$element.index() - 1;
  var oldIndex = index + direction;
  var oldItem = keywords[oldIndex];
  keywords[oldIndex] = keywords[index];
  keywords[index] = oldItem;
};

/**
 * Move a sub keyword to another parent.
 *
 * @param {jQuery} $target The new parent.
 * @param {int} direction Indicates the direction we're jumping in.
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.jumpKeyword = function ($target, direction) {
  var $ol = $target.children('ol');
  if (!$ol.length) {
    $ol = H5PEditor.$('<ol class="h5p-keywords-ol"></ol>').appendTo($target);
  }

  // Remove from params
  var keywords = this.params[this.cp.$current.index()].keywords;
  var subs = keywords[this.keywordsDNS.$parent.index()];
  var item = subs.subs.splice(this.keywordsDNS.$element.index() - 1, 1)[0];
  if (!subs.subs.length) {
    delete subs.subs;
  }

  // Update UI
  if (direction === -1) {
    this.keywordsDNS.$element.add(this.keywordsDNS.$placeholder).prependTo($ol);
  }
  else {
    this.keywordsDNS.$element.add(this.keywordsDNS.$placeholder).appendTo($ol);
  }

  // Add to params
  subs = keywords[$target.index()];
  if (subs.subs === undefined) {
    subs.subs = [item];
  }
  else {
    subs.subs.splice(this.keywordsDNS.$element.index() - 1, 0, item);
  }

  // Remove ol if empty.
  $ol = this.keywordsDNS.$parent.children('ol');
  if (!$ol.children('li').length) {
    $ol.remove();
  }
  this.keywordsDNS.$parent = $target;
};

/**
 * Adds slide after current slide.
 *
 * @param {object} slideParams
 * @returns {undefined} Nothing
 */
H5PEditor.CoursePresentation.prototype.addSlide = function (slideParams) {
  var that = this;

  if (slideParams === undefined) {
    // Set new slide params
    slideParams = {
      elements: []
    };
    if (this.cp.$keywords !== undefined) {
      slideParams.keywords = [];
    }
  }

  var index = this.cp.$current.index() + 1;
  this.elements.splice(index, 0, []);
  this.cp.elementInstances.splice(index, 0, []);

  // Add slide with elements
  var $slide = H5P.jQuery(H5P.CoursePresentation.createSlide(slideParams)).insertAfter(this.cp.$current);
  for (var i = 0; i < slideParams.elements.length; i++) {
    this.cp.addElement(slideParams.elements[i], $slide);
  }

  // Add keywords
  if (slideParams.keywords !== undefined) {
    H5PEditor.$(this.cp.keywordsHtml(slideParams.keywords)).insertAfter(this.cp.$currentKeyword).click(function () {
      that.cp.keywordClick(H5PEditor.$(this));
    }).find('span').click(function (event) {
      // Convert keywords into text areas when clicking.
      if (!that.keywordsDNS.moving && that.editKeyword(H5PEditor.$(this)) !== false) {
        event.stopPropagation();
      }
    }).mousedown(function (event) {
      that.keywordsDNS.press(H5PEditor.$(this).parent(), event.pageX, event.pageY);
      return false;
    });
  }

  // Add to and update slideination.
  var $slideinationSlide = H5P.jQuery(H5P.CoursePresentation.createSlideinationSlide()).insertAfter(this.cp.$currentSlideinationSlide).children('a').click(function () {
    that.cp.jumpToSlide(H5P.jQuery(this).text() - 1);
    return false;
  }).end();
  that.updateSlideination($slideinationSlide, index);

  // Switch to the new slide.
  this.cp.nextSlide();

  // Update presentation params.
  this.params.splice(index, 0, slideParams);
};

/**
 * Update slideination numbering.
 *
 * @param {H5P.jQuery} $slideinationSlide
 * @param {int} index
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.updateSlideination = function ($slideinationSlide, index) {
  while ($slideinationSlide.length) {
    index += 1;
    $slideinationSlide.children().text(index);
    $slideinationSlide = $slideinationSlide.next();
  }
};

/**
 * Remove the current slide
 *
 * @returns {Boolean} Indicates success
 */
H5PEditor.CoursePresentation.prototype.removeSlide = function () {
  var index = this.cp.$current.index();
  var $remove = this.cp.$current.add(this.cp.$currentSlideinationSlide).add(this.cp.$currentKeyword);

  // Confirm and change slide.
  if (!confirm(H5PEditor.t('H5PEditor.CoursePresentation', 'confirmDeleteSlide'))) {
    return false;
  }

  // Change slide
  var move = this.cp.previousSlide() ? -1 : (this.cp.nextSlide(true) ? 0 : undefined);
  if (move === undefined) {
    return false; // No next or previous slide
  }

  // Remove visuals.
  $remove.remove();

  // Update slideination numbering.
  this.updateSlideination(this.cp.$currentSlideinationSlide, index + move);

  // Preserve the whole continuous text.
  if (this.params[index].ct !== undefined) {
    this.params[index + 1].ct = this.params[index].ct;
  }

  // ExportableTextArea needs to know about the deletion:
  H5P.ExportableTextArea.CPInterface.onDeleteSlide(index);

  // Update presentation params.
  this.params.splice(index, 1);

  // Remove element forms
  var slideKids = this.elements[index];
  if (slideKids !== undefined) {
    for (var i = 0; i < slideKids.length; i++) {
      H5PEditor.removeChildren(slideKids[i].children);
    }
    this.elements.splice(index, 1);
  }

  // Update the list of element instances
  this.cp.elementInstances.splice(index, 1);

  H5P.ContinuousText.Engine.run(this);
};

/**
 * Sort current slide in the given direction.
 *
 * @param {H5PEditor.$} $element The next/prev slide.
 * @param {int} direction 1 for next, -1 for prev.
 * @returns {Boolean} Indicates success.
 */
H5PEditor.CoursePresentation.prototype.sortSlide = function ($element, direction) {
  if (!$element.length) {
    return false;
  }

  var index = this.cp.$current.index();

  var keywordsEnabled = this.cp.$currentKeyword !== undefined;

  // Move slides and keywords.
  if (direction === -1) {
    this.cp.$current.insertBefore($element.removeClass('h5p-previous'));
    if (keywordsEnabled) {
      this.cp.$currentKeyword.insertBefore(this.cp.$currentKeyword.prev());
    }
  }
  else {
    this.cp.$current.insertAfter($element.addClass('h5p-previous'));
    if (keywordsEnabled) {
      this.cp.$currentKeyword.insertAfter(this.cp.$currentKeyword.next());
    }
  }

  if (keywordsEnabled) {
    this.cp.scrollToKeywords();
  }

  // Update slideination
  var newIndex = index + direction;
  this.cp.jumpSlideination(newIndex);

  // Need to inform exportable text area about the change:
  H5P.ExportableTextArea.CPInterface.changeSlideIndex(direction > 0 ? index : index-1, direction > 0 ? index+1 : index);

  // Update params.
  this.params.splice(newIndex, 0, this.params.splice(index, 1)[0]);
  this.elements.splice(newIndex, 0, this.elements.splice(index, 1)[0]);
  this.cp.elementInstances.splice(newIndex, 0, this.elements.splice(index, 1)[0]);

  H5P.ContinuousText.Engine.run(this);

  return true;
};

/**
 * Edit keyword.
 *
 * @param {H5PEditor.$} $span Keyword wrapper.
 * @returns {unresolved} Nothing
 */
H5PEditor.CoursePresentation.prototype.editKeyword = function ($span) {
  var that = this;

  var $li = $span.parent();
  var $ancestor = $li.parent().parent();
  var main = $ancestor.hasClass('h5p-current');

  if (!main && !$ancestor.parent().parent().hasClass('h5p-current')) {
    return false;
  }

  var $delete = H5PEditor.$('<a href="#" class="h5p-delete-keyword" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'deleteKeyword') + '"></a>');
  var $textarea = H5PEditor.$('<textarea>' + ($li.hasClass('h5p-empty-keyword') ? '' : $span.text()) + '</textarea>').insertBefore($span.hide()).keydown(function (event) {
    if (event.keyCode === 13) {
      $textarea.blur();
      return false;
    }
  }).keyup(function () {
    $textarea.css('height', 1).css('height', $textarea[0].scrollHeight - 8);
  }).blur(function () {
    var keyword = $textarea.val();

    if (H5P.trim(keyword) === '') {
      $li.addClass('h5p-empty-keyword');
      keyword = H5PEditor.t('H5PEditor.CoursePresentation', 'newKeyword');
    }
    else {
      $li.removeClass('h5p-empty-keyword');
    }

    // Update visuals
    $span.text(keyword).show();
    $textarea.add($delete).remove();

    // Update params
    var slideIndex = that.cp.$current.index();
    if (main) {
      that.params[slideIndex].keywords[$li.index()].main = keyword;
    }
    else {
      that.params[slideIndex].keywords[$li.parent().parent().index()].subs[$li.index()] = keyword;
    }
  }).focus();

  $textarea.keyup();

  $delete.insertBefore($textarea).mousedown(function () {
    // Remove keyword
    var slideIndex = that.cp.$current.index();
    if (main) {
      that.params[slideIndex].keywords.splice($li.index(), 1);
      $li.add($textarea).remove();
    }
    else {
      // Sub keywords
      var pi = $li.parent().parent().index();
      var $ol = $li.parent();
      if ($ol.children().length === 1) {
        delete that.params[slideIndex].keywords[pi].subs;
        $ol.remove();
      }
      else {
        that.params[slideIndex].keywords[pi].subs.splice($li.index(), 1);
        $li.add($textarea).remove();
      }
    }
  });
};

/**
 * Remove keywords sidebar.
 *
 * @param {jQuery} $button
 * @returns {Boolean}
 */
H5PEditor.CoursePresentation.prototype.removeKeywords = function ($button) {
  if (!confirm(H5PEditor.t('H5PEditor.CoursePresentation', 'removeKeywords'))) {
    return false;
  }

  this.$keywordsDNB.remove();
  $button.parent().add(this.cp.$keywordsWrapper).remove();
  delete this.cp.$keywordsWrapper;
  delete this.cp.$keywords;
  var oldWidth = parseFloat(this.cp.keywordsWidth);
  this.cp.keywordsWidth = 0;
  this.cp.slideWidthRatio = 1;
  this.cp.$slidesWrapper.removeClass('h5p-keyword-slides');
  for (var i = 0; i < this.params.length; i++) {
    if (this.params[i].keywords !== undefined) {
      delete this.params[i].keywords;
    }
    if (this.params[i].elements !== undefined) {
      for (var j = 0; j < this.params[i].elements.length; j++) {
        if (this.params[i].elements[j].x !== undefined) {
          this.params[i].elements[j].x = parseFloat(this.params[i].elements[j].x) + oldWidth;
          this.elements[i][j].$wrapper.css('left', this.params[i].elements[j].x + '%');
        }
        if (this.params[i].elements[j].width) {
          this.params[i].elements[j].width = parseFloat(this.params[i].elements[j].width) * (100 - oldWidth)/100;
          this.elements[i][j].$wrapper.css('width', this.params[i].elements[j].width + '%');
        }
      }
    }
  }
};

/**
 * Generate element form.
 *
 * @param {Object} elementParams
 * @param {String} machineName
 * @param {Boolean} isContinuousText
 * @returns {Object}
 */
H5PEditor.CoursePresentation.prototype.generateForm = function (elementParams, machineName, isContinuousText) {
  var that = this;

  if (isContinuousText && this.ct !== undefined) {
    // ContinuousText uses the form of the first CT element.
    this.ct.counter++;
    this.ct.lastIndex++;

    return {
      '$form': this.ct.form
    };
  }

  var popupTitle = H5PEditor.t('H5PEditor.CoursePresentation', 'popupTitle', {':type': machineName.split('.')[1]});
  var element = {
    '$form': H5P.jQuery('<div title="' + popupTitle + '"></div>')
  };
  H5PEditor.processSemanticsChunk(this.field.field.fields[0].field.fields, elementParams, element.$form, this);
  element.children = this.children;

  // Hide library selector
  element.$form.children('.library:first').children('label, select').hide().next().css('margin-top', '0');

  // Continuous text specific code
  if (isContinuousText) {
    // TODO: Clean up and remove unused stuff.
    this.ct = {
      form: element.$form,
      children: element.children,
      element: elementParams,
      counter: 1,
      lastIndex: 0,
      wrappers: []
    };
  }

  // Set correct aspect ratio on new images.
  var library = element.children[0];
  var libraryChange = function () {
    if (library.children[0].field.type === 'image') {
      library.children[0].changes.push(function (params) {
        if (params === undefined) {
          return;
        }

        if (params.width !== undefined && params.height !== undefined) {
          elementParams.height = elementParams.width * (params.height / params.width) * that.slideRatio * that.cp.slideWidthRatio;
        }
      });
    }
  };
  if (library.children === undefined) {
    library.changes.push(libraryChange);
  }
  else {
    libraryChange();
  }

  return element;
};

/**
 * Callback used by CP when a new element is added.
 *
 * @param {Object} elementParams
 * @param {jQuery} $wrapper
 * @param {Number} slideIndex
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.processElement = function (elementParams, $wrapper, slideIndex, elementInstance) {
  var that = this;
  var elementIndex = $wrapper.index();
  var machineName = H5P.libraryFromString(elementParams.action.library).machineName;
  var isContinuousText = (machineName === 'H5P.ContinuousText');
  var isDragQuestion = (machineName === 'H5P.DragQuestion');

  if (this.elements[slideIndex] === undefined) {
    this.elements[slideIndex] = [];
  }

  if (this.elements[slideIndex][elementIndex] === undefined) {
    this.elements[slideIndex][elementIndex] = this.generateForm(elementParams, machineName, isContinuousText);
  }
  var element = this.elements[slideIndex][elementIndex];
  element.$wrapper = $wrapper;

  if (isContinuousText) {
    element.children = [];
    // Index is needed to later find the correct wrapper:
    elementParams.index = this.ct.lastIndex;
    this.ct.wrappers[this.ct.lastIndex] = $wrapper;
  }

  // Edit when double clicking
  $wrapper.dblclick(function () {
    that.showElementForm(element, $wrapper, elementParams);
  });

  // Allow moving of element
  $wrapper.mousedown(function (event) {
    if (that.resizing) {
      return; // Disable when resizing
    }
    if (that.dnb !== undefined) {
      that.dnb.dnd.press(H5P.jQuery(this), event.pageX, event.pageY);
    }
    return false;
  });

  var elementSize = {};

  var ctReflowRunning = false;
  var startCTReflowLoop = function () {
    ctReflowRunning = true;
    // Note: Not using setInterval because the reflow may be so slow it will
    // creep across timer boundaries. Better to force a 250ms wait inbetween.
    setTimeout(function reflowLoop() {
      H5P.ContinuousText.Engine.run(that);

      // Keep reflowing until stopped.
      if (ctReflowRunning) {
        setTimeout(reflowLoop, 250);
      }
    }, 250);
  };

  // Allow resize
  var minSize = this.cp.fontSize * 2;
  $wrapper.resizable({
    minWidth: minSize,
    minHeight: minSize,
    containment: 'parent',
    stop: function () {
      elementParams.width = ($wrapper.width() + 2) / (that.cp.$current.innerWidth() / 100);
      elementParams.height = ($wrapper.height() + 2) / (that.cp.$current.innerHeight() / 100);
      that.resizing = false;
      if (isDragQuestion) {
        that.updateDragQuestion($wrapper, element, elementParams);
      }
      if (isContinuousText) {
        ctReflowRunning = false;
      }
    },
    start: function (event, ui) {
      if (isContinuousText) {
        startCTReflowLoop();
      }

      elementSize = {
        width: ui.size.width,
        height: ui.size.height
      };
    }
  }).children('.ui-resizable-handle').mousedown(function () {
    that.resizing = true;
  });

  // Remove button
  H5PEditor.$('<div class="h5p-element-remove" title="' + H5PEditor.t('H5PEditor.CoursePresentation', 'removeElement') + '"></div>').appendTo($wrapper).click(function () {
    if (confirm(H5PEditor.t('H5PEditor.CoursePresentation', 'confirmRemoveElement'))) {
      that.removeElement(element, $wrapper, isContinuousText);
    }
  });

  if(elementInstance.onAdd) {
    elementInstance.onAdd(elementParams, slideIndex);
  }
};

H5PEditor.CoursePresentation.prototype.updateDragQuestion = function($wrapper, element, elementParams) {
  var size = elementParams.action.params.question.settings.size;
  size.width = Math.round(this.cp.$current.width() * elementParams.width / 100);
  size.height = Math.round(this.cp.$current.height() * elementParams.height / 100);
  this.redrawElement($wrapper, element, elementParams);
};

/**
 * Removes element from slide.
 *
 * @param {Object} element
 * @param {jQuery} $wrapper
 * @param {Boolean} isContinuousText
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.removeElement = function (element, $wrapper, isContinuousText) {
  var slideIndex = this.cp.$current.index();
  var elementIndex = $wrapper.index();

  var elementInstance = this.cp.elementInstances[slideIndex][elementIndex];

  if (this.dnb !== undefined && this.dnb.dnd.$coordinates !== undefined) {
    this.dnb.dnd.$coordinates.remove();
    delete this.dnb.dnd.$coordinates;
  }

  if (element.children.length) {
    H5PEditor.removeChildren(element.children);
  }

  this.elements[slideIndex].splice(elementIndex, 1);
  this.cp.elementInstances[slideIndex].splice(elementIndex, 1);
  this.params[slideIndex].elements.splice(elementIndex, 1);

  $wrapper.remove();
  if(elementInstance.onDelete) {
    elementInstance.onDelete(this.params,slideIndex,elementIndex);
  }

  if (isContinuousText) {
    this.ct.counter--;
    H5P.ContinuousText.Engine.run(this);
  }
};

/**
 * Displays the given form in a popup.
 *
 * @param {jQuery} $form
 * @param {jQuery} $wrapper
 * @param {object} element Params
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.showElementForm = function (element, $wrapper, elementParams) {
  var that = this;

  var isContinuousText = (H5P.libraryFromString(elementParams.action.library).machineName === 'H5P.ContinuousText');
  if (isContinuousText) {
    // Make sure form uses the right text. There ought to be a better way of
    // doing this.
    that.ct.form.find('.text .ckeditor').first().html(that.params[0].ct);
  }

  element.$form.dialog({
    modal: true,
    draggable: false,
    resizable: false,
    width: '80%',
    dialogClass: "h5p-dialog-no-close",
    appendTo: '.h5p-course-presentation',
    buttons: [
      {
        text: H5PEditor.t('H5PEditor.CoursePresentation', 'remove'),
        class: 'h5p-remove',
        click: function () {
          if (H5PEditor.Html) {
            H5PEditor.Html.removeWysiwyg();
          }
          element.$form.dialog('close');
          that.removeElement(element, $wrapper, isContinuousText);
        }
      },
      {
        text: H5PEditor.t('H5PEditor.CoursePresentation', 'done'),
        click: function () {
          var elementKids = isContinuousText ? that.ct.children : element.children;

          // Validate children
          var valid = true;
          for (var i = 0; i < elementKids.length; i++) {
            if (elementKids[i].validate() === false) {
              valid = false;
            }
          }
          if (!valid) {
            return false;
          }

          // Need to do reflow, to populate all other CT's
          // and to get this CT's content after editing
          if (isContinuousText) {
            // Get value from form:
            that.params[0].ct = that.ct.element.action.params.text;
            // Run reflow for all elements:
            H5P.ContinuousText.Engine.run(that);
          }
          else {
            that.redrawElement($wrapper, element, elementParams);
          }
          if (H5PEditor.Html) {
            H5PEditor.Html.removeWysiwyg();
          }
          element.$form.dialog('close');
        }
      }
    ]
  });
  if (H5P.libraryFromString(elementParams.action.library).machineName === 'H5P.DragQuestion') {
    this.manipulateDragQuestion(element);
  }
};

H5PEditor.CoursePresentation.prototype.redrawElement = function($wrapper, element, elementParams) {
  var elementIndex = $wrapper.index();
  var slideIndex = this.cp.$current.index();
  var elementsParams = this.params[slideIndex].elements;
  var elements = this.elements[slideIndex];
  var elementInstances = this.cp.elementInstances[slideIndex];

  // Remove instance of lib:
  elementInstances.splice(elementIndex, 1);

  // Update params
  elementsParams.splice(elementIndex, 1);
  elementsParams.push(elementParams);

  // Update elements
  elements.splice(elementIndex, 1);
  elements.push(element);

  // Update visuals
  $wrapper.remove();

  this.cp.addElement(elementParams, undefined, slideIndex);
};


H5PEditor.CoursePresentation.prototype.manipulateDragQuestion = function(element) {
  // TODO: Remove this when H5P supports semantics overriding
  element.$form.find('.dimensions').hide();

  // Clear the setSize function of the dimensions object in DragQuestion
  // TODO: Remove this function, it is only useful for people with a beta7 version or older of the core
  element.children[0].children[2].children[0].children[1].setSize = function () {};

  // call setActive on the second step so that any changes to params takes effect
  element.children[0].children[2].children[1].setActive();
};

/**
 * Collect functions to execute once the tree is complete.
 *
 * @param {function} ready
 * @returns {undefined}
 */
H5PEditor.CoursePresentation.prototype.ready = function (ready) {
  if (this.passReadies) {
    this.parent.ready(ready);
  }
  else {
    this.readies.push(ready);
  }
};

// Tell the editor what widget we are.
H5PEditor.widgets.coursepresentation = H5PEditor.CoursePresentation;

// Add translations
H5PEditor.language["H5PEditor.CoursePresentation"] = {
  "libraryStrings": {
    "confirmDeleteSlide": "Are you sure you wish to delete this slide?",
    "sortSlide": "Sort slide - :dir",
    "removeSlide": "Remove slide",
    "cloneSlide": "Clone slide",
    "newSlide": "Add new slide",
    "insertElement": "Click and drag to place :type",
    "newKeyword": "New keyword",
    "deleteKeyword": "Remove this keyword",
    "removeKeywords": "Are you sure you wish to remove the keywords? This action cannot be undone.",
    "disableKeywords": "Remove keywords",
    "removeElement": "Remove this element",
    "confirmRemoveElement": "Are you sure you wish to remove this element?",
    "cancel": "Cancel",
    "done": "Done",
    "remove": "Remove",
    "keywordsTip": "Drag in keywords using the two buttons above.",
    "popupTitle": "Edit :type",
    "loading": "Loading..."
  }
};