/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal:true, jQuery: true*/
/**
 * Behavior to add "Insert" buttons.
 */
(function ($, Drupal) {
  "use strict";
  Drupal.behaviors.TokenInsertText = {
    attach: function(context) {
      function insert (e){
        var $self = $(this);
        e.preventDefault();
        var token = $self.text();
        var id = $self.closest('.token-insert-text-table').attr('id');
        $('#' + Drupal.settings.token_insert.tables[id]).insertAtCursor(token);
      }
      function bindInsert(id) {
        $(context).find("#" + key).find('.token-insert-table .token-key').once('token-insert-table', function() {
          var newThis = $('<a href="javascript:void(0);" title="' + Drupal.t('Insert this token into your form') + '">' + $(this).html() + '</a>').click(insert);
          $(this).html(newThis);
        });
      }

      // Add the click handler to the insert button.
      if (typeof(Drupal.settings.token_insert) !== 'undefined') {
        for (var key in Drupal.settings.token_insert.tables) {
          if (Drupal.settings.token_insert.tables.hasOwnProperty(key)) {
            bindInsert(key, context);
          }
        }
      }
    }
  };
})(jQuery, Drupal);
