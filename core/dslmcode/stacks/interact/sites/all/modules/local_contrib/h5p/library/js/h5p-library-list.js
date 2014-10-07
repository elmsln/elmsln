var H5PLibraryList= H5PLibraryList || {};

(function ($) {

  /**
   * Initializing
   */
  H5PLibraryList.init = function () {
    var $adminContainer = H5PIntegration.getAdminContainer();
    
    var libraryList = H5PIntegration.getLibraryList();
    if (libraryList.notCached) {
      $adminContainer.append(H5PUtils.getRebuildCache(libraryList.notCached));
    }
    
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
    var t = H5PIntegration.i18n.H5P;
    $.each (libraries.listData, function (index, library) {
      var $libraryRow = H5PUtils.createTableRow([
        library.title,
        library.numContent,
        library.numContentDependencies === -1 ? t.NA : library.numContentDependencies,
        library.numLibraryDependencies,
        '<div class="h5p-admin-buttons-wrapper">\
          <button class="h5p-admin-upgrade-library"></button>\
          <button class="h5p-admin-view-library" title="' + t.viewLibrary + '"></button>\
          <button class="h5p-admin-delete-library"></button>\
        </div>'
      ]);
      
      if (library.upgradeUrl === null) {
        $('.h5p-admin-upgrade-library', $libraryRow).remove();
      }
      else if (library.upgradeUrl === false || library.numContent === 0) {
        $('.h5p-admin-upgrade-library', $libraryRow).attr('disabled', true);
      }
      else {
        $('.h5p-admin-upgrade-library', $libraryRow).attr('title', t.upgradeLibrary).click(function () {
          window.location.href = library.upgradeUrl;
        });
      }
      
      // Open details view when clicked
      $('.h5p-admin-view-library', $libraryRow).on('click', function () {
        window.location.href = library.detailsUrl;
      });
      
      var $deleteButton = $('.h5p-admin-delete-library', $libraryRow);
      if (library.numContent !== 0 || library.numContentDependencies !== 0 || library.numLibraryDependencies !== 0) {
        // Disabled delete if content.
        $deleteButton.attr('disabled', true);
      }
      else {
        // Go to delete page om click.
        $deleteButton.attr('title', t.deleteLibrary).on('click', function () {
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
