'use strict';
/* Filter */

apiTestApp.filter('jsbeautify',['$sce',function($sce){
    return function(jsCode){
        try{
            var strJsCode = jsCode.replace(/\n/g,"<br/>");
            strJsCode = strJsCode.replace(/ /g,"&nbsp;&nbsp;");
            return $sce.trustAsHtml(strJsCode);   //jsCode.replace(/\n/g,"<br>");
        }catch(e){
            console.log(e);
        }
        return jsCode;
    }
}]);

/* Controllers */

apiTestApp.controller('CallbackCtrl', ['$scope','ApiTestService','$timeout','$interval',function ($scope, ApiTestService, $timeout, $interval) {
    $scope.ivrServiceURI = "https://givr-ats.webex.com/api/v1.0/callbacks";
    $scope.phoneNumberPrefix = "86";
    $scope.phoneNumber = "551-66111745";
    $scope.referURI = "sip:1234@10.121.105.86";
    $scope.notifyURI = "http://10.121.105.72/poros/api/v1/notifications";
    $scope.requireConfirmation = true;
    $scope.showError = false;
    $scope.serviceProvider = "Spark";
    $scope.sponsor = "spark";
    $scope.toType = "PhoneNumber";
    $scope.postDialSequence = "";
    $scope.destinationType = "PSTN";
    $scope.siteID = "";
    $scope.siteName = "";
    $scope.meetingID = "";
    $scope.attendeeID = "";
    $scope.languageCode = "en_US";

    $scope.callback=function(){
         $scope.showError = false;
         var postData = {
             ivrServiceURI: $scope.ivrServiceURI,
             serviceProvider: $scope.serviceProvider,
             sponsor: $scope.sponsor,
             phoneNumberPrefix: $scope.phoneNumberPrefix,
             phoneNumber: $scope.phoneNumber,
             referURI: $scope.referURI,
             notifyURI: $scope.notifyURI,
             requireConfirmation: $scope.requireConfirmation,
             toType: $scope.toType,
             sipURI: $scope.sipURI,
             postDialSequence: $scope.postDialSequence,
             destinationType: $scope.destinationType,
             siteID: $scope.siteID,
             siteName: $scope.siteName,
             meetingID: $scope.meetingID,
             attendeeID: $scope.attendeeID,
             languageCode: $scope.languageCode
         };
         var promise = ApiTestService.createCallback(postData);
         promise.then(function(callback) {
             console.log(callback);
         }, function(data) {
             console.log(data);
             $scope.showError = true;
             if(data && data.trackingID && data.errors){
                 var errorDescription = "";
                 for(var i in data.errors){
                     errorDescription = errorDescription + data.errors[i].description + " ";
                 }
                 $scope.errorMessage="trackingID=" + data.trackingID + ", " + errorDescription;
             }
         });

    };
    //list
    var timer = $interval(function() {
        var promise = ApiTestService.getAllCallbacks();
        promise.then(function(data){
            $scope.callbacks = data;
        },function(data){
            console.log(data);
        });
    },6000);
    
    $scope.deleteCallback=function(taskID){
    	var promise = ApiTestService.deleteCallback(taskID);
        promise.then(function(data) {
        }, function(data) {
            console.log(data);
        });
    };

    $scope.deleteCallbackTask=function(taskID){
    	var promise = ApiTestService.deleteCallbackTask(taskID);
        promise.then(function(data) {
            $scope.showError = false;
        }, function(data) {
            console.log(data);
            $scope.showError = true;
            $scope.errorMessage=(data.errors[0].description);
        });
    };

    $scope.deleteAllCallback=function(){
    	var promise = ApiTestService.deleteAllCallback();
        promise.then(function(data) {
        }, function(data) {
            console.log(data);
        });
    };
    
}]);


