import { Component, OnInit } from '@angular/core';
import { UserService } from './user.service';
import { Router, ActivatedRoute, Params } from '@angular/router';
import { Store } from '@ngrx/store';
import { loadPermissions, loadAssignments } from './app.actions';
import { loadSubmissions } from './submission/submission.actions'
import { loadProjects } from './projects/project.actions';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
  providers: [UserService]
})
export class AppComponent implements OnInit {
  constructor(
    private router: Router,
    private store: Store<{}>
  ) {
  }
  ngOnInit() {
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