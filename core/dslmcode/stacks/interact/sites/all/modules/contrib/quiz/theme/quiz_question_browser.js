(function ($) {
/**
 * Sponsored by: Norwegian Centre for Telemedicine
 * Code: falcon
 *
 * @file
 * Javascript functions for the quizQuestionBrowser
 */

// The quiz object
var Quiz = Quiz || {inputEnabled:true};

/**
 * Adding behavior. Behaviors are called everytime a page is refreshed fully or through ahah.
 */

Drupal.behaviors.quizQuestionBrowserBehavior = {
  attach: function(context, settings) {

    $('.q-row input[id^=edit-auto-update-max-scores]').click(function() {
      var inputId = '#'+$(this).attr('id').replace('edit-auto-update-max-scores','edit-max-scores');
      console.log(inputId);
      
      if($(this).is(':checked')) {
        var original = $(inputId).attr('data-original');
        if(typeof original !== 'undefined' && original !== false) {
          $(inputId).val($(inputId).attr('data-original'));
        }
        
        $(inputId).parent().addClass('form-disabled');
        $(inputId).attr('disabled', 'disabled');
      }
      else {        
        var original = $(inputId).attr('data-original');
        if(typeof original == 'undefined' || original == false) {
          $(inputId).attr('data-original', $(inputId).val());
        }
        $(inputId).parent().removeClass('form-disabled');
        $(inputId).removeAttr('disabled');
      }
    });
    
    // Question rows in the browser
    $('.quiz-question-browser-row')
    .once()

    // Add selected class to already selected questions
    .filter(':has(:checkbox:checked)')
    .addClass('selected')
    .end()

    // When the browser row is clicked toggle the selected class and add the questions to the question list
    .click(function(event) {
      $(this).toggleClass('selected');
      if (event.target.type !== 'checkbox') {
        $(':checkbox', this).attr('checked', function() {
          return !this.checked;
        });
      }
      var idToShow = Quiz.findNidVidString(this.id);
      var oldHeight = $(document).height();
      if ($(this).hasClass('selected')) {
        // Show the question in the question list
        $('#question-list').css('display', 'table');
        $('#no-questions').hide();
        $('#q-' + idToShow).removeClass('hidden-question');
      } else {
        // Hide the question in the question list
        $('#q-' + idToShow).addClass('hidden-question');
      }
      $('#edit-stayers-' + idToShow).attr('checked', ($('#q-' + idToShow).hasClass('hidden-question')) ? false : true);
      Quiz.fixColorAndWeight($('#q-' + idToShow));
      var toScroll = $(document).height() - oldHeight;
      window.scrollBy(0, toScroll);
    });

    // Filter row in the browser

    // Mark all button
    $('#edit-browser-table-header-filters-all')
    .once()
    .click(function(event) {
      var ch = $(this).attr('checked');
      $('.quiz-question-browser-row').each(function() {
        if (!ch) {
          $(this).filter(':has(:checkbox:checked)').each(function() {
            $(this).click();
          });
        }
        else {
          $(this).filter(':has(:checkbox:not(:checked))').each(function() {
            $(this).click();
          });
        }
      });
    });

    // Type and date filters
    var selector = '#edit-browser-table-header-filters-type';
    selector += ', #edit-browser-table-header-filters-changed';
    $(selector)
    .once()
    .change(function(event) {
      $('#browser-pager').remove();
      Quiz.setInputEnabled(false);
    });

    //Title and username filters
    var quizRefreshId;
    selector = '#edit-browser-table-header-filters-title';
    selector += ', #edit-browser-table-header-filters-name';
    $(selector)
    .once()
    // triggering custom event "doneTyping" one second after the last key up in the text fields...
    .keyup(function(event) {
      clearInterval(quizRefreshId);
      var quizClicked = this;
      quizRefreshId = setInterval(function(){
        $('#browser-pager').remove();
        $(quizClicked).trigger('doneTyping');
        clearInterval(quizRefreshId);
        Quiz.setInputEnabled(false);
      }, 1000);
    });

    // Sorting

    // Making datastructure holding all sortable colums and the events that triggers sorting
    var toSort = [
      {
        name: 'title',
        event: 'doneTyping'
      },
      {
        name: 'name',
        event: 'doneTyping'
      },
      {
        name: 'type',
        event: 'change'
      },
      {
        name: 'changed',
        event: 'change'
      }
    ];

    for (i in toSort) {
      $('.quiz-browser-header-'+ toSort[i].name +' > a')
      .once()
      .attr('myName', toSort[i].name)
      .attr('myEvent', toSort[i].event)
      .click(function(event) {
        if (!Quiz.inputEnabled) {
          event.preventDefault();
          return;
        }
        var myUrl = $(this).attr('href');
        myUrl = myUrl.slice(myUrl.indexOf('?') + 1);
        // add-to-get is the query string used by drupals tablesort api.
        // We need to post the query string to drupal since we are using ajax.
        // The querystring will be added to $_REQUEST on the server.
        $('#edit-browser-table-add-to-get').val(myUrl);
        $('#edit-browser-table-header-filters-'+ $(this).attr('myName')).trigger($(this).attr('myEvent'));
        event.preventDefault();
        Quiz.setInputEnabled(false);
      });
    }
    /*
    // Pager
    $('.pager-item a'+ notDone +', .pager-first a'+ notDone +', .pager-next a'+ notDone +', .pager-previous a'+ notDone +', .pager-last a'+ notDone)
    .addClass(done)
    .click(function(event){
      if (!Quiz.inputEnabled) {
        event.preventDefault();
        return;
      }
      var myUrl = $(this).attr('href').substr(2);
      Quiz.updatePageInUrl(myUrl);
      $('.quiz-question-browser-row').remove();
      $('#edit-browser-table-filters-title').trigger('doneTyping');
      event.preventDefault();
      Quiz.setInputEnabled(false);
    });
    */
  // If js is active we don't want to show a checkbox for selecting questions
    $('.q-staying').css('display', 'none');
    // If js is active we use a link to remove questions from the question list
    $('.q-remove').css('display', 'inline');

    $('.handle-changes').click(function(event){
      if ($('#mq-fieldset .tabledrag-changed').length) {
        var proceed = confirm(Drupal.t('Any unsaved changes will be lost. Are you sure you want to proceed?'));
        if (!proceed)
          event.preventDefault();
      }
    });
    $('.q-compulsory').click(function(event){
      var idToToggle = Quiz.findNidVidString(this.id);
      if(this.checked) {
        $('#edit-max-scores-' + idToToggle).show();
      }
      else {
        $('#edit-max-scores-' + idToToggle).hide();
      }
    });
    $('.q-compulsory').each(function(){
      var idToToggle = Quiz.findNidVidString(this.id);
      if(!this.checked) {
        $('#edit-max-scores-' + idToToggle).hide();
      }
    });
  }
};


/**
 * Adding behavior. Behaviors are called everytime a page is refreshed fully or through ahah.
 */
Drupal.behaviors.attachRemoveAction = {
  attach: function (context, settings) {
    $('.rem-link:not(.attachRemoveAction-processed)')
    .addClass('attachRemoveAction-processed')
    .click(function (e) {
      var $this = $(this);
      var remID = $this.parents('tr').attr('id');
      var matches = remID.match(/[0-9]+-[0-9]+/);
      if (!matches || matches.length < 1) {
        return false;
      }
      Quiz.fixColorAndWeight($this.parents('tr'));

      //Hide the question
      $this.parents('tr').filter(':first').addClass('hidden-question');

      // Mark the question as removed
      $('#edit-stayers-' + matches[0]).attr('checked', false);

      // Uncheck the question in the browser
      $('#browser-'+ matches[0]).click();

      var table = Drupal.tableDrag['question-list'];
      if (!table.changed) {
        table.changed = true;
        $(Drupal.theme('tableDragChangedWarning')).insertAfter(table.table).hide().fadeIn('slow');
      }

      e.preventDefault();
      return true;
    });
  }
};




// This is only called once, not on ajax refreshes...
$(document).ready(function () {

  // There are some problems with table headers and ajax. We try to reduce those problems here...
  var oldTableHeader = Drupal.behaviors.tableHeader;
  Drupal.behaviors.tableHeader = function(context) {
    if (!$('table.sticky-enabled', context).size()) {
    return;
  }
    oldTableHeader(context);
  };

  // If a browser row is selected make sure it gets marked.
  $('.quiz_question_browser_row:has(:checkbox:checked)').each(function() {
    $(this).click();
  });

  // If validation of the form fails questions added using the browser will become invisible.
  // We fix this problem here:
  $('.q-row').each(function() {
    if ($('.q-staying', $(this)).attr('checked')) $(this).removeClass('hidden-question');
  });
});

/**
 * Updates the page part of the query string in the add-to-get hidden field
 *
 * @param myUrl
 *   The url in the links in the pager(string)
 */
Quiz.updatePageInUrl = function(myUrl) {
  // Finds page from input parameter
  var pageQuery = myUrl + '';
  var pattern = new RegExp('page=[0-9]+');
  pageQuery = pattern.exec(pageQuery);
  if (pageQuery == null) pageQuery = 'page=0';

  //Replaces stored query strings page with our page
  var currentQuery = jQuery('#edit-browser-table-add-to-get').val() + '';
  currentQuery = currentQuery.replace(pattern, '');
  currentQuery += pageQuery;
  jQuery('#edit-browser-table-add-to-get').val(currentQuery);
};

/**
 * Restripes the question list and adjusts the weight fields
 *
 * @param newest
 *   The row that last was added to the question list(jQuery object)
 */
Quiz.fixColorAndWeight = function(newest) {
  var nextClass = 'odd';
  var lastClass = 'even';
  var lastWeight = 0;
  var lastQuestion = null;
  var numQRows = 0;


    $('.q-row').each(function() {
      if (!$(this).hasClass('hidden-question') && $(this).attr('id') != newest.attr('id')) {
        // Color:
        numQRows++;
        if (!$(this).hasClass(nextClass)) $(this).removeClass(lastClass).addClass(nextClass);
        var currentClass = nextClass;
        nextClass = lastClass;
        lastClass = currentClass;
        lastQuestion = $(this);

        // Weight:
        var myId = Quiz.findNidVidString($(this).attr('id') + '');
        var weightField = $('#edit-weights-' + myId);
        weightField.val(lastWeight);
        lastWeight++;
      }
    });


  if (numQRows < 2) return;

  if (!newest.hasClass(nextClass)) newest.removeClass(lastClass).addClass(nextClass);
  var newestId = Quiz.findNidVidString(newest.attr('id'));

  //We move the newest question to the bottom of the list
  newest.insertAfter('#q-'+ Quiz.findNidVidString(lastQuestion.attr('id')));
  $('#edit-weights-' + newestId).val(lastWeight);
  var marker = Drupal.theme('tableDragChangedMarker');
  var cell = $('td:first', newest);
  if ($('span.tabledrag-changed', cell).length == 0) {
    cell.append(marker);
  }
  var table = Drupal.tableDrag['question-list'];
  if (!table.changed) {
    table.changed = true;
    $(Drupal.theme('tableDragChangedWarning')).insertAfter(table.table).hide().fadeIn('slow');
  }
};

/**
 * Finds and returns the part of a string holding the nid and vid
 *
 * @param str
 *   A string that should have nid and vid inside it on this format: nid-vid, for instance 23-24
 */
Quiz.findNidVidString = function(str) {
  var pattern = new RegExp('[0-9]+-[0-9]+');
  return pattern.exec(str);
};


/**
 * Adds question rows to the question list
 *
 * @param rowHtml
 *   The question rows to be added(html string)
 */
Quiz.addQuestions = function (rowHtml) {
  //Add the new rows:
  $('#question-list tr:last').after(rowHtml);

  var table = Drupal.tableDrag['question-list'];

  $('.hidden-question').each(function(){
	// Hide weight column:
    $('td:last', this).css('display', 'none');

    table.makeDraggable(this);
  });

  Drupal.attachBehaviors(table.table);
};

/**
 * Turn all input elements on or off
 *
 * @param enabled
 *   Should the inputs be swithced on or off?
 */
Quiz.setInputEnabled = function(enabled) {
  Quiz.inputEnabled = enabled;
  if (enabled) {
    $('.quizQuestionBrowserBehavior-processed').removeAttr('disabled');
  }
  else {
  jQuery('.quizQuestionBrowserBehavior-processed').attr('disabled', true);
  }
}

})(jQuery);
