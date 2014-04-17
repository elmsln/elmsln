var H5P = H5P || {};

if (H5P.getPath === undefined) {
  /**
   * Find the path to the content files based on the id of the content
   *
   * Also identifies and returns absolute paths
   *
   * @param {String} path Absolute path to a file, or relative path to a file in the content folder
   * @param {Number} contentId Identifier of the content requesting the path
   * @returns {String} The path to use.
   */
  H5P.getPath = function (path, contentId) {
    if (path.substr(0, 7) === 'http://' || path.substr(0, 8) === 'https://') {
      return path;
    }

    return H5PIntegration.getContentPath(contentId) + path;
  };
}

if (H5P.newInstance === undefined) {
  /**
   * Helps create new instance of H5P library.
   *
   * @param {Object} library Container library (the über name of the library(namespace, name and versionnumber)) and .
   * @returns {Object} Instance of library
   */
  H5P.newInstance = function (library) {
    // TODO: Add some try catching?
    // TODO: Dynamically try to load libraries currently not loaded?
    return new (H5P.classFromName(library.library.split(' ')[0]))(library.params, H5PEditor.contentId);
  };
}