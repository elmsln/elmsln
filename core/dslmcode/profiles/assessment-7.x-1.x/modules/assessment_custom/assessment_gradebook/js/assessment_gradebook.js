/**
* Provide the HTML to create the modal dialog.
*/
(function ($) {
  Drupal.theme.prototype.assessment_gradebook_modal = function () {
    var html = '<div id="ctools-modal" class="popups-box">';
    html += '  <div class="ctools-modal-content ctools-modal-assessment-gradebook-modal-content">';
    html += '    <span class="popups-close"><a class="close ctools-modal-assessment-gradebook-close" href="#">' + Drupal.CTools.Modal.currentSettings.closeImage + '</a></span>';
    html += '    <div><div id="modal-content" class="expand reveal-modal-open modal-content popups-body"></div></div>';
    html += '  </div>';
    html += '</div>';
    return html;
  }
  // ability to disable background scrolling on modal open
  Drupal.behaviors.gradebookBodyScrollDisable = {
  attach: function (context, settings) {
    $('.ctools-modal-assessment-gradebook-close').on("click", function () {
      $("body").removeClass("scroll-disabled")
    });
  }
  };
  // ajax submit cause ctools apparently doesn't support this w/ DS
  Drupal.behaviors.gradebookAssessmentSubmit = {
    'attach': function(context) {
      // checkboxes need prop set to be displayed dynamically
      if ($('#modal-content input[name=flag_submission_value]').val() == 1) {
        $('#modal-content input[name=flag_submission]').prop('checked', true);
      }
      $('#modal-content input[name=flag_submission]').val($('#modal-content input[name=flag_submission_value]').val());
      // select state
      $('#modal-content select[name=assessment_state]').val($('#modal-content input[name=assessment_state_value]').val());
      // set point value
      $('#modal-content input[name=assessment]').val($('#modal-content input[name=assessment_value]').val());
      // bind click event to fake the submission via ajax and update what we have to
      $('#modal-content .form-submit', context).bind('click', function() {
        // structure the data
        var data = {
          flag: $('#modal-content input[name=flag_submission]').val(),
          state: $('#modal-content select[name=assessment_state]').val(),
          points: $('#modal-content input[name=assessment]').val()
        };
        // kick off the ajax request to update the values with those selected
        $.ajax({
          url: Drupal.settings.basePath + 'gradebook/ajax/' + Drupal.settings.assessmentGradebookToken + '/' + $('#modal-content input[name=aid]').attr('value') + '/' + $('#modal-content input[name=submission]').attr('value'),
          type: 'POST',
          data: data,
        })
        .done(function(data) {
          var returned = jQuery.parseJSON(data);
          // update the grid where we have a match from the data returned
          sublight = '.assessment-submission-' + $('#modal-content input[name=submission]').attr('value');
          $(sublight).attr('src', $(sublight).attr('src').replace($('#modal-content input[name=assessment_state_value]').val(), returned.state));
          // close window
          $('.ctools-modal-assessment-gradebook-close').click();
        })
        .fail(function(data) {
          alert(Drupal.t('Save failed'));
        });
        return false;
      });
    }
  };
  // bind these events only once
  $(document).ready(function(){
    $('.ctools-modal-assessment-gradebook-modal.disable-scroll').on("click", function () {
      $("body").addClass("scroll-disabled");
    });
    // @todo need to disable escape closing colorbox or both events firing
    // if colorbox open, can't close ctools modal
    // if colorbox closed, can close ctools modal this way
    // maybe use unbind event
    // Bind a keypress on escape for closing the modalContent
    $(document).bind('keydown', function(event) {
      if (event.keyCode == 27) {
        $("body").removeClass("scroll-disabled")
        return false;
      }
    });
  });
})(jQuery);
