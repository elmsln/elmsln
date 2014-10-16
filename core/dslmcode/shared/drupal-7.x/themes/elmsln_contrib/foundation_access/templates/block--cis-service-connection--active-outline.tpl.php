<!-- Default Menu -->
<?php if ($elements['#outline_style'] == 'default') : ?>
<ul id="activeoutline" class="menu book-oultine slide-panels"><?php print $content; ?></ul>
<ul id="activeoutline-sticky" class="menu book-oultine slide-panels sticky-bar"><?php print $content; ?></ul>
<?php endif; ?>
<!-- Stacked Outline
<ul id="activeoutline2" class="menu book-oultine slide-panels">
  <li><a href='#unit-1' class="accordion-btn button">Unit 1</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <h3>Lesson 1</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel1c" class='outline-sub-link expand fi-page-multiple'>Topics</a>
        <div id="panel1c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel1c-2" class='outline-sub-link expand full button fi-checkbox'>Assignments</a>
        <div id="panel1c-2" class="content">
          <li><a href="#">Assignment 1</a></li>
          <li><a href="#">Assignment 2</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 2</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel2c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel2c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel2c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel2c-2" class="content">
          <li><a href="#">Assignment 3</a></li>
          <li><a href="#">Assignment 4</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 3</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel3c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel3c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel3c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel3c-2" class="content">
          <li><a href="#">Assignment 5</a></li>
          <li><a href="#">Assignment 6</a></li>
        </div>
      </dd>
    </dl>
  </li>
  <li><a href='#unit-2' class="accordion-btn button">Unit 2</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <h3>Lesson 4</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel4c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel4c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel4c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel4c-2" class="content">
          <li><a href="#">Assignment 7</a></li>
          <li><a href="#">Assignment 8</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 5</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel5c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel5c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel5c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel5c-2" class="content">
          <li><a href="#">Assignment 9</a></li>
          <li><a href="#">Assignment 10</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 6</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel6c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel6c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel6c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel6c-2" class="content">
          <li><a href="#">Assignment 11</a></li>
          <li><a href="#">Assignment 12</a></li>
        </div>
      </dd>
    </dl>
  </li>
  <li><a href='#unit-3' class="accordion-btn button">Unit 3</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <h3>Lesson 7</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel7c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel7c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel7c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel7c-2" class="content">
          <li><a href="#">Assignment 13</a></li>
          <li><a href="#">Assignment 14</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 8</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel8c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel8c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel8c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel8c-2" class="content">
          <li><a href="#">Assignment 15</a></li>
          <li><a href="#">Assignment 16</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 9</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel9c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel9c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel9c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel9c-2" class="content">
          <li><a href="#">Assignment 17</a></li>
          <li><a href="#">Assignment 18</a></li>
        </div>
      </dd>
    </dl>
  </li>
</ul>
 -->
<!-- Active Outline STICKY
<ul id="activeoutline-sticky" class="menu book-oultine slide-panels sticky-bar">
  <li><a href='#unit-1' class="accordion-btn button">Unit 1</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <h3>Lesson 1</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel1c" class='outline-sub-link expand fi-page-multiple'>Topics</a>
        <div id="panel1c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel1c-2" class='outline-sub-link expand full button fi-checkbox'>Assignments</a>
        <div id="panel1c-2" class="content">
          <li><a href="#">Assignment 1</a></li>
          <li><a href="#">Assignment 2</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 2</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel2c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel2c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel2c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel2c-2" class="content">
          <li><a href="#">Assignment 3</a></li>
          <li><a href="#">Assignment 4</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 3</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel3c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel3c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel3c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel3c-2" class="content">
          <li><a href="#">Assignment 5</a></li>
          <li><a href="#">Assignment 6</a></li>
        </div>
      </dd>
    </dl>
  </li>
  <li><a href='#unit-2' class="accordion-btn button">Unit 2</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <h3>Lesson 4</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel4c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel4c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel4c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel4c-2" class="content">
          <li><a href="#">Assignment 7</a></li>
          <li><a href="#">Assignment 8</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 5</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel5c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel5c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel5c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel5c-2" class="content">
          <li><a href="#">Assignment 9</a></li>
          <li><a href="#">Assignment 10</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 6</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel6c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel6c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel6c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel6c-2" class="content">
          <li><a href="#">Assignment 11</a></li>
          <li><a href="#">Assignment 12</a></li>
        </div>
      </dd>
    </dl>
  </li>
  <li><a href='#unit-3' class="accordion-btn button">Unit 3</a>
    <dl class="accordion" data-accordion="myAccordionGroup">
      <dd class="accordion-navigation">
        <h3>Lesson 7</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel7c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel7c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel7c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel7c-2" class="content">
          <li><a href="#">Assignment 13</a></li>
          <li><a href="#">Assignment 14</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 8</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel8c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel8c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel8c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel8c-2" class="content">
          <li><a href="#">Assignment 15</a></li>
          <li><a href="#">Assignment 16</a></li>
        </div>
      </dd>
      <dd class="accordion-navigation">
        <h3>Lesson 9</h3>
        <a href="#" class='outline-sub-link small button fi-info'>About</a>
        <a href="#panel9c" class='outline-sub-link expand small button fi-page-multiple'>Topics</a>
        <div id="panel9c" class="content">
          <li><a href="#">Introduction</a></li>
          <li><a href="#">Page 1</a></li>
          <li><a href="#">Page 2</a></li>
          <li><a href="#">Page 3</a></li>
          <li><a href="#">Summary</a></li>
        </div>
        <a href="#panel9c-2" class='outline-sub-link expand full small button fi-checkbox'>Assignments</a>
        <div id="panel9c-2" class="content">
          <li><a href="#">Assignment 17</a></li>
          <li><a href="#">Assignment 18</a></li>
        </div>
      </dd>
    </dl>
  </li>
</ul>
 -->
