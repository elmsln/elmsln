module.exports = function() {
	angular.module('Fa', [
	  'ngResource'
	])

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
	 * Controllers
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
	}])
	;
};