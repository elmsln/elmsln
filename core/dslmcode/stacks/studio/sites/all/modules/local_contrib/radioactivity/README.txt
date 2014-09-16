OVERVIEW
========

This module is written to provide better metrics for entity ranking
based on viewing rate (as an example). Radioactivity 2 provides a
field that can be attached to any entity, modified with Rules and
displayed in Views.


ALGORITHM
=========

The node ranking is based on radioactivity model. The algorithm
behind the model is pretty simple:

* Viewing a node adds energy to it and makes it 'hotter'.

* The energy decays at a rate defined by the half-life period, making
  it 'cooler'. For example, a click is worth 1 energy unit at the time
  of clicking, 0.5 energy units after one half-life period, 0.25
  energy units after two half-life periods, and so on.

Therefore, nodes that get lots of clicks stay hotter while inactive
nodes stay cooler. Note that the model is continuous, meaning that the
click energy is not degraded only once per half-life. Actually, it may
be degraded as often as required to get better precision. Degrading
more often means less energy is reduced per iteration.


IN PRACTICE
===========

By keeping half-life period short, let's say one hour, you'll get a
metric that reflects current node view rate. Using that metric in a
view, you can create a "most viewed nodes right now" list. By keeping
longer half-life, let's say 12 hours, you can setup a view that
roughly reflects todays most read nodes. The module supports setting
up multiple different decay rates.

RULES
=====

With the help of Rules module site builders are able to create systems
other than generic popularity meters. You can create simple rules that
raise or lower the energy level of a field on any event which the Rules
module provide. For instance a simple user activity meter can be created
with a few clicks.
