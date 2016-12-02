import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { ReactiveFormsModule, FormBuilder, FormGroup } from '@angular/forms';
import { Router } from '@angular/router';
import { Assignment } from '../../assignment';
import { AssignmentService } from '../../assignment.service';
import { Project } from '../../project';

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

  constructor(
    private formBuilder: FormBuilder,
    private assignmentService: AssignmentService,
    private router: Router
  ) { 
    this.form = this.formBuilder.group({
      title: '',
      body: '',
      endDate: '',
      startDate: ''
    })
  } 

  ngOnInit() {
  }

  // Update the body from the WYSIWYG changed event.
  bodyChanged($event) {
    this.form.patchValue({
      body: $event
    })
  }

  submitAssignment() {
    let assignment = new Assignment();
    assignment.title = this.form.value.title;
    assignment.body = this.form.value.body;
    assignment.endDate = this.form.value.endDate;
    assignment.startDate = this.form.value.startDate;
    assignment.project = this.project.id;

    this.assignmentService.createAssignment(assignment)
      .subscribe(data => {
        if (data.id) {
          this.assignmentCreated.emit();
        }
        console.log(data);
      })
  }
}
