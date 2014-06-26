/**
 * @file
 * Provides a component that previews the page in various device dimensions.
 */

(function ($, Backbone, Drupal, undefined) {

"use strict";

var strings = {
  close: Drupal.t('Close'),
  orientation: Drupal.t('Change orientation'),
  portrait: Drupal.t('Portrait'),
  landscape: Drupal.t('Landscape')
};

var options = $.extend({
  gutter: 60,
  // The width of the device border around the iframe. This value is critical
  // to determine the size and placement of the preview iframe container,
  // therefore it must be defined here instead of in the CSS file.
  bleed: 30
}, Drupal.settings.responsivePreview);

/**
 * Attaches behaviors to the navbar tab and preview containers.
 */
Drupal.behaviors.responsivePreview = {
  attach: function (context) {
    // jQuery.once() returns a jQuery set. It will be empty if no unprocessed
    // elements are found. window and window.parent are equivalent unless the
    // Drupal page is itself wrapped in an iframe.
    var $body = $(window.parent.document.body).once('responsive-preview');

    if ($body.length) {
      // If this window is itself in an iframe it must be marked as processed.
      // Its parent window will have been processed above.
      // When attach() is called again for the preview iframe, it will check
      // its parent window and find it has been processed. In most cases, the
      // following code will have no effect.
      $(window.document.body).once('responsive-preview');

      var envModel = Drupal.responsivePreview.models.envModel = new Drupal.responsivePreview.EnvironmentModel({
        dir: document.documentElement.getAttribute('dir')
      });
      var tabModel = Drupal.responsivePreview.models.tabModel = new Drupal.responsivePreview.TabStateModel();
      var previewModel = Drupal.responsivePreview.models.previewModel = new Drupal.responsivePreview.PreviewStateModel();

      // Manages the PreviewView.
      Drupal.responsivePreview.views.appView = new Drupal.responsivePreview.AppView({
        // The previewView model.
        model: previewModel,
        envModel: envModel,
        // Gutter size around preview frame.
        gutter: options.gutter,
        // Preview device frame width.
        bleed: options.bleed,
        strings: strings
      });

      // The navbar tab view.
      var $tab = $('#responsive-preview-navbar-tab').once('responsive-preview');
      if ($tab.length > 0) {
        Drupal.responsivePreview.views.tabView = new Drupal.responsivePreview.TabView({
          el: $tab.get(),
          model: previewModel,
          tabModel: tabModel,
          envModel: envModel,
          // Gutter size around preview frame.
          gutter: options.gutter,
          // Preview device frame width.
          bleed: options.bleed
        });
      }
      // The control block view.
      var $block = $('#block-responsive-preview-controls').once('responsive-preview');
      if ($block.length > 0) {
        Drupal.responsivePreview.views.blockView = new Drupal.responsivePreview.BlockView({
          el: $block.get(),
          model: previewModel,
          envModel: envModel,
          // Gutter size around preview frame.
          gutter: options.gutter,
          // Preview device frame width.
          bleed: options.bleed
        });
      }

      // Keyboard controls view.
      Drupal.responsivePreview.views.keyboardView = new Drupal.responsivePreview.KeyboardView({
        el: $block.get(),
        model: previewModel
      });

      /**
       * Sets the viewport width and height dimensions on the envModel.
       */
      var setViewportDimensions = function() {
        envModel.set({
          'viewportWidth': document.documentElement.clientWidth,
          'viewportHeight': document.documentElement.clientHeight
        });
      };

      $(window)
        // Update the viewport width whenever it is resized, but max 4 times/s.
        .on('resize.responsivepreview', Drupal.debounce(setViewportDimensions, 250));

      $(document)
        // Respond to viewport offsetting elements like the navbar.
        .on('drupalViewportOffsetChange.responsivepreview', function (event, offsets) {
          envModel.set('offsets', offsets);
        })
        .on('keyup.responsivepreview', function (event) {
          // Close the preview if the Esc key is pressed.
          if (event.keyCode === 27) {
            previewModel.set('isActive', false);
          }
        })
        // Close the preview if the overlay is opened.
        .on('drupalOverlayOpen.responsivepreview', function () {
          previewModel.set('isActive', false);
        });

      // Allow other scripts to respond to responsive preview mode changes.
      tabModel.on('change:isActive', function (model, isActive) {
        $(document).trigger((isActive) ? 'drupalResponsivePreviewStarted' : 'drupalResponsivePreviewStopped');
      });

      // Initialization: set the current viewport width.
      setViewportDimensions();
    }
    // The main window is equivalent to window.parent and window.self. Inside,
    // an iframe, these objects are not equivalent. If the parent window is
    // itself in an iframe, check that the parent window has been processed.
    // If it has been, this invocation of attach() is being called on the
    // preview iframe, not its parent.
    if ((window.parent !== window.self) && !$body.length) {
      var $frameBody = $(window.self.document.body).once('responsive-preview');
      if ($frameBody.length > 0) {
        $frameBody.addClass('responsive-preview-frame');
        // Call Drupal.displace in the next process frame to relayout the page
        // in the iframe. This will ensure that no gaps in the presentation
        // exist from elements that are hidden, such as the navbar.
        var win = window;
        window.setTimeout(function () {
          win.Drupal.displace();
        }, 0);
      }
    }
  },
  detach: function (context, settings, trigger) {
    /**
     * Loops through object properties; applies a callback function.
     */
    function looper (obj, iterator) {
      for (var prop in obj) {
        if (obj.hasOwnProperty(prop)) {
          iterator.call(null, prop, obj[prop]);
        }
      }
    }

    var app = Drupal.responsivePreview.views.appView || null;
    // Detach only if the app view is unloading.
    if (app && context === app && trigger === 'unload') {
      // Remove listeners on the window and document.
      $(window).add(document).off('.responsivepreview');
      // Remove and delete the view references.
      looper(Drupal.responsivePreview.views, function (label, view) {
        view.remove();
        Drupal.responsivePreview.views[label] = undefined;
      });
      // Reset models, remove listeners and delete the model references.
      looper(Drupal.responsivePreview.models, function (label, model) {
        model.set(model.defaults);
        model.off();
        Drupal.responsivePreview.models[label] = undefined;
      });
    }
  }
};

Drupal.responsivePreview = Drupal.responsivePreview || {

  // Storage for view instances.
  views: {},

  // Storage for model instances.
  models: {},

  /**
   * Backbone Model for the environment in which the Responsive Preview operates.
   */
  EnvironmentModel: Backbone.Model.extend({
    defaults: {
      // The viewport width, within which the preview will have to fit.
      viewportWidth: null,
      // The viewport height, within which the preview will have to fit.
      viewportHeight: null,
      // Text direction of the document, affects some positioning.
      dir: 'ltr',
      // Viewport offset values.
      offsets: {
        top: 0,
        right: 0,
        bottom: 0,
        left: 0
      }
    }
  }),

  /**
   * Backbone Model for the Responsive Preview navbar tab state.
   */
  TabStateModel: Backbone.Model.extend({
    defaults: {
      // The state of navbar list of available device previews.
      isDeviceListOpen: false
    }
  }),

  /**
   * Backbone Model for the Responsive Preview preview state.
   */
  PreviewStateModel: Backbone.Model.extend({
    defaults: {
      // The state of the preview.
      isActive: false,
      // Indicates whether the preview iframe has been built.
      isBuilt: false,
      // Indicates whether the device is portrait (false) or landscape (true).
      isRotated: false,
      // Indicates of the device details are visible in the preview frame.
      isDetailsExpanded: false,
      // The number of devices that fit the current viewport (i.e. previewable).
      fittingDeviceCount: 0,
      // Currently selected device link.
      activeDevice: null,
      // Dimensions of the currently selected device to preview.
      dimensions: {
        // The width of the device to preview.
        width: null,
        // The height of the device to preview.
        height: null,
        // The dots per pixel of the device to preview.
        dppx: null
      }
    },

    /**
     * {@inheritdoc}
     */
    initialize: function () {
      this.on('change:isActive', this.reset, this);
    },

    /**
     * Puts the model back into a ready state where no device is active.
     *
     * @param Backbone.Model model
     *   This model.
     * @param Boolean isActive
     *   Whether the responsive preview is currently active.
     */
    reset: function (model, isActive) {
      // Reset the model when it is deactivated.
      if (!isActive) {
        // Process this model change after any views have had the chance to
        // react to the change of isActive.
        var that = this;
        window.setTimeout(function () {
          that.set({
            isRotated: false,
            activeDevice: null,
            dimensions: {
              width: null,
              height: null,
              dppx: null
            }
          }, {silent: true});
        }, 0);
      }
    }
  }),

  /**
   * Manages the PreviewView.
   */
  AppView: Backbone.View.extend({

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.options = options;
      this.envModel = options.envModel;
      // Listen to changes on the previewModel.
      this.model.on('change:isActive', this.render, this);
    },

    /**
     * {@inheritdoc}
     */
    render: function (previewModel, isActive, options) {
      // The preview container view.
      if (isActive && !Drupal.responsivePreview.views.previewView) {
        // Holds the Backbone View of the preview. This view is created and destroyed
        // when the preview is enabled or disabled respectively.
        Drupal.responsivePreview.views.previewView = new Drupal.responsivePreview.PreviewView({
          el: Drupal.theme('responsivePreviewContainer'),
          // The previewView model.
          model: this.model,
          envModel: this.envModel,
          // Gutter size around preview frame.
          gutter: this.options.gutter,
          // Preview device frame width.
          bleed: this.options.bleed,
          strings: this.options.strings
        });
        // Remove the inlined opacity style so that the CSS opacity transition
        // will fade in the preview view.
        window.setTimeout(function () {
          Drupal.responsivePreview.views.previewView.el.style.opacity = null;
        }, 0);
      }
      else if (!isActive && Drupal.responsivePreview.views.previewView) {
        // The transitionEnd event is still heavily vendor-prefixed.
        var transitionEnd = "transitionEnd.responsivepreview webkitTransitionEnd.responsivepreview transitionend.responsivepreview msTransitionEnd.responsivepreview oTransitionEnd.responsivepreview";
        // When the fade transition is complete, remove the view.
        Drupal.responsivePreview.views.previewView.$el.on(transitionEnd, function (event) {
          Drupal.responsivePreview.views.previewView.remove();
          delete Drupal.responsivePreview.views.previewView;
        });
        // Fade out the preview.
        Drupal.responsivePreview.views.previewView.el.style.opacity = 0;
      }
    }
  }),

  /**
   * Handles responsive preview navbar tab interactions.
   */
  TabView: Backbone.View.extend({

    events: {
      'click .responsive-preview-trigger': 'toggleDeviceList',
      'mouseleave': 'toggleDeviceList'
    },

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.gutter = options.gutter;
      this.bleed = options.bleed;
      this.tabModel = options.tabModel;
      this.envModel = options.envModel;
      var handler;

      // Curry the 'this' object in order to pass it as an argument to the
      // selectDevice function.
      handler = selectDevice.bind(null, this);
      this.$el.on('click.responsivepreview', '.responsive-preview-device', handler);

      this.model.on('change:isActive change:dimensions change:activeDevice change:fittingDeviceCount', this.render, this);

      this.tabModel.on('change:isDeviceListOpen', this.render, this);

      // Curry the 'this' object in order to pass it as an argument to the
      // updateDeviceList function.
      handler = updateDeviceList.bind(null, this);
      this.envModel.on('change:viewportWidth', handler, null);

      this.envModel.on('change:viewportWidth', this.correctDeviceListEdgeCollision, this);
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var name = this.model.get('activeDevice');
      var isActive = this.model.get('isActive');
      var isDeviceListOpen = this.tabModel.get('isDeviceListOpen');
      this.$el
        // Render the visibility of the navbar tab.
        .toggle(this.model.get('fittingDeviceCount') > 0)
        // Toggle the display of the device list.
        .toggleClass('open', isDeviceListOpen);

      // Render the state of the navbar tab button.
      this.$el
        .find('> button')
        .toggleClass('active', isActive)
        .attr('aria-pressed', isActive);

      // Clean the active class from the device list.
      this.$el
        .find('.responsive-preview-device.active')
        .removeClass('active');

      this.$el
        .find('[data-responsive-preview-name="' + name + '"]')
        .toggleClass('active', isActive);
      // When the preview is active, a class on the body is necessary to impose
      // styling to aid in the display of the preview element.
      $('body').toggleClass('responsive-preview-active', isActive);
      // The list of devices might render outside the window.
      if (isDeviceListOpen) {
        this.correctDeviceListEdgeCollision();
      }
      return this;
    },

    /**
     * Toggles the list of devices available to preview from the navbar tab.
     *
     * @param jQuery.Event event
     */
    toggleDeviceList: function (event) {
      // All of this className checking is necessary because jQuery prior to
      // version 1.6 did not support event delegation in the on and off methods
      var targetClassName = typeof event.target.className === 'string' && event.target.className || false;
      var currentTargetClassName = typeof event.currentTarget.className === 'string' && event.currentTarget.className || false;
      var isTrigger = targetClassName && /responsive-preview-trigger/.test(targetClassName) || false;
      var isNavbarTab = currentTargetClassName && /navbar-tab-responsive-preview/.test(currentTargetClassName) || false;
      if (isTrigger || isNavbarTab) {
        // Force the options list closed on mouseleave.
        if (event.type === 'mouseleave') {
          this.tabModel.set('isDeviceListOpen', false);
        }
        else {
          this.tabModel.set('isDeviceListOpen', !this.tabModel.get('isDeviceListOpen'));
        }

        event.stopPropagation();
        event.preventDefault();
      }
    },

    /**
     * Model change handler; corrects possible device list window edge collision.
     */
    correctDeviceListEdgeCollision: function () {
      // The position of the dropdown depends on the language direction.
      var dir = this.envModel.get('dir');
      var edge = (dir === 'rtl') ? 'left' : 'right';
      this.$el
        .find('.item-list')
        .position_responsive_preview({
          'my': edge +' top',
          'at': edge + ' bottom',
          'of': this.$el,
          'collision': 'flip fit'
        });
    }
  }),

  /**
   * Handles responsive preview control block interactions.
   */
  BlockView: Backbone.View.extend({

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.gutter = options.gutter;
      this.bleed = options.bleed;
      this.envModel = options.envModel;
      var handler;

      // Curry the 'this' object in order to pass it as an argument to the
      // selectDevice function.
      handler = selectDevice.bind(null, this);
      this.$el.on('click.responsivepreview', '.responsive-preview-device', handler);

      this.model.on('change:isActive change:dimensions change:activeDevice change:fittingDeviceCount', this.render, this);

      // Curry the 'this' object in order to pass it as an argument to the
      // updateDeviceList function.
      handler = updateDeviceList.bind(null, this);
      this.envModel.on('change:viewportWidth', handler, null);
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      var name = this.model.get('activeDevice');
      var isActive = this.model.get('isActive');
      this.$el
        // Render the visibility of the navbar block.
        .toggle(this.model.get('fittingDeviceCount') > 0)
        .find('.responsive-preview-device.active')
        .removeClass('active');

      this.$el
        .find('[data-responsive-preview-name="' + name + '"]')
        .addClass('active');
      // When the preview is active, a class on the body is necessary to impose
      // styling to aid in the display of the preview element.
      $('body').toggleClass('responsive-preview-active', isActive);
      return this;
    }
  }),

  /**
   * Handles keyboard input.
   */
  KeyboardView: Backbone.View.extend({

    /*
     * {@inheritdoc}
     */
    initialize: function () {
      $(document).on('keyup.responsivepreview', _.bind(this.onKeypress, this));
    },

    /**
     * Responds to esc key press events.
     *
     * @param jQuery.Event event
     */
    onKeypress: function (event) {
      if (event.keyCode === 27) {
        this.model.set('isActive', false);
      }
    },

    /**
     * Removes a listener on the document; calls the standard Backbone remove.
     */
    remove: function () {
      // Unbind the keyup listener.
      $(document).off('keyup.responsivepreview');
      // Call the standard remove method on this.
      Backbone.View.prototype.remove.call(this);
    }
  }),

  /**
   * Handles the responsive preview element interactions.
   */
  PreviewView: Backbone.View.extend({

    events: {
      'click #responsive-preview-close': 'shutdown',
      'click #responsive-preview-modal-background': 'shutdown',
      'click #responsive-preview-scroll-pane': 'shutdown',
      'click #responsive-preview-orientation': 'rotate',
      'click #responsive-preview-frame-label': 'revealDetails'
    },

    /**
     * {@inheritdoc}
     */
    initialize: function (options) {
      this.gutter = options.gutter;
      this.bleed = options.bleed;
      this.strings = options.strings;
      this.envModel = options.envModel;

      this.model.on('change:isRotated change:isDetailsExpanded change:dimensions change:activeDevice', this.render, this);

      // Recalculate the size of the preview container when the window resizes.
      this.envModel.on('change:viewportWidth change:viewportHeight change:offsets', this.render, this);

      // Build the preview.
      this._build();

      // Call an initial render.
      this.render();
    },

    /**
     * {@inheritdoc}
     */
    render: function () {
      // Refresh the preview.
      this._refresh();
      Drupal.displace();

      // Render the state of the preview.
      var that = this;
      // Wrap the call in a setTimeout so that it invokes in the next compute
      // cycle, causing the CSS animations to render in the first pass.
      window.setTimeout(function () {
        that.$el.toggleClass('active', that.model.get('isActive'));
      }, 0);

      return this;
    },

    /**
     * Closes the preview.
     *
     * @param jQuery.Event event
     */
    shutdown: function (event) {
      this.model.set('isActive', false);
    },

    /**
     * Removes a listener on the document; calls the standard Backbone remove.
     */
    remove: function () {
      // Unbind transition listeners.
      this.$el.off('.responsivepreview');
      // Call the standard remove method on this.
      Backbone.View.prototype.remove.call(this);
    },

    /**
     * Responds to rotation button presses.
     *
     * @param jQuery.Event event
     */
    rotate: function (event) {
      this.model.set('isRotated', !this.model.get('isRotated'));
      event.stopPropagation();
    },

    /**
     * Responds to clicks on the device frame label.
     *
     * @param jQuery.Event event
     */
    revealDetails: function (event) {
      this.model.set('isDetailsExpanded', !this.model.get('isDetailsExpanded'));
      event.stopPropagation();
    },

    /**
     * Builds the preview iframe.
     */
    _build: function () {
      var offsets = this.envModel.get('offsets');
      var $frameContainer = $(Drupal.theme('responsivePreviewFrameContainer', this.strings))
        // The padding around the frame must be known in order to position it
        // correctly, so the style property is defined in JavaScript rather than
        // CSS.
        .css('padding', this.bleed);
      // Attach the iframe that will hold the preview.
      var $frame = $(Drupal.theme('responsivePreviewFrame'))
        // Load the current page URI into the preview iframe.
        .on('load.responsivepreview', this._refresh.bind(this))
        // Add the frame to the preview container.
        .appendTo($frameContainer);
      // Wrap the frame container in a pair of divs that will allow for
      // scrolling.
      $frameContainer = $frameContainer.wrap(Drupal.theme('responsivePreviewScrollContainer'))
        .closest('#responsive-preview-scroll-track');
      // Apply padding to the scroll pane.
      $frameContainer.find('#responsive-preview-scroll-pane')
        .css({
          'padding-bottom': this.bleed,
          'padding-top': this.bleed
        });
      // Insert the container into the DOM.
      this.$el
        .css({
          'top': offsets.top,
          'right': offsets.right,
          'left': offsets.left
        })
        // Apend the frame container.
        .append($frameContainer)
        // Append the container to the body to initialize the iframe document.
        .appendTo('body');
      // Load the path into the iframe.
      // Create a path from the basePath and the current path, chopping off the
      // trailing slash of the basePath. The pathname already includes it.
      $frame.get(0).contentWindow.location = Drupal.settings.basePath.slice(0, -1) + window.location.pathname;
      // Mark the preview element processed.
      this.model.set('isBuilt', true);
    },

    /**
     * Refreshes the preview based on the current state (device & viewport width).
     */
    _refresh: function () {
      var isRotated = this.model.get('isRotated');
      var $deviceLink = $('[data-responsive-preview-name="' + this.model.get('activeDevice') + '"]').eq(0);
      var $container = this.$el.find('#responsive-preview-frame-container');
      var $frame = $container.find('#responsive-preview-frame');
      var $scrollPane = this.$el.find('#responsive-preview-scroll-pane');
      var offsets = this.envModel.get('offsets');

      // Get the static state.
      var edge = (this.envModel.get('dir') === 'rtl') ? 'right' : 'left';
      var minGutter = this.gutter;

      // Get current (dynamic) state.
      var dimensions = this.model.get('dimensions');
      var viewportWidth = this.envModel.get('viewportWidth') - (offsets.left + offsets.right);

      // Calculate preview width & height. If the preview is rotated, swap width
      // and height.
      var displayWidth = dimensions[(isRotated) ? 'height' : 'width'];
      var displayHeight = dimensions[(isRotated) ? 'width' : 'height'];
      var width = displayWidth / dimensions.dppx;
      var height = displayHeight / dimensions.dppx;

      // Get the container padding and border width for both dimensions.
      var bleed = this.bleed;
      var widthSpread = width + (bleed * 2);

      // Calculate how much space is required to the right and left of the
      // preview container in order to center it.
      var gutterPercent = (1 - (widthSpread / viewportWidth)) / 2;
      var gutter = gutterPercent * viewportWidth;
      gutter = (gutter < minGutter) ? minGutter : gutter;

      // The device dimension size plus gutters must fit within the viewport
      // area for that dimension. The spread is how much room the preview
      // needs for that dimension.
      width = Math.ceil((viewportWidth - (gutter * 2) < widthSpread) ? viewportWidth - (gutter * 2) - (bleed * 2) : width);

      // Updated the state of the rotated icon.
      this.$el.find('.responsive-preview-control.responsive-preview-orientation').toggleClass('rotated', isRotated);

      // Reposition the preview root.
      this.$el.css({
          top: offsets.top,
          right: offsets.right,
          left: offsets.left,
          height: document.documentElement.clientHeight - (offsets.top + offsets.bottom)
        });

      // Position the frame.
      var position = {};
      // Position depends on text direction.
      position[edge] = (gutter > minGutter) ? gutter : minGutter;
      $frame
        .css({
          width: width,
          height: height
        });

      // Position the frame container.
      $container.css(position);

      // Resize the scroll pane.
      var paneHeight = height + (this.bleed * 2);
      // If the height of the pane that contains the preview frame is higher
      // than the available viewport area, then make it scroll.
      if (paneHeight > (document.documentElement.clientHeight - offsets.top - offsets.bottom)) {
        $scrollPane
          .css({
            height: paneHeight
          })
          // Select the parent container that constrains the overflow.
          .parent()
          .css({
            overflow: 'scroll'
          });
      }
      // If the height of the viewport area is sufficient to display the preview
      // frame, remove the scroll styling.
      else {
        $scrollPane.css({
            height: 'auto'
          })
          // Select the parent container that constrains the overflow.
          .parent()
          .css({
            overflow: 'visible'
          });
      }

      // Scale if not responsive.
      this._scaleIfNotResponsive();

      // Update the text in the device label.
      var $label = $container.find('.responsive-preview-device-label');
      $label
        .find('.responsive-preview-device-label-text')
        .text(Drupal.t('@label', {
          '@label': $deviceLink.text()
        }));

      // The device details are appended to the device label node in a separate
      // node so that their presentation can be varied independent of the label.
      $label
        .find('.responsive-preview-device-label-details')
        .text(Drupal.t('@displayWidth@width by @displayHeight, @dpi, @orientation', {
          '@displayWidth': displayWidth + 'px',
          // If the width of the preview element is not equivalent to the
          // configured display width, display the actual width of the preview
          // in parentheses.
          '@width': (displayWidth !== Math.floor(width * dimensions.dppx)) ? ' (' + (Math.floor(width * dimensions.dppx)) + 'px)' : '',
          '@displayHeight': displayHeight + 'px',
          '@dpi': dimensions.dppx + 'ppx',
          '@orientation': (isRotated) ? this.strings.landscape : this.strings.portrait
        }));

      // Expose the details if the user has expanded the label.
      var isDetailsExpanded = this.model.get('isDetailsExpanded');
      $label
        .toggleClass('responsive-preview-expanded', isDetailsExpanded)
        .find('.responsive-preview-device-label-details')
        .toggleClass('element-invisible', !isDetailsExpanded);
    },

    /**
     * Applies scaling in order to better approximate content display on a device.
     */
    _scaleIfNotResponsive: function () {
      var scalingCSS = this._calculateScalingCSS();
      if (scalingCSS === false) {
        return;
      }

      // Step 0: find DOM nodes we'll need to modify.
      var $frame = this.$el.find('#responsive-preview-frame');
      var doc = $frame[0].contentDocument || ($frame[0].contentWindow && $frame[0].contentWindow.document);
      // No document has been loaded into the iframe yet.
      if (!doc) {
        return;
      }
      var $html = $(doc).find('html');

      // Step 1: When scaling (as we're about to do), the background (color and
      // image) doesn't scale along. Fortunately, we can fix things in case of
      // background color.
      // @todo: figure out a work-around for background images, or somehow
      // document this explicitly.
      function isTransparent (color) {
        // TRICKY: edge case for Firefox' "transparent" here; this is a
        // browser bug: https://bugzilla.mozilla.org/show_bug.cgi?id=635724
        return (color === 'rgba(0, 0, 0, 0)' || color === 'transparent');
      }
      var htmlBgColor = $html.css('background-color');
      var bodyBgColor = $html.find('body').css('background-color');
      if (!isTransparent(htmlBgColor) || !isTransparent(bodyBgColor)) {
        var bgColor = isTransparent(htmlBgColor) ? bodyBgColor : htmlBgColor;
        $frame.css('background-color', bgColor);
      }

      // Step 2: apply scaling.
      $html.css(scalingCSS);
    },

    /**
     * Calculates scaling based on device dimensions and <meta name="viewport" />.
     *
     * Websites that don't indicate via <meta name="viewport" /> that their width
     * is identical to the device width will be rendered at a larger size: at the
     * layout viewport's default width. This width exceeds the visual viewport on
     * the device, and causes it to scale it down.
     *
     * This function checks whether the underlying web page is responsive, and if
     * it's not, then it will calculate a CSS scaling transformation, to closely
     * approximate how an actual mobile device would render the web page.
     *
     * We assume all mobile devices' layout viewport's default width is 980px. It
     * is the value used on all iOS and Android >=4.0 devices.
     *
     * Related reading:
     *  - http://www.quirksmode.org/mobile/viewports.html
     *  - http://www.quirksmode.org/mobile/viewports2.html
     *  - https://developer.apple.com/library/safari/#documentation/AppleApplications/Reference/SafariWebContent/UsingtheViewport/UsingtheViewport.html
     *  - http://tripleodeon.com/2011/12/first-understand-your-screen/
     *  - http://tripleodeon.com/wp-content/uploads/2011/12/table.html?r=android40window.innerw&c=980
     */
    _calculateScalingCSS: function () {
      var isRotated = this.model.get('isRotated');
      var settings = this._parseViewportMetaTag();
      var defaultLayoutWidth = 980, initialScale = 1;
      var layoutViewportWidth, layoutViewportHeight;
      var visualViewPortWidth; // The visual viewport width === the preview width.

      if (settings.width) {
        if (settings.width === 'device-width') {
          // Don't scale if the page is marked to be as wide as the device.
          return false;
        }
        else {
          layoutViewportWidth = parseInt(settings.width, 10);
        }
      }
      else {
        layoutViewportWidth = defaultLayoutWidth;
      }

      if (settings.height && settings.height !== 'device-height') {
        layoutViewportHeight = parseInt(settings.height, 10);
      }

      if (settings['initial-scale']) {
        initialScale = parseFloat(settings['initial-scale'], 10);
        if (initialScale < 1) {
          layoutViewportWidth = defaultLayoutWidth;
        }
      }

      // Calculate the scale, prevent excesses (ensure the (0.25, 1) range).
      var dimensions = this.model.get('dimensions');
      // If the preview is rotated, width and height are swapped.
      visualViewPortWidth = dimensions[(isRotated) ? 'height' : 'width'] / dimensions.dppx;
      var scale = initialScale * (100 / layoutViewportWidth) * (visualViewPortWidth / 100);
      scale = Math.min(scale, 1);
      scale = Math.max(scale, 0.25);

      var transform = "scale(" + scale + ")";
      var xOrigin = (this.envModel.get('dir') === 'rtl') ? layoutViewportWidth : '0';
      var origin = xOrigin + "px 0px";
      return {
          'min-width': layoutViewportWidth + 'px',
          'min-height': layoutViewportHeight + 'px',
          '-webkit-transform': transform,
              '-ms-transform': transform,
                  'transform': transform,
          '-webkit-transform-origin': origin,
              '-ms-transform-origin': origin,
                  'transform-origin': origin
      };
    },

    /**
     * Parses <meta name="viewport" /> tag's "content" attribute, if any.
     *
     * Parses something like this:
     *   <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=5, minimum-scale=1, user-scalable=yes">
     * into this:
     *   {
     *     width: 'device-width',
     *     initial-scale: '1',
     *     maximum-scale: '5',
     *     minimum-scale: '1',
     *     user-scalable: 'yes'
     *   }
     *
     * @return Object
     *   Parsed viewport settings, or {}.
     */
    _parseViewportMetaTag: function () {
      var settings = {};
      var $viewportMeta = $(document).find('meta[name=viewport][content]');
      if ($viewportMeta.length > 0) {
        $viewportMeta
          .attr('content')
          // Reduce multiple parts of whitespace to a single space.
          .replace(/\s+/g, '')
          // Split on comma (which separates the different settings).
          .split(',')
          .map(function (setting) {
            setting = setting.split('=');
            settings[setting[0]] = setting[1];
          });
      }
      return settings;
    }
  })
};

