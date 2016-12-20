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

  getAssignment(assignmentId) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments/' + assignmentId)
      .map(data => data.json().data)
      .map(data => this.convertToAssignment(data));
  }

  createAssignment(assignment:Assignment) {
    let newAssignment = this.prepareForDrupal(assignment);
    
    return this.elmsln.post(AppSettings.BASE_PATH + 'node', newAssignment)
      .map(data => data.json())
      .map(data => ({ type: 'ADD_ASSIGNMENT', payload: Object.assign({}, assignment, {id: parseInt(data.id)})}))
      .subscribe(action => {
        this.store.dispatch(action);
        Materialize.toast('Assignment created', 1000);
      });
  }

  updateAssignment(assignment:Assignment) {
    let newAssignment = this.prepareForDrupal(assignment);

    return this.elmsln.put(AppSettings.BASE_PATH + 'node/' + assignment.id, newAssignment)
      .map(data => data.json())
  }

  /**
   * @todo: this should eventually be more dynamic
   */
  getAssignmentTypes() {
    return [
      {
        value: 'open',
        display: 'Open'
      },
      {
        value: 'closed',
        display: 'Closed'
      }
    ];
  }

  private convertToAssignment(data:any) {
    let converted:Assignment = new Assignment();
    for(var propertyName in converted) {
      if (data[propertyName]) {
        converted[propertyName] = data[propertyName];
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
    if (assignment.description) {
      newAssignment.body = {
        value: assignment.description
      }
    }
    if (assignment.project) {
      newAssignment.field_assignment_project = assignment.project
    }
    if (assignment.type) {
      newAssignment.field_assignment_privacy_setting = assignment.type;
    }
    if (assignment.description) {
      newAssignment.field_assignment_description = {
        value: assignment.description
      }
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