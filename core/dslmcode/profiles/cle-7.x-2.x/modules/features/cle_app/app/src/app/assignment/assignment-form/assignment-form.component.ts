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
  @Input() assignment: Assignment;
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
  } 

  ngOnInit() {
    // create the form from the assignment object that we recieved
    this.form = this.formBuilder.group(this.assignment);
    // get a list of assignment 'types' that we have available so we can display
    // those in the select field
    this.assignmentTypes = this.assignmentService.getAssignmentTypes()
  }

  // Update the body from the WYSIWYG changed event.
  bodyChanged($event) {
    this.form.patchValue({
      description: $event
    })
  }

  save(model:Assignment) {
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
