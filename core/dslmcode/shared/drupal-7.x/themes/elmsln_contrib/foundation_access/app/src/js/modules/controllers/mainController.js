'use strict';

elmsMediaWidget.controller('mainController', ['$scope', function($scope){
  $scope.dropzoneConfig = {
    'options': { // passed into the Dropzone constructor
      'url': 'upload.php'
    },
    'eventHandlers': {
      'sending': function (file, xhr, formData) {
      },
      'success': function (file, response) {
      }
    }
  };
}]);

console.log('mainController');