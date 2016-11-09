(function ($) {
  $(document).ready(function(){
     // dyslexia functionality
    Drupal.a11y.simulateDyslexia = function(dyslexia){
      if (dyslexia == true) {
        $("body").addClass('a11y-simulate-dyslexia');
        var getTextNodesIn = function(el) {
          return $(el).find(":not(iframe,script)").addBack().contents().filter(function() {
            return this.nodeType == 3;
          });
        };
        Drupal.settings.a11y.textNodes = getTextNodesIn($("p, h1, h2, h3"));
        Drupal.settings.a11y.wordsInTextNodes = [];
        for (var i = 0; i < Drupal.settings.a11y.textNodes.length; i++) {
          var node = Drupal.settings.a11y.textNodes[i];
          var words = []
          var re = /\w+/g;
          var match;
          while ((match = re.exec(node.nodeValue)) != null) {
            var word = match[0];
            var position = match.index;
            words.push({
              length: word.length,
              position: position
            });
          }
          Drupal.settings.a11y.wordsInTextNodes[i] = words;
        };
        setInterval(messUpWords, 50);
      }
      else {
        location.reload();
        $("body").removeClass('a11y-simulate-dyslexia');
      }
    };

    $('#a11y_sim_dyslexia_checkbox').click(function(){
      Drupal.a11y.simulateDyslexia(this.checked);
    });
  });
  function isLetter(char) {
    return /^[\d]$/.test(char);
  }

  function messUpWords () {
    for (var i = 0; i < Drupal.settings.a11y.textNodes.length; i++) {
      var node = Drupal.settings.a11y.textNodes[i];
      for (var j = 0; j < Drupal.settings.a11y.wordsInTextNodes[i].length; j++) {
        // Only change a tenth of the words each round.
        if (Math.random() > 1/10) {
          continue;
        }
        var wordMeta = Drupal.settings.a11y.wordsInTextNodes[i][j];
        var word = node.nodeValue.slice(wordMeta.position, wordMeta.position + wordMeta.length);
        var before = node.nodeValue.slice(0, wordMeta.position);
        var after  = node.nodeValue.slice(wordMeta.position + wordMeta.length);
        node.nodeValue = before + messUpWord(word) + after;
      };
    };
  }
  function messUpWord (word) {
    if (word.length < 3) {
      return word;
    }
    return word[0] + messUpMessyPart(word.slice(1, -1)) + word[word.length - 1];
  }
  function messUpMessyPart (messyPart) {
    if (messyPart.length < 2) {
      return messyPart;
    }
    var a, b;
    while (!(a < b)) {
      a = getRandomInt(0, messyPart.length - 1);
      b = getRandomInt(0, messyPart.length - 1);
    }
    return messyPart.slice(0, a) + messyPart[b] + messyPart.slice(a+1, b) + messyPart[a] + messyPart.slice(b+1);
  }
  function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1) + min);
  }
})(jQuery);