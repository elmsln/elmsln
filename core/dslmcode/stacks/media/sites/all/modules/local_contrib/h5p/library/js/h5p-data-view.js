var H5PDataView = (function ($) {

  /**
   * Initialize a new H5P data view.
   *
   * @class
   * @param {Object} container
   *   Element to clear out and append to.
   * @param {String} source
   *   URL to get data from. Data format: {num: 123, rows:[[1,2,3],[2,4,6]]}
   * @param {Array} headers
   *   List with column headers. Can be strings or objects with options like
   *   "text" and "sortable". E.g.
   *   [{text: 'Col 1', sortable: true}, 'Col 2', 'Col 3']
   * @param {Object} l10n
   *   Localization / translations. e.g.
   *   {
   *     loading: 'Loading data.',
   *     ajaxFailed: 'Failed to load data.',
   *     noData: "There's no data available that matches your criteria.",
   *     currentPage: 'Page $current of $total',
   *     nextPage: 'Next page',
   *     previousPage: 'Previous page',
   *     search: 'Search'
   *   }
   * @param {Object} classes
   *   Custom html classes to use on elements.
   *   e.g. {tableClass: 'fixed'}.
   * @param {Array} filters
   *   Make it possible to filter/search in the given column.
   *   e.g. [null, true, null, null] will make it possible to do a text
   *   search in column 2.
   * @param {Function} loaded
   *   Callback for when data has been loaded.
   * @param {Object} order
   */
  function H5PDataView(container, source, headers, l10n, classes, filters, loaded, order) {
    var self = this;

    self.$container = $(container).addClass('h5p-data-view').html('');

    self.source = source;
    self.headers = headers;
    self.l10n = l10n;
    self.classes = (classes === undefined ? {} : classes);
    self.filters = (filters === undefined ? [] : filters);
    self.loaded = loaded;
    self.order = order;

    self.limit = 20;
    self.offset = 0;
    self.filterOn = [];

    self.loadData();
  }

  /**
   * Load data from source URL.
   *
   * @public
   */
  H5PDataView.prototype.loadData = function () {
    var self = this;

    // Throbb
    self.setMessage(H5PUtils.throbber(self.l10n.loading));

    // Create URL
    var url = self.source;
    url += (url.indexOf('?') === -1 ? '?' : '&') + 'offset=' + self.offset + '&limit=' + self.limit;

    // Add sorting
    if (self.order !== undefined) {
      url += '&sortBy=' + self.order.by + '&sortDir=' + self.order.dir;
    }

    // Add filters
    var filtering;
    for (var i = 0; i < self.filterOn.length; i++) {
      if (self.filterOn[i] === undefined) {
        continue;
      }

      filtering = true;
      url += '&filters[' + i + ']=' + encodeURIComponent(self.filterOn[i]);
    }

    // Fire ajax request
    $.ajax({
      dataType: 'json',
      cache: true,
      url: url
    }).fail(function () {
      // Error handling
      self.setMessage($('<p/>', {text: self.l10n.ajaxFailed}));
    }).done(function (data) {
      if (!data.rows.length) {
        self.setMessage($('<p/>', {text: filtering ? self.l10n.noData : self.l10n.empty}));
      }
      else {
        // Update table data
        self.updateTable(data.rows);

        // Update pagination widget
        self.updatePagination(data.num);
      }

      if (self.loaded !== undefined) {
        self.loaded();
      }
    });
  };

  /**
   * Display the given message to the user.
   *
   * @public
   * @param {jQuery} $message wrapper with message
   */
  H5PDataView.prototype.setMessage = function ($message) {
    var self = this;

    if (self.table === undefined) {
      self.$container.html('').append($message);
    }
    else {
      self.table.setBody($message);
    }
  };

  /**
   * Update table data.
   *
   * @public
   * @param {Array} rows
   */
  H5PDataView.prototype.updateTable = function (rows) {
    var self = this;

    if (self.table === undefined) {
      // Clear out container
      self.$container.html('');

      // Add filters
      self.addFilters();

      // Create new table
      self.table = new H5PUtils.Table(self.classes, self.headers);
      self.table.setHeaders(self.headers, function (order) {
        // Sorting column or direction has changed.
        self.order = order;
        self.loadData();
      }, self.order);
      self.table.appendTo(self.$container);
    }

    // Add/update rows
    self.table.setRows(rows);
  };

  /**
   * Update pagination widget.
   *
   * @public
   * @param {Number} num size of data collection
   */
  H5PDataView.prototype.updatePagination = function (num) {
    var self = this;

    if (self.pagination === undefined) {
      // Create new widget
      var $pagerContainer = $('<div/>', {'class': 'h5p-pagination'});
      self.pagination = new H5PUtils.Pagination(num, self.limit, function (offset) {
        // Handle page changes in pagination widget
        self.offset = offset;
        self.loadData();
      }, self.l10n);

      self.pagination.appendTo($pagerContainer);
      self.table.setFoot($pagerContainer);
    }
    else {
      // Update existing widget
      self.pagination.update(num, self.limit);
    }
  };

  /**
   * Add filters.
   *
   * @public
   */
  H5PDataView.prototype.addFilters = function () {
    var self = this;

    for (var i = 0; i < self.filters.length; i++) {
      if (self.filters[i] === true) {
        // Add text input filter for col i
        self.addTextFilter(i);
      }
    }
  };

  /**
   * Add text filter for given col num.

   * @public
   * @param {Number} col
   */
  H5PDataView.prototype.addTextFilter = function (col) {
    var self = this;

    /**
     * Find input value and filter on it.
     * @private
     */
    var search = function () {
      var filterOn = $input.val().replace(/^\s+|\s+$/g, '');
      if (filterOn === '') {
        filterOn = undefined;
      }
      if (filterOn !== self.filterOn[col]) {
        self.filterOn[col] = filterOn;
        self.loadData();
      }
    };

    // Add text field for filtering
    var typing;
    var $input = $('<input/>', {
      type: 'text',
      placeholder: self.l10n.search,
      on: {
        'blur': function () {
          clearTimeout(typing);
          search();
        },
        'keyup': function (event) {
          if (event.keyCode === 13) {
            clearTimeout(typing);
            search();
            return false;
          }
          else {
            clearTimeout(typing);
            typing = setTimeout(function () {
              search();
            }, 500);
          }
        }
      }
    }).appendTo(self.$container);
  };

  return H5PDataView;
})(H5P.jQuery);
