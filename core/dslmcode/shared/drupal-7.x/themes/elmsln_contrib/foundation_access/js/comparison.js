(function($) {
	$(document).ready(function(){
    $(".resizable").resizable({
      maxHeight: 316,
      maxWidth: 630,
      minHeight: 10,
      minWidth: 10,
			handles: "e, s, se",
    });
  });
})(jQuery);