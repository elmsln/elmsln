import { Component, OnInit, Input, OnChanges, Output, EventEmitter } from '@angular/core';
import { ReactiveFormsModule, FormBuilder, FormGroup } from '@angular/forms';
import { Submission } from '../submission';

@Component({
  selector: 'app-submission-form',
  templateUrl: './submission-form.component.html',
  styleUrls: ['./submission-form.component.css']
})
export class SubmissionFormComponent implements OnInit, OnChanges {
  @Input() submission:Submission;
  @Output() onSubmissionSave: EventEmitter<any> = new EventEmitter(); 
  @Output() onSubmissionCancel: EventEmitter<any> = new EventEmitter(); 
  form:FormGroup;

  constructor(
    private formBuilder: FormBuilder
  ) { }

  ngOnInit() {
    this.form = this.formBuilder.group(this.submission);
  }

  ngOnChanges() {
    this.form = this.formBuilder.group(this.submission);
  }

  submit() {
    const model = this.form.value;
    this.onSubmissionSave.emit(model);
  }

  cancel() {
    this.onSubmissionCancel.emit();
  }
}
