'use strict';

/* Services */

var apiTestAppServices = angular.module('apiTestApp.services', []);

apiTestAppServices.factory('ApiTestService', ['$http','$q',function($http, $q){
    var callbackRestURI = "../poros/api/v1/callbacks";
    var callbackTaskRestURI = "../poros/api/v1/callbacks/tasks";
    var meetingRestURI = "../poros/api/v1/meetings";
    var taskRestURI = "../poros/api/v1/tasks";
    var e2eCaseConfigURI = "../poros/api/v1/e2ecaseconfig";
    var e2eCaseResultURI = "../poros/api/v1/e2ecaseresult";
    var e2eCaseRunURI = "../poros/api/v1/e2ecaserun";
    var metricsURI = "../poros/api/v1/metrics";
    var diagnosticsURI = "../poros/api/v1/diagnostics/events";
    var customizeCallFlowURI = "../poros/api/v1/callflows";
    var callFlowActionsURI = "data/callflow/CallFlowActions.json";

    var mediaFileURI = "../poros/api/v1/mediafiles";

    var diagnosisURI = "../poros/api/v1/diagnosis";

    return {
        "createDiagnosis": function(callback){
            var delay = $q.defer();
            $http.post(diagnosisURI, callback, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },


        "createCallback": function(callback){
            var delay = $q.defer();
            $http.post(callbackRestURI, callback, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "createCallFlow": function(callback){
            var delay = $q.defer();
            $http.post(customizeCallFlowURI, callback, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "getAllCallFlows": function(){
            var delay = $q.defer();
            $http.get(customizeCallFlowURI, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "deleteCallFlow": function(customerID){
            var delay = $q.defer();
            $http.delete(customizeCallFlowURI + "/" + customerID, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },

        "getAllCallbacks": function(){
            var delay = $q.defer();
            $http.get(callbackRestURI,{}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "deleteCallbackTask": function(taskID){
                    var delay = $q.defer();
                    var deleteCallbackURI = callbackTaskRestURI + "/" + taskID;
                    $http.delete(deleteCallbackURI, {}).success(function(data, status, headers, config){
                        delay.resolve(data);
                    }).error(function(data, status, headers, config){
                        delay.reject(data);
                    });
                    return delay.promise;
                },
        "deleteAllCallback": function(){
            var delay = $q.defer();
            $http.delete(callbackRestURI, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "createMeeting": function(meeting){
            var delay = $q.defer();
            $http.post(meetingRestURI, meeting, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "deleteMeeting": function(meetingID){
            var delay = $q.defer();
            var deleteMeetingURI = meetingRestURI + "/" + meetingID;
            $http.delete(deleteMeetingURI, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },

        "getAllMeetings": function(){
            var delay = $q.defer();
            $http.get(meetingRestURI,{}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },

        "setE2eCaseConfig":function(e2eCaseConfig){
            var delay = $q.defer();
                $http.put(e2eCaseConfigURI, e2eCaseConfig, {}).success(function(data, status, headers, config){
                    delay.resolve(data);
                }).error(function(data, status, headers, config){
                    delay.reject(data);
                });
                return delay.promise;
        },
        "getE2eCaseConfig":function(){
            var delay = $q.defer();
            $http.get(e2eCaseConfigURI, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },

        "getE2eCaseResult":function(){
            var delay = $q.defer();
            $http.get(e2eCaseResultURI, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "e2eCaseRun":function(){
            var delay = $q.defer();
            $http.put(e2eCaseRunURI, {}, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "getAllMetrics":function(){
            var delay = $q.defer();
            $http.get(metricsURI,{}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "getAllDiagnostics":function(){
            var delay = $q.defer();
            $http.get(diagnosticsURI, {}, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "getCallFlowActions":function(){
            var delay = $q.defer();
            $http.get(callFlowActionsURI, {}, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },
        "getData":function(dataPath){
            var delay = $q.defer();
            $http.get(dataPath, {}, {}).success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        },

        "uploadFileToUrl" : function(file, customerName){
            var delay = $q.defer();
            var fd = new FormData();
            fd.append('file', file);
            fd.append('customerName', customerName);

            $http.post(mediaFileURI, fd, {
                transformRequest: angular.identity,
                headers: {'Content-Type': undefined}})
            .success(function(data, status, headers, config){
                delay.resolve(data);
            }).error(function(data, status, headers, config){
                delay.reject(data);
            });
            return delay.promise;
        }
    }
}]);