
// General Insert API functions.
(function ($) {
  $.fn.insertAtCursor = function (tagName) {
    return this.each(function(){
      if (document.selection) {
        //IE support
        this.focus();
        sel = document.selection.createRange();
        sel.text = tagName;
        this.focus();
      }else if (this.selectionStart || this.selectionStart == '0') {
        //MOZILLA/NETSCAPE support
        startPos = this.selectionStart;
        endPos = this.selectionEnd;
        scrollTop = this.scrollTop;
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
