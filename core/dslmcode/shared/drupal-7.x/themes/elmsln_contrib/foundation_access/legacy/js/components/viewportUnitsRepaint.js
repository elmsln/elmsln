module.exports = function(target) {
  'use strict';

  $(window).resize(function () {
    target.css('z-index', 1);
  });
};
