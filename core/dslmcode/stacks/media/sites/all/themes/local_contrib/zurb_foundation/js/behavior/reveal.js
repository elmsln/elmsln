Drupal.behaviors.zurbReveal = {
  attach: function(context, settings) {
    jQuery('#status-messages.reveal-modal', context).foundation('reveal', 'open');
  }
}