// SCORM Datamodel
//
// some parts adapted from the Moodle Scorm module
//

var cmi = new Object();

cmi.scorm_version = "";

cmi.lms_init_url = "";
cmi.lms_commit_url = "";
cmi.lms_completed_auto_exit = false;
cmi.lms_completed_url = "";
cmi.lms_completed_url_delay = 5000;
cmi.lms_exit_url = "";

cmi.save_log = true;
cmi.log = "";           // WO

cmi.comm_check = false;
cmi.commit_async = false;
cmi.log_suspend = false;

cmi.children = new Object();

cmi.learner_name = "";  // RO
cmi.learner_id = "";    // RO
cmi.location = "";      // RW
cmi.launch_data = "";   // RO
cmi.suspend_data = "";  // RW
cmi.entry = "ab-initio";    // RO   "ab-initio", "resume", ""
cmi.credit = "credit";  // RO   "credit", "no-credit"
cmi.mode = "normal";    // RO   "browse", "normal", "review"
cmi.max_time_allowed = 0;   // RO
cmi.time_limit_action = "continue,no message";  // RO   "exit,message", "continue,message", "exit,no message", "continue no message"
cmi.completion_status = "incomplete";   // RW   "completed", "incomplete", "not attempted", "unknown"
cmi.completion_threshold = 0.0; // RO
cmi.success_status = "unknown"; // RW   "passed", "failed", "unknown"
cmi.progress_measure = 0.0;     // RW
cmi.total_time = 0;     // RO - seconds
cmi.scaled_passing_score = 0.0; // RO
cmi.score_min = 0.0;    // RW
cmi.score_max = 0.0;    // RW
cmi.score_scaled = 0.0; // RW
cmi.score_raw = 0.0;    // RW
cmi.pref_audio = 0.0;   // RW
cmi.pref_lang = "";     // RW
cmi.pref_speed = 0.0;   // RW
cmi.pref_caption = 0;   // RW

cmi.exit = "_none_";    // WO   "time-out", "suspend", "logout", "normal", ""  - "_none_" is used to detect change to ""
cmi.session_time = 0;   // WO - seconds

cmi.interactions = new Array();
var cmi_interaction = new Object(); // RW
cmi_interaction.id = "";
cmi_interaction.type = "";          // "true-false", "choice", "fill-in", "long-fill-in", "matching", "performance", "sequencing", "likert", "numeric", "other"
cmi_interaction.timestamp = 0;      // UTC seconds
cmi_interaction.weighting = 0.0;
cmi_interaction.learner_response = "";
cmi_interaction.result = "";        // "correct", "incorrect", "unanticipated", "neutral"
cmi_interaction.latency = 0;
cmi_interaction.description = "";
cmi_interaction.objectives = new Array();
cmi_interaction.correct_responses = new Array();

cmi.comments = new Array();     // RW
cmi.lms_comments = new Array(); // RO
var cmi_comment = new Object();
cmi_comment.comment = "";
cmi_comment.location = "";
cmi_comment.timestamp = 0;      // UTC seconds

cmi.objectives = new Array();   // RW
var cmi_objective = new Object();
cmi_objective.id = "";
cmi_objective.success_status = "";      // "passed", "failed", "unknown"
cmi_objective.completion_status = "";   // "completed", "incomplete", "not attempted", "unknown"
cmi_objective.progress_measure = 0.0;
cmi_objective.description = "";
cmi_objective.score_min = 0.0;
cmi_objective.score_max = 0.0;
cmi_objective.score_raw = 0.0;
cmi_objective.score_scaled = 0.0;

adl_nav_request = "_none_";

cmi_children_2004 = {
    "cmi_children" : '_version,comments_from_learner,comments_from_lms,completion_status,credit,entry,exit,interactions,launch_data,learner_id,learner_name,learner_preference,location,max_time_allowed,mode,objectives,progress_measure,scaled_passing_score,score,session_time,success_status,suspend_data,time_limit_action,total_time',
    "comments_children" : 'comment,timestamp,location',
    "score_children" : 'max,raw,scaled,min',
    "objectives_children" : 'progress_measure,completion_status,success_status,description,score,id',
    "correct_responses_children" : 'pattern',
    "learner_preference_children" : 'audio_level,audio_captioning,delivery_speed,language',
    "interactions_children" : 'id,type,objectives,timestamp,correct_responses,weighting,learner_response,result,latency,description'
}

cmi_children_1_2 = {
    "cmi_children" : 'core,suspend_data,launch_data,comments,objectives,student_data,student_preference,interactions',
    "core_children" : 'student_id,student_name,lesson_location,credit,lesson_status,entry,score,total_time,lesson_mode,exit,session_time',
    "score_children" : 'raw,min,max',
    "objectives_children" : 'id,score,status',
    "correct_responses_children" : 'pattern',
    "student_data_children" : 'mastery_score,max_time_allowed,time_limit_action',
    "student_preference_children" : 'audio,language,speed,text',
    "interactions_children" : 'id,objectives,time,type,correct_responses,weighting,student_response,result,latency'
}

cmi.diagnostic = "";

// issue a commit before unload
cmi.unloaded = false;
cmi.unloadHandler = function() {
    if (!cmi.unloaded) {
        cmi.commit();
        cmi.unloaded = true;
    }
}

