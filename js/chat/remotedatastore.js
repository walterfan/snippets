var RemoteDataStore = (function() {

})();

RemoteDataStore.prototype.create=function(entity, respCb) {
    return $.post(this.serverUrl, entity, respCb(resp));
}

RemoteDataStore.prototype.read=function(id, respCb) {
    return $.get(this.serverUrl + "/" + id, respCb(resp));
}



RemoteDataStore.prototype.update=function(id, entity, successCb, errorCb) {
    return $.ajax(
        { 
            type: "UPDATE", 
            url: this.serverUrl + "/" + id, 
            data: entity, 
            dataType: "json",
            success: successCb, 
            error: errorCb
        }
    );
}
//success(result,status,xhr), error(xhr,status,error)
RemoteDataStore.prototype.delete=function(id, successCb, errorCb) {
    return $.ajax(
        { 
            type: "DELETE", 
            url: this.serverUrl + "/" + id, 
            success: successCb, 
            error: errorCb
        }
    );
}

RemoteDataStore.prototype.list=function(respCb) {
    return $.get(this.serverUrl, respCb(resp));
}