apiTestApp.controller('CallInCtrl', ['$scope','ApiTestService','$timeout', '$interval', function ($scope, ApiTestService, $timeout, $interval) {
    $scope.meetingID = "1234567890";
    $scope.sipURI = "sip:6494@10.224.2.213";
    var getAllMeetings = function(){
        var promise = ApiTestService.getAllMeetings();
        promise.then(function(data){
            $scope.meetings = data;
            if(data.length>0){
                $timeout(function(){
                    $scope.meetingID = "";
                    $scope.sipURI = "";
                });
            }
        },function(data){
            console.log(data);
        });
    }
    $scope.deleteMeeting=function(meetingID){
        var promise = ApiTestService.deleteMeeting(meetingID);
        promise.then(function(data) {
            getAllMeetings();
        }, function(data) {
            console.log(data);
        });
    }
    $scope.set=function(){
        var postData = {
            meetingID: $scope.meetingID,
            sipUri: $scope.sipURI
        };
        var promise = ApiTestService.createMeeting(postData);
        promise.then(function(data) {
            getAllMeetings();
        }, function(data) {
            console.log(data);
            $scope.showError = true;
            if(data && data.errors){
                $scope.errorMessage=data.errors[0];
            }
        });
    };
    getAllMeetings();
}]);


apiTestApp.controller('E2eCasesSettingCtrl', ['$scope','ApiTestService','$timeout','$interval',function ($scope, ApiTestService, $timeout, $interval) {
    $timeout(function(){
        var promise = ApiTestService.getE2eCaseConfig();
        promise.then(function(e2eCaseConfig) {
            console.log(e2eCaseConfig);
            $scope.cronExpression = e2eCaseConfig.cronExpression;
        });
    });

    $scope.setE2eCaseConfig=function(){
         $scope.showMessage = false;
         var putData = {
             cronExpression: $scope.cronExpression
         };
         var promise = ApiTestService.setE2eCaseConfig(putData);
         promise.then(function(data) {
             console.log(data);
             $scope.showMessage = true;
             $scope.message = "Setting Success.";
             $scope.messageClass = "alert-success";
         }, function(data) {
             console.log(data);
             $scope.showMessage = true;
             $scope.messageClass = "alert-danger";
             if(data && data.trackingID && data.errors){
                 var errorDescription = "";
                 for(var i in data.errors){
                     errorDescription = errorDescription + data.errors[i].description + " ";
                 }
                 $scope.message="trackingID=" + data.trackingID + ", " + errorDescription;
             }
         });

    };

    $scope.e2eCaseRun=function(){
         $scope.showMessage = false;
         var promise = ApiTestService.e2eCaseRun();
         promise.then(function(data) {
             $scope.showMessage = true;
             $scope.message = "e2e cases are running.";
             $scope.messageClass = "alert-success";
         }, function(data) {
             $scope.showMessage = true;
             $scope.messageClass = "alert-danger";
             if(data && data.trackingID && data.errors){
                 var errorDescription = "";
                 for(var i in data.errors){
                     errorDescription = errorDescription + data.errors[i].description + " ";
                 }
                 $scope.message="trackingID=" + data.trackingID + ", " + errorDescription;
             }
         });
    };

    var timer = $interval(function() {
        $scope.alertClass = "";
        var promise = ApiTestService.getE2eCaseResult();
        promise.then(function(e2eCaseResult){
            $scope.e2eCaseResult = e2eCaseResult;
            if((angular.isDefined(e2eCaseResult)) && "" != e2eCaseResult){
                $scope.showMessage = false;
                if(e2eCaseResult.ignoreCount > 0 || e2eCaseResult.failueCount > 0){
                    $scope.alertClass = "alert-danger";
                }else{
                    $scope.alertClass = "alert-success";
                }
            }
        },function(data){
            console.log(data);
        });
    },30000);

}]);

apiTestApp.controller('MetricsCtrl', ['$scope','ApiTestService','$timeout', '$interval', function ($scope, ApiTestService, $timeout, $interval) {
    var timer = $interval(function() {
        var promise = ApiTestService.getAllMetrics();
        promise.then(function(metrics){
            $scope.metrics = metrics;
        },function(data){
            console.log(data);
        });
    },30000);
}]);

apiTestApp.controller('DiagnosticsCtrl', ['$scope','ApiTestService','$timeout', '$interval', function ($scope, ApiTestService, $timeout, $interval) {
    var timer = $interval(function() {
        $scope.alertClass = "";
        var promise = ApiTestService.getAllDiagnostics();
        promise.then(function(diagnostics){
            $scope.diagnostics = diagnostics;
        },function(data){
            console.log(data);
        });
    },30000);
}]);


