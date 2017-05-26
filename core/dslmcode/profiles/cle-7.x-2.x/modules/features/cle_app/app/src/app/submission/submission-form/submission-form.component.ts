import { Component, OnInit, Input, OnChanges, Output, EventEmitter, OnDestroy} from '@angular/core';
import { ReactiveFormsModule, FormBuilder, FormGroup, Validators, FormControl } from '@angular/forms';
import { Store } from '@ngrx/store';
import { createImage, createImageSuccess, createImageFailure } from '../../image/image.actions';
import { ImageState } from '../../image/image.reducer';
import { Submission } from '../submission';
import { Observable } from 'rxjs/Observable';
import { SubmissionService } from '../submission.service';
import * as fromRoot from '../../app.reducer';
import { ImageStates } from '../../image/image.reducer';
declare const Materialize:any;
declare const jQuery:any;

@Component({
  selector: 'app-submission-form',
  templateUrl: './submission-form.component.html',
  styleUrls: ['./submission-form.component.css']
})
export class SubmissionFormComponent implements OnInit, OnChanges {
  @Input() submission:Submission;
  @Input() submissionType:string = 'submission';
  @Output() onSubmissionSave: EventEmitter<any> = new EventEmitter(); 
  @Output() onSubmissionCancel: EventEmitter<any> = new EventEmitter(); 
  @Output() onFormChanges: EventEmitter<any> = new EventEmitter();
  form:FormGroup;
  formValueChanges:number = 0;
  saveAttempted:boolean = false;
  savingImageToast:any;

  constructor(
    private formBuilder: FormBuilder,
    private store: Store<{}>,
    private submissionService: SubmissionService
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
    this.store.select(fromRoot.getImageState)
      .skip(1)
      .debounceTime(200)
      .distinctUntilChanged((x,y) => x === y)
      .subscribe((s) => {
        jQuery('.submission-form-image-saving').remove();
        if (s.state === ImageStates.saving) {
          Materialize.toast(savingImageMessage, null, 'submission-form-image-saving');
        }
        if (s.state === ImageStates.default) {
          Materialize.toast('Image uploaded', 1500);
        }
        if (s.state === ImageStates.error) {
          Materialize.toast(s.message, 1500);
        }
      })
  }

  ngOnChanges() {
  }

  onWysiwygInit() {
    this.form.markAsPristine();
  }

  onWysiwygImageAdded($event) {
  }

  onImageSave($event) {
    switch ($event.type) {
      case 'saving':
        this.store.dispatch(createImage());
        break;

      case 'success':
        this.store.dispatch(createImageSuccess());
        this.addImageAsEvidence($event.image);
        break;

      case 'error':
        this.store.dispatch(createImageFailure());
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
  }

  // find out if the submission form should be savable
  get savable():Observable<boolean> {
    return this.store.select(fromRoot.getSubmissionSavable);
  }

  private addImageAsEvidence(image) {
    // get the existing images
    var images:any[] = typeof this.form.value.evidence.images  === 'array' ? this.form.value.evidence.images : [];
    // add this new image fid onto the array
    images.push(image.fid);
    // update the images array in the submission form.
    this.form.patchValue({
      evidence: {
        images: images
      }
    });
  }
}
