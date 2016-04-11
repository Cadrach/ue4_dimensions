'use strict';

/* App Module */

var dimensionsControllers = angular.module('dimensionsControllers', []);

dimensionsControllers.controller('MainCtrl', ['$scope',
    function($scope) {
        $scope.testValue = "WORKING";
    }]);