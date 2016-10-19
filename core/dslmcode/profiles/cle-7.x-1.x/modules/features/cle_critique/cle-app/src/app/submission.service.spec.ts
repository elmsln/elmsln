/* tslint:disable:no-unused-variable */

import { TestBed, async, inject } from '@angular/core/testing';
import { SubmissionService } from './submission.service';

describe('Service: Submission', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [SubmissionService]
    });
  });

  it('should ...', inject([SubmissionService], (service: SubmissionService) => {
    expect(service).toBeTruthy();
  }));
});
