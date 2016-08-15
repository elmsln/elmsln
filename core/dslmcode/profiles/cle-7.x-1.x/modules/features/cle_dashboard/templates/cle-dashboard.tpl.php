<div ng-app="cleDashboard" ng-controller="cleAssignmentsController" class="cle-dashboard">
  <div class="collection with-header">
    <div class="collection-header"><h3>My Assignments</h3></div>
    <div ng-repeat="assignment in data.assignments">
      <a class="cle-dashboard__assignment" href="{{basePath}}node/{{assignment.nid}}"  ng-if="assignment.nid" ng-cloak>
        <div class="collapsible-header">
          <i class="material-icons">assignment</i>
          <b>{{assignment.node_title}}</b>
          <div class="secondary-content">
            <span class="chip" ng-if="assignment.active"> Open For Submissions </span>
            <span class="chip" ng-if="assignment.closed"> Closed </span>
            <span class="chip completed" ng-if="assignment.completed">  Done <i class="material-icons">check</i></span>
          </div>
          <div class="post-date">
            <span> Due: </span>
            <span ng-bind-html="assignment.field_field_begin_date[0].rendered['#markup']"> to</span>  <span ng-bind-html="assignment.field_field_due_date[0].rendered['#markup']"></span>
          </div>
        </div>
      </a>
      <a class="cle-dashboard__critique" href="{{assignment.critique.url}}" ng-if="assignment.critique" ng-if="assignment.nid" ng-cloak>
        <div class="collapsible-header">
          <i class="material-icons">subdirectory_arrow_right</i>
          <b>{{assignment.node_title}} Peer Review</b>
          <i class="material-icons right-align">comment</i>
          <div class="secondary-content">
            <span class="chip completed" ng-if="assignment.critique.completed"> <i class="material-icons">check</i> Done </span>
          </div>
          <div class="meta-content">
          </div>
          <div class="post-date">
            <span> Due: </span>
            <span ng-bind-html="assignment.field_field_critique_date[0].rendered['#markup']">  </span>
          </div>
        </div>
      </a>
    </div>
  </div>

  <div class="collection with-header">
    <div class="collection-header"><h3>My Submissions</h3></div>
    <a href="{{basePath}}node/{{submission.nid}}" class="avatar" ng-repeat="submission in data.submissions" ng-cloak>
      <div class="collapsible-header"><i class="material-icons">subject</i>
        <b>{{submission.node_title}}</b>
        <div class="secondary-content">
          <span ng-if="submission.field_field_submission_state[0]['rendered']['#markup'] == 'Submission ready for review'" class="chip completed" ><span ng-bind-html="submission.field_field_submission_state[0]['rendered']['#markup']"></span><i class="material-icons">check</i></span>
          <span ng-if="submission.field_field_submission_state[0]['rendered']['#markup'] != 'Submission ready for review'" class="chip" ng-bind-html="submission.field_field_submission_state[0]['rendered']['#markup']"></span>
        </div>
        <div class="meta-content">
          <div>Assignment: {{submission.node_field_data_field_assignment_title}}</div>
        </div>
        <div class="post-date" ng-if="submission.node_created">
          <span> Posted: </span> {{ submission.node_created | date: 'EEE, MM-dd-yy'}}
        </div>
      </div>
    </a>
  </div>

  <div class="collection with-header">
    <div class="collection-header"><h3>My Reviews</h3></div>
    <a href="{{basePath}}node/{{critique.nid}}" class="avatar" ng-repeat="critique in data.critiques" ng-cloak>
      <div class="collapsible-header"><i class="material-icons"> comment </i>
        <b>{{critique.node_title}}</b>
        <div class="meta-content">
          <div>Submission: {{critique.node_field_data_field_cle_crit_sub_ref_title}}</div>
        </div>
        <div class="post-date" ng-if="critique.node_created">
          <span> Posted: </span> {{ critique.node_created | date: 'EEE, MM-dd-yy'}}
        </div>
      </div>
    </a>
  </div>

</div>