/**
 * Functions that are common to both the TabView and BlockView.
 */

/**
 * Model change handler; hides devices that don't fit the current viewport.
 *
 * @param Backbone.View view
 *   The View curried to this handler. This function is used in multiple Views,
 *   so we bind it as an argument to the handler function in order to avoid
 *   having to reference it through a 'this' object which will trigger 'Possible
 *   strict violation' warning messages in JSHint.
 */
function updateDeviceList (view) {
  var gutter = view.gutter;
  var bleed = view.bleed;
  var viewportWidth = view.envModel.get('viewportWidth');
  var $devices = view.$el.find('.responsive-preview-device');
  var fittingDeviceCount = $devices.length;

  // Remove devices whose previews won't fit the current viewport.
  $devices.each(function (index, element) {
    var $this = $(this);
    var width = parseInt($this.data('responsive-preview-width'), 10);
    var dppx = parseFloat($this.data('responsive-preview-dppx'), 10);
    var previewWidth = width / dppx;
    var fits = ((previewWidth + (gutter * 2) + (bleed * 2)) <= viewportWidth);
    if (!fits) {
      fittingDeviceCount--;
    }
    // Set the button to disabled if the device doesn't fit in the current
    // viewport.
    // Toggle between the prop() and removeProp() methods.
    $this.attr('disabled', !fits)
      .attr('aria-disabled', !fits);
  });
  // Set the number of devices that fit the current viewport.
  view.model.set('fittingDeviceCount', fittingDeviceCount);
}

