module.exports = function() {
  'use strict';

  $(".video__open").click(function() {
    var videoContainer = $(this).parents('.video');

    videoContainer.toggleClass('video--is-open');
  });
};
