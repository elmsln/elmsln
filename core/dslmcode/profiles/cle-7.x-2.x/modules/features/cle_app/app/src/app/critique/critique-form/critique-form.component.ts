import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { FormGroup, FormBuilder } from '@angular/forms';
import { Critique } from '../../critique';
import { CritiqueService } from '../../critique.service';
import { Submission } from '../../submission';
import { Subject, Observable } from 'rxjs/Rx';

@Component({
  selector: 'cle-critique-form',
  templateUrl: './critique-form.component.html',
  styleUrls: ['./critique-form.component.css'],
  providers: [CritiqueService]
})
export class CritiqueFormComponent implements OnInit {
  content: string;
  private showPreview: boolean = false;
  private initialContent: string = '';
  update$: Subject<any> = new Subject();
  
  @Input()
  submission;

  @Output()
  critiqueCreated: EventEmitter<any> = new EventEmitter();

  constructor(
    private critiqueService: CritiqueService
  ) { }

  ngOnInit() {
  }

  submitForm() {
    if (this.content) {
      let newCritique: Critique =  new Critique(this.content);
      newCritique.submissionId = this.submission.nid;
      this.critiqueService.createCritique(newCritique)
        .subscribe(res => {
          if (res.ok) {
            this.content = '';
            this.critiqueCreated.emit(res.json());
          }
        });
    }
    // update existing critique
    else {
    }
  }

  onFocus() {
  }

  // When the content changes in the wysiwyg update the content variable
  onChange($event) {
    this.content = $event;
    console.log(this.content);
  }
  onBlur() {
  }
}