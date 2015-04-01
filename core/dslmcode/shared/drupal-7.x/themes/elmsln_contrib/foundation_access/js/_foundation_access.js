/* Implement customer javascript here */
$(".disable-scroll").on("show", function () {
  $("body").addClass("scroll-disabled");
}).on("hidden", function () {
  $("body").removeClass("scroll-disabled")
});