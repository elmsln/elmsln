import { Component, OnInit, OnDestroy } from '@angular/core';
import * as fromRoot from '../app.reducer';
import { ActivityFeedStates } from './activity-feed.reducer';
import { Observable } from 'rxjs/Observable';
import { Store } from '@ngrx/store';
declare const jQuery:any;

@Component({
  selector: 'app-activity-feed',
  templateUrl: './activity-feed.component.html',
  styleUrls: ['./activity-feed.component.css']
})
export class ActivityFeedComponent implements OnInit {
  constructor(
    private store: Store<fromRoot.State>
  ) { }

  ngOnInit() {
  }
}
