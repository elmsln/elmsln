(function ($, Drupal) {
  var maxLength = Drupal.settings.quiz_max_length;

  function quizStripTags(str) {
    return str.replace(/<\/?[^>]+>/gi, '');
  }

  function quizUpdateTitle() {
    var body = $("#edit-body textarea:eq(1)").val();
    if (quizStripTags(body).length > maxLength) {
      $("#edit-title").val(quizStripTags(body).substring(0, maxLength - 3) + "...");
    }
    else {
      $("#edit-title").val(quizStripTags(body).substring(0, maxLength));
    }
  }

  $(document).ready(function () {
    $("#edit-body textarea").keyup(quizUpdateTitle);

    // Do not use auto title if a title already has been set
    if ($("#edit-title").val().length > 0) {
      $("#edit-body textarea:eq(1)").unbind("keyup", quizUpdateTitle);
    }

    $("#edit-title").keyup(function () {
      $("#edit-body textarea:eq(1)").unbind("keyup", quizUpdateTitle);
    });
  });

})(jQuery, Drupal);
