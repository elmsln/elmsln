(function($){
  $(function(){
  	updateScroll();
    $('.button-collapse').sideNav();
  }); // end of document ready
  setInterval(function(){
  	if ($('.steptext').text().match(/6 of 6/g) == null) {
	    $.ajax({ url: "step.php", success: function(data){
	        $('.steptext').html(data);
	    }, dataType: "json"});
	    $.ajax({ url: "log.php", success: function(data){
	        $('.logarea').html(data);
	    }, dataType: "json"});
	    updateScroll();
	}
	}, 3000);
})(jQuery); // end of jQuery name space
function updateScroll(){
	var objDiv = document.getElementById("logid");
	objDiv.scrollTop = objDiv.scrollHeight;
}