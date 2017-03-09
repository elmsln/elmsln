import { Component, OnInit, OnDestroy, Input } from '@angular/core';
import * as fromRoot from '../app.reducer';
import { ActivityFeedStates } from './activity-feed.reducer';
import { Observable } from 'rxjs/Observable';
import { Store } from '@ngrx/store';
import { ActivityFeedService } from './activity-feed.service';
import { Router } from '@angular/router';
declare const jQuery:any;

@Component({
  selector: 'app-activity-feed',
  templateUrl: './activity-feed.component.html',
  styleUrls: ['./activity-feed.component.css']
})
export class ActivityFeedComponent implements OnInit {
  @Input() items;

  constructor(
    private store: Store<fromRoot.State>,
    private activityFeedService: ActivityFeedService,
    private router:Router
  ) { }

  ngOnInit() {
  }

  itemClicked(item) {
    this.router.navigate(['/submissions/' + item.id]);
  }
}
