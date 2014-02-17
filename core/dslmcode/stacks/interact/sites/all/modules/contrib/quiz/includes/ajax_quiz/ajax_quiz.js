
Drupal.AjaxLoadExample = Drupal.AjaxLoadExample || {};

/**
 * Ajax load example behavior.
 */
Drupal.behaviors.AjaxLoadExample = function (context) {
  // to proceed with the quiz
  $('.form-submit:not(.form-submit-clicked)', context)
    .each(function () {
      // The target should not be e.g. a node that will itself be
      // replaced, as this would mean no node is available for
      // ajax_load to attach behaviors to when all scripts are loaded.
      var target = this.parentNode;
      $(this)
        .addClass('form-submit-clicked')
        .click(function () {
          var tries = '';
          $('[name^="tries"]:not(.form-submit-clicked)').each(function (i) {
            switch(this.type) {
            case 'radio':
            case 'checkbox':
            	if (this.checked) {
            		tries += '&' + this.name + '=' + this.value;
            	}
            	break;
            default:
            	tries += '&' + this.name + '=' + this.value;
            	break;
            }
            $(this).addClass('form-submit-clicked');
          });
          $(this).attr('disabled', true);
          $.ajax({
            // Either GET or POST will work.
            type: 'POST',
            data: 'ajax_load_example=1&op=Next'+tries,
            // Need to specify JSON data.
            dataType: 'json',
            url: $(this).attr('href'),
            success: function(response) {
              $(this).prepend('answer saved');
              // Call all callbacks.
              //alert('sucess');
              if (response.__callbacks) {
                $.each(response.__callbacks, function(i, callback) {
                  // The first argument is a target element, the second
                  // the returned JSON data.
                  //alert(response);
                  eval(callback)(target, response);
                });
                // If you don't want to return this module's own callback,
                // you could of course just call it directly here.
                // Drupal.AjaxLoadExample.formCallback(target, response);
              }
            },
            error: function(xhr, opt, err) {
              alert(xhr.statusText);
              alert(opt);
              alert(err);
            },
          });
          return false;
        });
    });
  // to start the quiz
  $('a.ajax-load-example:not(.ajax-load-example-processed)', context)
    .each(function () {
      // The target should not be e.g. a node that will itself be
      // replaced, as this would mean no node is available for
      // ajax_load to attach behaviors to when all scripts are loaded.
      var target = this.parentNode;
      $(this)
        .addClass('ajax-load-example-processed')
        .click(function () {
          $.ajax({
            // Either GET or POST will work.
            type: 'POST',
            data: 'ajax_load_example=1',
            // Need to specify JSON data.
            dataType: 'json',
            url: $(this).attr('href'),
            success: function(response){
              // Call all callbacks.
              if (response.__callbacks) {
                $.each(response.__callbacks, function(i, callback) {
                  // The first argument is a target element, the second
                  // the returned JSON data.
                  eval(callback)(target, response);
                });
                // If you don't want to return this module's own callback,
                // you could of course just call it directly here.
                // Drupal.AjaxLoadExample.formCallback(target, response);
              }
            },
            error: function(){
              alert('An error has occurred. Please try again.');
            },
          });
          return false;
        });
    });
};

/**
 * Ajax load example callback.
 */
Drupal.AjaxLoadExample.formCallback = function (target, response) {
  target = $(target).append(response.content);
  Drupal.attachBehaviors(target);
};