// init cmi data
cmi.init = function(scorm_version) {

    result = true;

    cmi.scorm_version = scorm_version;
    if (cmi.scorm_version == "1.2") {
        cmi.children = cmi_children_1_2;
    }
    if (cmi.scorm_version == "2004") {
        cmi.children = cmi_children_2004;
    }

    // init data model from host
    if (cmi.lms_init_url != '') {

        // setup ajax error handling
        jQuery.ajaxSetup({
            error: function(jqXHR, exception) {
                if (jqXHR.status === 0) {
                    cmi.diagnostic = 'Not connected.\n Verify network connection.';
                } else if (jqXHR.status == 404) {
                    cmi.diagnostic = 'Requested page not found. [404]';
                } else if (jqXHR.status == 500) {
                    cmi.diagnostic = 'Internal Server Error [500].';
                } else if (exception === 'parsererror') {
                    cmi.diagnostic = 'Requested JSON parse failed.';
                } else if (exception === 'timeout') {
                    cmi.diagnostic = 'Time out error.';
                } else if (exception === 'abort') {
                    cmi.diagnostic = 'Ajax request aborted.';
                } else {
                    cmi.diagnostic = 'Uncaught Error.\n' + jqXHR.responseText;
                }
            }
        });

        var data = jQuery.ajax({
            type: "GET",
            url: cmi.lms_init_url,
            async: false,
            complete: function(jqXHR, textStatus) {
                if (textStatus != 'success') {
                    result = false;
                }
            }
        }).responseText;

        if (result) {
            try {
                // check for json string - must be wrapped in braces
                var exp = /^\s*{.*}/;
                if (!exp.test(data)) {
                    cmi.diagnostic = data;
                    result = false;
                }
                else {
                    cmi.initData(data);
                    if (!window.addEventListener) {
                        window.attachEvent("onbeforeunload", cmi.unloadHandler);
                        window.attachEvent("onunload", cmi.unloadHandler);
                    }
                    else {
                        window.addEventListener("beforeunload", cmi.unloadHandler, false);
                        window.addEventListener("unload", cmi.unloadHandler, false);
                    }                
                }
            }
            catch(err) {
                cmi.diagnostic = err.message;
                result = false;
            }
        }
    }

    return result;
}

// retrieve cmi value
cmi.getValue = function(property) {

    var result = "";
    var item = property.split(".");

    if (item[0] == "cmi") {

        switch (item[1]) {
            case "_children":
                result = cmi.children["cmi_children"];
                break;

            case "_version":
                result = cmi._version;
                break;

            case "learner_id":
                result = cmi.learner_id;
                break;

            case "learner_name":
                result = cmi.learner_name;
                break;

            case "location":
                result = cmi.location;
                break;

            case "launch_data":
                result = cmi.launch_data;
                break;

            case "suspend_data":
                result = cmi.suspend_data;
                break;

            case "credit":
                result = cmi.credit;
                break;

            case "entry":
                result = cmi.entry;
                break;

            case "completion_status":
                result = cmi.completion_status;
                break;

            case "completion_threshold":
                result = cmi.completion_threshold;
                break;

            case "time_limit_action":
                result = cmi.time_limit_action;
                break;

            case "success_status":
                result = cmi.success_status;
                break;

            case "progress_measure":
                result = cmi.progress_measure;
                break;

            case "total_time":
                result = cmi._seconds_to_timeinterval(cmi.total_time + cmi.session_time);
                break;

            case "mode":
                result = cmi.mode;
                break;

            case "max_time_allows":
                result = cmi.max_time_allowed;
                break;

            case "scaled_passing_score":
                result = cmi.scaled_passing_score;
                break;

            case "score" :
                switch (item[2]) {
                    case "_children":
                        result = cmi.children["score_children"];
                        break;
                    case "min":
                        result = cmi.score_min;
                        break;
                    case "max":
                        result = cmi.score_max;
                        break;
                    case "scaled":
                        result = cmi.score_scaled;
                        break;
                    case "raw":
                        result = cmi.score_raw;
                        break;
                }
                break;

            case "learner_preference" :
                switch (item[2]) {
                    case "_children":
                        result = cmi.children["learner_preference_children"];
                        break;
                    case "audio_level":
                        result = cmi.audio;
                        break;
                    case "language":
                        result = cmi.lang;
                        break;
                    case "delivery_speed":
                        result = cmi.speed;
                        break;
                    case "audio_captioning":
                        result = cmi.caption;
                        break;
                }
                break;

            case "student_preference" :     // 1.2
                switch (item[2]) {
                    case "_children":
                        result = cmi.children["student_preference_children"];
                        break;
                    case "audio":
                        result = cmi.audio;
                        break;
                    case "language":
                        result = cmi.lang;
                        break;
                    case "speed":
                        result = cmi.speed;
                        break;
                    case "text":
                        result = cmi.caption;
                        break;
                }
                break;

            case "student_data" :     // 1.2
                switch (item[2]) {
                    case "_children":
                        result = cmi.children["student_data_children"];
                        break;
                    case "mastery_score":
                        result = cmi.scaled_passing_score;
                        break;
                    case "max_time_allowed":
                        result = cmi.max_time_allowed;
                        break;
                    case "time_limit_action":
                        result = cmi.time_limit_action;
                        break;
                }
                break;

            case "comments":    // 1.2
                if (cmi.comments[0]) {
                    result = cmi.comments[0].comment;
                }

            case "comments_from_learner":
                switch (item[2]) {
                    case "_children":
                        result = cmi.children["comments_children"];
                        break;
                    case "_count":
                        result = cmi.comments.length;
                        break;
                    default:
                        var n = parseInt(item[2]);
                        if (!isNaN(n) && cmi.comments.length > n) {
                            var c = cmi.comments[n];
                            switch (item[3]) {
                                case "comment":
                                    result = c.comment;
                                    break;
                                case "location":
                                    result = c.location;
                                    break;
                                case "timestamp":
                                    result = cmi._timestamp_to_date(c.timestamp);
                                    break;
                            }
                        }

                }

            case "comments_from_lms":
                if (cmi.scorm_version == "1.2") {
                    if (cmi.lms_comments[0]) {
                        result = cmi.lms_comments[0].comment;
                    }
                }
                else {
                    switch (item[2]) {
                        case "_children":
                            result = cmi.children["comments_children"];
                            break;
                        case "_count":
                            result = cmi.lms_comments.length;
                            break;
                        default:
                            var n = parseInt(item[2]);
                            if (!isNaN(n) && cmi.lms_comments.length > n) {
                                var c = cmi.lms_comments[n];
                                switch (item[3]) {
                                    case "comment":
                                        result = c.comment;
                                        break;
                                    case "location":
                                        result = c.location;
                                        break;
                                    case "timestamp":
                                        result = cmi._timestamp_to_date(c.timestamp);
                                        break;
                                }
                            }

                    }
                }

            case "interactions":
                switch (item[2]) {
                    case "_children":
                        result = cmi.children["interactions_children"];
                        break;
                    case "_count":
                        result = cmi.interactions.length;
                        break;
                    default:
                        var n = parseInt(item[2]);
                        if (!isNaN(n) && cmi.interactions.length > n) {
                            inter = cmi.interactions[n];
                            switch (item[3]) {
                                case "id":
                                    result = inter.id;
                                    break;
                                case "type":
                                    result = inter.type;
                                    break;
                                case "timestamp":
                                    result = cmi._timestamp_to_date(inter.timestamp);
                                    break;
                                case "time":                    // 1.2
                                    result = cmi._timestamp_to_time(inter.timestamp);
                                    break;
                                case "weighting":
                                    result = inter.weighting;
                                    break;
                                case "learner_response":
                                case "student_response":        // 1.2
                                    result = inter.learner_response;
                                    break;
                                case "result":
                                    result = inter.result;
                                    break;
                                case "latency":
                                    if (cmi.scorm_version == "2004") {
                                        result = cmi._seconds_to_timeinterval(inter.latency);
                                    }
                                    if (cmi.scorm_version == "1.2") {
                                        result = cmi._seconds_to_cmitimespan(inter.latency);
                                    }
                                    break;
                                case "description":
                                    result = inter.description;
                                    break;
                                case "correct_responses":
                                    if (item[4] == "_count") {
                                        result = inter.correct_responses.length;
                                    }
                                    else {
                                        var n2 = parseInt(item[4]);
                                        if (inter.correct_responses[n2]) {
                                            result = inter.correct_responses[n2];
                                        }
                                    }
                                    break;
                                case "objectives":
                                    if (item[4] == "_count") {
                                        result = inter.objectives.length;
                                    }
                                    else {
                                        var n2 = parseInt(item[4]);
                                        if (inter.objectives[n2]) {
                                            result = inter.objectives[n2];
                                        }
                                    }
                                    break;
                            }
                        }
                }
                break;

            case "objectives":
                switch (item[2]) {
                    case "_children":
                        result = cmi.children["objectives_children"];
                        break;
                    case "_count":
                        result = cmi.objectives.length;
                        break;
                    default:
                        var n = parseInt(item[2]);
                        if (!isNaN(n) && cmi.objectives.length > n) {
                            obj = cmi.objectives[n];
                            switch (item[3]) {
                                case "id":
                                    result = obj.id;
                                    break;
                                case "success_status":
                                    result = obj.success_status;
                                    break;
                                case "completion_status":
                                case "status":      // 1.2
                                    result = obj.completion_status;
                                    break;
                                case "progress_measure":
                                    result = obj.progress_measure;
                                    break;
                                case "description":
                                    result = obj.description;
                                    break;
                                case "score":
                                    switch (item[4]) {
                                        case "_children":
                                            result = cmi.children["score_children"];
                                            break;
                                        case "min":
                                            result = obj.score_min;
                                            break;
                                        case "max":
                                            result = obj.score_max;
                                            break;
                                        case "scaled":
                                            result = obj.score_scaled;
                                            break;
                                        case "raw":
                                            result = obj.score_raw;
                                            break;
                                }
                                    break;
                            }
                        }
                }
                break;

            case "core":        // 1.2
                switch (item[2]) {
                    case "_children":
                        result = cmi.children["core_children"];
                        break;
                    case "student_id":
                        result = cmi.learner_id;
                        break;
                    case "student_name":
                        result = cmi.learner_name;
                        break;
                    case "lesson_location":
                        result = cmi.location;
                        break;
                    case "credit":
                        result = cmi.credit;
                        break;
                    case "entry":
                        result = cmi.entry;
                        break;
                    case "lesson_status":
                        result = cmi.completion_status;
                        break;
                    case "total_time":
                        result = cmi._seconds_to_cmitimespan(cmi.total_time + cmi.session_time);
                        break;
                    case "lesson_mode":
                        result = cmi.mode;
                        break;
                    case "score" :
                        switch (item[3]) {
                            case "_children":
                                result = cmi.children["score_children"];
                                break;
                            case "min":
                                result = cmi.score_min;
                                break;
                            case "max":
                                result = cmi.score_max;
                                break;
                            case "raw":
                                result = cmi.score_raw;
                                break;
                        }
                        break;
                }
                break;
        }
    }       // end - if (item[0] == 'cmi'

    else if (item[0] == "adl" && item[1] == 'nav') {

        switch (item[2]) {

            case "request":
                result = adl_nav_request;
                break;

            case "request_valid":
                if (adl_nav_request == "_none_") {
                    result = "unknown";
                }
                else {
                    result = "true";
                    switch (item[3]) {
                        case "continue":
                            if (!sco_node_nav_can_move_next()) {
                                result = "false";
                            }
                            break;
                        case "previous":
                            if (!sco_node_nav_can_move_prev()) {
                                result = "false";
                            }
                            break;
                    }
                }
                break;
        }
    }

    return result;
}

