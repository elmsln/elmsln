
(function($) {
  Drupal.behaviors.jqueryColorpicker = {
    attach: function() {
      var targets = "";
      var first = true;
      // First we initialize some CSS settings - adding the background that the user has chosen etc.
      for (var i = 0; i < Drupal.settings.jqueryColorpicker.ids.length; i++) {
        if (!first) {
          targets += ", ";
        }
        else {
          first = false;
        }
        // This following gives us the ID of the element we will use as a point of reference for the settings
        var id = "#" + Drupal.settings.jqueryColorpicker.ids[i] + "-inner_wrapper";
        // Next we use that point of reference to set a bunch of CSS settings
        $(id).css({"background-image" : "url(" + Drupal.settings.jqueryColorpicker.backgrounds[i] + ")", "height" : "36px", "width" : "36px", "position" : "relative"})
          .children(".color_picker").css({"background-image" : "url(" + Drupal.settings.jqueryColorpicker.backgrounds[i] + ")", "background-repeat" : "no-repeat", "background-position" : "center center", "height" : "30px", "width" : "30px", "position" : "absolute", "top" : "3px", "left" : "3px"})
          .children().css({"display" : "none"});
        // we build a list of IDS that will then be acted upon in the next section of code
       targets += id;
     }

     // next we use the list of IDs we just built and act upon each of them
     $(targets).each(function() {
       // First we get a point of reference from which to work
       var target = $(this).attr("id");
       // we set the display of the label to inline. The reason for this is that clicking on a label element
       // automatically sets the focus on the input. With the jquery colorpicker, this means the colorpicker
       // pops up. When the display isn't set to inline, it extends to 100% width, meaning the clickable
       // area is much bigger than it should be, making the 'invisible' clickable space very large.
       // When it's set to inline, the width of the lable is only as wide as the text
       // as big as.
       $("#" + target).parent().siblings("label").css("display",  "inline");
       // next we get the background color of the element
       var defaultColor = $("#" + target + " .color_picker").css("background-color");
       // if the background color is an rgb value, which it is when using firefox, we convert it to a
       // hexidecimal number
       if(defaultColor.match(/rgb/)) {
         defaultColor = rgb2hex(defaultColor);
       }
       // finally we initialize the colorpicker element. This calls functions provided by the 3rd party code.
         var trigger = $(this).children(".color_picker:first");
         trigger.ColorPicker({
           color: defaultColor,
           onShow: function (colpkr) {
             $(colpkr).fadeIn(500);
             return false;
           },
           onHide: function (colpkr) {
             $(colpkr).fadeOut(500);
             return false;
           },
           onChange: function (hsb, hex, rgb) {
             $("#" + target + " .color_picker").css("backgroundColor", "#" + hex).find("input").val(hex).change();
           }
         });
       });
     }
  };
  // This is the conversion function to convert rgb color values to hexadecimal number values
  function rgb2hex(rgb) {
    var result = new String;
    var number = new Number;
    var numbers = rgb.match(/\d+/g), j, result, number;
    for (j = 0; j < numbers.length; j += 1) {
      number = numbers[j] * 1;
      // convert to hex
      number = number.toString(16);
      // enforce double-digit
      if (number.length < 2) {
        number = "0" + number;
      }
      result += number;
    }
    return result;
  };
})(jQuery);
