/*!
 * jQuery outside events - v1.1 - 3/16/2010
 * http://benalman.com/projects/jquery-outside-events-plugin/
 *
 * Copyright (c) 2010 "Cowboy" Ben Alman
 * Dual licensed under the MIT and GPL licenses.
 * http://benalman.com/about/license/
 */
(function(e,t,n){"$:nomunge";function r(r,i){function u(t){e(s).each(function(){var n=e(this);if(this!==t.target&&!n.has(t.target).length){n.triggerHandler(i,[t.target])}})}i=i||r+n;var s=e(),o=r+"."+i+"-special-event";e.event.special[i]={setup:function(){s=s.add(this);if(s.length===1){e(t).bind(o,u)}},teardown:function(){s=s.not(this);if(s.length===0){e(t).unbind(o)}},add:function(e){var t=e.handler;e.handler=function(e,n){e.target=n;t.apply(this,arguments)}}};}e.map("click dblclick mousemove mousedown mouseup mouseover mouseout touchstart touchend touchmove change select submit keydown keypress keyup".split(" "),function(e){r(e)});r("focusin","focus"+n);r("focusout","blur"+n);e.addOutsideEvent=r;})(jQuery,document,"outside")