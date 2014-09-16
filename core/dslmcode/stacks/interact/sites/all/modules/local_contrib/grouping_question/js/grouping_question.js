/**
 * @file
 */

(function($) {
    var members = new Array();
    var groups = new Array();
    var answer_fields = new Array();

$(document).ready(function() {

    var reg = /quiz-grouping-member-([0-9]*)/;

    $('.quiz-grouping-member').each(function() {
      var id = $(this).attr('id').replace(reg, "$1");
      members[id] = new Array();
      // name of the member
      members[id][0] = $(this).text();
      // group member is in
      members[id][1] = '';
      // a reference to the member's div
      members[id][2] = this;
      // false if not positioned yet
      members[id][3] = false;
    });

    var reg2 = /quiz-grouping-group-([0-9]*)/;

    $('.quiz-grouping-group').each(function() {
      var id = $(this).attr('id').replace(reg2, "$1");
      groups[id] = new Array();
      groups[id][0] = $(this).text();
      groups[id][1] = $(this).position().top;
    });

    //var reg3 = /edit-tries-([0-9]*)-user-answers/;
    var reg3 = /tries\[([0-9]*)\]\[user_answers\]/;

    $('.quiz-grouping-answer-field').each(function() {

      var id = $(this).attr('name').replace(reg3, "$1");
      answer_fields[id] = this;
      if ($(this).val().length > 0) {
        // already answers in here
        var answers = $(this).val().split(',');
        for (var aid = 0; aid<answers.length; aid++) {
          for (var mid=0; mid<members.length; mid++) {
            if (answers[aid]==members[mid][0] && members[mid][3]==false) {
              $(members[mid][2]).css({
                "position" : "relative",
                "top": groups[id][1]+10
              });
              members[mid][3] = true;
              members[mid][1] = groups[id][0];
              break;
            }
          }
        }
      }
    });

    $('.quiz-grouping-member').draggable();

    $('.quiz-grouping-member').bind("dragstop", function(event,ui) {

        var id = $(this).attr('id').replace(reg, "$1");
        for(var i=1; i<groups.length; i++) {
          if ($(this).position().top > groups[i][1]) {
            members[id][1] = groups[i][0];
          }
        }

        for (var j = 1; j < groups.length; j++) {
          $(answer_fields[j]).val('');

          for (var k=0; k<members.length; k++) {
            if (members[k][1]==groups[j][0]) {
              $(answer_fields[j]).val($(answer_fields[j]).val() + members[k][0] + ',');
            }
          }
          if ($(answer_fields[j]).val().length > 1) {
            // remove the trailing comma
            $(answer_fields[j]).val($(answer_fields[j]).val().substr(0,$(answer_fields[j]).val().length-1));
          }
        }
    });

});

}(jQuery));
