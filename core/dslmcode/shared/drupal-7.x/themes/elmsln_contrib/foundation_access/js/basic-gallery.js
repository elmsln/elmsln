(function($) {
  $(document).ready(function(){
    $('.elmsln-basic-gallery a').click(function(){
      var img = $(this).children('img');
      var trigger = $(this).attr('data-elmsln-triggers');
      $('#' + trigger).attr('href', $(this).attr('data-elmsln-lightbox'));
      $('#' + trigger).children('.elmsln-featured-image-title').html($(img).attr('title'));
      $('#' + trigger).children('img').attr('src', $(img).attr('src')).attr('alt', $(img).attr('alt')).attr('title', $(img).attr('title'));
    });
  });
})(jQuery);