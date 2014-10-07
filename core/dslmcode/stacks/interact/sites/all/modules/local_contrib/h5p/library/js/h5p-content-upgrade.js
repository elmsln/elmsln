var H5PUpgrades = H5PUpgrades || {};

(function ($) {
  var info, $container;
  
  // Initialize
  $(document).ready(function () {
    // Get library info
    info = H5PIntegration.getLibraryInfo();
    
    // Get and reset container
    $container = $('#h5p-admin-container').html('<p>' + info.message + '</p>');
    
    // Make it possible to select version
    var $version = $(getVersionSelect(info.versions)).appendTo($container);
    
    // Add "go" button
    $('<button/>', {
      class: 'h5p-admin-upgrade-button',
      text: info.buttonLabel,
      click: function () {
        // Start new content upgrade
        new ContentUpgrade($version.val());
      }
    }).appendTo($container);
  });  

  /**
   * Generate html for version select.
   *  
   * @param {Object} versions
   * @returns {String}
   */
  var getVersionSelect = function (versions) {
    var html = '';
    for (var id in versions) {
      html += '<option value="' + id + '">' + versions[id] + '</option>';
    }
    if (html !== '') {
      html = '<select>' + html + '</select>';
      return html;
    }
  };
  
  /**
   * Private. Helps process each property on the given object asynchronously in serial order.
   * 
   * @param {Object} obj
   * @param {Function} process
   * @param {Function} finished
   */
  var asyncSerial = function (obj, process, finished) {
    var id, isArray = obj instanceof Array;
    
    // Keep track of each property that belongs to this object. 
    if (!isArray) {
      var ids = [];
      for (id in obj) {
        if (obj.hasOwnProperty(id)) {
          ids.push(id);
        }
      }
    }
    
    var i = -1; // Keeps track of the current property
    
    /**
     * Private. Process the next property
     */
    var next = function () {
      id = isArray ? i : ids[i];
      process(id, obj[id], check);
    };
    
    /**
     * Private. Check if we're done or have an error.
     *  
     * @param {String} err
     */
    var check = function (err) {
      i++;
      if (i === (isArray ? obj.length : ids.length) || (err !== undefined && err !== null)) {
        finished(err);
      }
      else {
        next();
      }
    };
    
    check(); // Start
  };

  /** 
   * Make it easy to keep track of version details.
   * 
   * @param {String} version
   * @param {Number} libraryId
   * @returns {_L1.Version}
   */
  function Version(version, libraryId) {
    if (libraryId !== undefined) {
      version = info.versions[libraryId];
      
      // Public
      this.libraryId = libraryId;
    }
    var versionSplit = version.split('.', 3);
    
    // Public
    this.major = versionSplit[0];
    this.minor = versionSplit[1];
    
    /**
     * Public. Custom string for this object.
     * 
     * @returns {String}
     */
    this.toString = function () {
      return version;
    };
  }

  /**
   * Displays a throbber in the status field.
   *  
   * @param {String} msg
   * @returns {_L1.Throbber}
   */
  function Throbber(msg) {
    var $throbber = H5PUtils.throbber(msg);
    $container.html('').append($throbber);
    
    /**
     * Makes it possible to set the progress.
     * 
     * @param {String} progress
     */
    this.setProgress = function (progress) {
      $throbber.text(msg + ' ' + progress);
    };
  }

  /**
   * Start a new content upgrade.
   * 
   * @param {Number} libraryId
   * @returns {_L1.ContentUpgrade}
   */
  function ContentUpgrade(libraryId) {
    var self = this;
    
    // Get selected version
    self.version = new Version(null, libraryId);
    
    // Create throbber with loading text and progress
    self.throbber = new Throbber(info.inProgress.replace('%ver', self.version));

    // Get the next batch
    self.nextBatch({
      libraryId: libraryId,
      token: info.token
    });
  }
  
  /**
   * Get the next batch and start processing it.
   * 
   * @param {Object} outData
   */
  ContentUpgrade.prototype.nextBatch = function (outData) {
    var self = this;
    
    $.post(info.infoUrl, outData, function (inData) {
      if (!(inData instanceof Object)) {
        // Print errors from backend
        return self.setStatus(inData);
      } 
      if (inData.left === 0) {
        // Nothing left to process
        return self.setStatus(info.done);
      }
      
      self.left = inData.left;
      self.token = inData.token;
      
      // Start processing
      self.processBatch(inData.params);
    });
  };
  
  /**
   * Set current status message.
   * 
   * @param {String} msg
   */
  ContentUpgrade.prototype.setStatus = function (msg) {
    $container.html(msg);
  };

  /**
   * Process the given parameters.
   * 
   * @param {Object} parameters
   */
  ContentUpgrade.prototype.processBatch = function (parameters) {
    var self = this;
    var upgraded = {}; // Track upgraded params
    
    var current = 0; // Track progress
    asyncSerial(parameters, function (id, params, next) {
      
      // Make params possible to work with
      params = JSON.parse(params);
      
      // Upgrade this content.
      self.upgrade(info.library.name, new Version(info.library.version), self.version, params, function (err, params) {
        if (!err) {
          upgraded[id] = JSON.stringify(params);

          current++;
          self.throbber.setProgress(Math.round((info.total - self.left + current) / (info.total / 100)) + ' %');
        }
        next(err);
      });

    }, function (err) {
      // Finished with all parameters that came in
      if (err) {
        return self.setStatus('<p>' + info.error + '<br/>' + err + '</p>');
      }

      // Save upgraded content and get next round of data to process
      self.nextBatch({
        libraryId: self.version.libraryId,
        token: self.token,
        params: JSON.stringify(upgraded)
      });
    });
  };
  
  /**
   * Upgade the given content.
   * 
   * @param {String} name
   * @param {Version} oldVersion
   * @param {Version} newVersion
   * @param {Object} params
   * @param {Function} next
   * @returns {undefined}
   */
  ContentUpgrade.prototype.upgrade = function (name, oldVersion, newVersion, params, next) {
    var self = this;
    
    // Load library details and upgrade routines
    self.loadLibrary(name, newVersion, function (err, library) {
      if (err) {
        return next(err);
      }
      
      // Run upgrade routines on params
      self.processParams(library, oldVersion, newVersion, params, function (err, params) {
        if (err) {
          return next(err);
        }
        
        // Check if any of the sub-libraries need upgrading
        asyncSerial(library.semantics, function (index, field, next) {
          self.processField(field, params[field.name], function (err, upgradedParams) {
            if (upgradedParams) {
              params[field.name] = upgradedParams;
            }
            next(err);
          });
        }, function (err) {
          next(err, params);
        });
      });
    });
  };
  
  /**
   * Load library data needed for content upgrade.
   * 
   * @param {String} name
   * @param {Version} version
   * @param {Function} next
   */
  ContentUpgrade.prototype.loadLibrary = function (name, version, next) {
    var self = this;
    
    $.ajax({
      dataType: 'json',
      url: info.libraryBaseUrl + '/' + name + '/' + version.major + '/' + version.minor
    }).fail(function () {
      next(info.errorData.replace('%lib', name + ' ' + version));
    }).done(function (library) {
      if (library.upgradesScript) {
        self.loadScript(library.upgradesScript, function (err) {
          if (err) {
            err = info.errorScript.replace('%lib', name + ' ' + version);
          }
          next(err, library);
        });
      }
      else {
        next(null, library);
      }
    });
  };
  
  /**
   * Load script with upgrade hooks.
   * 
   * @param {String} url
   * @param {Function} next
   */
  ContentUpgrade.prototype.loadScript = function (url, next) {
    $.ajax({
      dataType: 'script',
      cache: true,
      url: url
    }).fail(function () {
      next(true);
    }).done(function () {
      next();
    });
  };
  
  /**
   * Run upgrade hooks on params.
   * 
   * @param {Object} library
   * @param {Version} oldVersion
   * @param {Version} newVersion
   * @param {Object} params
   * @param {Function} next
   */
  ContentUpgrade.prototype.processParams = function (library, oldVersion, newVersion, params, next) {
    if (H5PUpgrades[library.name] === undefined) {
      if (library.upgradesScript) {
        // Upgrades script should be loaded so the upgrades should be here.
        return next(info.errorScript.replace('%lib', library.name + ' ' + newVersion));
      }
      
      // No upgrades script. Move on
      return next(null, params);
    }

    // Run upgrade hooks. Start by going through major versions
    asyncSerial(H5PUpgrades[library.name], function (major, minors, nextMajor) {
      if (major < oldVersion.major || major > newVersion.major) {
        // Older than the current version or newer than the selected 
        nextMajor();
      }
      else {
        // Go through the minor versions for this major version
        asyncSerial(minors, function (minor, upgrade, nextMinor) {
          if (minor <= oldVersion.minor || minor > newVersion.minor) {
            // Older than or equal to the current version or newer than the selected
            nextMinor();
          }
          else {
            // We found an upgrade hook, run it
            if (upgrade.contentUpgrade !== undefined && typeof upgrade.contentUpgrade === 'function') {
              upgrade.contentUpgrade(params, function (err, upgradedParams) {
                params = upgradedParams;
                nextMinor(err);
              });
            }
            else {
              nextMinor(info.errorScript.replace('%lib', library.name + ' ' + newVersion));
            }
          }
        }, nextMajor);
      }
    }, function (err) {
      next(err, params);
    });
  };
  
  /**
   * Process parameter fields to find and upgrade sub-libraries.
   * 
   * @param {Object} field
   * @param {Object} params
   * @param {Function} next
   */
  ContentUpgrade.prototype.processField = function (field, params, next) {
    var self = this;
    
    if (params === undefined) {
      return next();
    }
    
    switch (field.type) {
      case 'library':
        if (params.library === undefined || params.params === undefined) {
          return next();
        }
        
        // Look for available upgrades
        var usedLib = params.library.split(' ', 2);
        for (var i = 0; i < field.options.length; i++) {
          var availableLib = field.options[i].split(' ', 2);
          if (availableLib[0] === usedLib[0]) {
            if (availableLib[1] === usedLib[1]) {
              return next(); // Same version
            }
            
            // We have different versions
            var usedVer = new Version(usedLib[1]);
            var availableVer = new Version(availableLib[1]);
            if (usedVer.major > availableVer.major || (usedVer.major === availableVer.major && usedVer.minor >= availableVer.minor)) {
              return next(); // Larger or same version that's available
            }
            
            // A newer version is available, upgrade params
            return self.upgrade(availableLib[0], usedVer, availableVer, params.params, function (err, upgraded) {
              if (!err) {
                params.library = availableLib[0] + ' ' + availableVer.major + '.' + availableVer.minor;
                params.params = upgraded;
              }
              next(err, params);
            });
          }
        }
        next();
        break;

      case 'group':
        if (field.fields.length === 1) {
          // Single field to process, wrapper will be skipped
          self.processField(field.fields[0], params, function (err, upgradedParams) {
            if (upgradedParams) {
              params = upgradedParams;
            }
            next(err, params);
          });
        }
        else {
          // Go through all fields in the group
          asyncSerial(field.fields, function (index, subField, next) {
            self.processField(subField, params[subField.name], function (err, upgradedParams) {
              if (upgradedParams) {
                params[subField.name] = upgradedParams;
              }
              next(err);
            });
          }, function (err) {
            next(err, params);
          });
        }
        break;

      case 'list':
        // Go trough all params in the list
        asyncSerial(params, function (index, subParams, next) {
          self.processField(field.field, subParams, function (err, upgradedParams) {
            if (upgradedParams) {
              params[index] = upgradedParams;
            }
            next(err);
          });
        }, function (err) {
          next(err, params);
        });
        break;

      default:
        next();
    }
  };

})(H5P.jQuery);