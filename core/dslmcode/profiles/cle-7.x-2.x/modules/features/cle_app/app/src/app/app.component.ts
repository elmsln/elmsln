import { Component, OnInit } from '@angular/core';
import { UserService } from './user.service';
import { Router, ActivatedRoute, Params } from '@angular/router';
import { Store } from '@ngrx/store';
import { loadPermissions, loadAssignments } from './assignment/assignment.actions';
import { loadSubmissions } from './submission/submission.actions'
import { loadProjects } from './projects/project.actions';
import { AppSettings } from './app-settings';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
  providers: [UserService]
})
export class AppComponent implements OnInit {
  basePath:string;

  constructor(
    private router: Router,
    private store: Store<{}>
  ) {
  }
  ngOnInit() {
    this.basePath = AppSettings.BASE_PATH;

    // Find out if the user is already logged In
    let auth = localStorage.getItem('basicAuthCredentials');
    if (auth) {
      this.router.navigate(['/projects']);
    }
    else {
      this.router.navigate(['/login']);
    }
    this.store.dispatch(loadAssignments());
    this.store.dispatch(loadPermissions());
    this.store.dispatch(loadSubmissions());
    this.store.dispatch(loadProjects());
  }
}