// set cmi value
cmi.setValue = function(property, value) {

    result = true;
    force_commit = false;
    completed = false;

    var item = property.split(".");

    if (item[0] == "cmi") {

        switch (item[1]) {

            case "suspend_data":
                cmi.suspend_data = value;
                if (cmi.comm_check) {
                    // try to detect invalid strings from Articulate
                    if (value.length > 0 && value.substr(0, 1) == '|') {
                        alert("ERROR - The presentation does not appear to be communicating with the website properly.\n\nThe presentation cannot continue.");
                        cmi.diagnostic = "cmi.suspend_data value is invalid";
                        result = false;
                        setTimeout(function() { window.location = cmi.lms_exit_url; }, 1000);
                    }
                }
                force_commit = true;
                break;

            case "location":
                cmi.location = value;
                break;

            case "session_time":
                cmi.session_time = cmi._timeinterval_to_seconds(value);
                break;

            case "completion_status":
                if (value == 'completed' || value == 'passed') {
                    completed = true;
                }
                // if attempt is marked complete, don't allow sco to mark as incomplete
                if (cmi.completion_status == 'completed' || cmi.completion_status == 'passed') {
                    if (value == 'incomplete' || value == 'failed') {
                        break;
                    }
                }
                cmi.completion_status = value;
                force_commit = true;
                break;

            case "success_status":
                // if attempt is marked as passed, don't allow sco to mark as failed
                if (cmi.success_status == 'passed' && value == 'failed') {
                    break;
                }
                cmi.success_status = value;
                force_commit = true;
                break;

            case "exit":
                cmi.exit = value;
                force_commit = true;
                break;

            case "progress_measure":
                if (!isNaN(parseFloat(value))) {
                    cmi.progress_measure = parseFloat(value);
                }
                break;

            case "score":
                switch (item[2]) {
                    case "min":
                        if (!isNaN(parseFloat(value))) {
                            cmi.score_min = parseFloat(value);
                        }
                        break;
                    case "max":
                        if (!isNaN(parseFloat(value))) {
                            cmi.score_max = parseFloat(value);
                        }
                        break;
                    case "scaled":
                        if (!isNaN(parseFloat(value))) {
                            cmi.score_scaled = parseFloat(value);
                        }
                        break;
                    case "raw":
                        if (!isNaN(parseFloat(value))) {
                            cmi.score_raw = parseFloat(value);
                        }
                        break;
                    default:
                        result = false;
                }
                break;

            case "learner_preference":
                switch (item[2]) {
                    case "audio_level":
                        if (!isNaN(parseFloat(value))) {
                            cmi.audio = parseFloat(value);
                        }
                        break;
                    case "language":
                        cmi.lang = value;
                        break;
                    case "delivery_speed":
                        if (!isNaN(parseFloat(value))) {
                            cmi.speed = parseFloat(value);
                        }
                        break;
                    case "audio_captioning":
                        if (!isNaN(parseInt(value))) {
                            cmi.caption = parseInt(value);
                        }
                        break;
                    default:
                        result = false;
                }
                break;

            case "student_preference":      // 1.2
                switch (item[2]) {
                    case "audio":
                        if (!isNaN(parseFloat(value))) {
                            cmi.audio = parseFloat(value);
                        }
                        break;
                    case "language":
                        cmi.lang = value;
                        break;
                    case "speed":
                        if (!isNaN(parseFloat(value))) {
                            cmi.speed = parseFloat(value);
                        }
                        break;
                    case "text":
                        if (!isNaN(parseInt(value))) {
                            cmi.caption = parseInt(value);
                        }
                        break;
                    default:
                        result = false;
                }
                break;

            case "comments":        // 1.2
                c = Object.create(comment);
                c.comment = value;
                cmi.comments[0] = c;

            case "comments_from_learner":
                var n = parseInt(item[2]);
                if (!isNaN(n)) {
                    var c = null;
                    if (cmi.comments.length > n) {
                        c = cmi.comments[n];
                    }
                    else {
                        c = Object.create(cmi_comment);
                        cmi.comments[n] = c;
                    }
                    switch (item[3]) {
                        case "comment":
                            c.comment = value;
                            break;
                        case "location":
                            c.location = value;
                            break;
                        case "timestamp":
                            if (Date.parse(value) > 0) {
                                c.timestamp = Date.parse(value) / 1000;
                            }
                            break;
                        default:
                            result = false;
                    }
                    cmi.comments[n] = c;
                }
                else {
                    result = false;
                }
                break;

            case "interactions":
                var n = parseInt(item[2]);
                if (!isNaN(n)) {
                    var inter = null;
                    if (cmi.interactions.length > n) {
                        inter = cmi.interactions[n];
                    }
                    else {
                        inter = Object.create(cmi_interaction);
                        cmi.interactions[n] = inter;
                    }
                    switch (item[3]) {
                        case "id":
                            inter.id = value;
                            break;
                        case "type":
                            inter.type = value;
                            break;
                        case "timestamp":
                            if (Date.parse(value) > 0) {
                                inter.timestamp = Date.parse(value) / 1000;
                            }
                            break;
                        case "weighting":
                            if (!isNaN(parseFloat(value))) {
                                inter.weighting = parseFloat(value);
                            }
                            break;
                        case "learner_response":
                            inter.learner_response = value;
                            break;
                        case "result":
                            inter.result = value;
                            break;
                        case "latency":
                            if (cmi.scorm_version == "2004") {
                                inter.latency = cmi._timeinterval_to_seconds(value);
                            }
                            if (cmi.scorm_version == "1.2") {
                                inter.latency = cmi._cmitimespan_to_seconds(value);
                            }
                            break;
                        case "description":
                            inter.description = value;
                            break;
                        case "correct_responses":
                            var n2 = parseInt(item[4]);
                            if (!isNaN(n2)) {
                                inter.correct_responses[n2] = value;
                            }
                            break;
                        case "objectives":
                            var n2 = parseInt(item[4]);
                            if (!isNaN(n2)) {
                                inter.objectives[n2] = value;
                            }
                            break;
                        default:
                            result = false;
                    }
                    cmi.interactions[n] = inter;
                }
                else {
                    result = false;
                }
                break;

            case "objectives":
                var n = parseInt(item[2]);
                if (!isNaN(n)) {
                    var obj = null;
                    if (cmi.objectives.length > n) {
                        obj = cmi.objectives[n];
                    }
                    else {
                        obj = Object.create(cmi_objective);
                        cmi.objectives[n] = obj;
                    }
                    switch (item[3]) {
                        case "id":
                            obj.id = value;
                            break;
                        case "success_status":
                            obj.success_status = value;
                            break;
                        case "completion_status":
                        case "status":      // 1.2
                            obj.completion_status = value;
                            break;
                        case "progress_measure":
                            if (!isNaN(parseFloat(value))) {
                                obj.progress_measure = parseFloat(value);
                            }
                            break;
                        case "description":
                            obj.description = value;
                            break;
                        case "score":
                            switch (item[4]) {
                                case "min":
                                    if (!isNaN(parseFloat(value))) {
                                        obj.score_min = parseFloat(value);
                                    }
                                    break;
                                case "max":
                                    if (!isNaN(parseFloat(value))) {
                                        obj.score_max = parseFloat(value);
                                    }
                                    break;
                                case "scaled":
                                    if (!isNaN(parseFloat(value))) {
                                        obj.score_scaled = parseFloat(value);
                                    }
                                    break;
                                case "raw":
                                    if (!isNaN(parseFloat(value))) {
                                        obj.score_raw = parseFloat(value);
                                    }
                                    break;
                                default:
                                    result = false;
                            }
                            break;
                        default:
                            result = false;
                    }
                    cmi.objectives[n] = obj;
                }
                else {
                    return false;
                }
                break;

            case "core":                     // 1.2
                switch (item[2]) {
                    case "session_time":
                        cmi.session_time = cmi._cmitimespan_to_seconds(value);
                        break;
                    case "lesson_location":
                        cmi.location = value;
                        break;
                    case "lesson_status":
                        if (value == 'completed' || value == 'passed') {
                            completed = true;
                        }
                        if (value == 'completed' || value == 'incomplete' || value == 'browsed' || value == 'not attempted') {
                            cmi.completion_status = value;
                        }
                        if (value == 'passed' || value == 'failed') {
                            cmi.success_status = value;
                        }
                        force_commit = true;
                        break;
                    case "exit":
                        cmi.exit = value;
                        force_commit = true;
                        break;
                    case "score" :
                        switch (item[3]) {
                            case "min":
                                if (!isNaN(parseFloat(value))) {
                                    cmi.score_min = parseFloat(value);
                                }
                                break;
                            case "max":
                                if (!isNaN(parseFloat(value))) {
                                    cmi.score_max = parseFloat(value);
                                }
                                break;
                            case "raw":
                                if (!isNaN(parseFloat(value))) {
                                    cmi.score_raw = parseFloat(value);
                                }
                                break;
                            default:
                                result = false;
                        }
                        break;
                    default:
                      result = false;
                }
                break;
            default:
                result = false;
        }
    }       // end - if item[0] == 'cmi'...

    else if (item[0] == 'adl' && item[1] == 'nav' && item[2] == 'request') {
        adl_nav_request = value;
    }
    else {
        result = false;
    }

    // force a commit under certain conditions
    if (force_commit) {
        cmi.commit();
    }

    // navigate on completion - if set
    if (completed && cmi.lms_completed_auto_exit) {
        var url = cmi.lms_exit_url;
        if (cmi.lms_completed_url != "") {
           url = cmi.lms_completed_url;
        }
        setTimeout(function() { window.location = url; }, cmi.lms_completed_url_delay);
    }

    return result;
}

