import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { ReactiveFormsModule, FormBuilder, FormGroup } from '@angular/forms';
import { Router } from '@angular/router';
import { Assignment } from '../../assignment';
import { AssignmentService } from '../../assignment.service';
import { Project } from '../../project';
declare const jQuery:any;

@Component({
  selector: 'app-assignment-form',
  templateUrl: './assignment-form.component.html',
  styleUrls: ['./assignment-form.component.css'],
  providers: [Assignment, AssignmentService]
})
export class AssignmentFormComponent implements OnInit {
  // assignments will always have a project attached to it
  @Input() project: Project;
  // this is the newly created assignment
  @Output() assignment: Assignment;
  // assignment creation event
  @Output() assignmentCreated: EventEmitter<any> = new EventEmitter();
  // The assignment form that we will attach all of the fields to
  form: FormGroup;
  assignmentTypes:any[];

  constructor(
    private formBuilder: FormBuilder,
    private assignmentService: AssignmentService,
    private router: Router
  ) { 
    this.form = this.formBuilder.group({
      title: <string>'',
      body: <string>'',
      endDate: <string>null,
      startDate: <string>null,
      type: <string>null,
    });

    this.assignmentTypes = this.assignmentService.getAssignmentTypes();
  } 

  ngOnInit() {
  }

  // Update the body from the WYSIWYG changed event.
  bodyChanged($event) {
    this.form.patchValue({
      body: $event
    })
  }

  save(model:Assignment) {
    // add project id
    model.project = this.project.id;
    console.log('Submit Assignment initiated', model);
    this.assignmentService.createAssignment(model)
      .subscribe(data => {
        console.log('Assignment creation response: ', data);
        if (data.id) {
          this.assignmentCreated.emit();
          this.form.reset();
        }
      })
  }
}
