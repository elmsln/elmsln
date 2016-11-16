(function($){
  $(function(){
    $('.button-collapse').sideNav();
  }); // end of document ready
  setInterval(function(){
  	if ($('.steptext').html() != 'Step 6 of 6: Install complete!')
	    $.ajax({ url: "step.php", success: function(data){
	        $('.steptext').html(data);
	    }, dataType: "json"});
	    $.ajax({ url: "log.php", success: function(data){
	        $('.logarea').html(data);
	    }, dataType: "json"});
	}
	}, 3000);
})(jQuery); // end of jQuery name space