/**
 * Updates the model to reflect the properties of the chosen device.
 *
 * @param Backbone.View view
 *   The View curried to this handler. This function is used in multiple Views,
 *   so we bind it as an argument to the handler function in order to avoid
 *   having to reference it through a 'this' object which will trigger 'Possible
 *   strict violation' warning messages in JSHint.
 * @param jQuery.Event event
 */
function selectDevice (view, event) {
  if (typeof event.target.className === 'string' && /responsive-preview-device/.test(event.target.className)) {
    var $link = $(event.target);
    var name = $link.data('responsive-preview-name');
    // If the clicked link is already active, then shut down the preview.
    if (view.model.get('activeDevice') === name) {
      view.model.set('isActive', false);
      return;
    }
    // Update the device dimensions.
    view.model.set({
      'activeDevice': name,
      'dimensions': {
        'width': parseInt($link.data('responsive-preview-width'), 10),
        'height': parseInt($link.data('responsive-preview-height'), 10),
        'dppx': parseFloat($link.data('responsive-preview-dppx'), 10)
      }
    });
    // Toggle the preview on.
    view.model.set('isActive', true);

    event.preventDefault();
    event.stopPropagation();
    event.stopImmediatePropagation();
  }
}

/**
 * Registers theme templates with Drupal.theme().
 */