// commit cmi data to lms
cmi.commit = function() {

    var result = true;

    // post cmi data to host
    if (cmi.lms_commit_url != '') {
        var json = cmi.formatData();
        var resp = jQuery.ajax({
                       type: 'POST',
                       contentType: 'application/json; charset=utf-8',
                       url: cmi.lms_commit_url,
                       async: cmi.commit_async,
                       data: json,
                       complete: function(jqXHR, textStatus) {
                           if (textStatus != 'success') {
                               result = false;
                           }
                       }
                   }).responseText;
        // LMS must respond with "store complete...", otherwise an error occurred
        if (resp == "") {
            result = false;
        }
        else {
            var exp = /^store complete/;
            if (!exp.test(resp)) {
                cmi.diagnostic = resp;
                result = false;
            }
            // reset WO values
            cmi.exit = '_none_';
            cmi.session_time = 0;
            cmi.log = '';
        }
    }

    return result;
}

// format cmi data as JSON
cmi.formatData = function() {

    var result = "";
    var items = new Array();

    items.push("\"location\":" + _json_quote(cmi.location));
    items.push("\"suspend_data\":" + _json_quote(cmi.suspend_data));
    items.push("\"completion_status\":" + _json_quote(cmi.completion_status));
    items.push("\"success_status\":" + _json_quote(cmi.success_status));
    items.push("\"progress_measure\":" + cmi.progress_measure);
    items.push("\"score_min\":" + cmi.score_min);
    items.push("\"score_max\":" + cmi.score_max);
    items.push("\"score_scaled\":" + cmi.score_scaled);
    items.push("\"score_raw\":" + cmi.score_raw);
    items.push("\"pref_audio\":" + cmi.pref_audio);
    items.push("\"pref_lang\":" + _json_quote(cmi.pref_lang));
    items.push("\"pref_speed\":" + cmi.pref_speed);

    // push WO values if updated
    if (cmi.exit != "_none_") {
        items.push("\"exit\":" + _json_quote(cmi.exit));
    }
    if (cmi.session_time > 0) {
        items.push("\"session_time\":" + cmi.session_time);
    }

    if (cmi.log != "") {
        items.push("\"log\":" + _json_quote(cmi.log));
    }

    if (cmi.interactions.length > 0) {
        var inter_items = new Array();
        for (i=0; i<cmi.interactions.length; i++) {
            var inter = cmi.interactions[i];
            var inter_item = new Array();
            inter_item.push("\"id\":" + _json_quote(inter.id));
            inter_item.push("\"type\":" + _json_quote(inter.type));
            inter_item.push("\"timestamp\":" + inter.timestamp);
            inter_item.push("\"weighting\":" + inter.weighting);
            inter_item.push("\"learner_response\":" + _json_quote(inter.learner_response));
            inter_item.push("\"result\":" + _json_quote(inter.result));
            inter_item.push("\"latency\":" + inter.latency);
            inter_item.push("\"description\":" + _json_quote(inter.description));
            if (inter.objectives.length > 0) {
                objs = new Array();
                for (j=0; j<inter.objectives.length; j++) {
                    objs.push(_json_quote(inter.objectives[j]));
                }
                inter_item.push("\"objectives\":[" + objs.join() + "]");
            }
            if (inter.correct_responses.length > 0) {
                resps = new Array();
                for (j=0; j<inter.correct_responses.length; j++) {
                    resps.push(_json_quote(inter.correct_responses[j]));
                }
                inter_item.push("\"correct_responses\":[" + resps.join() + "]");
            }
            if (inter_item.length > 0) {
                inter_items.push("{" + inter_item.join() + "}");
            }
        }
        if (inter_items.length > 0) {
            items.push("\"interactions\":[" + inter_items.join() + "]");
        }
    }

    if (cmi.comments.length > 0) {
        var comment_items = new array();
        for (i=0; i<cmi.comments.length; i++) {
            var c = cmi.comments[i];
            var comment_item = new Array();
            comment_item.push("\"comment\":" + _json_quote(c.comment));
            comment_item.push("\"location\":" + _json_quote(c.location));
            comment_item.push("\"timestamp\":" + c.timestamp);
            if (comment_item.length > 0) {
                comment_items.push("{" + comment_item.join() + "}");
            }
        }
        if (comment_items.length > 0) {
            items.push("\"comments\":[" + comment_items.join() + "]");
        }
    }

    if (cmi.objectives.length > 0) {
        var obj_items = new Array();
        for (i=0; i<cmi.objectives.length; i++) {
            var obj = cmi.objectives[i];
            var obj_item = new Array();
            obj_item.push("\"id\":" + _json_quote(obj.id));
            obj_item.push("\"success_status\":" + _json_quote(obj.success_status));
            obj_item.push("\"completion_status\":" + _json_quote(obj.completion_status));
            obj_item.push("\"progress_measure\":" + obj.progress_measure);
            obj_item.push("\"description\":" + _json_quote(obj.description));
            obj_item.push("\"score_min\":" + obj.score_min);
            obj_item.push("\"score_max\":" + obj.score_max);
            obj_item.push("\"score_raw\":" + obj.score_raw);
            obj_item.push("\"score_scaled\":" + obj.score_scaled);
            if (obj_item.length > 0) {
                obj_items.push("{" + obj_item.join() + "}");
            }
        }
        if (obj_items.length > 0) {
            items.push("\"objectives\":[" + obj_items.join() + "]");
        }
    }

    if (items.length > 0) {
        result = "{" + items.join() + "}";
    }

    return result;
}

