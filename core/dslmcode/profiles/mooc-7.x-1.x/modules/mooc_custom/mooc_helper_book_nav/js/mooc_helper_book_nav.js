(function ($) {
$(document).ready(function() {
  document.onkeyup = function(e) {
    if(document.all) {
      e = event;
    }
    if(e.keyCode==37){  // left key
      if ($('.page-previous').attr('href')) {
        window.location = $('.page-previous').attr('href');
        return false;
      }
    }
    if(e.keyCode==39){  // right key
      if ($('.page-next').attr('href')) {
        window.location = $('.page-next').attr('href');
        return false;
      }
    }
    if(e.keyCode==79){  // outline key
      $('.mooc-helper-toc').click();
      return false;
    }
  };
 });
})(jQuery);
