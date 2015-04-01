/* Implement customer javascript here */
//body.scroll-disabled {
//     overflow: hidden;
// }
(function ($) {
  // popup event listeners
Drupal.behaviors.outlineDesignerCancelButton = function (context) {
  $(".disable-scroll", context).on("show", function () {
    $("body").addClass("scroll-disabled");
  }).on("hidden", function () {
    $("body").removeClass("scroll-disabled")
  });
};
})(jQuery);
