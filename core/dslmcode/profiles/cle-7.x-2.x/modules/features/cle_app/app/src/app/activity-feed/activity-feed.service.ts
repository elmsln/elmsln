import { Injectable } from '@angular/core';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs/Observable';
import * as fromRoot from '../app.reducer';
import { SubmissionService } from '../submission/submission.service';
import { Submission } from '../submission/submission';

@Injectable()
export class ActivityFeedService {

  constructor(
    private store: Store<fromRoot.State>,
    private submissionService: SubmissionService
  ) { }

  public pluckCritiquesForUser():Observable<any> {
    return Observable.combineLatest(
      this.store.select(fromRoot.getAllSubmissions),
      this.store.select(fromRoot.getMySubmissions),
      ((allSubs:Submission[], mySubs:Submission[]) => {
        // Find out if there are any of this users submission id's
        // in the list of relatedSubmissions 
        const mySubIds:number[] = mySubs.map(s => s.id);
        // return allSubs.filter(s => mySubIds.find(id => id === s.relatedSubmission));
        return allSubs;
      })
    )
  }
}
