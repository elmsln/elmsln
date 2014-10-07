//
// SCORM 2004 API Implementation
//
// some portions adapted from the Moodle Scorm module
//
function SCORM_API_2004() {

    var Initialized = false;
    var Terminated = false;
    var errorCode = "0";

    function Initialize(param) {

        AppendToSCOLog("User Agent: " + navigator.userAgent);
        if(FlashDetect.installed){
            AppendToSCOLog("Flash is installed - Version info: "+ FlashDetect.raw);      
        }
        else {
            AppendToSCOLog("Flash was not detected");
        }
        
        var result = "false";
        errorCode = "0";

        if (param == "") {
            if (!Initialized) {
                Initialized = cmi.init("2004");
                if (!Initialized) {
                    errorCode = "102";      // init error
                }
                else {
                    Terminated = false;
                    result = "true";
                }
            }
            else {
                errorCode = "103";  // already initialized
            }
        }
        else {
            errorCode = "201";      // argument error
        }
        LogSCOAPICall("Initialize", param, "", errorCode);
        return result;
    }

    function Terminate(param) {

        var result = "false";
        errorCode = "0";

        if (param == "") {
            if (Initialized) {
                Initialized = false;
                Terminated = true;

                // store data
                cmi.commit();

                result = "true";

                if (adl_nav_request != "_none_") {
                    switch (adl_nav_request) {
                        case 'continue':
                            setTimeout('sco_node_nav_move_next();',500);
                            break;
                        case 'previous':
                            setTimeout('sco_node_nav_move_prev()',500);
                            break;
                        case 'choice':
                            break;
                        case 'jump':
                            break;
                        case 'exit':
                            break;
                        case 'exitAll':
                            break;
                        case 'abandon':
                            break;
                        case 'abandonAll':
                            break;
                    }
                }
            }
            else {
                if (Terminated) {
                    errorcode = "113";      // term after term
                }
                else {
                    errorCode = "112";      // term before init
                }
            }
        }
        else {
            errorCode = "201";      // argument error
        }
        LogSCOAPICall("Terminate", param, "", errorCode);
        return result;
    }

    function GetValue(element) {

        var result = "";
        var errorCode = "0";

        if (Initialized) {
            if (element != "") {
                // get element value
                result = cmi.getValue(element);
            }
            else {
                errorCode = "201";      // argument error
            }
        }
        else {
            if (Terminated) {
                errorCode = "123";      // get value after term
            }
            else {
                errorCode = "122";      // get value before init
            }
        }
        
        logresult = result;
        if (!cmi.log_suspend && element == "suspend_data") {
            logresult = "(Value Omitted)";
        }
        LogSCOAPICall("GetValue", element, logresult, errorCode);
        return result;
    }

    function SetValue(element, value) {

        var result = "false";
        errorCode = "0";

        if (Initialized) {
            if (element != "") {

                // store element value
                if (!cmi.setValue(element, value)) {
                    errorCode = "351";  // set error
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
            if (Terminated) {
                errorCode = "133";      // store data after term
            }
            else {
                errorCode = "132";      // store data before init
            }
        }

        logvalue = value;
        if (!cmi.log_suspend && element == "cmi.suspend_data") {
            logvalue = "(Value Omitted)";
        }        
        LogSCOAPICall("SetValue", element, logvalue, errorCode);
        return result;
    }

    function Commit(param) {

        var result = "false";
        errorCode = "0";

        if (param == "") {

            if (Initialized) {

                // store data
                if (cmi.commit()) {
                    result = "true";
                }
                else {
                    errorCode = "391";  // commit error
                }
            }
            else {
                if (Terminated) {
                    errorCode = "143";  // commit after term
                }
                else {
                    errorCode = "142";  // commit before init
                }
            }
        }
        else {
            errorCode = "201";      // argment error
        }

        LogSCOAPICall("Commit", param, "", errorCode);
        return result;
    }

    function GetLastError() {

        LogSCOAPICall("GetLastError", "", "", errorCode);
        return errorCode;
    }

    function GetErrorString(param) {

        if (param != "") {
            var errorString = new Array();
            errorString["0"] = "No error";
            errorString["101"] = "General exception";
            errorString["102"] = "General initialization failure";
            errorString["103"] = "Already initialized";
            errorString["104"] = "Content instance terminated";
            errorString["111"] = "General termination failure";
            errorString["112"] = "Termination before initialization";
            errorString["113"] = "Termination after termination";
            errorString["122"] = "Retrieve data before initialization";
            errorString["123"] = "Retrieve data after termination";
            errorString["132"] = "Store data before initialization";
            errorString["133"] = "Store data after termination";
            errorString["142"] = "Commit before initialization";
            errorString["143"] = "Commit data after termination";
            errorString["201"] = "General argument error";
            errorString["301"] = "General get failure";
            errorString["351"] = "General set failure";
            errorString["391"] = "General commit failure";
            errorString["401"] = "Undefined data model element";
            errorString["402"] = "Unimplemented data model element";
            errorString["403"] = "Data model element not initialized";
            errorString["404"] = "Data model element is read only";
            errorString["405"] = "Data model element is write only";
            errorString["406"] = "Data model element type mismatch";
            errorString["407"] = "Data model element value out of range";
            errorString["408"] = "Data model dependency not established";
            LogSCOAPICall("GetErrorString", param,  errorString[param], 0);
            return errorString[param];
        }
        else {
            LogSCOAPICall("GetErrorString", param,  "No error string found!", 0);
            return "";
        }
    }

    function GetDiagnostic(param) {

        result = "";
        if (cmi.diagnostic != "") {
            result = cmi.diagnostic;
            cmi.diagnostic = "";
        }
        else if (errorCode != "") {
            result = errorCode;
        }

        LogSCOAPICall("GetDiagnostic", param, result, 0);

        return result;
    }

    this.Initialize = Initialize;
    this.Terminate = Terminate;
    this.GetValue = GetValue;
    this.SetValue = SetValue;
    this.Commit = Commit;
    this.GetLastError = GetLastError;
    this.GetErrorString = GetErrorString;
    this.GetDiagnostic = GetDiagnostic;
}

var API_1484_11 = new SCORM_API_2004();