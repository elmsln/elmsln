// $Id$

(function($){
if (Drupal.settings.admin_menu_dropdown.default) {
  $(document).ready(function(){$('#admin-menu').hide();$('body').addClass('adm_menu_hidden');});
}
$(document).keypress(function(e) {
  var unicode=e.keyCode? e.keyCode : e.charCode;
  if (String.fromCharCode(unicode)==Drupal.settings.admin_menu_dropdown.key){
    $('#admin-menu').slideToggle('fast');
    // TODO: Maybe animate the margin change so its not so jumpy?
    $('body').toggleClass('adm_menu_hidden');
  }
});
})(jQuery);
