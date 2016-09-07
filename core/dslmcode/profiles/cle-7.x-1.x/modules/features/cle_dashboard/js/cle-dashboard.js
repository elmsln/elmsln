Drupal.behaviors.cleDashboard = {
  attach: function (context, settings) {
    angular.module('cleDashboard', ['ngSanitize'])
      .controller('cleAssignmentsController', ['$scope', function($scope) {
        if (Drupal.settings.cleDashboard) {
          console.log(Drupal.settings.cleDashboard);
          $scope.data = Drupal.settings.cleDashboard;
          $scope.basePath = Drupal.settings.basePath;
        }
      }])
    ; // end Angular
  }
};
