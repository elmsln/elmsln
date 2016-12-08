import { Injectable } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { ElmslnService } from './elmsln.service';
import { AppSettings } from './app-settings';
import { Assignment } from './assignment';

@Injectable()
export class AssignmentService {
  constructor(
    private elmsln: ElmslnService
  ) { }

  getAssignments(projectId?:number) {
    // 
    let query = projectId ? '?project=' + projectId : '';
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments' + query)
      .map(data => data.json())
  }

  getAssignment(assignmentId) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments/' + assignmentId)
      .map(data => data.json())
  }

  createAssignment(assignment:Assignment) {
    let newAssignment = this.prepareForDrupal(assignment);
    
    return this.elmsln.post(AppSettings.BASE_PATH + 'node', newAssignment)
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

  private prepareForDrupal(assignment:Assignment) {
    // Convert date fields
    let newAssignment: any = {};

    // We have to construct a new assignment object to send to RESTws
    newAssignment.type = 'cle_assignment';
    if (assignment.title) {
      newAssignment.title = assignment.title
    }
    if (assignment.body) {
      newAssignment.body = {
        value: assignment.body
      }
    }
    if (assignment.project) {
      newAssignment.field_assignment_project = assignment.project
    }
    if (assignment.type) {
      newAssignment.field_assignment_privacy_setting = assignment.type;
    }
    if (assignment.critique) {
      newAssignment.field_critique_method = assignment.critique;
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
          value: assignment.startDate 
        }
        newAssignment.field_assignment_due_date = {
          value2: assignment.endDate
        }
      }
      else {
        newAssignment.field_assignment_due_date = {
          value: assignment.endDate,
          value2: assignment.endDate
        }
      }
    }

    return newAssignment;
  }

}