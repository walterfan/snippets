# 24点游戏

* GameApp
* GameController
* GameService

## 例子

### JavaScript
	
	var app = angular.module("GameApp", []);
	
	app.controler('GameApp', ['$scope', function($scope) {
		$scope.name = "Walter"
	
	}]);

### Html
	<!DOCTYPE html>
	<html lang="en-US">
	<script src="http://ajax.googleapis.com/ajax/libs/angularjs/1.4.8/angular.min.js"></script>
	<body>
	
	<div ng-app="">
	 	<p>Name : <input type="text" ng-model="name"></p>
	 	<h1>Hello {{name}}</h1>
	</div>
	
	</body>
	</html>
	




