'use strict';

// Defining angularjs application.
var myApp = angular.module('myApp', []);
// Controller function and passing $http service and $scope var.
myApp.controller('myController', function($scope, $http) {
    // create a blank object to handle form data.
    $scope.user = {};
    // calling our submit function.
    $scope.submitForm = function() {
        var postData = {
            username:$scope.user.username,
            email: $scope.user.email,
            password: $scope.user.password,
            passwordConfirmation: $scope.user.passwordConfirmation
        };
        $http({
            method  : 'POST',
            url     : '/checklist/api/v1/users/register',
            data    : postData,
            headers : {'Content-Type': 'application/json'}
        })
            .success(function(data) {
                if (data.errors) {
                    // Showing errors.
                    $scope.errorName = data.errors.name;
                    $scope.errorUserName = data.errors.username;
                    $scope.errorEmail = data.errors.email;
                } else {
                    $scope.message = data.message;
                }
            });
    };
});