// initialize data model from lms - lmsdata is expected to be in JSON format
cmi.initData = function(lmsdata) {

    var lms = _json_parse(lmsdata);
    if (lms) {
        if (lms.hasOwnProperty("learner_id")) {
            cmi.learner_id = lms.learner_id;
        }
        if (lms.hasOwnProperty("learner_name")) {
            cmi.learner_name = lms.learner_name;
        }
        if (lms.hasOwnProperty("location")) {
            cmi.location = lms.location;
        }
        if (lms.hasOwnProperty("launch_data")) {
            cmi.launch_data = lms.launch_data;
        }
        if (lms.hasOwnProperty("suspend_data")) {
            cmi.suspend_data = lms.suspend_data;
        }
        if (lms.hasOwnProperty("entry")) {
            cmi.entry = lms.entry;
        }
        if (lms.hasOwnProperty("credit")) {
            cmi.credit = lms.credit;
        }
        if (lms.hasOwnProperty("mode")) {
            cmi.mode = lms.mode;
        }
        if (lms.hasOwnProperty("max_time_allowed")) {
            cmi.max_time_allowed = lms.max_time_allowed;
        }
        if (lms.hasOwnProperty("time_limit_action")) {
            cmi.time_limit_action = lms.time_limit_action;
        }
        if (lms.hasOwnProperty("completion_status")) {
            cmi.completion_status = lms.completion_status;
        }
        if (lms.hasOwnProperty("success_status")) {
            cmi.success_status = lms.success_status;
        }
        if (lms.hasOwnProperty("progress_measure")) {
            cmi.progress_measure = lms.progress_measure;
        }
        if (lms.hasOwnProperty("total_time")) {
            cmi.total_time = lms.total_time;
        }
        if (lms.hasOwnProperty("scaled_passing_score")) {
            cmi.scaled_passing_score = lms.scaled_passing_score;
        }
        if (lms.hasOwnProperty("score_min")) {
            cmi.score_min = lms.score_min;
        }
        if (lms.hasOwnProperty("score_max")) {
            cmi.score_max = lms.score_max;
        }
        if (lms.hasOwnProperty("score_scaled")) {
            cmi.score_scaled = lms.score_scaled;
        }
        if (lms.hasOwnProperty("score_raw")) {
            cmi.score_raw = lms.score_raw;
        }
        if (lms.hasOwnProperty("pref_audio")) {
            cmi.pref_audio = lms.pref_audio;
        }
        if (lms.hasOwnProperty("pref_lang")) {
            cmi.pref_lang = lms.pref_lang;
        }
        if (lms.hasOwnProperty("pref_speed")) {
            cmi.pref_speed = lms.pref_speed;
        }
        if (lms.hasOwnProperty("pref_caption")) {
            cmi.pref_caption = lms.pref_caption;
        }
        if (lms.hasOwnProperty("interactions")) {
            if (lms.interactions.length > 0) {
                for (i=0; i<lms.interactions.length; i++) {
                    var lmsinter = lms.interactions[i];
                    var inter = Object.create(cmi_interaction);
                    var index = cmi.interactions.length;
                    cmi.interactions[index] = inter;
                    if (lmsinter.hasOwnProperty("id")) {
                        inter.id = lmsinter.id;
                    }
                    if (lmsinter.hasOwnProperty("type")) {
                        inter.type = lmsinter.type;
                    }
                    if (lmsinter.hasOwnProperty("timestamp")) {
                        inter.timestamp = lmsinter.timestamp;
                    }
                    if (lmsinter.hasOwnProperty("weighting")) {
                        inter.weighting = lmsinter.weighting;
                    }
                    if (lmsinter.hasOwnProperty("learner_response")) {
                        inter.learner_response = lmsinter.learner_response;
                    }
                    if (lmsinter.hasOwnProperty("result")) {
                        inter.result = lmsinter.result;
                    }
                    if (lmsinter.hasOwnProperty("latency")) {
                        inter.latency = lmsinter.latency;
                    }
                    if (lmsinter.hasOwnProperty("description")) {
                        inter.description = lmsinter.description;
                    }
                    if (lmsinter.hasOwnProperty("objectives")) {
                        if (lmsinter.objectives.length > 0) {
                            for (j=0; j<lmsinter.objectives.length; j++) {
                                inter.objectives[j] = lmsinter.objectives[j];
                            }
                        }
                    }
                    if (lmsinter.hasOwnProperty("correct_responses")) {
                        if (lmsinter.correct_responses.length > 0) {
                            for (j=0; j<lmsinter.correct_responses.length; j++) {
                                inter.correct_responses[j] = lmsinter.correct_responses[j];
                            }
                        }
                    }
                    cmi.interactions[index] = inter;
                }
            }
        }

        if (lms.hasOwnProperty("comments")) {
            if (lms.comments.length > 0) {
                for (i=0; i<lms.comments.length; i++) {
                    var lmscomment = lms.comments[i];
                    var comment = Object.create(cmi_comment);
                    var index = cmi.comments.length;
                    cmi.comments[index] = comment;
                    if (lmscomment.hasOwnProperty("comment")) {
                        comment.comment = lmscomment.comment;
                    }
                    if (lmscomment.hasOwnProperty("location")) {
                        comment.location = lmscomment.location;
                    }
                    if (lmscomment.hasOwnProperty("timestamp")) {
                        comment.timestamp = lmscomment.timestamp;
                    }
                    cmi.comments[index] = comment;
                }
            }
        }

        if (lms.hasOwnProperty("lms_comments")) {
            if (lms.lms_comments.length > 0) {
                for (i=0; i<lms.lms_comments.length; i++) {
                    var lmscomment = lms.lms_comments[i];
                    var comment = Object.create(cmi_comment);
                    var index = cmi.lms_comments.length;
                    cmi.lms_comments[index] = comment;
                    if (lmscomment.hasOwnProperty("comment")) {
                        comment.comment = lmscomment.comment;
                    }
                    if (lmscomment.hasOwnProperty("location")) {
                        comment.location = lmscomment.location;
                    }
                    if (lmscomment.hasOwnProperty("timestamp")) {
                        comment.timestamp = lmscomment.timestamp;
                    }
                    cmi.lms_comments[index] = comment;
                }
            }
        }

        if (lms.hasOwnProperty("objectives")) {
            if (lms.objectives.length > 0) {
                for (i=0; i<lms.objectives.length; i++) {
                    var lmsobj = lms.objectives[i];
                    var obj = Object.create(cmi_objective);
                    var index = cmi.objectives.length;
                    cmi.objectives[index] = obj;
                    if (lmsobj.hasOwnProperty("id")) {
                        obj.id = lmsobj.id;
                    }
                    if (lmsobj.hasOwnProperty("success_status")) {
                        obj.success_status = lmsobj.success_status;
                    }
                    if (lmsobj.hasOwnProperty("completion_status")) {
                        obj.completion_status = lmsobj.completion_status;
                    }
                    if (lmsobj.hasOwnProperty("progress_measure")) {
                        obj.progress_measure = lmsobj.progress_measure;
                    }
                    if (lmsobj.hasOwnProperty("description")) {
                        obj.description = lmsobj.description;
                    }
                    if (lmsobj.hasOwnProperty("score_min")) {
                        obj.score_min = lmsobj.score_min;
                    }
                    if (lmsobj.hasOwnProperty("score_max")) {
                        obj.score_max = lmsobj.score_max;
                    }
                    if (lmsobj.hasOwnProperty("score_raw")) {
                        obj.score_raw = lmsobj.score_raw;
                    }
                    if (lmsobj.hasOwnProperty("score_scaled")) {
                        obj.score_scaled = lmsobj.score_scaled;
                    }
                    cmi.objectives[index] = obj;
                }
            }
        }
    }
}

