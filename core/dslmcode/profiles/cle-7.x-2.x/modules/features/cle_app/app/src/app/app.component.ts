import { Component, OnInit } from '@angular/core';
import { UserService } from './user.service';
import { Router, ActivatedRoute, Params } from '@angular/router';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs/Observable';
import { loadPermissions, loadAssignments } from './assignment/assignment.actions';
import { loadSubmissions } from './submission/submission.actions'
import { loadProjects } from './projects/project.actions';
import { toggleActivityFeed, closeActivityFeed } from './activity-feed/activity-feed.actions';
import { ActivityFeedStates } from './activity-feed/activity-feed.reducer';
import { AppSettings } from './app.settings';
import { ActivityFeedService } from './activity-feed/activity-feed.service';
import * as fromRoot from './app.reducer';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
  providers: [UserService]
})
export class AppComponent implements OnInit {
  basePath:string;
  activityFeed$: Observable<any>;


  constructor(
    private router: Router,
    private activityFeedService: ActivityFeedService,
    private store: Store<fromRoot.State>
  ) {
  }
  ngOnInit() {
    this.basePath = AppSettings.BASE_PATH;
    this.store.dispatch(loadAssignments());
    this.store.dispatch(loadPermissions());
    this.store.dispatch(loadSubmissions());
    this.store.dispatch(loadProjects());

    this.activityFeed$ = this.activityFeedService.pluckCritiquesForUser();
  }
}