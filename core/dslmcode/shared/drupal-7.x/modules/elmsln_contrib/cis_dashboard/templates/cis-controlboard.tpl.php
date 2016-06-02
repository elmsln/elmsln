<div class="row" ng-app="Fa" ng-controller="cisDashboard">

<div class="large-6 columns">
  <div class="large-6 columns text-right">
   <ul id="sort-drop" class="f-dropdown f-open-dropdown text-left" data-dropdown-content="" style="position: absolute; left: 13.3281px; top: 1892.75px;" aria-hidden="false">
    <li><a href="#">Ascending</a></li>
    <li><a href="#">Descending</a></li>
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
            <a class="item" href="node/{{course.nid}}/edit?destination=cis-dashboard">
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
        <dd ng-class="{ active: isSet(1)}"><a href="#panel-sections-{{$index}}" ng-click="setTab(1)">Sections</a></dd>
        <dd ng-class="{ active: isSet(2)}"><a href="#panel-content-{{$index}}" ng-click="setTab(2)">Content</a></dd>
        <dd ng-class="{ active: isSet(3)}"><a href="#panel-people-{{$index}}" ng-click="setTab(3)">People</a></dd>
        <dd ng-class="{ active: isSet(4)}"><a href="#panel-network-{{$index}}" ng-click="setTab(4)">Network</a></dd>
      </dl>

      <div class="tabs-content cis--tab-panel__wrapper">
        <div ng-show="isSet(1)" class="content active row cis--course-item__vertical-tabs-wrapper" id="panel-sections-{{$index}}">
          <dl class="tabs vertical cis--tabs__vertical" data-tab>
            <dd ng-class="{active: isActive(offering)}" ng-repeat="offering in course.field_offerings"><a href="#section-tab-panel-{{$index}}" class="offering-year-button" ng-click="select(offering)" ng-class="{active: isActive(offering)}">{{ offering.field_semester.und[0].value}} {{offering.field_year.und[0].value}}</a></dd>
          </dl>
          <div class="tabs-content vertical" ng-repeat="offering in course.field_offerings">
            <div class="content" id="section-tab-panel-{{$index}}" ng-class="{active: isActive(offering)}">
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
                    <p>{{offering.field_semester.und[0].value}} {{offering.field_year.und[0].value}}</p>
                  </div>
                  <div class="cis--element__menu small-12 columns" ng-repeat="section in offering.field_sections.und">
                    <p><a href="#">Section {{section.field_section_number.und[0].safe_value}}</a>
                    <ul>
                    <li ng-repeat="string in section.field_access_string.und">{{string.value}}</li>
                    </ul>
                    </p>
                    <a href="field-collection/field-sections/{{section.item_id}}/edit?destination=cis-dashboard"><i class="material-icons">edit</i>&nbsp;</a>
                    <a href="#"><i class="material-icons">refresh</i>&nbsp;</a>
                    <a href="#"><i class="material-icons">people</i>&nbsp;</a>
                    <a href="#"><i class="material-icons">mail</i>&nbsp;</a>
                    <a href="#"><i class="material-icons">file_download</i>&nbsp;</a>
                    <a href=""><i class="material-icons">link</i>&nbsp;</a>
                    <a href="#"><i class="material-icons">event</i>&nbsp;</a>
                    <a href="#"><i class="material-icons">content_copy</i>&nbsp;</a>
                    <a href="#"><i class="material-icons">delete</i>&nbsp;</a>
                  </div> <!--END cis--element__menu small-12 columns-->
                 </div> <!--END row cis--element__category-->
                </div> <!--END cis--element small-12 columns -->
              </div> <!--END row collapse-->
            </div> <!--END content-->
          </div> <!--END tabs-content vertical-->
        </div> <!--END content active row cis--course-item__vertical-tabs-wrapper-->

        <div ng-show="isSet(2)" class="content active row cis--course-item__vertical-tabs-wrapper" id="panel-content-{{$index}}">
          <dl class="tabs vertical cis--tabs__vertical" data-tab>
            <dd ng-class="{active: isActive(offering)}" ng-repeat="offering in course.field_offerings"><a href="#content-tab-panel-{{$index}}" class="offering-year-button" ng-click="select(offering)" ng-class="{active: isActive(offering)}">Content Tab {{$index}}</a></dd> <!--TODO: ng-repeat to whatever data the content data is-->
          </dl>
          <div class="tabs-content vertical" ng-repeat="offering in course.field_offerings">
            <div class="content" id="content-tab-panel-{{$index}}" ng-class="{active: isActive(offering)}">
              <div class="row collapse">
               <div class="cis--element small-12 columns">
                </div>
                <div class="cis--element small-12 columns">
                <div class="row cis--element__category">
                  <div class=" small-12 columns">
                    <p> Content {{$index}}</p>
                  </div>
                 </div> <!--END row cis--element__category-->
                </div> <!--END cis--element small-12 columns -->
              </div> <!--END row collapse-->
            </div> <!--END content-->
          </div> <!--END tabs-content vertical-->
        </div> <!--END content active row cis--course-item__vertical-tabs-wrapper-->

        <div ng-show="isSet(3)" class="content active row cis--course-item__vertical-tabs-wrapper" id="panel-people-{{$index}}">
          <dl class="tabs vertical cis--tabs__vertical" data-tab>
            <dd ng-class="{active: isActive(offering)}" ng-repeat="offering in course.field_offerings"><a href="#people-tab-panel-{{$index}}" class="offering-year-button" ng-click="select(offering)" ng-class="{active: isActive(offering)}">People Tab {{$index}}</a></dd> <!--TODO: ng-repeat to whatever data the content data is-->
          </dl>
          <div class="tabs-content vertical" ng-repeat="offering in course.field_offerings">
            <div class="content" id="people-tab-panel-{{$index}}" ng-class="{active: isActive(offering)}">
              <div class="row collapse">
               <div class="cis--element small-12 columns">
                </div>
                <div class="cis--element small-12 columns">
                <div class="row cis--element__category">
                  <div class=" small-12 columns">
                    <p> People {{$index}}</p>
                  </div>
                 </div> <!--END row cis--element__category-->
                </div> <!--END cis--element small-12 columns -->
              </div> <!--END row collapse-->
            </div> <!--END content-->
          </div> <!--END tabs-content vertical-->
        </div> <!--END content active row cis--course-item__vertical-tabs-wrapper-->

        <div ng-show="isSet(4)" class="content active row cis--course-item__vertical-tabs-wrapper" id="panel-network-{{$index}}">
          <dl class="tabs vertical cis--tabs__vertical" data-tab>
            <dd ng-class="{active: isActive(offering)}" ng-repeat="offering in course.field_offerings"><a href="#network-tab-panel-{{$index}}" class="offering-year-button" ng-click="select(offering)" ng-class="{active: isActive(offering)}">Network Tab {{$index}}</a></dd> <!--TODO: ng-repeat to whatever data the content data is-->
          </dl>
          <div class="tabs-content vertical" ng-repeat="offering in course.field_offerings">
            <div class="content" id="network-tab-panel-{{$index}}" ng-class="{active: isActive(offering)}">
              <div class="row collapse">
               <div class="cis--element small-12 columns">
                </div>
                <div class="cis--element small-12 columns">
                <div class="row cis--element__category">
                  <div class=" small-12 columns">
                    <p> Network {{$index}}</p>
                  </div>
                 </div> <!--END row cis--element__category-->
                </div> <!--END cis--element small-12 columns -->
              </div> <!--END row collapse-->
            </div> <!--END content-->
          </div> <!--END tabs-content vertical-->
        </div> <!--END content active row cis--course-item__vertical-tabs-wrapper-->

        </div>
      </div><!-- /.columns -->
    </div><!-- /.row -->
  </div><!-- /.columns .cis--course-item -->
<!-- -------------- END FIRST ITEM -------------- -->
</div><!-- /.row -->
