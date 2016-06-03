angular.module('Fa', [
  'ngResource'
  ])
/**
 * Notes / TODO: 
 * We will need to make 'Fa' 'elmsln_' eventually when we do a multiple app.js file approach
 */

/**
 * Constants
 */
.constant('endpoint_url', '')

/**
 * Config
 */
.config(['$resourceProvider', function($resourceProvider) {
  // Don't strip trailing slashes from calculated URLs
  $resourceProvider.defaults.stripTrailingSlashes = false;
}])

/**
 * Service
 */
.service('CoursesService', ['$resource', 'endpoint_url', function($resource, endpoint_url) {
  return $resource(endpoint_url + '/node.json?type=course&deep-load-refs=field_collection_item,node', null, {
  	query: {
  		method: 'GET',
  		isArray: false
  	}
  });
}])

/**
 * Controllers (For now all functions are in 1 controller...may want more than one later?)
 */
 .controller('cisDashboard', ['$scope', 'CoursesService', function($scope, CoursesService) {
  $scope.courses = CoursesService.query();
  // simple selector to make this item be 'active'
  $scope.select = function(item) {
    $scope.selected = item;
  };
  // test to see if something is 'active'
  $scope.isActive = function(item) {
    return $scope.selected === item;
  };
  // Sets the default tab = '1' representing 'Sections'
  $scope.tab = 1; 
  // setTab function sets updates the tab in the view when called
  $scope.setTab = function(tab) {
    $scope.tab = tab;
  };
  // isSet checks if what tab is set to display the correct tab view. 
  $scope.isSet = function(tab) {
    return ($scope.tab === tab);
  };
  $scope.predicate = 'title';
  $scope.reverse = false;
  $scope.order = function(predicate) {
    $scope.predicate = predicate;
    $scope.reverse = ($scope.predicate === predicate) ? !$scope.reverse : false;
    console.log('within order function');
    console.log("Scope Predicate = " + $scope.predicate + " Var Predicate = " + predicate);
  };

}])
; // end Angular
console.log('cis angular working');
