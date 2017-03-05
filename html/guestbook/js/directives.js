'use strict';

var apiTestAppDirectives = angular.module('apiTestApp.directives', []);

apiTestAppDirectives.directive('callbackstates',function() {
    return {
        restrict: 'E',
        replace: true,
        templateUrl: 'views/callbackStates.html'
    };
});

apiTestAppDirectives.directive('e2ecasestep',function() {
    return {
        restrict: 'E',
        replace: true,
        templateUrl: 'views/e2eCaseStep.html',
        link:function(scope, element, attrs){
            if(scope.caseResult.success==false){
                var index = scope.$index + 1;
                if(index === scope.caseResult.currentStep){
                    scope.stepClass = "alert-danger";
                }else{
                    if(index < scope.caseResult.currentStep){
                       scope.stepClass = "alert-success";
                    }
                }
            }else{
                scope.stepClass = "alert-success";
            }
        }
    };
});

//added by walter for file upload
apiTestAppDirectives.directive('fileModel', ['$parse', function ($parse) {
    return {
        restrict: 'A',
        link: function(scope, element, attrs) {
            var model = $parse(attrs.fileModel);
            var modelSetter = model.assign;

            element.bind('change', function(){
                scope.$apply(function(){
                    modelSetter(scope, element[0].files[0]);
                });
            });
        }
    };
}]);


apiTestAppDirectives.directive('customizationcallflow',['ApiTestService', function(ApiTestService) {
    return {
        restrict: 'E',
        replace: true,
        templateUrl: 'views/customizationCallFlow.html',
        link:function(scope, element, attrs){
            var buttons = element.find("button");
            var textArea = element.find("textarea");
            var selectClips = element.find("select");
            var promise = ApiTestService.getCallFlowActions();
            var callFlowActions;
            promise.then(function(data) {
                callFlowActions = data;
                //init clips
                scope.audioClips = callFlowActions["Clips"];
                //var clips = callFlowActions["Clips"];
                scope.audioClips.sort();
                for(var i = 0; i<scope.audioClips.length; i++){
                    var o = new Option(scope.audioClips[i],scope.audioClips[i]);
                    selectClips[0].options.add(o);
                }
            }, function(data) {
                console.log(data);
            });
            var insertText =function (obj,str) {
                if (document.selection) {
                    var sel = document.selection.createRange();
                    sel.text = str;
                } else if (typeof obj.selectionStart === 'number' && typeof obj.selectionEnd === 'number') {
                    var startPos = obj.selectionStart,
                        endPos = obj.selectionEnd,
                        cursorPos = startPos,
                        tmpStr = obj.value;
                    obj.value = tmpStr.substring(0, startPos) + str + tmpStr.substring(endPos, tmpStr.length);
                    cursorPos += str.length;
                    obj.selectionStart = obj.selectionEnd = cursorPos;
                } else {
                    obj.value += str;
                }
                obj.focus();
                scope.scriptContent = obj.value;
            }

            var formatScript=function(scriptType){
                 var scriptContent = textArea[0].value;
                 if(scriptType==="XML"){
                     scriptContent = vkbeautify.xml(scriptContent);
                 }else if(scriptType==="JavaScript"){
                     scriptContent = js_beautify(scriptContent,{"indent_size":1, "indent_char":"\t"});
                 }
                 textArea[0].value = scriptContent;
                 scope.scriptContent = scriptContent;
            }

            var uploadFile=function() {
                console.log("upload file...");
                var dialog = $("#uploadDialog" ).dialog({
                    autoOpen: false,
                    height: 360,
                    width: 420,
                    modal: true,
                    buttons: {
                        Close: function() {
                            dialog.dialog( "close" );
                        }
                    },
                    close: function() {
                        form[ 0 ].reset();
                        //allFields.removeClass( "ui-state-error" );
                    }
                });
                var form = dialog.find( "form" ).on( "submit", function( event ) {
                    event.preventDefault();
                    console.log("upload file submit...");
                    $("#uploadDialog").submit();


                });
                $('#uploadDialog').show();
                dialog.dialog( "open" );

            }

            var setTextAreaContent=function(ele){
                var scriptType = scope.scriptType;
                var cmd = ele.attributes["cmd"].value;
                if(cmd === "Format"){
                    formatScript(scriptType);
                } else if(cmd === "Upload"){
                    uploadFile();
                } else{
                    var scriptObj=callFlowActions[cmd];
                    var content = "";
                    if(scriptType==="XML"){
                        content = scriptObj["xml"];
                    }else if(scriptType==="JavaScript"){
                        content = scriptObj["js"];
                    }
                    insertText(textArea[0], content+"\n");
                }
            }

            buttons.bind("click", function (event) {
                setTextAreaContent(event.currentTarget);
            });

            selectClips.bind("dblclick", function(event){
                var length = this.options.length;
                var selectedValue = "";
                for(var i =0;i<length;i++){
                    var option = this.options[i];
                    if(option.selected){
                        selectedValue=option.value;
                        break;
                    }
                }
                insertText(textArea[0], selectedValue);
            });
        }
    };
}]);
