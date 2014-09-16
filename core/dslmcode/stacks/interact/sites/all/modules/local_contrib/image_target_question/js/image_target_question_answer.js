/**
 * @file
 * Javascript functions for the image_target_question question when answering
 */

(function($) {

Drupal.behaviors.imageTargetQuestionAlternativeBehavior = {

  attach : function (context) {
    var answer_box = $('input.answer-box');
    var answers = answer_box.val().split(':');

    var update_answer = function() {
      var new_answer = '';
      for (var i=0; i<answers.length; i++) {
        if (i==0) {
          new_answer += answers[i];
        } else {
          new_answer += ':' + answers[i];
        }
      }
      answer_box.val(new_answer);
    }

    var reg = /image_target_question-target-([0-9]*)/;
    $('.image_target_question-target')
      .draggable({
        stop: function() {
          var id = parseInt($(this).attr('id').replace(reg, '$1')) - 1;
          var left = $(this).offset().left - $('#image_target_question_image > img').offset().left + Math.round( $(this).width() / 2 );
          var top = $(this).offset().top - $('#image_target_question_image > img').offset().top + Math.round( $(this).height() / 2 );
          //alert ($(this).offset().left +'/'+ $('#image_target_question_image > img').offset().left +'/'+ Math.round( $(this).height() / 2));
          answers[id] = top + ',' + left;
          update_answer();
        }
      });


      $('div.image_target_question-target').each(
        function( intIndex ){

        //i = intIndex + 1;

        //var image = $('#image_target_question-target-'+ i);
        var image = $(this);
        image.css('top', -14);
        image.css('left', 0);
        var id = parseInt($(image).attr('id').replace(reg, '$1')) - 1;
        if (typeof answers[id] != 'undefined' && answers[id].length > 0) {
          //console.log(answers[id].length +':length');
          a = answers[id].split(',');
          //console.log(a[0] +'{}'+ a[1] +'{}'+ id +'{}'+ $(image).attr('id'));
          if (isNaN(a[0]) == false && isNaN(a[1]) == false && (a[0] > 0 || a[1] > 0)) {
            var left = - (image.offset().left - $('#image_target_question_image > img').offset().left + Math.round( image.width() /2) - a[1]);
            var top = - (image.offset().top - $('#image_target_question_image > img').offset().top + Math.round( image.height() /2) + 14 - a[0]);

            //console.log(left +'{}'+ top);
            image.css('top', top);
            image.css('left', left);
          }
        }
      }
    );
}

};

})(jQuery);
