/* tslint:disable:no-unused-variable */

import { TestBed, async, inject } from '@angular/core/testing';
import { ElmslnService } from './elmsln.service';

describe('Service: Elmsln', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [ElmslnService]
    });
  });

  it('should ...', inject([ElmslnService], (service: ElmslnService) => {
    expect(service).toBeTruthy();
  }));
});
