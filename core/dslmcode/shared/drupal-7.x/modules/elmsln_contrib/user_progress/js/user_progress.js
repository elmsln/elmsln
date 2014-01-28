(function ($) {
// JavaScript Document
$(document).ready(function(){  // extend the drupal js object by adding in user_progress
  Drupal.user_progress = Drupal.user_progress || { functions: {} };
  // standard function to get / set results via AJAX
  Drupal.user_progress.ajax_call = function(call_type, up_action, params) {
    // establish the two parameters that we know will be there
    // burden is on the function calling ajax_call to provide others
    params += '&guid='+ Drupal.settings.user_progress.guid;
    params += '&nid='+ Drupal.settings.user_progress.nid;
    // send call
    $.ajax({
      type: "GET",
      url: Drupal.settings.user_progress.ajax_path +'/'+ call_type +'/'+ up_action,    
      data: params,
      success: function(msg){
        // store resulting record in case we want to update it
        Drupal.settings.user_progress.lastcall = msg;
      }
    });
  }
});
})(jQuery);