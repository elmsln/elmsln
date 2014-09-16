var H5PLibraryList= H5PLibraryList || {};

(function ($) {

  /**
   * Initializing
   */
  H5PLibraryList.init = function () {
    var $adminContainer = H5PIntegration.getAdminContainer();
    
    // Create library list
    $adminContainer.append(H5PLibraryList.createLibraryList(H5PIntegration.getLibraryList()));
  };
  
  /**
   * Create the library list
   * 
   * @param {object} libraries List of libraries and headers
   */
  H5PLibraryList.createLibraryList = function (libraries) {
    
    if(libraries.listData === undefined || libraries.listData.length === 0) {
      return;
    }
    
    // Create table
    var $table = H5PUtils.createTable(libraries.listHeaders);
    $table.addClass('libraries');
    
    // Add libraries
    $.each (libraries.listData, function (index, library) {
      var $libraryRow = H5PUtils.createTableRow([
        library.name, 
        library.machineName, 
        library.contentCount, 
        library.libraryDependencyCount,
        '<button class="h5p-admin-view-library">&#xf002;</button>' +
        '<button class="h5p-admin-delete-library">&#xf057;</button>'
      ]);
      
      // Open details view when clicked
      $('.h5p-admin-view-library', $libraryRow).on('click', function () {
        window.location.href = library.detailsUrl;
      });
      
      var $deleteButton = $('.h5p-admin-delete-library', $libraryRow);
      if (library.contentCount !== 0 || library.libraryDependencyCount !== 0) {
        // Disabled delete if content.
        $deleteButton.attr('disabled', true); //.addClass('disabled');
      }
      else {
        // Go to delete page om click.
        $deleteButton.on('click', function () {
          window.location.href = library.deleteUrl;
        });
      }

      $table.append($libraryRow);
    });
    
    return $table;
  };
 
  
  // Initialize me:
  $(document).ready(function () {
    if (!H5PLibraryList.initialized) {
      H5PLibraryList.initialized = true;
      H5PLibraryList.init();
    }
  });
  
})(H5P.jQuery);
