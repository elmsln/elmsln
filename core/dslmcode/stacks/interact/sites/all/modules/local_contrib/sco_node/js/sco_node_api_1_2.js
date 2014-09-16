//
// SCORM 1.2 API Implementation
//
// some portions adapted from the Moodle Scorm module
//
function SCORM_API_1_2() {

    var Initialized = false;
    var errorCode = "0";

    function LMSInitialize(param) {

        AppendToSCOLog("User Agent: " + navigator.userAgent);
        if(FlashDetect.installed){
            AppendToSCOLog("Flash is installed - Version info: "+ FlashDetect.raw);      
        }
        else {
            AppendToSCOLog("Flash was not detected");
        }

        result = "false";
        errorCode = "0";

        if (param == "") {
            if (!Initialized) {
                Initialized = cmi.init("1.2");
                if (Initialized) {
                    result = "true";
                }
                else {
                    errorCode = "101";  // init error
                }
            }
            else {
                errorCode = "101";  // already initialized
            }
        }
        else {
            errorCode = "201";  // argument error
        }
        LogSCOAPICall("LMSInitialize", param, "", errorCode);
        return result;
    }

    function LMSFinish(param) {

        result = "false";
        errorCode = "0";

        if (param == "") {
            if (Initialized) {
                Initialized = false;

                // store data
                cmi.commit();

                result = "true";
            }
            else {
                errorCode = "301";  // not initialized
            }
        }
        else {
            errorCode = "201";  // argument error
        }

        LogSCOAPICall("LMSFinish", param, "", errorCode);
        return result;
    }

    function LMSGetValue(element) {

        result = "";
        errorCode = "0";

        if (Initialized) {
            if (element != "") {

                // get element value
                result = cmi.getValue(element);

            }
            else {
                errorCode = "201";  // argument error
            }
        }
        else {
            errorCode = "301";  // not initialized
        }

        LogSCOAPICall("LMSGetValue", element, result, errorCode);
        return result;
    }

    function LMSSetValue(element, value) {

        result = "false";
        errorCode = "0";

        if (Initialized) {
            if (element != "") {
                // store element value
                if (!cmi.setValue(element, value)) {
                    errorCode = "101";     // general error
                }
                else {
                    result = "true";
                }
            }
            else {
                errorCode = "201";      // argument error
            }
        }
        else {
            errorCode = "301";      // not initialized
        }

        LogSCOAPICall("LMSSetValue", element, value, errorCode);
        return result;
    }

    function LMSCommit (param) {

        result = "false";
        errorCode = "0";

        if (param == "") {
            if (Initialized) {

                // store data here
                if (cmi.commit()) {
                    result = "true";
                }
                else {
                    errorCode = "101";      // commit error
                }
            }
            else {
                errorCode = "301";      // not initialized
            }
        } else {
            errorCode = "201";      // argument error
        }

        LogSCOAPICall("LMSCommit", param, "", 0);
        return result;
    }

    function LMSGetLastError() {

        LogSCOAPICall("LMSGetLastError", "", "", errorCode);
        return errorCode;
    }

    function LMSGetErrorString(param) {

        if (param != "") {
            var errorString = new Array();
            errorString["0"] = "No error";
            errorString["101"] = "General exception";
            errorString["201"] = "Invalid argument error";
            errorString["202"] = "Element cannot have children";
            errorString["203"] = "Element not an array - cannot have count";
            errorString["301"] = "Not initialized";
            errorString["401"] = "Not implemented error";
            errorString["402"] = "Invalid set value, element is a keyword";
            errorString["403"] = "Element is read only";
            errorString["404"] = "Element is write only";
            errorString["405"] = "Incorrect data type";
            LogSCOAPICall("LMSGetErrorString", param,  errorString[param], 0);
            return errorString[param];
        }
        else {
            LogSCOAPICall("LMSGetErrorString", param,  "No error string found!", 0);
            return "";
        }
    }

    function LMSGetDiagnostic(param) {

        result = "";
        if (cmi.diagnostic != "") {
            result = cmi.diagnostic;
            cmi.diagnostic = "";
        }
        else if (errorCode != "") {
            result = errorCode;
        }

        LogSCOAPICall("LMSGetDiagnostic", param, result, 0);

        return result;
    }

    this.LMSInitialize = LMSInitialize;
    this.LMSFinish = LMSFinish;
    this.LMSGetValue = LMSGetValue;
    this.LMSSetValue = LMSSetValue;
    this.LMSCommit = LMSCommit;
    this.LMSGetLastError = LMSGetLastError;
    this.LMSGetErrorString = LMSGetErrorString;
    this.LMSGetDiagnostic = LMSGetDiagnostic;
}

var API = new SCORM_API_1_2();