// return the number of seconds from a session time value - P[yY][mM][dD][T[hH][nM][s[.s]S]]
cmi._timeinterval_to_seconds = function(time) {

    var secs = 0;
    var daysecs = 24 * 60 * 60;
    var mondays = ((365 * 4) + 1) / 48;
    var matchexpr = /^P((\d+)Y)?((\d+)M)?((\d+)D)?(T((\d+)H)?((\d+)M)?((\d+(\.\d{1,2})?)S)?)?$/;
    var arr = time.match(matchexpr);
    if (arr != null) {
        if (parseFloat(arr[13]) > 0) {
            secs = Math.round(parseFloat(arr[13]));
        }
        var mins = 0;
        if (parseInt(arr[11]) > 0) {
            mins = parseInt(arr[11]);
        }
        secs += mins * 60;
        var hours = 0;
        if (parseInt(arr[9]) > 0) {
            hours = parseInt(arr[9]);
        }
        secs += hours * 3600;
        var days = 0;
        if (parseInt(arr[6]) > 0) {
            days = parseInt(arr[6]);
        }
        secs += days * daysecs;
        var months = 0;
        if (parseInt(arr[4]) > 0) {
            months = parseInt(arr[4]);
        }
        secs += months * mondays * daysecs;
        var years = 0;
        if (parseInt(arr[2]) > 0) {
            years = parseInt(arr[2]);
        }
        secs += years * 365 * daysecs;
    }

    return secs;
}

