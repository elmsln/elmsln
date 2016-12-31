import { Injectable, Inject } from '@angular/core';
import { Observable, Subscription } from 'rxjs';
import { Store } from '@ngrx/store';
import { ElmslnService } from '../elmsln.service';
import { AppSettings } from '../app-settings';
import { Submission } from './submission';
declare const Materialize:any;

@Injectable()
export class SubmissionService {
  submissions: Observable<Array<Submission>>;

  constructor(
    private elmsln: ElmslnService,
    private store: Store<{}>
  ) {
    this.submissions = this.store.select((state:any) => state.submissions);
  }

  getSubmissions(assignmentId?:number) {
    let query = assignmentId ? '?assignment=' + assignmentId : '';
    this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/submissions' + query)
      .map(data => data.json().data)
      .map((data:any[]) => {
        if (data) {
          // convert list of data into list of Submissions
          let d:any[] = [];
          data.forEach(item => d.push(this.convertToSubmission(item)));
          return d;
        }
      })
      .map(payload => ({ type: 'ADD_SUBMISSIONS', payload }))
      .subscribe(action => this.store.dispatch(action));
  }

  loadSubmissions(): Observable<Submission[]> {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/submissions')
      .map(data => data.json().data)
      .map((data:any[]) => {
        if (data) {
          // convert list of data into list of Submissions
          let d:any[] = [];
          data.forEach(item => d.push(this.convertToSubmission(item)));
          return d;
        }
      })
  }

  getSubmission(submissionId) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/submissions/' + submissionId)
      .map(data => data.json().data)
      .map(data => this.convertToSubmission(data));
  }

  createSubmission(submission:Submission) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/submissions/' + submission.id + '/create')
      .map(data => data.json())
  }

  updateSubmission(submission:Submission) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/submissions/' + submission.id + '/update')
      .map(data => data.json())
  }

  deleteSubmission(submission:Submission) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/submissions/' + submission.id + '/delete')
      .map(data => data.json())
  }

  /**
   * @todo: this should eventually be more dynamic
   */
  getSubmissionOptions() {
    return {
      type: [
        { value: 'open', display: 'Open' },
        { value: 'closed', display: 'Closed' }
      ],
      critiqueMethod: [
        { value: 'open', display: 'Open'},
        { value: 'random', display: 'Random'}
      ],
      critiqueStyle: [
        { value: 'open', display: 'Open'},
        { value: 'blind', display: 'Blind'},
        { value: 'double_blind', display: 'Double blind'}
      ]
    }
  }

  private convertToSubmission(data:any) {
    let converted:Submission = new Submission();
    for(var propertyName in converted) {
      if (data[propertyName]) {
        converted[propertyName] = data[propertyName];
      }
    }

    return converted;
  }

  private prepareForDrupal(submission:Submission) {
    return submission;
  }
}