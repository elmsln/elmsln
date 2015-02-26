(function ($) {

  // Bind removing of file to selector elements
  function plup_remove_item(selector) {
    $(selector).bind('click', function(event) {
      var parent = $(this).parent();
      var parentsParent = parent.parent();
      parent.remove();
      parentsParent.trigger('formUpdated');
    });
  }

  // Bind resize effect on title and alt fields on focus
  function plup_resize_input(selector) {
    var w = $(selector).outerWidth();
    if (w < 300) {
      $(selector).bind('focus', function(event) {
        $(this).css('z-index', 10).animate({'width': '300px'}, 300);
      });
      $(selector).bind('blur', function(event) {
        $(this).removeAttr('style');
      });
    }
  }

  Drupal.behaviors.plup = {
    attach: function(context, settings) {

      // Apply Plupload to each form element instance
      $.each(settings.plup, function(plupName, plupInstance) {
            var cid = plupInstance.container;
            var id = '#' + cid;


            // Apply setting only once
            $(id).once('plup', function() {
                  /**
                  * Initial tasks
                  */

                  $(id +' .plup-list').sortable(); // Activate sortable
                  $(id +'-plup-upload').hide(); // Hide upload button
                  var uploader = new plupload.Uploader(plupInstance); // Create Plupload instance
                  plup_remove_item(id +' .plup-remove-item'); // Bind remove functionality on existing images
                  plup_resize_input(id +' .plup-list > li > input.form-text'); // Bind resizing effect on existing inputs


                  /**
                   * Events
                   */

                  // Initialization
                  uploader.bind('Init', function(up, params) {
                    // Nothing to do, just reminder of the presence for this event
                  });


                  // Starting upload
                  uploader.bind('Start', function(up, files) {
                    // Nothing to do, just reminder of the presence for this event
                  });


                  // Upload process state
                  uploader.bind('StateChanged', function(up) {
                    if (up.state == 2) {
                      $(id +' .plup-progress').progressbar(); // Activate progressbar
                    }
                    if (up.state == 1) {
                      $(id +' .plup-progress').progressbar('destroy'); // Destroy progressbar
                      $(id +'-plup-upload').hide(); // Hide upload button
                      $(id +' .plup-drag-info').show(); // Show info
                    }
                  })


                  // Files were added into queue(only CURRENTLY added files)
                  uploader.bind('FilesAdded', function(up, files) {
                    $(id +' .plup-drag-info').hide(); // Hide info
                    $(id +'-plup-upload').show(); // Show upload button

                    // Put files visually into queue
                    $.each(files, function(i, file) {
                      $(id +'-plup-filelist table').append('<tr id="' + file.id + '">' +
                        '<td class="plup-filelist-file">' +  file.name + '</td>' +
                        '<td class="plup-filelist-size">' + plupload.formatSize(file.size) + '</td>' +
                        '<td class="plup-filelist-message"></td>' +
                        '<td class="plup-filelist-remove"><a class="plup-remove-file"></a></td>' +
                        '</tr>');

                      // Bind "remove" functionality to files added into queue
                      $(id +' #' + file.id + ' .plup-filelist-remove > a').bind('click', function(event) {
                        $('#' + file.id).remove();
                        up.removeFile(file);
                      });
                    });

                    up.refresh(); // Refresh for flash or silverlight
                  });


                  // File was removed from queue
                  // Doc states this ARE files but actually it IS a file
                  uploader.bind('FilesRemoved', function(up, file) {
                    // If there are not files in queue
                    if (up.files.length == 0) {
                      $(id +'-plup-upload').hide(); // Hide upload button
                      $(id +' .plup-drag-info').show(); // Show info
                    }
                  });


                  // File is being uploaded
                  uploader.bind('UploadProgress', function(up, file) {
                    // Refresh progressbar
                    $(id +' .plup-progress').progressbar({value: uploader.total.percent});
                  });


                  // Error event
                  uploader.bind('Error', function(up, err) {
                    $(id +' #' + err.file.id + ' > .plup-filelist-message').append('<b>Error: ' + err.message + '</b>');
                    up.refresh(); // Refresh for flash or silverlight
                  });


                  // Event after a file has been uploaded from queue
                  uploader.bind('FileUploaded', function(up, file, response) {
                    // Response is an object with response parameter so 2x response
                    var fileSaved = $.parseJSON(response.response);
                    var delta = $(id +' .plup-list li').length;
                    var name = plupName +'[' + delta + ']';

                    // Plupload has weird error handling behavior so we have to check for errors here
                    if (fileSaved.error_message) {
                      $(id +' #' + file.id + ' > .plup-filelist-message').append('<b>Error: ' + fileSaved.error_message + '</b>');
                      up.refresh(); // Refresh for flash or silverlight
                      return;
                    }

                    $(id +'-plup-filelist #' + file.id).remove(); // Remove uploaded file from queue
                    var title_field = plupInstance.title_field ? '<input title="'+ Drupal.t('Title') +'" type="text" class="form-text plup-title" name="'+ name + '[title]" value="" />' : '';
                    var alt_field = plupInstance.alt_field ? '<input title="'+ Drupal.t('Alternative text') +'" type="text" class="form-text plup-alt" name="'+ name + '[alt]" value="" />' : '';

                    // Add image thumbnail into list of uploaded items
                    $(id +' .plup-list').append(
                      '<li class="ui-state-default">' +
                      '<div class="plup-thumb-wrapper"><img src="'+ fileSaved.secure_uri + '" title="'+ Drupal.checkPlain(file.target_name) +'" /></div>' +
                      '<a class="plup-remove-item"></a>' +
                      title_field +
                      alt_field +
                      '<input type="hidden" name="' + name + '[fid]" value="' + fileSaved.fid + '" />' +
                      '<input type="hidden" name="' + name + '[weight]" value="' + delta + '" />' +
                      '<input type="hidden" name="' + name + '[rename]" value="' + file.name +'" />' +
                      '</li>');

                    // Bind remove functionality to uploaded file
                    var new_element = $('input[name="'+ name +'[fid]"]');
                    var remove_element = $(new_element).siblings('.plup-remove-item');
                    plup_remove_item(remove_element);

                    // Bind resize effect to inputs of uploaded file
                    var text_element = $(new_element).siblings('input.form-text');
                    plup_resize_input(text_element);

                    // Tell Drupal that form has been updated
                    new_element.trigger('formUpdated');
                  });


                  // All fields from queue has been uploaded
                  uploader.bind('UploadComplete', function(up, files) {
                    $(id +' .plup-list').sortable('refresh'); // Refresh sortable
                    $(id +' .plup-drag-info').show(); // Show info
                  });



                  /**
                   * Additional tasks
                   */

                  // Upload button functionality
                  $('#'+ plupInstance.upload).click(function(e) {
                    // Forbid uploading more than the allowed number of files, if set
                    if (plupInstance.max_files > 0) {
                      var uploaded = $(id +' .plup-list li').length;
                      var selected = $(id +'-plup-filelist td.plup-filelist-file').length;
                      var allowed = plupInstance.max_files - uploaded;
                      if ((selected + uploaded) > plupInstance.max_files) {
                        alert(Drupal.formatPlural(allowed, 'You can upload only 1 file.', 'You can upload only @count files.'));
                        return;
                      }
                    }
                    uploader.start();
                    e.preventDefault();
                  });


                  // Initialize Plupload
                  uploader.init();


                  // Change weight values for images when reordering using sortable
                  $(id +' .plup-list').bind('sortupdate', function(event, ui) {
                    $(this).find('li').each(function(index) {
                      $(this).find('input[name$="[weight]"]').val(index);
                    });
                  });


            });
      });
    }
  }

})(jQuery);