cmi._seconds_to_timeinterval = function(secs) {

    var daysecs = 24 * 60 * 60;
    var mondays = ((365 * 4) + 1) / 48;

    var yy = sec / (365 * daysecs);
    sec -= (yy * 365 * daysecs);
    var mo = sec / (mondays * daysecs);
    sec -= (mo * mondays * daysecs);
    var dd = sec / daysecs;
    sec -= dd * daysecs;
    var hh = sec / (60 * 60);
    sec -= hh * 60 * 60;
    var mm = sec / 60;
    sec -= mm * 60;
    ss = Math.round(sec);

    timeinterval = "P";
    if (yy > 0) {
        timeinterval += yy + "Y";
    }
    if (mo > 0) {
        timeinterval += mo + "M";
    }
    if (dd > 0) {
        timeinterval += dd + "D";
    }
    if (hh > 0 || mm > 0 || ss > 0) {
        timeinterval += "T";
    }
    if (hh > 0) {
        timeinterval += hh + "H";
    }
    if (mm > 0) {
        timeinterval += mm + "M";
    }
    if (ss > 0) {
        timeinterval += ss + "S";
    }

    return timeinterval;
}

cmi._cmitimespan_to_seconds = function(time) {

    var arr = time.split(":");
    var secs = 0;
    if (parseFloat(arr[2]) > 0) {
        secs = Math.round(parseFloat(arr[2]));
    }
    var mm = 0;
    if (parseInt(arr[1]) > 0) {
        mm = parseInt(arr[1]);
    }
    secs += mm * 60;
    var hh = 0;
    if (parseInt(arr[0]) > 0) {
        hh = parseInt(arr[0]);
    }
    secs += hh * 60 * 60;

    return secs;
}

cmi._seconds_to_cmitimespan = function(secs) {

    var hh = sec / (60 * 60);
    sec -= hh * 60 * 60;
    var mm = sec / 60;
    sec -= mm * 60;
    ss = Math.round(sec);

    secs = ss.toString();
    if (ss < 10) {
        secs = "0" + secs;
    }
    mins = mm.toString();
    if (mm < 10) {
        mins = "0" + mins;
    }
    hours = hh.toString();
    if (hh < 10) {
        hours = "0" + hours;
    }

    return hours + ":" + mins + ":" + secs;
}

cmi._timestamp_to_date = function(ts) {

    var date = new Date(inter.timestamp * 1000);
    var ds = date.getFullYear() + "-";
    var mon = date.getMonth() + 1;
    if (mon < 10) {
        mon = "0" + mon;
    }
    ds += mon + "-";
    var day = date.getDate();
    if (day < 10) {
        day = "0" + day;
    }
    ds += day + "T";
    var hh = date.getHours();
    if (hh < 10) {
        hh = "0" + hh;
    }
    ds += hh + ":";
    var mm = date.getMinutes();
    if (mm < 10) {
        mm = "0" + mm;
    }
    ds += mm + ":"
    var ss = date.getSeconds();
    if (ss < 10) {
        ss = "0" + ss;
    }
    ds += ss;

    return ds;
}

