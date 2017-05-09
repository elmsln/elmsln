/* tslint:disable:no-unused-variable */

import { TestBed, async, inject } from '@angular/core/testing';
import { AssignmentService } from './assignment.service';

describe('Service: Assignment', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [AssignmentService]
    });
  });

  it('should ...', inject([AssignmentService], (service: AssignmentService) => {
    expect(service).toBeTruthy();
  }));
});
