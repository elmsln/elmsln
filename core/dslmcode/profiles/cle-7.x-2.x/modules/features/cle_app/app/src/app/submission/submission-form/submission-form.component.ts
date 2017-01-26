import { Component, OnInit, Input, OnChanges, Output, EventEmitter } from '@angular/core';
import { ReactiveFormsModule, FormBuilder, FormGroup, Validators, FormControl } from '@angular/forms';
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
  @Output() onFormChanges: EventEmitter<any> = new EventEmitter();
  form:FormGroup;
  formValueChanges:number = 0;
  saveAttempted:boolean = false;

  constructor(
    private formBuilder: FormBuilder
  ) { }

  ngOnInit() {
    let form:any = this.submission;
    this.form = this.formBuilder.group(form);
    this.form.setControl('title', new FormControl(this.submission.title, Validators.required))
    this.form.valueChanges
      .subscribe(() => {
        /**
         * @todo: hack to make form dirty work. WYSIWYG is
         * fireing a change event on init
         */
        if (this.formValueChanges > 1) {
          this.onFormChanges.emit(this.form.dirty);
        }
        this.formValueChanges++;
      });
  }

  ngOnChanges() {
  }

  onWysiwygInit() {
    this.form.markAsPristine();
  }

  onWysiwygImageAdded($event) {
    // get the existing images
    var images:any[] = typeof this.form.value.evidence.images  === 'array' ? this.form.value.evidence.images : [];
    // add this new image fid onto the array
    images.push($event.fid);
    // update the images array in the submission form.
    this.form.patchValue({
      evidence: {
        images: images
      }
    });
  }

  submit() {
    if (this.form.status === 'VALID') {
      this.onSubmissionSave.emit(this.form.value);
    }
    else {
      this.saveAttempted = true;
      if (this.form.get('title').status) {
        alert('The title field is required.');
      }
    }
  }

  cancel() {
    this.onSubmissionCancel.emit();
    this.form.reset();
  }
}
