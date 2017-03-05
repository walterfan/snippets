var app = angular.module("KanbanApp", ['ngResource']);


app.factory('Messae', fucntion($resource){
    return $resource('/api/messages/:id');
});

app.service("greeter", function() {
	this.name="";
	this.greeting=function() {
		return (this.name)? "Hello, " + this.name:"";
	};
}) ;

app.controller("KanbanController", function($scope, greeter) {
	$scope.greeter = greeter;
})
