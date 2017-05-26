/*global jQuery, Drupal*/
/*jslint white:true, multivar, this, browser:true*/

(function($, Drupal) {
	// This is the conversion function to convert rgb color values to hexadecimal number values
	function rgb2hex(rgb)
	{
		var result, numbers;

		result = "";
		numbers = rgb.match(/\d+/g);

		$.each(numbers, function(index)
		{
			var number;

			number = numbers[index] * 1;
			// convert to hex
			number = number.toString(16);
			// enforce double-digit
			if(number.length < 2)
			{
				number = "0" + number;
			}

			result += number;
		});

		return result;
	}

    function initializeCSS(element, key)
	{
		// Set base CSS settings
		element.css(
		{
			backgroundImage : "url(" + Drupal.settings.jqueryColorpicker[key] + ")",
			height : "36px",
			width: "36px",
			position: "relative"
		})
		.children(".color_picker").css(
		{
			backgroundImage: "url(" + Drupal.settings.jqueryColorpicker[key]+ ")",
			backgroundRepeat: "no-repeat",
			backgroundPosition: "center center",
			height: "30px",
			width: "30px",
			position: "absolute",
			top: "3px",
			left: "3px"
		})
		.children().css(
		{
			display: "none"
		});
	}

	function initializeElement(element)
	{
		var defaultColor, trigger;

		// Set the display of the label to inline. The reason for this is that clicking on a label element
		// automatically sets the focus on the input. With the jquery colorpicker, this means the colorpicker
		// pops up. When the display isn't set to inline, it extends to 100% width, meaning the clickable
		// area is much bigger than it should be, making the 'invisible' clickable space very large.
		// When it's set to inline, the width of the lable is only as wide as the text.

		element.parent().siblings("label").css("display",  "inline");

		// Next get the background color of the element
		defaultColor = element.find(".color_picker:first").css("background-color");

		// If the background color is an rgb value, convert it to a hexidecimal number
		if(defaultColor.match(/rgb/))
		{
			defaultColor = rgb2hex(defaultColor);
		}

		// Initialize the colorpicker element. This calls functions provided by the 3rd party code.
		trigger = element.children(".color_picker:first");
		trigger.ColorPicker(
		{
			color: defaultColor,
			onShow: function (colpkr)
			{
				$(colpkr).fadeIn(500);
				return false;
			},
			onHide: function (colpkr)
			{
				$(colpkr).fadeOut(500);
				element.find(".color_picker:first").find("input").blur();
				return false;
			},
			onChange: function (hsb, hex)
			{
				// For jSlint validation
				hsb = hsb;

				element.find(".color_picker:first").css(
				{
					backgroundColor: "#" + hex
				}).find("input").val(hex).change();
			}
		});
	}

	function inputWatcher(context, htmlID, key)
	{
		$(htmlID, context).once("jquery-colorpicker-input-watcher", function()
		{
			initializeCSS($(this), key);
			initializeElement($(this));
		});
	}

	function inputWatcher(context, htmlID, key)
	{
		$(htmlID, context).once("jquery-colorpicker-input-watcher", function()
		{
			initializeCSS($(this), key);
			initializeElement($(this));
		});
	}

	function clearWatcher(context)
	{
		$(".jquery_colorpicker_field_clear_link", context).once("jquery-colorpicker-clear-watcher", function()
		{
			$(this).click(function()
			{
				$(this).parents(".jquery_colorpicker:first").find(".color_picker:first").css("background-color", "#FFFFFF").find("input:first").val("");

				return false;
			});
		});
	}

	function removeWatcher(context)
	{
		$(".jquery_colorpicker_field_remove_link", context).once("jquery-colorpicker-remove-watcher", function()
		{
			$(this).click(function()
			{
				$(this).parents(".jquery_colorpicker:first").find("input:first").val("").parents("tr:first").hide();

				return false;
			});
		});
	}

	function init(context)
	{
		$.each(Drupal.settings.jqueryColorpicker, function(index)
		{
			// The following gives the ID of the element to will use as a point of reference for the settings
			var id = "#" + index + "-inner_wrapper";

			inputWatcher(context, id, index);
		});
	}

	Drupal.behaviors.jqueryColorpicker = {
		attach: function(context)
		{
			init(context);
			removeWatcher(context);
			clearWatcher(context);
		}
	};
}(jQuery, Drupal));
