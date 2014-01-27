Footnotes module can be used to easily create automatically numbered footnote 
references into an article or post (such as a reference to a URL). <strong>It
now supports also TinyMCE and CKEditor via WYSIWYG module</strong>.

<h3>ABOUT FOOTNOTES</h3>

The Footnotes module can be used to create automatically numbered footnotes
within a text. In the place where you want to add a footnote enclose the
footnote text within an fn tag: <code>[fn]like this[/fn]</code>. By default,
footnotes are placed at the end of the text. You can also use a
<code>[footnotes]</code> or <code>[footnotes /]</code> tag to position it
anywhere you want. 

The filter will take the text within the tag and move it to a footnote at the
bottom of the page. In it's place it will place a number which is also a link to
the footnote. Footnotes supports both <code>[fn]square brackets[/fn]</code> 
and <code><fn>angle brackets</fn></code>. 

You can also use a "value" attribute to a) set the numbering to start from the
given value, or b) to set an arbitrary text string as label. 
Ex: <code> [fn value="5"]This becomes footnote #5. Subsequent are #6, #7...[/fn]
 [fn value="*"]This footnote is assigned the label "*"[/fn]</code>

Using value="" you can have multiple references to the same footnote in the text 
body.
<code> [fn value="5"]This becomes footnote #5.[/fn]
 [fn value="5"]This is a reference to the same footnote #5, this text itself is
discarded.[/fn]</code>

Since 2.4 Footnotes supports both TinyMCE and CKEditor via plugins to the WYSIWYG
module. They each work slightly differently, please see the README for those
plugins to learn more.

Version 2.4 introduces an optional feature that identical footnotes are
collapsed into one, as if they had the same value="" attribute. This must be
enabled from admin/settings/filters by choosing the relevant "Input format" and
then the "Configure" tab. By default, footnotes are separate unless you specify
them to have the same value="" attribute.

<h3>TEXTILE FILTER</h3>

The Textile variant of Footnotes is now removed in 7.x-2.5. You can use the 
standard [fn]...[/fn] filter also together with Textile notation.

<h3>BETTER URL FILTER</h3>

The Footnotes module also used to ship a "Better URL filter". This code has
now been committed to Drupal core and you can use it from there as the
regular URL filter. Better URL filter has been removed from the 7.x-2.x
version of footnotes.

<h3>INSTALL INSTRUCTIONS FOR FOOTNOTES.MODULE</h3>

1. Copy the contents of this module to sites/all/modules/footnotes folder.
2. Login as site administrator.
3. Activate footnotes on the administer->modules page.
4. To use the footnotes filter in some input formats, go to Configuration ->
   Text formats.
5. For the Text formats you want to support footnotes markup, select configure 
   and activate a suitable footnotes filter. 

<h3>TIPS n TRICKS (CSS)</h3>

Many Footnotes users don't want the footnotes to show in teasers (such as the
front page listing). The correct way to prevent that is by using CSS. See
[#209037] for examples.

Beginning with version 2.4, Footnotes will highlight the footnote text if you
click on the footnote reference link. (This was inspired by wikipedia, see
[#728658]). The highlight color is light gray. If this clashes with your site's
colors, or you want to set a nicer color (or unset the feature
altogether) you need to override the default color in your own theme. The below
CSS can be used for that:

<code>
.see_footnote:target,
.footnotes .footnote:target {
  background-color: #ffeeee; /* Set footnote highlight color to light pink. */
}
.see_footnote:target {
  border: solid 1px #ffaaaa; /* Set border color of highlighted footnote ref to
light red. */
}
</code>

As part of this feature, CSS class names have moved tags. While unlikely, if you
have used these in your own themes, please change your CSS accordingly:
<ul>
<li>The "footnote" class used to be the A or SPAN element that is the footnote
number/label in the list of footnotes. This class is now the LI element
containing the entire footnote.</li>
<li>The A or SPAN element now has the class "footnote_label"</li>
</ul>

Due to changes in HTML and CSS, <strong>you need to clear the Drupal
cache</strong> after upgrading to version 2.4 or later.


<h3>HTML FILTER</h3>

Footnotes.module is designed such that it can be used together with Drupal's
html filter, and in particular you should have footnotes first and html filter
later.

This version of Footnotes has been redesigned so that it only outputs html tags
that are allowed in a default installation of HTML filter. (Tags used are A, UL
and LI.)


<h3>KNOWN ISSUES</h3>

Version 2.0 uses a new markup for the list of footnotes. It is an UL list with
CSS taking away the browser generated list bullets and moving the link numbers
towards the left instead. All IE versions have a bug that the numbers are
slightly lower than the baseline of the footnote text. (If you know how to fix
this, please tell.) In addition IE 5.5 has a more serious bug that the footnote
number will be on top of the first letters of the footnote text. There doesn't
seem to be a way to fix this.

The Views API functionality only works in the common use case when footnotes
are at the end of the text, but does not work correctly when using [footnotes]
tag explicitly. See [#1003690] to follow up on this bug.

The Views module is not yet ported to Drupal 7 and consequently also Footnotes
Views cannot be ported.


<h3>COPYRIGHT AND ACKNOWLEDGEMENTS</h3>

Footnotes.module is copyrighted by Henrik Ingo and other contributors. It is
licensed by the same conditions as Drupal itself. (GPL license)

Footnotes.module was originally created by henrik.ingo@avoinelama.fi ("hingo" on
drupal.org) in the summer of 2006.

The HTML footnotes were seriously enhanced by "beginner" (on drupal.org) and
later on by other users comments and code snippets.

Footnotes was originally developed for http://openlife.cc/onlinebook
Beginner was the second to use it on his site at 
http://www.reuniting.info/wisdom/sources/metaphysical/
a_course_in_miracles_sacred_sexuality_holy_relationship

I wish to thank all contributors for letting me experience the miracle of
maintaining an Open Source module living its own life!
