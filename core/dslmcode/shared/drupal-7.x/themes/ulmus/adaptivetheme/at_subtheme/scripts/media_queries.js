/**
 * @file
 * Fire callbacks for media query breakpoints
 *
 * To use this file enable the OnMediaQuery.js polyfill in your subthemes
 * appearance settings - this will load the required plugin and this file.
 *
 * This allows you to write context (media query) specific JS without hard
 * coding the media queries, aka like matchMedia. Each context matches the
 * media queries you set in theme settings (by adding the font-family
 * declarations to the responsive layout CSS).
 *
 * SEE: https://github.com/JoshBarr/js-media-queries
 *
 * IMPORTANT: do not rename or move this file, or change the directory name!
 */
var queries = [

  /*
   * Smalltouch
   */
  {
    context: ['smalltouch_portrait', 'smalltouch_landscape'], // portrait and landscape
    call_in_each_context: false,
    callback: function() {
      // console.log('smalltouch');

      // Example: this will remove the search block in smartphones
      // el = document.getElementById("block-search-form");
      // el.parentNode.removeChild(element);
    }
  },
  {
    context: 'smalltouch_portrait', // portrait only
    callback: function() {
      //console.log('smalltouch portrait');
    }
  },
  {
    context: 'smalltouch_landscape', // landscape only
    callback: function() {
      //console.log('smalltouch_landscape ');
    }
  },


  /*
   * Tablet
   */
  {
    context: ['tablet_portrait', 'tablet_landscape'], // portrait and landscape
    call_in_each_context: false,
    callback: function() {
      //console.log('tablet');
    }
  },
  {
    context: 'tablet_portrait', // portrait only
    callback: function() {
      //console.log('tablet_portrait');
    }
  },
  {
    context: 'tablet_landscape', // landscape only
    callback: function() {
      //console.log("tablet_landscape");
    }
  },


  /*
   * Standard desktop layout
   */
  {
    context: 'standard',
    callback: function() {
      //console.log("standard desktop");
    }
  },
];

MQ.init(queries);