cmi._timestamp_to_time = function(ts) {

    var date = new Date(inter.timestamp * 1000);
    var hh = date.getHours();
    if (hh < 10) {
        hh = "0" + hh;
    }
    ds = hh + ":";
    var mm = date.getMinutes();
    if (mm < 10) {
        mm = "0" + mm;
    }
    ds += mm + ":"
    var ss = date.getSeconds();
    if (ss < 10) {
        ss = "0" + ss;
    }
    ds += ss;

    return ds;
}

//
// JSON functions adapted from https://github.com/douglascrockford (public domain)
//
var _json_parse = (function () {
    "use strict";

// This is a function that can parse a JSON text, producing a JavaScript
// data structure. It is a simple, recursive descent parser. It does not use
// eval or regular expressions, so it can be used as a model for implementing
// a JSON parser in other languages.

// We are defining the function inside of another function to avoid creating
// global variables.

    var at, // The index of the current character
        ch, // The current character
        escapee = {
            '"': '"',
            '\\': '\\',
            '/': '/',
            b: '\b',
            f: '\f',
            n: '\n',
            r: '\r',
            t: '\t'
        },
        text,

        error = function (m) {

// Call error when something is wrong.

            throw {
                name: 'SyntaxError',
                message: m,
                at: at,
                text: text
            };
        },

        next = function (c) {

// If a c parameter is provided, verify that it matches the current character.

            if (c && c !== ch) {
                error("Expected '" + c + "' instead of '" + ch + "'");
            }

// Get the next character. When there are no more characters,
// return the empty string.

            ch = text.charAt(at);
            at += 1;
            return ch;
        },

        number = function () {

// Parse a number value.

            var number,
                string = '';

            if (ch === '-') {
                string = '-';
                next('-');
            }
            while (ch >= '0' && ch <= '9') {
                string += ch;
                next();
            }
            if (ch === '.') {
                string += '.';
                while (next() && ch >= '0' && ch <= '9') {
                    string += ch;
                }
            }
            if (ch === 'e' || ch === 'E') {
                string += ch;
                next();
                if (ch === '-' || ch === '+') {
                    string += ch;
                    next();
                }
                while (ch >= '0' && ch <= '9') {
                    string += ch;
                    next();
                }
            }
            number = +string;
            if (!isFinite(number)) {
                error("Bad number");
            } else {
                return number;
            }
        },

        string = function () {

// Parse a string value.

            var hex,
                i,
                string = '',
                uffff;

// When parsing for string values, we must look for " and \ characters.

            if (ch === '"') {
                while (next()) {
                    if (ch === '"') {
                        next();
                        return string;
                    }
                    if (ch === '\\') {
                        next();
                        if (ch === 'u') {
                            uffff = 0;
                            for (i = 0; i < 4; i += 1) {
                                hex = parseInt(next(), 16);
                                if (!isFinite(hex)) {
                                    break;
                                }
                                uffff = uffff * 16 + hex;
                            }
                            string += String.fromCharCode(uffff);
                        } else if (typeof escapee[ch] === 'string') {
                            string += escapee[ch];
                        } else {
                            break;
                        }
                    } else {
                        string += ch;
                    }
                }
            }
            error("Bad string");
        },

        white = function () {

// Skip whitespace.

            while (ch && ch <= ' ') {
                next();
            }
        },

        word = function () {

// true, false, or null.

            switch (ch) {
            case 't':
                next('t');
                next('r');
                next('u');
                next('e');
                return true;
            case 'f':
                next('f');
                next('a');
                next('l');
                next('s');
                next('e');
                return false;
            case 'n':
                next('n');
                next('u');
                next('l');
                next('l');
                return null;
            }
            error("Unexpected '" + ch + "'");
        },

        value, // Place holder for the value function.

        array = function () {

// Parse an array value.

            var array = [];

            if (ch === '[') {
                next('[');
                white();
                if (ch === ']') {
                    next(']');
                    return array; // empty array
                }
                while (ch) {
                    array.push(value());
                    white();
                    if (ch === ']') {
                        next(']');
                        return array;
                    }
                    next(',');
                    white();
                }
            }
            error("Bad array");
        },

        object = function () {

// Parse an object value.

            var key,
                object = {};

            if (ch === '{') {
                next('{');
                white();
                if (ch === '}') {
                    next('}');
                    return object; // empty object
                }
                while (ch) {
                    key = string();
                    white();
                    next(':');
                    if (Object.hasOwnProperty.call(object, key)) {
                        error('Duplicate key "' + key + '"');
                    }
                    object[key] = value();
                    white();
                    if (ch === '}') {
                        next('}');
                        return object;
                    }
                    next(',');
                    white();
                }
            }
            error("Bad object");
        };

    value = function () {

// Parse a JSON value. It could be an object, an array, a string, a number,
// or a word.

        white();
        switch (ch) {
        case '{':
            return object();
        case '[':
            return array();
        case '"':
            return string();
        case '-':
            return number();
        default:
            return ch >= '0' && ch <= '9' ? number() : word();
        }
    };

// Return the json_parse function. It will have access to all of the above
// functions and variables.

    return function (source) {
        var result;

        text = source;
        at = 0;
        ch = ' ';
        result = value();
        white();
        if (ch) {
            error("Syntax error");
        }
        return result;
    };
}());

var _json_escapable = /[\\\"\x00-\x1f\x7f-\x9f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g;
var _json_sub = { // table of character substitutions
            '\b': '\\b',
            '\t': '\\t',
            '\n': '\\n',
            '\f': '\\f',
            '\r': '\\r',
            '"' : '\\"',
            '\\': '\\\\'
        };

function _json_quote(string) {

    if (typeof (JSON.stringify) === "function") {
        return JSON.stringify(string);
    }
    else {
        _json_escapable.lastIndex = 0;
        return _json_escapable.test(string) ? '"' + string.replace(_json_escapable, function (a) {
            var c = _json_sub[a];
            return typeof c === 'string'
                ? c
                : '\\u' + ('0000' + a.charCodeAt(0).toString(16)).slice(-4);
        }) + '"' : '"' + string + '"';
    }
}

