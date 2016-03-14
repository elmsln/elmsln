<div class="row" ng-app="Fa" ng-controller="cisDashboard">

<div class="large-6 columns">
  <div class="large-6 columns text-right">
   <ul id="sort-drop" class="f-dropdown f-open-dropdown text-left" data-dropdown-content="" style="position: absolute; left: 13.3281px; top: 1892.75px;" aria-hidden="false">
    <li><a href="#">Ascending</a></li>
    <li><a href="#">Descedning</a></li>
    <li><a href="#">Newest</a></li>
     <li><a href="#">Oldest</a></li>
  </ul>
    <a href="#" data-dropdown="sort-drop" class="tiny secondary radius button dropdown">Sort</a>
    <a class="fi-filter tiny secondary radius button" href="#">&nbsp;</a>
    <a class="fi-list-thumbnails tiny secondary radius button " href="#">&nbsp;</a>
    <a class="fi-thumbnails tiny secondary radius button" href="#">&nbsp;</a>
  </div>
   </div>

<div class="row">
<div class="small-12 columns cis--course-item" ng-repeat="course in courses.list">
<div class="row collapse">
  <div class="small-12 columns">
    <div class="cis--course-item__header row">
      <div class="small-12 medium-8 columns cis--course-item__titles">
        <h2>{{course.title}}</h2>
        <h3>{{course.field_course_title}}</h3>
      </div>
      <div class="small-12 medium-4 columns cis--course-item__menu">
        <div class="icon-bar five-up">
          <a class="item">
            <i class="material-icons">edit</i>
          </a>
          <a class="item">
            <i class="material-icons">refresh</i>
          </a>
          <a class="item">
            <i class="material-icons">folder</i>
          </a>
          <a class="item">
            <i class="material-icons">insert_chart</i>
          </a>
          <a class="item">
            <i class="material-icons">add</i>
          </a>
        </div>
      </div><!-- /.columns .cis--course-item__titles-->
    </div><!-- /.row-->

    <dl class="tabs cis--tabs__horizontal" data-tab>
      <dd class="active"><a href="#panel-sections">Sections</a></dd>
      <dd><a href="#panel-content">Content</a></dd>
      <dd><a href="#panel-people">People</a></dd>
      <dd><a href="#panel-network">Network</a></dd>
    </dl>
    <div class="tabs-content cis--tab-panel__wrapper">
      <div class="content active row cis--course-item__vertical-tabs-wrapper" id="panel-sections">
        <dl class="tabs vertical cis--tabs__vertical" data-tab>
          <dd class="active"><a href="#section-tab-panel-1">2015</a></dd>
          <dd><a href="#section-tab-panel-2">2016</a></dd>
        </dl>
        <div class="tabs-content vertical">
          <div class="content active" id="section-tab-panel-1">
            <div class="row collapse">
             <div class="cis--element small-12 columns">
               <form>
               <div class="row collapse">
                 <div class="large-10 columns">
                     <input type="text" placeholder="Section Name" />
                 </div>
                 <div class="large-2 columns">
                   <a href="#" class="button tiny expand fi-plus">&nbsp Add</a>
                 </div>
               </div>
               </form>
              </div>
              <div class="cis--element small-12 columns">
              <div class="row cis--element__category">
                 <div class=" small-12 columns">
              <p>Spring</p>
                </div>
                <div class="cis--element__menu small-12 columns">
                  <p><a href="#">Course section 001</a></p>
                  <a href="#"><i class="material-icons">edit</i>&nbsp;</a>
                  <a href="#"><i class="material-icons">refresh</i>&nbsp;</a>
                  <a href="#"><i class="material-icons">people</i>&nbsp;</a>
                  <a href="#"><i class="material-icons">mail</i>&nbsp;</a>
                  <a href="#"><i class="material-icons">file_download</i>&nbsp;</a>
                  <a href="#"><i class="material-icons">link</i>&nbsp;</a>
                  <a href="#"><i class="material-icons">event</i>&nbsp;</a>
                  <a href="#"><i class="material-icons">content_copy</i>&nbsp;</a>
                  <a href="#"><i class="material-icons">delete</i>&nbsp;</a>
                </div>
                <div class="cis--element__menu small-12 columns">
                  <p><a href="#">Course section 002</a></p>
                  <a href="#"><i class="fi-pencil"></i>&nbsp;</a>
                  <a href="#"><i class="fi-loop"></i>&nbsp;</a>
                  <a href="#"><i class="fi-torsos"></i>&nbsp;</a>
                  <a href="#"><i class="fi-mail"></i>&nbsp;</a>
                  <a href="#"><i class="fi-download"></i>&nbsp;</a>
                  <a href="#"><i class="fi-link"></i>&nbsp;</a>
                  <a href="#"><i class="fi-calendar"></i>&nbsp;</a>
                  <a href="#"><i class="fi-arrows-compress"></i>&nbsp;</a>
                  <a href="#"><i class="fi-page-copy"></i>&nbsp;</a>
                  <a href="#"><i class="fi-trash"></i>&nbsp;</a>
                </div>
               </div>
            </div>
              
            <div class="cis--element small-12 columns">
              <div class="row cis--element__category">
                 <div class=" small-12 columns">
              <p>Fall</p>
                </div>
                <div class="cis--element__menu small-12 columns">
                  <p><a href="#">Course section 001</a></p>
                  <a href="#"><i class="fi-pencil"></i>&nbsp;</a>
                  <a href="#"><i class="fi-loop"></i>&nbsp;</a>
                  <a href="#"><i class="fi-torsos"></i>&nbsp;</a>
                  <a href="#"><i class="fi-mail"></i>&nbsp;</a>
                  <a href="#"><i class="fi-download"></i>&nbsp;</a>
                  <a href="#"><i class="fi-link"></i>&nbsp;</a>
                  <a href="#"><i class="fi-calendar"></i>&nbsp;</a>
                  <a href="#"><i class="fi-arrows-compress"></i>&nbsp;</a>
                  <a href="#"><i class="fi-page-copy"></i>&nbsp;</a>
                  <a href="#"><i class="fi-trash"></i>&nbsp;</a>
                </div>
                <div class="cis--element__menu small-12 columns">
                  <p><a href="#">Course section 002</a></p>
                  <a href="#"><i class="fi-pencil"></i>&nbsp;</a>
                  <a href="#"><i class="fi-loop"></i>&nbsp;</a>
                  <a href="#"><i class="fi-torsos"></i>&nbsp;</a>
                  <a href="#"><i class="fi-mail"></i>&nbsp;</a>
                  <a href="#"><i class="fi-download"></i>&nbsp;</a>
                  <a href="#"><i class="fi-link"></i>&nbsp;</a>
                  <a href="#"><i class="fi-calendar"></i>&nbsp;</a>
                  <a href="#"><i class="fi-arrows-compress"></i>&nbsp;</a>
                  <a href="#"><i class="fi-page-copy"></i>&nbsp;</a>
                  <a href="#"><i class="fi-trash"></i>&nbsp;</a>
                </div>
               </div>
            </div>
            
              
            </div>
          </div>
          <div class="content" id="section-tab-panel-2">
            <p>Section 2</p>
          </div>
        </div>
      </div>

      <div class="content row cis--course-item__vertical-tabs-wrapper" id="panel-content">
        <dl class="tabs vertical cis--tabs__vertical" data-tab>
          <dd class="active"><a href="#content-tab-panel-1">Content tab 1</a></dd>
          <dd><a href="#content-tab-panel-2">Content tab 2</a></dd>
        </dl>
        <div class="tabs-content vertical">
          <div class="content active" id="content-tab-panel-1">
            <p>Content 1</p>
          </div>
          <div class="content" id="content-tab-panel-2">
            <p>Content 2</p>
          </div>
        </div>
      </div>

      <div class="content row cis--course-item__vertical-tabs-wrapper" id="panel-people">
        <dl class="tabs vertical cis--tabs__vertical" data-tab>
          <dd class="active"><a href="#people-tab-panel-1">people tab 1</a></dd>
          <dd><a href="#people-tab-panel-2">people tab 2</a></dd>
        </dl>
        <div class="tabs-content vertical">
          <div class="content active" id="people-tab-panel-1">
            <p>people 1</p>
          </div>
          <div class="content" id="people-tab-panel-2">
            <p>people 2</p>
          </div>
        </div>
      </div>
      
      <div class="content cis--course-item__vertical-tabs-wrapper row" id="panel-network">
        <dl class="tabs vertical cis--tabs__vertical" data-tab>
          <dd class="active"><a href="#network-tab-panel-1">network tab 1</a></dd>
          <dd><a href="#network-tab-panel-2">network tab 2</a></dd>
        </dl>
        <div class="tabs-content vertical">
          <div class="content active" id="network-tab-panel-1">
            <p>network 1</p>
          </div>
          <div class="content" id="network-tab-panel-2">
            <p>network 2</p>
          </div>
        </div>
      </div>
      </div>
    </div><!-- /.columns -->
  </div><!-- /.row -->
</div><!-- /.columns .cis--course-item -->

<!-- -------------- END FIRST ITEM -------------- -->


</div><!-- /.row -->



