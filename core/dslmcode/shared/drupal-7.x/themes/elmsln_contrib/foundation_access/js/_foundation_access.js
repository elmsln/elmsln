/* Implement customer javascript here */
$(".disable-scroll").on("show", function () {
  $("body").addClass("scroll-disabled");
}).on("hidden", function () {
  $("body").removeClass("scroll-disabled")
});

$('*[data-reveal-id]').click(function () {
  var revealID = $(this).attr("data-reveal-id");
  var wrapper = $("#" + revealID);
  // If the wrapper element is open then give it focus
  if (wrapper.hasClass('open')) {
    wrapper.focus();
  }
}