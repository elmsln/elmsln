// Check for jQuery.
if (typeof(jQuery) === 'undefined') {
  var jQuery;
  // Check if require is a defined function.
  if (typeof(require) === 'function') {
<<<<<<< e65c74aae289a769861e434ed793b68185dc8ac0
    jQuery = $ = require('jquery');
=======
    jQuery = $ = require('jQuery');
>>>>>>> Starting point for Materialize.
  // Else use the dollar sign alias.
  } else {
    jQuery = $;
  }
<<<<<<< e65c74aae289a769861e434ed793b68185dc8ac0
}
=======
}
>>>>>>> Starting point for Materialize.
