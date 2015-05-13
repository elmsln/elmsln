/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global jQuery: true*/
// General Insert API functions.
(function ($) {
  "use strict";
  $.fn.insertAtCursor = function (tagName) {
    return this.each(function(){
      if (document.selection) {
        //IE support
        this.focus();
        var sel = document.selection.createRange();
        sel.text = tagName;
        this.focus();
      }
      else if (this.selectionStart || this.selectionStart === 0) {
        //MOZILLA/NETSCAPE support
        var startPos = this.selectionStart;
        var endPos = this.selectionEnd;
        var scrollTop = this.scrollTop;
        this.value = this.value.substring(0, startPos) + tagName + this.value.substring(endPos,this.value.length);
        this.focus();
        this.selectionStart = startPos + tagName.length;
        this.selectionEnd = startPos + tagName.length;
        this.scrollTop = scrollTop;
      } else {
        this.value += tagName;
        this.focus();
      }
    });
  };
})(jQuery);

