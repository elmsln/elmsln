/* tslint:disable:no-unused-variable */

import { TestBed, async, inject } from '@angular/core/testing';
import { CritiqueService } from './critique.service';

describe('Service: Critique', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [CritiqueService]
    });
  });

  it('should ...', inject([CritiqueService], (service: CritiqueService) => {
    expect(service).toBeTruthy();
  }));
});
