import { Injectable, Inject } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable, Subscription } from 'rxjs';
import { Store } from '@ngrx/store';
import { AppState } from './state';
import { ElmslnService } from './elmsln.service';
import { AppSettings } from './app-settings';
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
      .map(data => data.json().data)
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
    let newAssignment = this.prepareForDrupal(assignment);
    return this.elmsln.post(AppSettings.BASE_PATH + 'node', newAssignment)
      .map(data => data.json())
  }

  updateAssignment(assignment:Assignment) {
    let newAssignment = this.prepareForDrupal(assignment);
    return this.elmsln.put(AppSettings.BASE_PATH + 'node/' + assignment.id, newAssignment)
      .map(data => data.json())
  }

  deleteAssignment(assignment:Assignment) {
    return this.elmsln.delete(AppSettings.BASE_PATH + 'node/' + assignment.id)
      .map(data => data.json())
  }

  /**
   * @todo: this should eventually be more dynamic
   */
  getAssignmentOptions() {
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

  private convertToAssignment(data:any) {
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

    if (data['metadata']) {
      if (data['metadata']['canCreate']) {
        converted['canCreate'] = data['metadata']['canCreate'];
      }
    }

    return converted;
  }

  private prepareForDrupal(assignment:Assignment) {
    // Convert date fields
    let newAssignment: any = {};

    // We have to construct a new assignment object to send to RESTws
    newAssignment.type = 'cle_assignment';
    if (assignment.title) {
      newAssignment.title = assignment.title
    }
    if (assignment.project) {
      newAssignment.field_assignment_project = assignment.project
    }
    if (assignment.type) {
      newAssignment.field_assignment_privacy_setting = assignment.type;
    }
    if (assignment.body) {
      newAssignment.field_assignment_description = {
        value: assignment.body
      }
    }
    if (assignment.critiqueMethod) {
      newAssignment.field_critique_method = assignment.critiqueMethod;
    }
    if (assignment.critiquePrivacy) {
      newAssignment.field_critique_privacy = assignment.critiquePrivacy;
    }
    if (assignment.critiqueStyle) {
      newAssignment.field_critique_style = assignment.critiqueStyle;
    }
    
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
        newAssignment.field_assignment_due_date = {
          value: assignment.startDate,
          value2: assignment.endDate
        }
      }
      else {
        newAssignment.field_assignment_due_date = {
          value: assignment.endDate
        }
      }
    }

    return newAssignment;
  }
}