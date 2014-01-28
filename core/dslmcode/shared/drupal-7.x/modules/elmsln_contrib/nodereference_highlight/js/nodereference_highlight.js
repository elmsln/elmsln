// JavaScript Document
(function ($) {
  Drupal.nodereference_highlight = {"text" : ""};
  Drupal.nodereference_highlight.getSelected = function(){
    var t = '';
    if(window.getSelection){
      t = window.getSelection();
    }else if(document.getSelection){
      t = document.getSelection();
    }else if(document.selection){
      t = document.selection.createRange().text;
    }
    return t;
  }

  Drupal.nodereference_highlight.mouseup = function(e){
    var text = Drupal.nodereference_highlight.getSelected();
    if(text !=''){
      // get the selected text
      Drupal.nodereference_highlight.text = text;
      // append to each link in case of a click
      $('#nrhi_container a').each(function(){
        if ($(this).attr('href') != '=') {
          $(this).attr('href', $(this).attr('href') + Drupal.nodereference_highlight.text);
        }
        else {
          $(this).attr('href', '#');
        }
      });
      //display the container and position it near where the mouse was released
      $("#nrhi_container").css('display', 'block').css('top', e.pageY + 10).css('left', e.pageX - 30);
    }
    else {
      //strip the text off the end of each link
      $('#nrhi_container a').each(function(){
        var tmp = $(this).attr('href').split('=');
        tmp.pop();
        tmp = tmp.join('=') +'=';
        $(this).attr('href', tmp);
      });
      //hide the container
      $("#nrhi_container").css('display', 'none');
      //set it back to empty
      Drupal.nodereference_highlight.text = '';
    }
  }
  
  $(document).ready(function(){
    $('.node').bind("mouseup", Drupal.nodereference_highlight.mouseup);
  });
})(jQuery);