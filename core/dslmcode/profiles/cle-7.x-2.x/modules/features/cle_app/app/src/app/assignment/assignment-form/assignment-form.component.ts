import { Component, OnInit, Input, Output, EventEmitter, OnChanges } from '@angular/core';
import { ReactiveFormsModule, FormBuilder, FormGroup, Validators, FormControl, AbstractControl } from '@angular/forms';
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
  assignmentOptions:any;
  saveAttempted:boolean;

  constructor(
    private formBuilder: FormBuilder,
    private assignmentService: AssignmentService,
    private router: Router
  ) { } 

  ngOnInit() {
    // get a list of assignment 'types' that we have available so we can display
    // those in the select field
    this.assignmentOptions = this.assignmentService.getAssignmentOptions();
  }

  ngOnChanges() {
    let form:any = this.assignment;
    // Add validation to the title
    // create the form from the assignment object that we recieved
    this.form = this.formBuilder.group(form);
    this.form.setControl('title', new FormControl(this.assignment.title, Validators.required))

    /**
     * @todo: first attempt at autoSaveForm
     */
    // this.form.valueChanges
    //   .debounceTime(1000)
    //   .subscribe(() => this.autoSaveForm());
  }

  // private autoSaveForm() {
  //   const saved:Assignment[] = localStorage.getItem('assignments_autosave') ? JSON.parse(localStorage.getItem('assignments_autosave')) : [];
  //   const currentForm:Assignment = this.form.value;
  //   let newSaved:Assignment[];

  //   if (currentForm.id) {
  //     saved.map(assignment => {
  //       if (assignment.id === currentForm.id) {
  //         return currentForm;
  //       }
  //       return assignment;
  //     });
  //   }
  //   else {
  //     newSaved['new_assignment'] = currentForm;
  //   }

  //   localStorage.setItem('assignments_autosave', JSON.stringify(newSaved));
  // }

  save() {
    // first check to make sure the form is valid
    if (this.form.status === 'VALID') {
      // emit the assignmentSave and send up the new form
      this.assignmentSave.emit(this.form.value);
      // reset the form 
      this.form.reset();
    }
    // if the form isn't valid then we will give
    // the user some indication of what they need
    // to fill out.
    else {
      this.saveAttempted = true;
      if (this.form.get('title').status) {
        alert('The title field is required.');
      }
    }
  }
}
