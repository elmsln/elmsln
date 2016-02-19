(function($) {

  // Input: Array of JSON objects {selector, offset, callback}

  Materialize.scrollFire = function(options) {

    var didScroll = false;

    window.addEventListener("scroll", function() {
      didScroll = true;
    });

    // Rate limit to 100ms
    setInterval(function() {
      if(didScroll) {
          didScroll = false;

          var windowScroll = window.pageYOffset + window.innerHeight;

          for (var i = 0 ; i < options.length; i++) {
            // Get options from each line
            var value = options[i];
            var selector = value.selector,
                offset = value.offset,
                callback = value.callback;

            var currentElement = document.querySelector(selector);
            if ( currentElement !== null) {
              var elementOffset = currentElement.getBoundingClientRect().top + window.pageYOffset;

              if (windowScroll > (elementOffset + offset)) {
                if (value.done !== true) {
<<<<<<< e65c74aae289a769861e434ed793b68185dc8ac0
                  if (typeof(callback) === 'function') {
                    callback.call(this);
                  } else if (typeof(callback) === 'string') {
                    var callbackFunc = new Function(callback);
                    callbackFunc();
                  }
=======
                  var callbackFunc = new Function(callback);
                  callbackFunc();
>>>>>>> Starting point for Materialize.
                  value.done = true;
                }
              }
            }
          }
      }
    }, 100);
  };

<<<<<<< e65c74aae289a769861e434ed793b68185dc8ac0
})(jQuery);
=======
})(jQuery);
>>>>>>> Starting point for Materialize.
