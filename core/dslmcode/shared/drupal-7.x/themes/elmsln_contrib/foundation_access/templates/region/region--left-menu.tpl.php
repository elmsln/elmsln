<?php
/**
 * @file
 * Default theme implementation to display a region.
 *
 * Available variables:
 * - $content: The content for this region, typically blocks.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the following:
 *   - region: The current template type, i.e., "theming hook".
 *   - region-[name]: The name of the region with underscores replaced with
 *     dashes. For example, the page_top region would have a region-page-top class.
 * - $region: The name of the region variable as defined in the theme's .info file.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 *
 * @see template_preprocess()
 * @see template_preprocess_region()
 * @see template_process()
 */
?>
<aside class="left-off-canvas-menu">
  <!-- Menu Item Dropdowns -->
        <div id="off-canvas-admin-menu" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
          <ul class="button-group">
          	<li><a href="#">Edit course outline</a></li>
          	<li><a href="#">Print course outline</a></li>
          	<li><a href="#">Save As new outline</a></li>
          	<hr>
          	<li><a href="#" data-reveal-id="block-menu-menu-course-tools-menu-nav-modal">Course Settings</a></li>
          </ul>
        </div>
        <div id="off-canvas-add-menu" data-dropdown-content class="f-dropdown content" aria-hidden="true" tabindex="-1">
          <ul class="button-group">
          	<li><a href="#">Add a new lesson</a></li>
          	<hr>
          	<li><a href="#">Add a new unit</a></li>
          </ul>
        </div>



   <nav class="top-bar" data-topbar role="navigation">
    <section class="right top-bar-section">
      <a class="off-canvas-toolbar-item toolbar-menu-icon" href="#" data-dropdown="off-canvas-admin-menu" aria-controls="offcanvas-admin-menu" aria-expanded="false">
		<div class="icon-chevron-down-black off-canvas-toolbar-item-icon"></div>
      </a>
  </section>
  <section class="right top-bar-section">
      <a href="#" class="off-canvas-toolbar-item toolbar-menu-icon" data-dropdown="off-canvas-add-menu" aria-controls="add-button" aria-expanded="false">
		<div class="icon-plus-black off-canvas-toolbar-item-icon"></div>
	  </a>
  </section>
  </nav>
  <a role="button" class="left-off-canvas-toggle close"><div class="icon-close-black outline-nav-icon" data-grunticon-embed></div></a>
  	<div class="content-outline-navigation in-place-scroll">

		<ul class="off-canvas-list content-outline-navigation">
			<li><a href="/sing100/node/514"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Brainstorming Video</a></li>
			<li><a href="/sing100/node/515"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Rubric</a></li>
			<li><a href="/sing100/node/516"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Creating Your Artwork</a></li>
			<li><a href="/sing100/node/517"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Written Narrative</a></li>
			<li><a href="/sing100/node/518"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Submit Assignment</a></li>
			<li><a href="/sing100/node/519"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Feedback</a></li>
		</ul>

		<ul class="accordion" data-accordion="">
			<li class="accordion-navigation">
				<a href="#unit1-panel"><h2>Unit 1</h2><h3>Things to Learn</h3></a>
			<!-- STYLE TESTING HTML-->
				<div id="unit1-panel" class="content">
			  	<ul class="accordion sub-tier-1" data-accordion="">

					<!-- -------------------------------------------------------- -->
					<li class="accordion-navigation">
						<a href="#unit-96-panel"><h2>Lesson 96</h2><h3>Fantasy and You</h3></a>
						<div id="unit-96-panel" class="content">
							<ul class="off-canvas-list content-outline-navigation expanded">
								<!-- <h2>Lesson 98</h2>
								<h3>Fantasy and You</h3> -->
								<li><a href="/sing100/node/494"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Textbook Reading</a></li>
								<li class="has-submenu expanded"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed=""></div><span class="outline-nav-text">Fantastic Art Overview</span></a>
									<ul class="left-submenu level-1-sub">
										<h2>Lesson 96</h2>
										<h3>Fantastic Art Overview</h3>
										<li class="back"><a href="#">Back</a></li>
										<li><a href="/sing100/node/496"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Origins of Fantastic Art</a></li>
										<li><a href="/sing100/node/497"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Independent Fantastic Artists</a></li>
										<li><a href="/sing100/node/498"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>The Dada Movement</a></li>
										<li><a href="/sing100/node/499"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Surrealism</a></li>
										<li><a href="/sing100/node/500"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Automatism and Veristic Surrealism</a></li>
										<li><a href="/sing100/node/501"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>About the Artists</a></li>
										<li><a href="/sing100/node/502"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Henri Rousseau</a></li>
										<li><a href="/sing100/node/503"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Marc Chagall</a></li>
										<li><a href="/sing100/node/504"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Giorgio de Chirico</a></li>
										<li><a href="/sing100/node/505"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Marcel Duchamp</a></li>
										<li><a href="/sing100/node/506"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Man Ray</a></li>
										<li><a href="/sing100/node/507"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Jean (Hans) Arp</a></li>
										<li><a href="/sing100/node/508"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Joan Miro</a></li>
										<li><a href="/sing100/node/509"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Max Ernst</a></li>
										<li><a href="/sing100/node/510"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Salvador Dali</a></li>
										<li><a href="/sing100/node/511"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Fantastic Art Today</a></li>
									</ul>
								</li>
								<li><a href="/sing100/node/512"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Quiz Directions</a></li>
								<li class="has-submenu last expanded"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed=""></div><span class="outline-nav-text">Fantasy and You Assignment</span></a>
									<ul class="left-submenu level-1-sub">
										<h2>Lesson 96</h2>
										<h3>Fantasy and You Assignment</h3>
										<li class="back">
										<a href="#">Back</a></li>
										<li><a href="/sing100/node/514"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Brainstorming Video</a></li>
										<li><a href="/sing100/node/515"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Rubric</a></li>
										<li><a href="/sing100/node/516"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Creating Your Artwork</a></li>
										<li><a href="/sing100/node/517"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Written Narrative</a></li>
										<li><a href="/sing100/node/518"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Submit Assignment</a></li>
										<li><a href="/sing100/node/519"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Feedback</a></li>
									</ul>
								</li>
							</ul>
						</div>
					</li>

					<li class="accordion-navigation">
						<a href="#unit-97-panel"><h2>Lesson 97</h2><h3>Fantasy and You</h3></a>
						<div id="unit-97-panel" class="content">
							<ul class="off-canvas-list content-outline-navigation expanded">
								<!-- <h2>Lesson 98</h2>
								<h3>Fantasy and You</h3> -->
								<li><a href="/sing100/node/494"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Textbook Reading</a></li>
								<li class="has-submenu expanded"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed=""></div><span class="outline-nav-text">Fantastic Art Overview</span></a>
									<ul class="left-submenu level-1-sub">
										<h2>Lesson 97</h2>
										<h3>Fantastic Art Overview</h3>
										<li class="back"><a href="#">Back</a></li>
										<li><a href="/sing100/node/496"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Origins of Fantastic Art</a></li>
										<li><a href="/sing100/node/497"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Independent Fantastic Artists</a></li>
										<li><a href="/sing100/node/498"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>The Dada Movement</a></li>
										<li><a href="/sing100/node/499"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Surrealism</a></li>
										<li><a href="/sing100/node/500"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Automatism and Veristic Surrealism</a></li>
										<li><a href="/sing100/node/501"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>About the Artists</a></li>
										<li><a href="/sing100/node/502"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Henri Rousseau</a></li>
										<li><a href="/sing100/node/503"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Marc Chagall</a></li>
										<li><a href="/sing100/node/504"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Giorgio de Chirico</a></li>
										<li><a href="/sing100/node/505"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Marcel Duchamp</a></li>
										<li><a href="/sing100/node/506"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Man Ray</a></li>
										<li><a href="/sing100/node/507"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Jean (Hans) Arp</a></li>
										<li><a href="/sing100/node/508"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Joan Miro</a></li>
										<li><a href="/sing100/node/509"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Max Ernst</a></li>
										<li><a href="/sing100/node/510"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Salvador Dali</a></li>
										<li><a href="/sing100/node/511"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Fantastic Art Today</a></li>
									</ul>
								</li>
								<li><a href="/sing100/node/512"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Quiz Directions</a></li>
								<li class="has-submenu last expanded"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed=""></div><span class="outline-nav-text">Fantasy and You Assignment</span></a>
									<ul class="left-submenu level-1-sub">
										<h2>Lesson 97</h2>
										<h3>Fantasy and You Assignment</h3>
										<li class="back">
										<a href="#">Back</a></li>
										<li><a href="/sing100/node/514"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Brainstorming Video</a></li>
										<li><a href="/sing100/node/515"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Rubric</a></li>
										<li><a href="/sing100/node/516"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Creating Your Artwork</a></li>
										<li><a href="/sing100/node/517"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Written Narrative</a></li>
										<li><a href="/sing100/node/518"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Submit Assignment</a></li>
										<li><a href="/sing100/node/519"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Feedback</a></li>
									</ul>
								</li>
							</ul>
						</div>
					</li>
					<!-- -------------------------------------------------------- -->
				</ul>
				</div>
			</li>
		</ul> <!-- End Unit 1 Panel -->

		<ul class="accordion" data-accordion="">
			<li class="accordion-navigation">
				<a href="#unit-1-panel"><h2>Lesson 98</h2><h3>Fantasy and You</h3></a>
				<div id="unit-1-panel" class="content">
					<ul class="off-canvas-list content-outline-navigation expanded">
						<!-- <h2>Lesson 98</h2>
						<h3>Fantasy and You</h3> -->
						<li><a href="/sing100/node/494"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Textbook Reading</a></li>
						<li class="has-submenu expanded"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed=""></div><span class="outline-nav-text">Fantastic Art Overview</span></a>
							<ul class="left-submenu level-1-sub">
								<h2>Lesson 98</h2>
								<h3>Fantastic Art Overview</h3>
								<li class="back"><a href="#">Back</a></li>
								<li><a href="/sing100/node/496"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Origins of Fantastic Art</a></li>
								<li><a href="/sing100/node/497"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Independent Fantastic Artists</a></li>
								<li><a href="/sing100/node/498"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>The Dada Movement</a></li>
								<li><a href="/sing100/node/499"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Surrealism</a></li>
								<li><a href="/sing100/node/500"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Automatism and Veristic Surrealism</a></li>
								<li><a href="/sing100/node/501"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>About the Artists</a></li>
								<li><a href="/sing100/node/502"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Henri Rousseau</a></li>
								<li><a href="/sing100/node/503"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Marc Chagall</a></li>
								<li><a href="/sing100/node/504"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Giorgio de Chirico</a></li>
								<li><a href="/sing100/node/505"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Marcel Duchamp</a></li>
								<li><a href="/sing100/node/506"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Man Ray</a></li>
								<li><a href="/sing100/node/507"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Jean (Hans) Arp</a></li>
								<li><a href="/sing100/node/508"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Joan Miro</a></li>
								<li><a href="/sing100/node/509"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Max Ernst</a></li>
								<li><a href="/sing100/node/510"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Salvador Dali</a></li>
								<li><a href="/sing100/node/511"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Fantastic Art Today</a></li>
							</ul>
						</li>
						<li><a href="/sing100/node/512"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Quiz Directions</a></li>
						<li class="has-submenu last expanded"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed=""></div><span class="outline-nav-text">Fantasy and You Assignment</span></a>
							<ul class="left-submenu level-1-sub">
								<h2>Lesson 98</h2>
								<h3>Fantasy and You Assignment</h3>
								<li class="back">
								<a href="#">Back</a></li>
								<li><a href="/sing100/node/514"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Brainstorming Video</a></li>
								<li><a href="/sing100/node/515"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Rubric</a></li>
								<li><a href="/sing100/node/516"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Creating Your Artwork</a></li>
								<li><a href="/sing100/node/517"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Written Narrative</a></li>
								<li><a href="/sing100/node/518"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Submit Assignment</a></li>
								<li><a href="/sing100/node/519"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Feedback</a></li>
							</ul>
						</li>
					</ul>
				</div>
			</li>

			<li class="accordion-navigation">
				<a href="#unit-2-panel"><h2>Lesson 99</h2><h3>Fantasy and You</h3></a>
				<div id="unit-2-panel" class="content">
					<ul class="off-canvas-list content-outline-navigation expanded">
						<!-- <h2>Lesson 98</h2>
						<h3>Fantasy and You</h3> -->
						<li><a href="/sing100/node/494"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Textbook Reading</a></li>
						<li class="has-submenu expanded"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed=""></div><span class="outline-nav-text">Fantastic Art Overview</span></a>
							<ul class="left-submenu level-1-sub">
								<h2>Lesson 98</h2>
								<h3>Fantastic Art Overview</h3>
								<li class="back"><a href="#">Back</a></li>
								<li><a href="/sing100/node/496"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Origins of Fantastic Art</a></li>
								<li><a href="/sing100/node/497"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Independent Fantastic Artists</a></li>
								<li><a href="/sing100/node/498"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>The Dada Movement</a></li>
								<li><a href="/sing100/node/499"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Surrealism</a></li>
								<li><a href="/sing100/node/500"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Automatism and Veristic Surrealism</a></li>
								<li><a href="/sing100/node/501"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>About the Artists</a></li>
								<li><a href="/sing100/node/502"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Henri Rousseau</a></li>
								<li><a href="/sing100/node/503"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Marc Chagall</a></li>
								<li><a href="/sing100/node/504"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Giorgio de Chirico</a></li>
								<li><a href="/sing100/node/505"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Marcel Duchamp</a></li>
								<li><a href="/sing100/node/506"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Man Ray</a></li>
								<li><a href="/sing100/node/507"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Jean (Hans) Arp</a></li>
								<li><a href="/sing100/node/508"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Joan Miro</a></li>
								<li><a href="/sing100/node/509"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Max Ernst</a></li>
								<li><a href="/sing100/node/510"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Salvador Dali</a></li>
								<li><a href="/sing100/node/511"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Fantastic Art Today</a></li>
							</ul>
						</li>
						<li><a href="/sing100/node/512"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Quiz Directions</a></li>
						<li class="has-submenu last expanded"><a href="#"><div class="icon-content-black outline-nav-icon" data-grunticon-embed=""></div><span class="outline-nav-text">Fantasy and You Assignment</span></a>
							<ul class="left-submenu level-1-sub">
								<h2>Lesson 99</h2>
								<h3>Fantasy and You Assignment</h3>
								<li class="back">
								<a href="#">Back</a></li>
								<li><a href="/sing100/node/514"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Brainstorming Video</a></li>
								<li><a href="/sing100/node/515"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Rubric</a></li>
								<li><a href="/sing100/node/516"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Creating Your Artwork</a></li>
								<li><a href="/sing100/node/517"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Written Narrative</a></li>
								<li><a href="/sing100/node/518"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Submit Assignment</a></li>
								<li><a href="/sing100/node/519"><div class="icon-assignment-black outline-nav-icon" data-grunticon-embed=""></div>Assignment Feedback</a></li>
							</ul>
						</li>
					</ul>
				</div>
			</li>

		</ul>



	   <?php if ($content): ?>
	      <?php print $content; ?>
	    <?php endif; ?>
	</div>
</aside>
