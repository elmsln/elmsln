/* tslint:disable:no-unused-variable */

import { TestBed, async, inject } from '@angular/core/testing';
import { ActivityFeedService } from './activity-feed.service';

describe('ActivityFeedService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [ActivityFeedService]
    });
  });

  it('should ...', inject([ActivityFeedService], (service: ActivityFeedService) => {
    expect(service).toBeTruthy();
  }));
});
