(function ($) {

  Drupal.behaviors.codefilter = {
    attach:function (context) {
      // Provide expanding text boxes when code blocks are too long.
      $("div.codeblock.nowrap-expand", context).each(function () {
          var contents_width = $(this).contents().width();
          var width = $(this).width();
          if (contents_width > width) {
            $(this).hover(function () {
              // Add a small right margin to width.
              $(this).animate({ width:(contents_width + 10) + "px"}, 250, function () {
                $(this).css('overflow-x', 'visible');
              });
            },
            function () {
              $(this).css('overflow-x', 'hidden').animate({ width:width + "px" }, 250);
            });
          }
        }
      );
    }
  }

})(jQuery);