apiTestApp.controller('diagnosisCtrl', ['$scope','ApiTestService',function($scope, ApiTestService) {
    $scope.url = "https://diagnostics-integration.wbx2.com/diagnostics/api/v1/events";
    $scope.id = "sid.xxx";
    $scope.start = new Date().toISOString();
    $scope.end = new Date().toISOString();
    $scope.limit = 10;
    $scope.output = "output:";

    $scope.createDiagnosis = function() {
        console.log("createDiagnosis...");
        var postData = {
            url:$scope.url,
            id: $scope.id,
            start: $scope.start,
            end: $scope.end,
            limit: $scope.limit
        };
        var promise = ApiTestService.createDiagnosis(postData);
        promise.then(function(data) {
            console.log("success: " + data);
            $scope.output = JSON.stringify(data);
        }, function(data) {
            console.log("failure: " + data);
        });
    }

}]);

apiTestApp.controller('CallFlowScriptCtrl', ['$scope','ApiTestService','$timeout', '$interval', 'ngDialog', function ($scope, ApiTestService, $timeout, $interval, ngDialog) {
    $scope.callFlowType = "callIn";
    $scope.scriptType = "JavaScript";
    $scope.customerName = "Quintiles";
    $scope.accessNumber = "5510571933";
    $scope.enabledCustomization = false;
    $scope.metadata = "Quintiles";
    var jsTemplate = "";
    var xmlTemplate = "";

    ApiTestService.getData("data/callflow/XMLTemplate.xml").then(function(data){
        xmlTemplate = data;
        
    },function(data){
        console.log(data);
    });

    ApiTestService.getData("data/callflow/JavascriptTemplate.js").then(function(data){
        jsTemplate = data;
        $scope.scriptContent = jsTemplate;
    },function(data){
        console.log(data);
    });

    $scope.audioClips = [];
    $scope.scriptContent = xmlTemplate;
    $scope.changeScriptType = function(){
        var scriptType = $scope.scriptType;
        if(scriptType == "JavaScript"){
            $scope.scriptContent = jsTemplate;
        }else if(scriptType == "XML"){
            $scope.scriptContent = xmlTemplate;
        }else{
            $scope.scriptContent = "";
        }
    };
    var getAllCallFlows = function(){
        ApiTestService.getAllCallFlows().then(function(callFlows) {
           $scope.callFlows=callFlows;
        }, function(data) {
            console.log(data);
        });
    }

    $scope.resetCallFlowScript = function() {
        $scope.scriptContent="play({\"clip\":\"play_weltowebex_callin_ivr\"});\njoinConf();";
    };

    $scope.tbd = function() {
        alert("To be done...");
    };

    $scope.saveCallFlowScript = function(){
        var postData = {
             customerName: $scope.customerName,
             accessNumber: $scope.accessNumber,
             callFlowType: $scope.callFlowType,
             enabledCustomization:$scope.enabledCustomization,
             scriptType: $scope.scriptType,
             scriptContent: $scope.scriptContent
        };
        var promise = ApiTestService.createCallFlow(postData);
        promise.then(function(callback) {
            console.log(callback);
            getAllCallFlows();
        }, function(data) {
            console.log(data);
        });
    }
    $scope.deleteCallFlow = function(customerID){
        ApiTestService.deleteCallFlow(customerID).then(function(data) {
            getAllCallFlows();
        }, function(data) {
            console.log(data);
        });
    }
    $scope.showTranslatedScript = function(customerID){
        var callFlows = $scope.callFlows;

        for(var i=0;i<callFlows.length;i++){
            var callFlow = callFlows[i];
            if(callFlow.customerID === customerID){
                callFlow.scriptContent = (vkbeautify.xml(callFlow.scriptContent));
                $scope.selectedCallFlow = callFlow;
                break;
            }
        }
        ngDialog.open({ template: 'views/translatedScript.html',
            className: 'ngdialog-theme-plain custom-width',
            scope:$scope
        });
    }

    $scope.uploadFile = function(){
        var file = $scope.myFile;

        console.log('file is ' );
        console.dir(file);

        var promise = ApiTestService.uploadFileToUrl(file, $scope.customerName);
        promise.then(function(data) {
            console.log(data.filename);

            $('#audioClips')
                .append($("<option></option>")
                    .attr("value",data.filename)
                    .text(data.filename));
        }, function(data) {
            console.log(data);
        });
    };

    getAllCallFlows();
}]);
