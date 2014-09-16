// SCORM debugging functions
//
// parts adapted from the Moodle Scorm module

function UpdateSCOLog(s) {

    var log = jQuery("#sco-node-log", window.top.document);
    if (log) {
        log.append(s);
    }
}

//add an individual log entry
function AppendToSCOLog(s) {

    var now = new Date();
    now.setTime(now.getTime());
    var logrec = FormatSCOLogTimeStamp(now) + ' - ' + s;
    if (cmi.hasOwnProperty("log") && cmi.hasOwnProperty("save_log") && cmi.save_log) {
        cmi.log += logrec + "\n";
    }
    UpdateSCOLog('<div>' + logrec + '<\/div>');
}

function FormatSCOLogTimeStamp(ts) {

//    return ts.toUTCString();
    var mon = (ts.getMonth() + 1);
    if (mon < 10) {
        mon = '0' + mon;
    }
    var day = ts.getDate();
    if (day < 10) {
        day = '0' + day;
    }
    var hh = ts.getHours();
    if (hh < 10) {
        hh = '0' + hh;
    }
    var mm = ts.getMinutes();
    if (mm < 10) {
        mm = '0' + mm;
    }
    var ss = ts.getSeconds();
    if (ss < 10) {
        ss = '0' + ss;
    }
    
    return mon + '/' + day + '/' + ts.getFullYear() + ' ' + hh + ':' + mm + ':' + ss;
}

// format a log entry
function LogSCOAPICall(func, nam, val, rc) {

    // don't record error calls
    if (func.match(/GetLastError/)) {
        return;
    }
    var s = func + '("' + nam + '"';
    if (val != null && ! (func.match(/GetValue|GetLastError/))) {
        s += ', "' + val + '"';
    }
    s += ')';
    if (func.match(/GetValue/)) {
        s += ' - ' + val;
    }
    s += ' => ' + String(rc);
    if (rc > 0 && cmi.diagnostic != '') {
        s += ' (' + cmi.diagnostic + ')';
    }
    AppendToSCOLog(s);
}
