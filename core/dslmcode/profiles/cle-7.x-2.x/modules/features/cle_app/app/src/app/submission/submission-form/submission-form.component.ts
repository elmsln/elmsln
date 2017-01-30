import { Component, OnInit, Input, OnChanges, Output, EventEmitter } from '@angular/core';
import { ReactiveFormsModule, FormBuilder, FormGroup, Validators, FormControl } from '@angular/forms';
import { Submission } from '../submission';
import { createSubmissionImage, createSubmissionImageSuccess, createSubmissionImageFailure } from '../submission.actions';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs/Observable';

declare const Materialize:any;
declare const jQuery:any;

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
  savingImage$:Observable<boolean>
  savingImageToast:any;

  constructor(
    private formBuilder: FormBuilder,
    private store: Store<{}>
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

    this.savingImage$ = this.store.select('submissions')
      .map((s:any) => s.savingImage);

    /**
     * Saving Image notifications
     */
    let savingImageMessage = `
      Saving image 
      <div class="preloader-wrapper small active">
        <div class="spinner-layer spinner-green-only">
          <div class="circle-clipper left">
            <div class="circle"></div>
          </div><div class="gap-patch">
            <div class="circle"></div>
          </div><div class="circle-clipper right">
            <div class="circle"></div>
          </div>
        </div>
      </div>
    `;
    // when savingImage changes in the reducer
    // change the notifications
    this.savingImage$
      .skip(1)
      .debounceTime(200)
      .distinctUntilChanged((x,y) => x === y)
      .subscribe((s:any) => {
        if (s === true) {
          Materialize.toast(savingImageMessage, null, 'submission-form-image-saving');
        }
        if (s === false) {
          jQuery('.submission-form-image-saving').remove();
          Materialize.toast('Image uploaded', 1500);
        }
      })

    // this.store.dispatch(createSubmissionImage());
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

  onImageSave($event) {
    switch ($event.type) {
      case 'saving':
        this.store.dispatch(createSubmissionImage());
        break;

      case 'success':
        this.store.dispatch(createSubmissionImageSuccess());
        break;

      case 'error':
        this.store.dispatch(createSubmissionImageFailure());
        break;
    
      default:
        break;
    }
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
