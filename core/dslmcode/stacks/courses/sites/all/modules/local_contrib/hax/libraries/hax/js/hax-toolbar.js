(function ($) {

  Hax.haxToolbarForm = function (context, settings) {
    // handle click on submit button so that we populate the body area at that time
    // this way we save what was loaded into the page
    $('#hax-page-edit-form').submit(function(event) {
      // trap form being empty and block submission
      if ($('#edit-hax-body').val() == null) {
        event.preventDefault();
      }
      // set the body area to whatever is in this DOM element
      $('#edit-hax-body').val($('.hax-body').html());
    });
  };
  // jarvis
  Hax.say = function(text) {
    // talk to me
    var Jarvis = new SpeechSynthesisUtterance(text);
    // nothing crazy so we can understand our robot
    Jarvis.pitch = 1;
    Jarvis.rate = 1;
    Jarvis.lang = 'en-US';
    var synth = window.speechSynthesis;
    var voices = synth.getVoices();
    // set the default voice to use
    for(i = 0; i < voices.length ; i++) {
      if(voices[i].default) {
        Jarvis.voice = voices[i].name;
      }
    }
    // THOU SPEAKITH
    synth.speak(Jarvis);
    $('.jarvis-conversation').append('<div><span class="robot">Jarvis: insert ' + text + '</span></div>');
  };

  $(document).ready(function() {
    // Using setTimeout to run after other ready callbacks
    setTimeout(function () {
      // create toolbar buttons for appending items to the interface
      $('.hax-toolbar-tool').on('click', function(){
        var tool = $(this).attr('data-hax-tool');
        var path = tool.split('-');
        $.get('templates/' + path[0] + '/' + path[1] + '/' + haxTemplates[tool].template, function(data) {
          var container = $.parseHTML(data);
          // load first item of the container to add actions to
          container[0].setAttribute('data-guid', Hax.getGUID());
          // easiest use-case, insert the markup we have
          if (haxTemplates[tool].action == 'insert') {
            // see if this is a container or content
            if (haxTemplates[tool].type == 'row') {
              Hax.applyDrop(container[0]);
              Hax.applyDrag(container[0]);
            }
            else if (haxTemplates[tool].type == 'column') {
              Hax.applyDrop(container[0]);
            }
            else {
              Hax.applyDrag(container[0]);
            }
            Hax.applyEventListeners(container[0]);
            var prependto = '';
            for (var len = Hax.selections.activeitems.length, i = 0; i < len; i++) {
              // drop item after the current one in the same parent
              if (Hax.selections.activeitems[i].getAttribute('data-draggable') == 'item') {
                prependto = 'item';
                $(container[0]).prependTo(Hax.selections.activeitems[i].parentNode);
                // @todo need to reorder so it's not at the end of this parent
              }
              else if (Hax.selections.activeitems[i].getAttribute('data-draggable') == 'target') {
                prependto = 'target';
                $(container[0]).prependTo(Hax.selections.activeitems[i]);
              }
            }
            // didn't find any targets so just stick it to the body in general
            if (prependto == '') {
              $(container[0]).prependTo('.hax-body');
            }
            $('#edit-hax-body').val($('.hax-body').html());
          }
        });
      });
    }, 100);
  });

})(jQuery);