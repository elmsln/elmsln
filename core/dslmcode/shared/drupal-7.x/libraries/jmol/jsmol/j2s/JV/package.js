var path = ClazzLoader.getClasspathFor ("JV.package");
path = path.substring (0, path.lastIndexOf ("package.js"));
ClazzLoader.jarClasspath (path + "StateManager.js", [
"JV.Connections",
"$.Connection",
"$.StateManager",
"$.Scene"]);
ClazzLoader.jarClasspath (path + "ActionManager.js", [
"JV.ActionManager",
"$.Gesture",
"$.MotionPoint"]);
