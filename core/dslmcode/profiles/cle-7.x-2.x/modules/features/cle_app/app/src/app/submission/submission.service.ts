import { Injectable, Inject } from '@angular/core';
import { Observable, Subscription } from 'rxjs';
import { Store } from '@ngrx/store';
import { ElmslnService } from '../elmsln.service';
import { AppSettings } from '../app-settings';
import { Submission } from './submission';
import { Assignment } from '../assignment/assignment';
import { loadAssignments } from '../assignment/assignment.actions';
import { normalize, schema, Schema } from 'normalizr';
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
      .map(data => data.json())
      .map(data => typeof data.data !== 'undefined' ? data.data : [])
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
      .map(data => data.json().data[0])
      .map(data => this.convertToSubmission(data));
  }

  createSubmission(submission:Submission) {
    const newSub = this.prepareForDrupal(submission);
    return this.elmsln.post(AppSettings.BASE_PATH + 'api/v1/cle/submissions/create', newSub)
      .map(data => data.json().node)
      .map(node => this.convertToSubmission(node))
  }

  updateSubmission(submission:Submission) {
    const newSub = this.prepareForDrupal(submission);
    return this.elmsln.put(AppSettings.BASE_PATH + 'api/v1/cle/submissions/' + submission.id + '/update', newSub)
      .map(data => data.json())
      .map(node => this.convertToSubmission(node))
  }

  deleteSubmission(submission:Submission) {
    return this.elmsln.delete(AppSettings.BASE_PATH + 'api/v1/cle/submissions/' + submission.id + '/delete')
      .map(data => data.json())
  }

  /**
   * @todo: this should eventually be more dynamic
   */
  getSubmissionOptions():any {
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
      ],
      state: [
        { value: 'submission_in_progress', display: 'Submission in progress', icon: 'autorenew', color: 'lightgoldenrodyellow'},
        { value: 'submission_ready', display: 'Submission Ready', icon: 'done', color: 'lightgreen'}
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

    if (data['nid']) {
      converted.id = Number(data['nid']);
    }

    if (data.evidence) {
      if (data.evidence.body) {
        converted.body = data.evidence.body;
      }
    }

    return converted;
  }

  private prepareForDrupal(submission:Submission) {
    const newSub:any = Object.assign({}, submission);

    if (submission.body) {
      newSub.evidence = {
        body: {
          value: submission.body,
          format: 'textbook_editor'
        }
      }
    }

    if (submission.evidence) {
      if (submission.evidence.images) {
        newSub.evidence['images'] = submission.evidence.images; 
      }
    }

    return newSub;
  }

  // get the submission from the store using the submissionID and 
  // return an observable
  getSubmissionFromStore(submissionId:Number):Observable<Submission> {
    return this.store.select('submissions')
      .map((state:any) => state.submissions.find((sub:Submission) => sub.id === submissionId))
  }

  // find out if the current user can edit the submission
  userCanEditSubmission(submissionId:Number):Observable<boolean> {
    return this.store.select('submissions')
      .map((state:any) => state.submissions.find((sub:Submission) => sub.id === submissionId))
      .map((state:any) => {
        if (state) {
          if (typeof state.metadata !== 'undefined') {
            if (typeof state.metadata.canUpdate !== 'undefined') {
              return state.metadata.canUpdate;
            }
          }
        }
        return false;
      })
  }

  /**
   * Return the submission type
   * This will check the parent assignment that the submission
   * is attached to and figure out what the critique method is.
   * If there is a critqiue method other than 'none' then it will
   * return that as the submission type. If there is no critique method
   * then it will just return 'submission' which is the default type
   */
  getSubmissionType(submission$:Observable<Submission>):Observable<string> {
    // combine the submission and assignments streams
    return Observable.combineLatest(submission$, this.store.select('assignments').map((state:any) => state.assignments))
      .map((streams:any) => {
        const submission:Submission = streams[0];
        const assignment:Assignment = streams[1].find((a:Assignment) => a.id === submission.assignment);
        if (assignment) {
          if (typeof assignment.critiqueMethod === 'string' && assignment.critiqueMethod !== 'none') {
            return 'critique';
          }
        }
        return 'submission';
      });
  }

  getSubmissionAssignment(submission:Submission):Observable<Assignment> {
    return this.store.select('assignments')
      .map((state:any) => state.assignments.find((assignment:Assignment) => assignment.id === submission.assignment))
  }
}