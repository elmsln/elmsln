Clazz.declarePackage ("J.io");
Clazz.load (null, "J.io.JmolBinary", ["java.io.BufferedInputStream", "java.util.Hashtable", "JU.PT", "$.Rdr", "$.SB", "J.api.Interface", "JU.Logger", "JV.FileManager"], function () {
c$ = Clazz.decorateAsClass (function () {
this.fm = null;
this.jzu = null;
Clazz.instantialize (this, arguments);
}, J.io, "JmolBinary");
Clazz.makeConstructor (c$, 
function () {
});
Clazz.defineMethod (c$, "set", 
function (fm) {
this.fm = fm;
return this;
}, "JV.FileManager");
c$.getEmbeddedScript = Clazz.defineMethod (c$, "getEmbeddedScript", 
function (script) {
if (script == null) return script;
var pt = script.indexOf ("**** Jmol Embedded Script ****");
if (pt < 0) return script;
var pt1 = script.lastIndexOf ("/*", pt);
var pt2 = script.indexOf ((script.charAt (pt1 + 2) == '*' ? "*" : "") + "*/", pt);
if (pt1 >= 0 && pt2 >= pt) script = script.substring (pt + "**** Jmol Embedded Script ****".length, pt2) + "\n";
while ((pt1 = script.indexOf (" #Jmol...\u0000")) >= 0) script = script.substring (0, pt1) + script.substring (pt1 + " #Jmol...\u0000".length + 4);

if (JU.Logger.debugging) JU.Logger.debug (script);
return script;
}, "~S");
Clazz.defineMethod (c$, "getJzu", 
 function () {
return (this.jzu == null ? this.jzu = J.api.Interface.getOption ("io.JmolUtil", this.fm.vwr, "file") : this.jzu);
});
Clazz.defineMethod (c$, "getAtomSetCollectionOrBufferedReaderFromZip", 
function (adapter, is, fileName, zipDirectory, htParams, asBufferedReader) {
return this.getJzu ().getAtomSetCollectionOrBufferedReaderFromZip (this.fm.vwr, adapter, is, fileName, zipDirectory, htParams, 1, asBufferedReader);
}, "J.api.JmolAdapter,java.io.InputStream,~S,~A,java.util.Map,~B");
Clazz.defineMethod (c$, "getImage", 
function (fullPathNameOrBytes, echoName, forceSync) {
return this.getJzu ().getImage (this.fm.vwr, fullPathNameOrBytes, echoName, forceSync);
}, "~O,~S,~B");
c$.getFileReferences = Clazz.defineMethod (c$, "getFileReferences", 
function (script, fileList) {
for (var ipt = 0; ipt < JV.FileManager.scriptFilePrefixes.length; ipt++) {
var tag = JV.FileManager.scriptFilePrefixes[ipt];
var i = -1;
while ((i = script.indexOf (tag, i + 1)) >= 0) {
var s = JU.PT.getQuotedStringAt (script, i);
if (s.indexOf ("::") >= 0) s = JU.PT.split (s, "::")[1];
fileList.addLast (s);
}
}
}, "~S,JU.Lst");
c$.getManifestScriptPath = Clazz.defineMethod (c$, "getManifestScriptPath", 
function (manifest) {
if (manifest.indexOf ("$SCRIPT_PATH$") >= 0) return "";
var ch = (manifest.indexOf ('\n') >= 0 ? "\n" : "\r");
if (manifest.indexOf (".spt") >= 0) {
var s = JU.PT.split (manifest, ch);
for (var i = s.length; --i >= 0; ) if (s[i].indexOf (".spt") >= 0) return "|" + JU.PT.trim (s[i], "\r\n \t");

}return null;
}, "~S");
Clazz.defineMethod (c$, "spartanFileGetRdr", 
function (name, info) {
var name00 = name;
var header = info[1];
var fileData =  new java.util.Hashtable ();
if (info.length == 3) {
var name0 = this.spartanGetObjectAsSections (info[2], header, fileData);
fileData.put ("OUTPUT", name0);
info = this.spartanFileList (name, fileData.get (name0));
if (info.length == 3) {
name0 = this.spartanGetObjectAsSections (info[2], header, fileData);
fileData.put ("OUTPUT", name0);
info = this.spartanFileList (info[1], fileData.get (name0));
}}var sb =  new JU.SB ();
if (fileData.get ("OUTPUT") != null) sb.append (fileData.get (fileData.get ("OUTPUT")));
var s;
for (var i = 2; i < info.length; i++) {
name = info[i];
name = this.spartanGetObjectAsSections (name, header, fileData);
JU.Logger.info ("reading " + name);
s = fileData.get (name);
sb.append (s);
}
s = sb.toString ();
this.fm.spardirPut (name00.$replace ('\\', '/'), s.getBytes ());
return JU.Rdr.getBR (s);
}, "~S,~A");
Clazz.defineMethod (c$, "spartanFileList", 
 function (name, zipDirectory) {
return this.getJzu ().spartanFileList (this.fm.vwr.getJzt (), name, zipDirectory);
}, "~S,~S");
Clazz.defineMethod (c$, "spartanGetObjectAsSections", 
 function (name, header, fileData) {
if (name == null) return null;
var subFileList = null;
var asBinaryString = false;
var name0 = name.$replace ('\\', '/');
if (name.indexOf (":asBinaryString") >= 0) {
asBinaryString = true;
name = name.substring (0, name.indexOf (":asBinaryString"));
}var sb = null;
if (fileData.containsKey (name0)) return name0;
if (name.indexOf ("#JMOL_MODEL ") >= 0) {
fileData.put (name0, name0 + "\n");
return name0;
}var fullName = name;
if (name.indexOf ("|") >= 0) {
subFileList = JU.PT.split (name, "|");
name = subFileList[0];
}var bis = null;
try {
var t = this.fm.getBufferedInputStreamOrErrorMessageFromName (name, fullName, false, false, null, false, true);
if (Clazz.instanceOf (t, String)) {
fileData.put (name0, t + "\n");
return name0;
}bis = t;
if (JU.Rdr.isCompoundDocumentS (bis)) {
var doc = J.api.Interface.getInterface ("JU.CompoundDocument", this.fm.vwr, "file");
doc.setStream (this.fm.vwr.getJzt (), bis, true);
doc.getAllDataMapped (name.$replace ('\\', '/'), "Molecule", fileData);
} else if (JU.Rdr.isZipS (bis)) {
this.fm.vwr.getJzt ().getAllZipData (bis, subFileList, name.$replace ('\\', '/'), "Molecule", fileData);
} else if (asBinaryString) {
var bd = J.api.Interface.getInterface ("JU.BinaryDocument", this.fm.vwr, "file");
bd.setStream (this.fm.vwr.getJzt (), bis, false);
sb =  new JU.SB ();
if (header != null) sb.append ("BEGIN Directory Entry " + name0 + "\n");
try {
while (true) sb.append (Integer.toHexString (bd.readByte () & 0xFF)).appendC (' ');

} catch (e1) {
if (Clazz.exceptionOf (e1, Exception)) {
sb.appendC ('\n');
} else {
throw e1;
}
}
if (header != null) sb.append ("\nEND Directory Entry " + name0 + "\n");
fileData.put (name0, sb.toString ());
} else {
var br = JU.Rdr.getBufferedReader (JU.Rdr.isGzipS (bis) ?  new java.io.BufferedInputStream (this.fm.vwr.getJzt ().newGZIPInputStream (bis)) : bis, null);
var line;
sb =  new JU.SB ();
if (header != null) sb.append ("BEGIN Directory Entry " + name0 + "\n");
while ((line = br.readLine ()) != null) {
sb.append (line);
sb.appendC ('\n');
}
br.close ();
if (header != null) sb.append ("\nEND Directory Entry " + name0 + "\n");
fileData.put (name0, sb.toString ());
}} catch (ioe) {
if (Clazz.exceptionOf (ioe, Exception)) {
fileData.put (name0, ioe.toString ());
} else {
throw ioe;
}
}
if (bis != null) try {
bis.close ();
} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
} else {
throw e;
}
}
if (!fileData.containsKey (name0)) fileData.put (name0, "FILE NOT FOUND: " + name0 + "\n");
return name0;
}, "~S,~S,java.util.Map");
Clazz.defineMethod (c$, "getCachedPngjBytes", 
function (pathName) {
return this.getJzu ().getCachedPngjBytes (this, pathName);
}, "~S");
Clazz.defineStatics (c$,
"PMESH_BINARY_MAGIC_NUMBER", "PM\1\0");
});
