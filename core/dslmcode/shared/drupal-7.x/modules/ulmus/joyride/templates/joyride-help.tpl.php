<div class="joyride-help-page">
  <style type="text/css">
    .joyride-help-page ol li { list-style : decimal inside; margin-left: 10px;}
  </style>
  <h1 style="font-size: 16px;">Zurb Joyride Context help index</h1>
  <br />

  <div class="row">
    <div class="twelve columns">
      <h2 style="font-size: 14px;">Contents of this document</h2>
      <br />
      <ol>
        <li>Install Joyride jQuery plugin.</li>
        <li>Create context to manage your tour.</li>
        <li>Create Joyride Tips content.</li>
      </ol>
      <hr>
    </div>
  </div>

  <br />

  <div class="row">
    <div class="twelve columns">
      <h2 style="font-size: 14px;">1. Install Joyride jQuery plugin.</h2>
      <br />
      <ol>
        <li>Download Joyride plugin from <a href="https://github.com/zurb/joyride" target="_blank">GitHub</a> repository. </li>
        <li>Extract contents of the archive to <code>sites/all/lbraries/joyride</code> folder.</li>
        <li>Rename
          <code>jquery.joyride-X.Y.Z.js</code> to
          <code>jquery.joyride.js</code> and
          <code>joyride-X.Y.Z.css</code> to
          <code>joyride.css</code>.
        </li>
      </ol>
      <hr>
    </div>
  </div>

  <br />

  <div class="row">
    <div class="twelve columns">
      <h2 style="font-size: 14px;">2. Create context to manage your tour.</h2>
      <br />
      <ol>
        <li>Navigate to context <a href="/admin/structure/context" target="_blank">overview</a> page.</li>
        <li>Optionally review module's bundled contexts to get an idea of how they works. Bundler contexts are tagged with "joyride" tag.</li>
        <li>Create new context as you usually do. In "Conditions" section add "Path" condition and enter URLs of pages where you want to have your Joyride tour enabled.</li>
        <li>In "Reactions" section paste tips content that will be shown as Joyride tour tips. <a href="#create-tips-content">More info on this.</a></li>
      </ol>
      <hr>
    </div>
  </div>

  <br />

  <div class="row">
    <div class="twelve columns">
      <h2 id="create-tips-content" style="font-size: 14px;">3. Create Joyride Tips content.</h2>
      <br />
      <ol>
        <li>Joyride module expects that tips content will be formatted to use <code>&lt;li&gt;</code> as item wrappers</li>
        <li>You can use following code as a reference:
          <pre>
  &lt;li data-id="step-welcome" data-button="Next" data-options="tipAnimation:fade"&gt;
    &lt;h5>Tip heading&lt;/h5&gt;
    &lt;p>Pellentesque ornare sem lacinia quam venenatis vestibulum.&lt;/p&gt;
  &lt;/li&gt;
          </pre>
        </li>
        <li>Please check <a href="http://www.zurb.com/playground/jquery-joyride-feature-tour-plugin" target="_blank">documentation</a> to see complete list of options and features.</li>
      </ol>
      <hr>
    </div>
  </div>

  <br />

</div>
