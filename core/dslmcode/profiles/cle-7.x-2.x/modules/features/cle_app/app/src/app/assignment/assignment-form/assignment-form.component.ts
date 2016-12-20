import { Component, OnInit, Input, Output, EventEmitter, OnChanges } from '@angular/core';
import { ReactiveFormsModule, FormBuilder, FormGroup } from '@angular/forms';
import { Router } from '@angular/router';
import { Assignment } from '../../assignment';
import { AssignmentService } from '../../assignment.service';
import { Project } from '../../project';
import { Observable } from 'rxjs';
declare const jQuery:any;
declare const Materialize:any;

@Component({
  selector: 'app-assignment-form',
  templateUrl: './assignment-form.component.html',
  styleUrls: ['./assignment-form.component.css'],
  providers: [Assignment, AssignmentService]
})
export class AssignmentFormComponent implements OnInit, OnChanges {
  @Input() assignment:Assignment;
  // assignment creation event
  @Output() assignmentSave: EventEmitter<any> = new EventEmitter();
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

  ngOnChanges() {
    this.form = this.formBuilder.group(this.assignment);
  }

  save() {
    let model = this.form.value;
    if (model.id) {
      this.assignmentService.updateAssignment(model)
        .subscribe(data => {
            Materialize.toast('Assignment Updated', 1000);
            this.assignmentSave.emit();
            this.form.reset();
        })
    }
    else {
      this.assignmentService.createAssignment(model);
      this.assignmentSave.emit();
      this.form.reset();
    }
  }
}
