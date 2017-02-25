import { Injectable, Inject } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable, Subscription } from 'rxjs';
import { Store } from '@ngrx/store';
import { AppState } from '../state';
import { ElmslnService } from '../elmsln.service';
import { AppSettings } from '../app-settings';
import { Assignment } from './assignment';
declare const Materialize:any;


@Injectable()
export class AssignmentService {
  assignments: Observable<Array<Assignment>>;


  constructor(
    private elmsln: ElmslnService,
    private store: Store<AppState>
  ) {
    this.assignments = this.store.select(state => state.assignments);
  }

  getAssignments(projectId?:number) {
    let query = projectId ? '?project=' + projectId : '';
    this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments' + query)
      .map(data => data.json())
      .map(data => typeof data.data !== 'undefined' ? data.data : [])
      .map((data:any[]) => {
        if (data) {
          // convert list of data into list of Assignments
          let d:any[] = [];
          data.forEach(item => d.push(this.convertToAssignment(item)));
          return d;
        }
      })
      .map(payload => ({ type: 'ADD_ASSIGNMENTS', payload }))
      .subscribe(action => this.store.dispatch(action));
  }

  loadAssignments(): Observable<Assignment[]> {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments')
      .map(data => data.json().data)
      .map((data:any[]) => {
        if (data) {
          // convert list of data into list of Assignments
          let d:any[] = [];
          data.forEach(item => d.push(this.convertToAssignment(item)));
          return d;
        }
     })
  }

  getAssignment(assignmentId) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments/' + assignmentId)
      .map(data => data.json().data[0])
      .map(data => this.convertToAssignment(data))
  }

  createAssignment(assignment:Assignment) {
    const newAssignment = this.prepareForDrupal(assignment);
    return this.elmsln.post(AppSettings.BASE_PATH + 'api/v1/cle/assignments/create', newAssignment)
      .map(data => data.json().node)
      .switchMap(node => this.getAssignment(node.nid))
  }

  updateAssignment(assignment:Assignment) {
    const newAssignment = this.prepareForDrupal(assignment);
    return this.elmsln.put(AppSettings.BASE_PATH + 'api/v1/cle/assignments/' + assignment.id + '/update', newAssignment )
      .map(data => data.json().node)
      .map(node => this.convertToAssignment(node))
  }

  deleteAssignment(assignment:Assignment) {
    return this.elmsln.delete(AppSettings.BASE_PATH + 'api/v1/cle/assignments/' + assignment.id + '/delete')
      .map(data => data.json())
  }

  startCritique(assignment:Assignment) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments/' + assignment.id + '/critique')
      .map(data => data.json())
  }

  /**
   * @todo: this should eventually be more dynamic
   */
  getAssignmentOptions() {
    return {
      type: [
        { value: 'open', display: 'Open' },
        { value: 'open_after_submission', display: 'Open After Submission' },
        { value: 'closed', display: 'Closed' }
      ],
      critiqueMethod: [
        { value: 'none', display: 'None'},
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

  convertToAssignment(data:any) {
    let converted:Assignment = new Assignment();
    for(var propertyName in converted) {
      if (data[propertyName]) {
        converted[propertyName] = data[propertyName];
      }
    }
    if (data['hierarchy']) {
      if (data['hierarchy']['project']) {
        converted['project'] = Number(data['hierarchy']['project']);
      }
    }
    if (data['evidence']) {
      if (data['evidence']['critique']) {
        if (data['evidence']['critique']['method']) {
          converted.critiqueMethod = data['evidence']['critique']['method'];
        }
        if (data['evidence']['critique']['public']) {
          converted.critiquePrivacy = data['evidence']['critique']['public'];
        }
      }
    }

    return converted;
  }

  private prepareForDrupal(assignment:Assignment) {
    if (!assignment) {
      return assignment;
    }
    // Convert date fields
    let newAssignment: any = Object.assign({}, assignment);
    // remove created
    delete newAssignment.created;
    if (assignment.body) {
      newAssignment.body = {
        value: assignment.body,
        format: 'textbook_editor'
      }
    }
    if (assignment.type) {
      Object.assign(newAssignment, assignment.type);
    }
    Object.assign(newAssignment, {evidence: {critique: { 
      method: assignment.critiqueMethod,
      public: assignment.critiquePrivacy ? 1 : 0
    }}});
    
    let dateFields = ['startDate', 'endDate'];
    dateFields.forEach(function(field) {
      if (assignment[field]) {
        assignment[field] = (Date.parse(assignment[field]) / 1000);
        assignment[field] = assignment[field].toString();
      }
    });

    // the due date works weird so we need to do some custom logic to find out what field to populate
    // in Drupal
    if (assignment.endDate !== null) {
      if (assignment.startDate !== null) {
        newAssignment.startDate =  assignment.startDate,
        newAssignment.endDate= assignment.endDate
      }
      else {
        newAssignment.startDate = assignment.endDate;
        newAssignment.endDate = null;
      }
    }

    return newAssignment;
  }

  // Return if the user should be able to edit a project
  get userCanEdit():Observable<boolean> {
    return this.store.select('user')
      .map((state:any) => state.permissions.includes('edit own cle_assignment content'));
  }

  /**
   * Find out if an assignment is a Critique assignment
   */
  public assignmentIsCritique(assignment:Assignment):boolean {
    if (assignment.hierarchy) {
      if (assignment.hierarchy.dependencies) {
        if (assignment.hierarchy.dependencies.length > 0) {
          return true;
        }
      }
    }
    return false;
  }
}