(function () {
  var f = document,
    a = window,
    b = f.createElement("div"),
    c = "window-size-indicator",
    e = function () {
      if (a.innerWidth === undefined) {
        b.innerText = f.documentElement.clientWidth + "x" + f.documentElement.clientHeight;
      } else if (f.all) {
        b.innerText = a.innerWidth + "x" + a.innerHeight;
      } else {
        b.textContent = window.innerWidth + "x" + window.innerHeight;
      }
    };
  f.body.appendChild(b);
  b.setAttribute("class", c);
  e();
  if (a.addEventListener) {
    a.addEventListener("resize", e, false);
  } else {
    if (a.attachEvent) {
      a.attachEvent("onresize", e);
    } else {
      a.onresize = e;
    }
  }
})();
