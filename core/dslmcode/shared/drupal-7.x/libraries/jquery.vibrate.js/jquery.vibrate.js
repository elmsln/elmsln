(function() {
  "use strict";

  /*
  Vibration API
  Copyright (C) 2014-2016 Ilias Ismanalijev
      
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
   */
  var $;

  $ = jQuery;

  $.fn.vibrate = function(options) {
    var canVibrate, debug;
    debug = function() {};
    if (options != null) {
      if ((options.debug != null) && options.debug === true) {
        debug = function(msg) {
          return console.log("Vibration : " + msg);
        };
      }
      if (typeof options === "string") {
        switch (options) {
          case "short":
            options = {
              duration: 20
            };
            debug("Duration = 20");
            break;
          case "medium":
          case "default":
            options = {
              duration: 50
            };
            debug("Duration = 50");
            break;
          case "long":
            options = {
              duration: 100
            };
            debug("Duration = 100");
        }
      } else if (typeof options === "number") {
        if (!isNaN(options)) {
          options = {
            duration: options
          };
        }
        debug("Duration = " + options);
      }
    } else {
      options = {};
    }
    canVibrate = "vibrate" in navigator || "mozVibrate" in navigator;
    debug("Can Vibrate = " + canVibrate);
    if (canVibrate === false) {
      return this;
    } else if (canVibrate === true) {
      return $(this).each(function() {
        var $this, triggerStop;
        $this = $(this);
        $this.defaults = {
          trigger: "click",
          duration: 50,
          vibrateClass: "vibrate",
          debug: false
        };
        if (typeof options === "object") {
          $this.defaults = $.extend($this.defaults, options);
        }
        triggerStop = null;
        if ($this.defaults.trigger === "mousedown") {
          triggerStop = "mouseup";
          debug("StopEvent = mouseup");
        }
        if ($this.defaults.trigger === "touchstart") {
          triggerStop = "touchend";
          debug("StopEvent = touchend");
        }
        if (!$this.hasClass("vibrate")) {
          $this.addClass($this.defaults.vibrateClass);
        }
        debug("Class = " + $this.defaults.vibrateClass);
        $this.bind($this.defaults.trigger, function() {
          debug("Vibrate " + $this.defaults.duration + "ms");
          if ("vibrate" in navigator) {
            return navigator.vibrate($this.defaults.pattern || $this.defaults.duration);
          } else if ("mozVibrate" in navigator) {
            return navigator.mozVibrate($this.defaults.pattern || $this.defaults.duration);
          }
        });
        if ((triggerStop != null)) {
          return $this.bind(triggerStop, function() {
            debug("Vibrate Stop");
            if ("vibrate" in navigator) {
              return navigator.vibrate(0);
            } else if ("mozVibrate" in navigator) {
              return navigator.mozVibrate(0);
            }
          });
        }
      });
    }
  };

}).call(this);

//# sourceMappingURL=jquery.vibrate.js.map
