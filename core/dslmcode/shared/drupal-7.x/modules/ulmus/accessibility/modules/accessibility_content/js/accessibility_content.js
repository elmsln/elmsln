(function($) {
  Drupal.behaviors.accessibilityContent = {
    
    messages : {},

    formErrors : {},
    
    attach: function (context) {
      if (Drupal.settings.accessibility_content.options.form) {
        this.checkForm();
      }
      else {
        if (Drupal.settings.accessibility_content.show_toggle) {
          this.addToggle();
        }
        else {
          if (Drupal.settings.accessibility_content.show_default) {
            this.checkContent();
          }
        }
      }
    },
    
    checkForm : function() {
      var that = this;
      $('.accessible-content-check-form').each(function() {
        that.checkFormElement($(this));
        $(this).change(function() {
          that.checkFormElement($(this));
        });
      });
    },

    checkFormElement : function($element) {
      var that = this;
      var current = 0;
      $element.data('accessible-content-errors', 0);
      var severity = $element.data('accessible-content-severity').split(',');
      Drupal.accessibility.checkElement($($element.val()), function(event) {
        if (severity.indexOf(event.severity) > -1) {
          current++;
          $element.data('accessible-content-errors', current);
        }
        that.checkFormStatus($element.parents('form'));
      }, function() { }, 'content');
    },

    checkFormStatus : function($form) {
      var total = 0;
      $form.find('.accessible-content-check-form').each(function() {
        total += $(this).data('accessible-content-errors');
        if ($(this).data('accessible-content-errors')) {
          $(this).addClass('error');
        }
        else {
          $(this).removeClass('error');
        }
      });
      if (total) {
        $form.find('[type=submit]')
             .attr('disabled', 'disabled')
             .addClass('disabled');
      }
      else {
        $form.find('[type=submit]')
             .removeAttr('disabled')
             .removeClass('disabled');
      }
    },
    
    addToggle : function() {
      var that = this;
      var $toggle = $('<div>').attr('id', 'accessibility-content-toggle')
                              .addClass('accessibility-content-toggle');
      var $link = $('<a>').html(Drupal.settings.accessibility_content.toggle.off_message)
                          .attr('role', 'button')
                          .attr('href', '#');
      $toggle.append($link);
      $('body').append($toggle);
      $('#accessibility-content-toggle a').bind('click', function() {
        if ($('body').hasClass('accessibility-checked')) {
          $(this).html(Drupal.settings.accessibility_content.toggle.off_message);
          $('body').removeClass('accessibility-checked');
          Drupal.accessibility.cleanUpHighlight();
          Drupal.accessibility.errorConsole.hide();
        }
        else {
          $(this).html(Drupal.settings.accessibility_content.toggle.on_message);
          that.checkContent();
        }
        return false;
      });
      if (Drupal.settings.accessibility_content.show_default) {
        $('#accessibility-content-toggle a').click();
      }
      $('body').bind('accessibility-console-show', function() {
        var height = $('#accessibility-console').outerHeight();
        $('#accessibility-content-toggle').css('bottom', height + 'px');
      });
      $('body').bind('accessibility-console-hide', function() {
        $('#accessibility-content-toggle').css('bottom', '0px');
      });
    },
    
    checkContent : function() {
      var that = this;
      if ($('body').hasClass('accessibility-checked')) {
        return;
      }
      $('body').addClass('accessibility-checked');
      Drupal.accessibility.checkElement($('.ac-check-field'), false, function() { }, 'content');
    }
  };
})(jQuery);
