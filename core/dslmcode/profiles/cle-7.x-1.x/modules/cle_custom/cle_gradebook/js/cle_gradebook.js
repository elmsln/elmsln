/**
* Provide the HTML to create the modal dialog.
*/
(function ($) {
Drupal.theme.prototype.cle_gradebook_modal = function () {
  var html = '';
  html += '<div id="ctools-modal" class="popups-box">';
  html += '  <div class="ctools-modal-content ctools-modal-cle-gradebook-modal-content">';
  html += '    <span class="popups-close"><a class="close" href="#">' + Drupal.CTools.Modal.currentSettings.closeImage + '</a></span>';
  html += '    <div class="modal-scroll"><div id="modal-content" class="modal-content popups-body"></div></div>';
  html += '  </div>';
  html += '</div>';
  return html;
}
})(jQuery);
