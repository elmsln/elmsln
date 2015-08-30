/**
 * Author: Mathis Hofer <hofer@puzzle.ch>
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Puzzle ITC GmbH
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

(function (window, document, $, Waypoint) {
  'use strict';

  $(document).ready(function () {
    // Menu should be always visible when scrolling
    var $hgtMenu = $('.hgt-menu');
    if ($hgtMenu.length){
      new Waypoint.Sticky({
        element: $hgtMenu[0],
        stuckClass: 'hgt-sticky',
        wrapper: '<div class="hgt-sticky-menu-wrapper" />',
        offset: 5
      });
    }

    function selectMenuItem(hash) {
      $('.hgt-menu-item').removeClass('selected');
      $('.hgt-menu-item[href="' + hash + '"]').addClass('selected');
    }

    // Update selected menu item on scrolling
    $('.hgt-content > h1').waypoint({
      handler: function() {
        selectMenuItem('#' + $(this.element).attr('id'));
      }
    });

    // Smoothly scroll to clicked menu item content
    $('.hgt-menu-item').on('click', function (event) {
      var hash = $(this).attr('href'),
        pos = Math.min($(hash).offset().top, $(document).height() - $(window).height());

      event.preventDefault();

      $('html,body').stop().animate({scrollTop : pos}, 200, function (){
        window.location.hash = hash;
        selectMenuItem(hash);
      });
    });

    // Initially select menu item
    if (window.location.hash) {
      setTimeout(function () {
        selectMenuItem(window.location.hash);
      }, 0);
    } else {
      $('.hgt-menu-item:first-child').addClass('selected');
    }
  });
})(window, window.document, jQuery, Waypoint);
