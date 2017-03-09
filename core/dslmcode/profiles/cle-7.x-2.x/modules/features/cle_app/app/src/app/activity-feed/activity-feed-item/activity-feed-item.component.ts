import { Component, OnInit, Input } from '@angular/core';

@Component({
  selector: 'app-activity-feed-item',
  templateUrl: './activity-feed-item.component.html',
  styleUrls: ['./activity-feed-item.component.css']
})
export class ActivityFeedItemComponent implements OnInit {
  @Input() item;

  constructor(
  ) { }

  ngOnInit() {
  }

  get title() {
    return this.item.title ? this.item.title : '';
  }
}
