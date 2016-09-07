/**
 @file
 Original Speed Reader by Charlotte Dann
 Fork gutted and supported by Bryan Ollendyke
*/
(function ($) {
  $(document).ready(function(){
    function words_load() {
      words_set();
      word_show(0);
      word_update();
      spritz_pause(true);
    }

  /* TEXT PARSING */
  function words_set() {
    // make a tmp container to rip out HTML chars
    var tmp = document.createElement("div");
    tmp.innerHTML = $words.html();
    if (document.all) {
      words = tmp.innerText;
    }
    else {
      words = tmp.textContent;
    }
    words = words.replace(/\s{2,}/g, ' ');
    words = words.trim().split(' ');
    for (var j = 1; j < words.length; j++) {
      words[j] = words[j].replace(/{linebreak}/g, '   ');
    }
  }
  /* ON EACH WORD */
  function word_show(i) {
    $('#spritz_progress').width(100*i/words.length+'%');
    var word = words[i];
    if (typeof word !== 'undefined') {
      var stop = Math.round((word.length+1)*0.4)-1;
      $space.html('<div>'+word.slice(0,stop)+'</div><div>'+word[stop]+'</div><div>'+word.slice(stop+1)+'</div>');
    }
  }
  function word_next() {
    i++;
    word_show(i);
  }
  function word_prev() {
    i--;
    word_show(i);
  }

  /* ITERATION FUNCTION */
  function word_update() {
    spritz = setInterval(function() {
      word_next();
      if (i+1 == words.length) {
        setTimeout(function() {
          $space.html('');
          spritz_pause(true);
          i = 0;
          word_show(0);
        }, interval);
        clearInterval(spritz);
      }
    }, interval);
  }

  /* PAUSING FUNCTIONS */
  function spritz_pause(ns) {
      if (!paused) {
      clearInterval(spritz);
      paused = true;
      $('html').addClass('paused');
    }
  }
  function spritz_play() {
    word_update();
    paused = false;
    $('html').removeClass('paused');
  }
  function spritz_flip() {
    if (paused) {
      spritz_play();
    } else {
      spritz_pause();
    }
  }

  /* SPEED FUNCTIONS */
  function spritz_speed() {
    interval = 60000/$('#spritz_wpm').val();
    if (!paused) {
      clearInterval(spritz);
      word_update();
    }
  }
  function spritz_faster() {
    $('#spritz_wpm').val(parseInt($('#spritz_wpm').val(), 10) + 50);
    spritz_speed();
  }
  function spritz_slower() {
    if ($('#spritz_wpm').val() >= 100) {
      $('#spritz_wpm').val(parseInt($('#spritz_wpm').val(), 10) - 50);
    }
    spritz_speed();
  }

  /* KEY EVENTS */
  function button_flash(btn, time) {
    var $btn = $('.controls a.'+btn);
    $btn.addClass('active');
    if (typeof(time) === 'undefined') time = 100;
    setTimeout(function() {
      $btn.removeClass('active');
    }, time);
  }
    var $wpm = $('#spritz_wpm');
    var interval = 60000/$wpm.val();
    var paused = false;
    var $space = $('#spritz_word');
    var i = 0;
    var night = false;
    var $words = $(Drupal.settings.speedreader.selector);
    /* CONTROLS */
    $('#spritz_wpm').change(function() {
      spritz_speed();
    });
    $('.controls a, .controls label').click(function() {
      switch (this.id) {
        case 'spritz_slower':
          spritz_slower(); break;
        case 'spritz_faster':
          spritz_faster(); break;
        case 'spritz_pause':
          spritz_flip(); break;
      }
      return false;
    });

    $(document).keyup(function(e) {
      // ensure this is on screen before triggering
      if ($('#spritz_word').is(':visible')) {
        if (e.target.tagName.toLowerCase() != 'body') {
          return;
        }
        switch (e.keyCode) {
          case 32:
            spritz_flip(); button_flash('pause'); break;
          case 38:
            spritz_faster(); button_flash('faster'); break;
          case 40:
            spritz_slower(); button_flash('slower'); break;
        }
      }
    });

    /* INITIATE */
    words_load();

    $('a.toggle').click(function() {
      $(this).siblings('.togglable').slideToggle();
      return false;
    });
  });
})(jQuery);
