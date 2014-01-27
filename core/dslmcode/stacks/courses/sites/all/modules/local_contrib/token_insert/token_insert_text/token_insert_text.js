
/**
 * Behavior to add "Insert" buttons.
 */
(function ($) {
Drupal.behaviors.TokenInsertText = {
  attach: function(context) {
    // Add the click handler to the insert button.
    if(!(typeof(Drupal.settings.token_insert) == 'undefined')){
      for(var key in Drupal.settings.token_insert.buttons){
        $("#" + key, context).click(insert);
      }
    }

    function insert() {
      var field = $(this).attr('id');
      var selectbox = field.replace('button', 'select');
      var content = '[' + $('#' + selectbox ).val() + ']';
      $('#' + Drupal.settings.token_insert.buttons[field]).insertAtCursor(content);
      return false;
    }
  }
};
})(jQuery);

