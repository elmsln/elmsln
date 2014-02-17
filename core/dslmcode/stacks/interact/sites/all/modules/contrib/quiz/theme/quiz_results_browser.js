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

Drupal.behaviors.quizResultsBrowserBehavior = {
  attach: function(context, settings) {
    // Result rows in the browser
    $('.quiz-results-browser-row').once()

    // Add selected class to already selected results
    .filter(':has(:checkbox:checked)')
    .addClass('selected')
    .end()

    // When the browser row is clicked toggle the selected class
    .click(function(event) {
      if (typeof event.target.href == 'string') return;
      if ($(':checkbox', this).attr('DISABLED')) return;
      $(this).toggleClass('selected');
      $('.quiz-hover-menu', this).addClass('stop-anim');
      if (event.target.type !== 'checkbox') {
        $(':checkbox', this).attr('checked', function() {
          return !this.checked;
        });
      }
    })
    .hover(
      function() {
        if ($(':checkbox', this).attr('disabled')) return;
        $('.quiz-hover-menu', this)
        .css('opacity', 1);
      },
      function() {
        $('.quiz-hover-menu', this).css('opacity', 0);
      }
    );

    $('.hover-del').once()
    .click(function(event) {
      $('.quiz-results-browser-row:has(:checkbox:checked)').click();
      var nidRid = Quiz.findNidRidString($(event.target).attr('id'));
      $('#edit-table-body-name-' + nidRid).click();
      $('#edit-bulk-action').val('del');
      $('#edit-update--2').click();
      event.preventDefault();
      event.stopPropagation();
    });
    // Filter row in the browser

    // Mark all button
    $('#edit-table-header-filters-all').once()
    .click(function(event) {
      var ch = $(this).attr('checked');
      $('.quiz-results-browser-row').each(function() {
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

    $('#edit-table-header-filters-best-results, #edit-table-header-filters-not-in-progress').once()
    .click(function(event) {
      $('#browser-pager').remove();
      Quiz.setInputEnabled(false);
    });

    // started, finished, duration and score filters
    this.selector = '#edit-table-header-filters-started';
    this.selector += ', #edit-table-header-filters-finished';
    this.selector += ', #edit-table-header-filters-duration';
    this.selector += ', #edit-table-header-filters-score';
    this.selector += ', #edit-table-header-filters-evaluated';
    $(this.selector).once()
    .change(function(event) {
      $('#browser-pager').remove();
      Quiz.setInputEnabled(false);
    });

    // Username filters
    var quizRefreshId;
    $('#edit-table-header-filters-name').once()
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
        name: 'name',
        event: 'doneTyping'
      },
      {
        name: 'started',
        event: 'change'
      },
      {
        name: 'finished',
        event: 'change'
      },
      {
        name: 'score',
        event: 'change'
      },
      {
        name: 'evaluated',
        event: 'change'
      }
    ];

    for (i in toSort) {
      $('.quiz-browser-header-'+ toSort[i].name +' > a').once()
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
        $('#edit-table-add-to-get').val(myUrl);
        if ($(this).attr('myName') == 'name') $('#edit-table-header-filters-all').hide();
        $('#edit-table-header-filters-'+ $(this).attr('myName')).trigger($(this).attr('myEvent'));
        Quiz.setInputEnabled(false);
        event.preventDefault();
      });
    }

    // Pager
    $('.pager-item a, .pager-first a, .pager-next a, .pager-previous a, .pager-last a').once()
    .click(function(event) {
      if (!Quiz.inputEnabled) {
        event.preventDefault();
        return;
      }
      var myUrl = $(this).attr('href').substr(2);
      Quiz.updatePageInUrl(myUrl);
      $('#edit-table-header-filters-all').hide();
      $('.quiz-results-browser-row').remove();
      $('#edit-table-header-filters-name').trigger('doneTyping');
      event.preventDefault();
      Quiz.setInputEnabled(false);
    });
    $('.quiz-hover-menu').css('opacity', 0);
    $('#edit-table-header-filters-all').show();
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
  $('.quiz_results_browser_row:has(:checkbox:checked)').each(function() {
    $(this).click();
  });

  $('#edit-update--2').click(function(event){
    if ($('#edit-bulk-action').val() == 'del') {
      $('#quiz-results-update').css('display', 'none');
      $('#quiz-results-confirm-delete').css('display', 'block');
      //$('input:not(#edit-confirm-delete--2), select').attr('DISABLED', true);
      event.preventDefault();
      $('.quiz-hover-menu').hide();
    }
  });
  $('#quiz-results-cancel-delete').click(function(event){
	  $('#quiz-results-update').css('display', 'block');
	  $('#quiz-results-confirm-delete').css('display', 'none');
	  //$('input:not(#edit-confirm-delete--2), select').removeAttr('DISABLED');
	  event.preventDefault();
	  $('.quiz-hover-menu').show();
  });
  $('#edit-confirm-delete').click(function(event){
    //$('input:not(#edit-confirm-delete--2), select').removeAttr('DISABLED');
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
  var currentQuery = $('#edit-table-add-to-get').val() + '';
  currentQuery = currentQuery.replace(pattern, '');
  currentQuery += pageQuery;
  $('#edit-table-add-to-get').val(currentQuery);
};

/**
 * Finds and returns the part of a string holding the nid and vid
 *
 * @param str
 *   A string that should have nid and vid inside it on this format: nid-vid, for instance 23-24
 */
Quiz.findNidRidString = function(str) {
  var pattern = new RegExp('[0-9]+-[0-9]+');
  return pattern.exec(str);
};

/**
 * Turn all input elements on or off
 *
 * @param on
 *   Should the inputs be swithced on or off?
 */
Quiz.setInputEnabled = function(enabled) {
  Quiz.inputEnabled = enabled;
  if (enabled) {
    $('.quizResultsBrowserBehavior-processed').removeAttr('disabled');
  }
  else {
    $('.quizResultsBrowserBehavior-processed').attr('disabled', true);
  }
}

})(jQuery);