$.extend(Drupal.theme, {
  /**
   * Theme function for the preview container element.
   *
   * @return
   *   The corresponding HTML.
   */
  responsivePreviewContainer: function () {
    return '<div id="responsive-preview" class="responsive-preview" style="opacity: 0;"><div id="responsive-preview-modal-background" class="responsive-preview-modal-background"></div></div>';
  },

  /**
   * Theme function for the close button for the preview container.
   *
   * @param Object strings
   *   A hash of strings to use in the template.
   * @return
   *   The corresponding HTML.
   */
  responsivePreviewFrameContainer: function (strings) {
    return '<div id="responsive-preview-frame-container" class="responsive-preview-frame-container" aria-describedby="responsive-preview-frame-label">' +
        '<label id="responsive-preview-frame-label" class="responsive-preview-device-label" for="responsive-preview-frame-container">' +
          '<span class="responsive-preview-device-label-text"></span>' +
          // The space is necessary to prevent screen readers from pronouncing a
          // run-on word between the last word of the label and the first word
          // of the details.
          '<span>&#32;</span>' +
          '<span class="responsive-preview-device-label-details element-invisible"></span>' +
        '</label>' +
        '<button id="responsive-preview-close" title="' + strings.close + '" role="button" class="responsive-preview-icon responsive-preview-icon-close responsive-preview-control responsive-preview-close" aria-pressed="false"><span class="element-invisible">' + strings.close + '</span></button>' +
        '<button id="responsive-preview-orientation" title="' + strings.orientation + '" role="button" class="responsive-preview-icon responsive-preview-icon-orientation responsive-preview-control responsive-preview-orientation" aria-pressed="false"><span class="element-invisible">' + strings.orientation + '</span></button>' +
      '</div>';
  },

  /**
   * Theme function for the scrolling wrapper of the preview container.
   *
   * @return
   *   The corresponding HTML.
   */
  responsivePreviewScrollContainer: function () {
    return '<div id="responsive-preview-scroll-track"><div id="responsive-preview-scroll-pane"></div></div>';
  },

  /**
   * Theme function for a responsive preview iframe element.
   *
   * @return
   *   The corresponding HTML.
   */
  responsivePreviewFrame: function () {
    return '<iframe id="responsive-preview-frame" width="100%" height="100%" frameborder="0" scrolling="auto" allowtransparency="true"></iframe>';
  }
});

}(jQuery, Backbone, Drupal));
